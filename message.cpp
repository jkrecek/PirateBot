#include "message.h"

#include "ircconstants.h"

Message::Message() :
    sender_m(Sender(QString(), QString(), QString())),
    senderChannel_m(QString()),
    command_m(QString()),
    content_m(QString()),
    code_m(0),
    isServerMessage_m(false),
    isChannelMessage_m(false)
{
}

bool Message::isPing() const
{
    return (command_m == IRC::Command::Ping);
}

bool Message::isPrivate() const
{
    return (senderChannel_m == sender_m.GetNickName()); // also possible: !(senderChannel_m.startsWith("#"))
}

