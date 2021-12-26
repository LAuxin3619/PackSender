#ifndef TCPMESSAGE_H
#define TCPMESSAGE_H

#include "ipmessage.h"


class TcpMessage
{
public:
    TcpMessage();

    void tcpSetSrc(int val);
    void tcpSetDst(int val);
    void tcpSetSeq(int val);
    void tcpSetOfst(int val);
    void tcpSetWin(int val);
    void tcpSetChk(int val);

    void showTcp();

private:
    int tcpSrcPort;
    int tcpDstPort;
    int tcpSeq;
    int tcpOfst;
    int tcpWin;
    int tcpChk;

};

#endif // TCPMESSAGE_H
