#ifndef TCPMESSAGE_H
#define TCPMESSAGE_H

#include "ipmessage.h"
#include <string>


class TcpMessage
{
public:
    TcpMessage();

    void tcpSetSrc(int val);
    void tcpSetDst(int val);
    void tcpSetText(std::string txt);

    std::string* tcpEquipList();

    void showTcp();

private:
    int tcpSrcPort;
    int tcpDstPort;
    std::string tcpText;
    std::string equipList[10]={"Device1","Device2"};
    std::string chosenEquip;
};

#endif // TCPMESSAGE_H
