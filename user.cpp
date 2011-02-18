#include "user.h"
#include "ircserver.h"
#include "message.h"
#include "spambot.h"
//class Bot;

User::User(Sender sender, IRCServer* server, QMap<QString, QString> settings) :
    userInfo_m(sender),
    server_m(server),
    settings_m(settings)
{
    kicked_times = 0;
    isBanned_m = false;
    if (userInfo_m.GetNickName() == server->GetOwnNick() ||
        userInfo_m.GetNickName() == "geordi")
        isIdentified_m = true;
    else
        isIdentified_m = false;
}

void User::Ban(QString now, QString unban)
{
    isBanned_m = true;
    server_m->sendMessageToChannel(currentChannel_m, userInfo_m.GetNickName()+" is being banned until "+unban+" (now is: "+now+")");
    server_m->handleBan(userInfo_m, currentChannel_m, BAN_HOST, true);
    kicked_times = 0;
}

void User::Unban()
{
    isBanned_m = false;
    server_m->sendMessageToChannel(currentChannel_m, userInfo_m.GetNickName()+" is being unbanned!");
    server_m->handleBan(userInfo_m, currentChannel_m, BAN_HOST, false);

}

void User::HandleMessage(const Message& message)
{
    // push back message into list
    last_messages.push_back(message);

    int s = 0;
    int tr = 0;
    for(QList<Message>::iterator itr = last_messages.begin(); itr != last_messages.end();)
    {
        const Message& m = (*itr);
        if (m.content().toLower() == message.content().toLower())
            ++s;
        else
            s = 0;

        int age = message.sendTime() - m.sendTime();
        if ( age > 0 /*from config settings*/ )
            ++tr;

        if ( age > 0 /*from config delete interval*/ )
        {
            last_messages.erase(itr);
            itr = last_messages.begin();
        }
        else
            ++itr;
    }
}
