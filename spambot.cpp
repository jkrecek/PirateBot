#include "spambot.h"

#include <QStringList>
#include <iostream>
#include <QDebug>
#include <QFile>
#include "ircserver.h"
#include "user.h"
#include "channel.h"
#include "ircconstants.h"
#include "spambot.h"
#include <ctime>
#include <math.h>

Bot::Bot(QObject* parent) : QObject(parent)
{
    // read settings from txt file
    readSettings();

    // connecting to servers
    server_m = new IRCServer(GetStringSettings("server", "irc.rizon.net"), GetIntSettings("port", 6667));
    server_m->connectAs(GetStringSettings("nick", "Pirate"), GetStringSettings("user", "BOT"), "BOT", "Kurva_tahnite_mi_z_nicku");

    // getting channels list
    QString defaultChannel = "#valhalla";
    QStringList all_channels;
    if (fromTxtSettings.contains("channels"))
    {
        QStringList channelsToBeJoined = fromTxtSettings["channels"].split(",");
        foreach(QString channel, channelsToBeJoined)
        {
            if (channel.trimmed().startsWith("#"))
                all_channels.push_back(channel);
            else
                all_channels.push_back("#"+channel);
        }
    }else all_channels.push_back(defaultChannel);

    // joining to channels
    foreach(QString ch, all_channels)
    {
        server_m->joinChannel(ch);
        server_m->sendMessageToChannel(ch, "Hi, I'm an antiflood bot Pirate and I'm now under development, so I'm sorry for any inconvinience during this time");
    }

    // identify at nickserv
    server_m->identify(GetStringSettings("pass", ""));

    message_repeted = 0;
    nick_repeted = 0;

    qsrand(sqrt(time(0))*2);

    ResetSettings();

    HandleNextMinute();
    HandleNextHour();

    connect(server_m, SIGNAL(messageReceived(Message)), this, SLOT(handleReceivedMessage(Message)));
}

void Bot::readSettings()
{
    QFile file("settings.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    while (!file.atEnd())
    {
        QString line = file.readLine();
        // allow putting comments into file
        if (line.isNull() || line.startsWith("//"))
            continue;

        QStringList part = line.split("=", QString::SkipEmptyParts);
        fromTxtSettings[part[0].trimmed()] = part[1].trimmed();
    }
}

void Bot::ResetSettings()
{
    is_running = true;
    banning = GetBoolSettings("banning", true);
    kicks_to_ban = GetIntSettings("banning", 3);
    message_repete = GetBoolSettings("same_messages", true);
    message_repetition = GetIntSettings("same_messages", 4);
    user_repete = GetBoolSettings("same_user", true);
    user_repetition = GetIntSettings("same_user", 13);
    kick_command = GetBoolSettings("kick_comm_alow", true);
    prefix_for_kick = GetStringSettings("kick_comm", "!"+QString::number(qrand()));

    // print settings
    std::cout << "Settings are: Banning: " << banning
            << ", Kicks till ban: " << kicks_to_ban
            << ", Message repete: " << message_repete
            << ", Message repetition: " << message_repetition
            << ", User repete: " << user_repete
            << ", User repetition: " << user_repetition
            << ", Kick command: " << kick_command
            << ", Prefix for kick: " << prefix_for_kick.toStdString()
            << "\n";
}

void Bot::Kick(User* user, QString reason)
{
    if (user->IsIdentified())
        return;

    server_m->kick(user->info().GetNickName(), user->currentChannel(), reason);

    if (!banning)
        return;

    int times = user->Kicked();
    if (times >= kicks_to_ban)
        user->Ban(GetTimeFromUnix(time(0)), GetTimeFromUnix(FindNextHour()));
}

void Bot::handleReceivedMessage(const Message& message)
{
    std::cout << "Nick: "<< message.sender().GetNickName().toStdString() << " " <<
            "Channel: " << message.senderChannel().toStdString() << " " <<
            "Command: " << message.command().toStdString() << " " <<
            "Content: " << message.content().toStdString() << "\n";

    // if cannot join because is banned
    if (message.command() == IRC::Reply::BANNED)
    {
        HandleBanned(server_m->GetLastJoinedChannel());
        return;
    }
    // someone is already on nick -> ghost kick him
    else if (message.command() == IRC::Reply::NICKTAKEN)
    {
        server_m->ghostCommand(GetStringSettings("pass", ""));
        server_m->joinChannel("#valhalla");
        server_m->identify(GetStringSettings("pass", ""));
    }

    // do not run where is off or is sended by bot itself
    if (message.sender().GetNickName() == server_m->GetOwnNick() ||
        !is_running)
        return;

    QStringList commands = message.content().split(" ");
    // rejoin on kick (TODO:: do not rejoin on every kick)
    if (message.command() == IRC::Command::Kick)
        server_m->joinChannel(message.senderChannel());

    // someone changed his nick
    if (message.command() == IRC::NickIdentifyPrefix)
        foreach(User* user, Users)
            if (user->info().GetNickName() == message.sender().GetNickName())
                user->info().ChangeNickName(message.content());

    // handle channel mode setting
    if (message.command() == IRC::Command::Mode && commands.size() == 5)
        HandleMode(commands[2], commands[3], commands[4], message.sender().GetNickName());

    if (!message.isServerMessage() && message.command() == IRC::Command::PrivMsg)
    {
        // kicking throung pm
        if (message.isPrivate())
        {
            if (isKickPrefix(commands[0]) && commands.size() == 3 && kick_command)
            {
                QString ch = commands[1].startsWith("#") ? commands[1] : "#"+commands[1];
                server_m->kick(commands[2], ch, "Someone asked me in PM");
            }
            return;
        }

        // get sender of message
        User* sender = GetSender(message.sender(), message.senderChannel());

        // handle settings
        if (isSettingsPrefix(commands[0]))
            HandleSettings(message);

        // handle sending key
        if (message.content().toLower().startsWith("!sendmekey") && time(0)/60 > last_minute)
        {
            HandleNextMinute();
            if (sender->IsIdentified())
                server_m->sendMessageToUser(sender->info().GetNickName(), "Current key is: "+QString::number(key_m));
        }

        // command to print all known users
        if (message.content().toLower().startsWith("!printmeusers"))
        {
            QString users;
            foreach(User* user, Users)
                users += user->info().GetNickName() + " ";

            server_m->sendMessageToChannel(sender->currentChannel(), users);
        }

        // handle op command
        if (commands[0].toLower() == ("!op"))
        {
            if (commands[1].toLower() == ("self") || commands[1].toLower() == server_m->GetOwnNick())
                server_m->opSelf(sender->currentChannel());
            else if (sender->IsIdentified())
            {
                if (commands[1].toLower() == ("me"))
                    server_m->opUser(sender->info().GetNickName(), sender->currentChannel(), true);
                else
                    server_m->opUser(commands[1], sender->currentChannel(), true);
            }
        }

        // handle op command
        if (commands[0].toLower() == ("!deop") && sender->IsIdentified())
        {
            if (commands[1].toLower() == ("me"))
                server_m->opUser(sender->info().GetNickName(), sender->currentChannel(), false);
            else
                server_m->opUser(commands[1], sender->currentChannel(), false);
        }

        // handle identifyme request
        if (isIdentifyPrefix(commands[0]))
            HandleIdentifyRequest(sender, commands);

         // Channel Messages
         else
         {
             if (time(0)/60/60 > last_hour)
                 HandleNextHour();

             // send message data to user
             sender->HandleMessage(message);

             // handle channel flood messages
             HandleFlood(sender, message);
         }
     }
}

void Bot::HandleFlood(User* user, const Message &message)
{
    // Kick due to exact repeat
    // repeat counting
    if (message.content() == last_message.content() &&
        message.sender().GetNickName() == last_message.sender().GetNickName() &&
        message_repete)
        ++message_repeted;
    else
    {
        last_message = message;
        message_repeted = 0;
    }

    // repeat count handling
    if (message_repeted >= (message_repetition-1))
    {
        Kick(user, "There is no point in writing the same sentance such many times!");
        message_repeted = 0;
    }

    // Kick due to one man speaking
    // counting
    if (last_nick == message.sender().GetNickName() && user_repete)
    {
        if (message.content().size() < 15)
            nick_repeted += 0.5f;
        else
            ++nick_repeted;
    }
    else
    {
        last_nick = message.sender().GetNickName();
        nick_repeted = 0;
    }

    // repeted count handling
    if (nick_repeted > (user_repetition-1))
    {
        Kick(user, "If you want to talk to yourself, please use mirror!");
        last_nick = "";
    }

}

void Bot::HandleNextMinute()
{
    last_minute = time(0)/60;

    GenerateNewKey();
}

void Bot::HandleNextHour()
{
    // unban banned
    last_hour = time(0)/60/60;
    last_hour_time = time(0);

    foreach(User* user, Users)
    {
        if (user->IsBanned())
            user->Unban();

        user->ResetKickCounter();
    }
}

User* Bot::GetSender(Sender sender, QString channel)
{
    if (sender.GetNickName().isEmpty() || channel.isEmpty() || channel != sender.GetNickName())
        return 0;

    User* messageSender = NULL;

    // try to find user in existing users
    foreach(User* user, Users)
    {
        if (user->info().GetNickName() == sender.GetNickName())
        {
            messageSender = user;
            break;
        }
    }

    // if not found create new one
    if (!messageSender)
    {
        messageSender = new User(sender, server_m, fromTxtSettings);
        Users.push_back(messageSender);
    }

    // set current channel
    if (messageSender->info().GetNickName() != channel)
        messageSender->setCurrentChannel(channel);

    // look for channel in known channels for user
    bool found = false;
    foreach(UsersChannel ch, messageSender->GetKnownChannels())
    {
        if (ch.GetName() == channel)
        {
            found = true;
            break;
        }
    }
    // if channel unknown create new one
    if (!found)
        messageSender->AddChannel(channel);

    return messageSender;
}

void Bot::HandleSettings(const Message& message)
{
    QStringList commands = message.content().split(" ");

    if (commands.size() != 4 || commands[1].isEmpty() || commands[2].isEmpty() || commands[3].isEmpty())
    {
        server_m->sendMessageToChannel(message.senderChannel(), "Sorry, correct format is '!nastav key setting value'");
        return;
    }

    const int input_key = commands[1].toInt();
    if (input_key != key_m)
    {
        server_m->sendMessageToChannel(message.senderChannel(), "Sorry dude, wrong code!");
        return;
    }

    GenerateNewKey();

    const int setting = commands[2].toInt();
    QString svalue = commands[3];
    const int ivalue = svalue.toInt();
    bool bvalue = bool(ivalue);
    QString corrected_value = QString::number(ivalue);

    QString am = bvalue ?  "m"  : "m not";
    QString have = bvalue ?  "have"  : "haven't";
    QString output_message;
    switch(setting)
    {
        case SETTING_BOT_RUNNING:
        {
            is_running = bvalue;
            output_message = "I' "+am+" running";
            break;
        }
        case SETTING_BOT_BAN:
        {
            banning = bvalue;
            output_message = "I "+have+" enabled banning";
            break;
        }
        case SETTING_KICKS_TO_BAN:
        {
            kicks_to_ban = ivalue;
            output_message = "I will now ban after "+corrected_value+" kicks";
            break;
        }
        case SETTING_MESSAGE_REPETE:
        {
            message_repete = bvalue;
            output_message = "I "+have+" enabled kicking after same message from same user";
            break;
        }
        case SETTING_MESSAGE_REPETITION:
        {
            message_repetition = ivalue;
            output_message = "I will now kick after"+corrected_value+" same messages from same user";
            break;
        }
        case SETTING_USER_REPETE:
        {
            user_repete = bvalue;
            output_message = "I "+have+" enabled kicking after recieving messages from same user";
            break;
        }
        case SETTING_USER_REPETITION:
        {
            user_repetition = ivalue;
            output_message = "I will now kick after"+corrected_value+" messages from same user";
            break;
        }
        case SETTING_KICK_ON_COMMAND:
        {
            kick_command = bvalue;
            output_message = "I "+have+" enabled kicking through pm";
            break;
        }
        case SETTING_KICK_COMMAND:
        {
            prefix_for_kick = svalue;
            output_message = "My prefix to kick is now "+svalue;
            break;
        }
        default:
            output_message = "unknown setting command!";
    }

    server_m->sendMessageToChannel(message.senderChannel(), output_message);
}

void Bot::HandleIdentifyRequest(User* user, QStringList& commands)
{
    if (user->IsIdentified())
    {
        server_m->sendMessageToChannel(user->currentChannel(), "You have already been idetified!");
        GenerateNewKey();
        return;
    }
    if (commands.size() != 2 || commands[1].isEmpty())
    {
        server_m->sendMessageToChannel(user->currentChannel(), "Sorry, correct format is '!identifyme key'");
        return;
    }

    const int input_key = commands[1].toInt();
    if (input_key != key_m)
    {
        server_m->sendMessageToChannel(user->currentChannel(), "Sorry dude, wrong code!");
        return;
    }

    GenerateNewKey();
    user->Identify();
    if (user->IsIdentified())
        server_m->sendMessageToChannel(user->currentChannel(), "You are now identified");
}

bool Bot::isKickPrefix(const QString& prefix)
{
    QString lowerPrefix = prefix.toLower();
    return (lowerPrefix.startsWith(prefix_for_kick));
}

bool Bot::isSettingsPrefix(const QString &prefix)
{
    QString lowerPrefix = prefix.toLower();
    return (lowerPrefix.startsWith("!nastav"));
}

bool Bot::isIdentifyPrefix(const QString& prefix)
{
    QString lowerPrefix = prefix.toLower();
    return (lowerPrefix.startsWith("!identifyme"));
}

void Bot::GenerateNewKey()
{
    key_m = qrand();
    std::cout << "!!! New key is: " << key_m << " !!! \n";
}

void Bot::HandleBanned(QString channel)
{
    server_m->sendMessageToUser("chanserv", "UNBAN #valhalla ME");
    server_m->joinChannel(channel);
}

QString Bot::GetTimeFromUnix(int original_unix )
{
    if (!original_unix)
        original_unix = time(0);

    int hours = (original_unix/3600)%24;
    int minutes = (original_unix/60)%60;
    int seconds = (original_unix)%60;

    // correction due to GMT
    ++hours;

    QString hour = QString::number(hours);
    QString minute = (minutes < 10 ? "0" : "")+QString::number(minutes);
    QString second = (seconds < 10 ? "0" : "")+QString::number(seconds);
    return hour+":"+minute+":"+second;
}

int Bot::FindNextHour()
{
    int time = 0;
    while(time < last_hour_time)
        time += 3600;

    return time;
}

void Bot::HandleMode(QString channel, QString mode, QString arg, QString sender)
{
    bool apply = mode.startsWith("+");
    QString type = mode.at(1);

    if (type.toLower() == "o")
    {
        if (!apply)
        {
            if (arg.toLower() == server_m->nickName().toLower())
            {
                server_m->opSelf(channel);
                server_m->sendActionToChannel(channel, "slaps "+sender+" around a bit with a large trout");
            }
        }
    }
}
