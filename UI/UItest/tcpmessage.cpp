#include "tcpmessage.h"
#include "ipmessage.h"
#include <iostream>

TcpMessage::TcpMessage()
{

}

void TcpMessage::tcpSetSrc(int val)
{
    this->tcpSrcPort = val;
}

void TcpMessage::tcpSetDst(int val)
{
    this->tcpDstPort = val;
}

void TcpMessage::tcpSetSeq(int val)
{
    this->tcpSeq = val;
}

void TcpMessage::tcpSetOfst(int val)
{
    this->tcpOfst = val;
}

void TcpMessage::tcpSetWin(int val)
{
    this->tcpWin = val;
}

void TcpMessage::tcpSetChk(int val)
{
    this->tcpChk = val;
}

void TcpMessage::showTcp()
{
    std::cout<<"Current TCP message is:"<<std::endl;
    std::cout
            <<"tcpSrcPort: "<<this->tcpSrcPort<<std::endl
            <<"tcpDstPort: "<<this->tcpDstPort<<std::endl
            <<"tcpSeq: "<<this->tcpSeq<<std::endl
            <<"tcpOfst: "<<this->tcpOfst<<std::endl
            <<"tcpWin: "<<this->tcpWin<<std::endl
            <<"tcpChk: "<<this->tcpChk<<std::endl<<std::endl;
}
