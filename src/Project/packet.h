#pragma once

#include <QObject>

enum MessageType {
    Trigger_QUESTION = 0x01,
    Trigger_EVENT = 0x02,
};

struct PacketHeader {
    quint8 fixedByte{0};
    quint8 messageType{0};
    quint16 messageId{0};
    quint32 payloadLength{0};
};
