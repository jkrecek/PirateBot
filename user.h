#ifndef USER_H
#define USER_H

#include <QString>
#include "message.h"
#include <QStringList>
#include <QList>
#include <QMap>

class IRCServer;
struct Sender;

class UsersChannel
{
    public:
        UsersChannel(QString channelName) : name_m(channelName) {}
        QString GetName() const { return name_m; }

    private:
        QString name_m;
};

class User
{
    public:
        User(Sender sender, IRCServer* server_m, QMap<QString, QString> settings);

        //QString nickname() const { return nickname_m; }
        Sender info() const { return userInfo_m; }
        QString currentChannel() const { return currentChannel_m; }
        IRCServer* server() const { return server_m; }
        bool IsBanned() const { return isBanned_m; }
        bool IsIdentified() const { return isIdentified_m; }

        void HandleMessage(const Message& message);
        int Kicked() { return ++kicked_times; }
        void ResetKickCounter() { kicked_times = 0; }
        void setCurrentChannel(QString channel) { currentChannel_m = channel; }
        void Identify() {isIdentified_m = true; }
        void Ban(QString now, QString unban);
        void Unban();
        QList<UsersChannel> GetKnownChannels() const { return channels_m; }
        void AddChannel(UsersChannel channel) { channels_m.push_back(channel); }

    private:
        Sender userInfo_m;
        QString currentChannel_m;
        IRCServer* server_m;

        int kicked_times;
        bool isBanned_m;
        bool isIdentified_m;

        QList<UsersChannel> channels_m;
        QList<Message> last_messages;
        QMap<QString, QString> settings_m;
};

#endif // USER_H
