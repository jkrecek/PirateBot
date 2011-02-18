#ifndef SPAMBOT_H
#define SPAMBOT_H

#include <QObject>
#include "message.h"
#include "user.h"
#include <QStringList>
#include <QMap>

class IRCServer;

enum Settings
{
    SETTING_BOT_RUNNING         = 0,
    SETTING_BOT_BAN             = 1,
    SETTING_KICKS_TO_BAN        = 2,
    SETTING_MESSAGE_REPETE      = 3,
    SETTING_MESSAGE_REPETITION  = 4,
    SETTING_USER_REPETE         = 5,
    SETTING_USER_REPETITION     = 6,
    SETTING_KICK_ON_COMMAND     = 7,
    SETTING_KICK_COMMAND        = 8
};

class Bot : public QObject
{
    Q_OBJECT

    public:
        Bot(QObject* parent = 0);

        void Kick(User* user, QString reason);
        void GenerateNewKey();

        QList<User*> Users;

    private slots:
        void handleReceivedMessage(const Message& message);
        void HandleNextMinute();
        void HandleNextHour();
        void HandleIdentifyRequest(User* user, QStringList& commands);
        void HandleSettings(const Message& message);
        void HandleMode(QString channel, QString mode, QString arg, QString sender);
        void ResetSettings();
        void HandleBanned(QString channel);
        void HandleFlood(User* user, const Message& message);
        int FindNextHour();

        User* GetSender(Sender sender, QString channel);

        bool ExistsSettings(const QString& setting) { return fromTxtSettings.contains(setting); }
        QString GetStringSettings(const QString& setting, QString defvalue) { return ExistsSettings(setting) ? fromTxtSettings[setting] : defvalue; }
        int GetIntSettings(const QString& setting, int defvalue) { return ExistsSettings(setting) ? fromTxtSettings[setting].toInt() : defvalue; }
        bool GetBoolSettings(const QString& setting, bool defvalue) { return ExistsSettings(setting) ? fromTxtSettings[setting].toInt() : defvalue; }


    private:
        bool isKickPrefix(const QString& prefix);
        bool isIdentifyPrefix(const QString& prefix);
        bool isSettingsPrefix(const QString& prefix);

        void readSettings();

        IRCServer* server_m;

        Message last_message;
        int message_repeted;

        QString last_nick;
        QString GetTimeFromUnix(int original_unix = 0);
        float nick_repeted;

        //QString own_nick;

        int last_minute;
        int last_hour;
        int last_hour_time;

        int key_m;

        QMap<QString, QString> fromTxtSettings;

        // variables
        bool is_running;
        bool banning;
        int kicks_to_ban;
        bool message_repete;
        int message_repetition;
        bool user_repete;
        int user_repetition;
        bool kick_command;
        QString prefix_for_kick;
};
#endif
