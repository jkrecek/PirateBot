#ifndef MESSAGE_H
#define MESSAGE_H

#include <QString>
#include "ircconstants.h"
#include <ctime>
//#include "user.h"


struct Sender
{
    public:
        Sender(const QString nick, const QString user, const QString host) : nickname_m(nick),  username_m(user),
            host_m(host) {}

        QString GetNickName() const { return nickname_m; }
        QString GetUser() const { return username_m; }
        QString GetHost() const { return host_m; }

        QString GetFullID() { return nickname_m + IRC::UserPrefix + username_m + IRC::HostPrefix + host_m; }

        void ChangeNickName(QString nick) { nickname_m = nick; }

    private:
        QString nickname_m;
        QString username_m;
        QString host_m;
};

struct Message
{
    public:
        friend class MessageParser;

        Message();
        ~Message() {};

        //QString senderNick() const { return senderNick_m; }
        //QString senderUser() const { return senderUser_m; }
        //QString senderHost() const { return senderHost_m; }
        Sender sender() const { return sender_m; }
        QString senderChannel() const { return senderChannel_m; }
        QString command() const { return command_m; }
        QString content() const { return content_m; }
        int sendTime() const { return send_time_m; }
        quint8 code() const { return code_m; }
        bool isServerMessage() const { return isServerMessage_m; }
        bool isChannelMessage() const { return isChannelMessage_m; }
        bool isPing() const;
        bool isPrivate() const;

    private:
        //void setSenderNick(QString senderNick) { senderNick_m = senderNick; }
        //void setSenderUser(QString senderUser) { senderUser_m = senderUser; }
        //void setSenderHost(QString senderHost) { senderHost_m = senderHost; }
        void setSender(Sender sender) { sender_m = sender; }
        void setSenderChannel(QString senderChannel) { senderChannel_m = senderChannel; }

        void setCommand(QString command) { command_m = command; }
        void setContent(QString content) { content_m = content; }
        void setCode(uint code) { code_m = code; }
        void setIsServerMessage(bool isServerMessage) { isServerMessage_m = isServerMessage; }
        void setIsChannelMessage(bool isChannelMessage) { isChannelMessage_m = isChannelMessage; }
        void setSendTime(int time = time(0)) { send_time_m = time; }

        //QString senderNick_m;
        //QString senderUser_m;
        //QString senderHost_m;
        Sender sender_m;
        QString senderChannel_m;
        QString command_m;
        QString content_m;
        quint8 code_m;
        bool isServerMessage_m;
        bool isChannelMessage_m;
        int send_time_m;
};


#endif // MESSAGE_H
