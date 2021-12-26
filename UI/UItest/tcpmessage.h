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

    void showTcp();

private:
    int tcpSrcPort;
    int tcpDstPort;
    std::string tcpText;
};

#endif // TCPMESSAGE_H
