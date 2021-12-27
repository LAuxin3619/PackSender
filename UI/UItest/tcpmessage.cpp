#include "tcpmessage.h"
#include "ipmessage.h"
#include <iostream>

TcpMessage::TcpMessage()
{
    tcpSrcPort = 0;
    tcpDstPort = 0;
    tcpText = "";
}

void TcpMessage::tcpSetSrc(int val)
{
    this->tcpSrcPort = val;
}

void TcpMessage::tcpSetDst(int val)
{
    this->tcpDstPort = val;
}

void TcpMessage::tcpSetText(std::string txt)
{
    this->tcpText = txt;
}

void TcpMessage::showTcp()
{
    std::cout<<"Current TCP message is:"<<std::endl;
    std::cout
            <<"tcpSrcPort: "<<this->tcpSrcPort<<std::endl
            <<"tcpDstPort: "<<this->tcpDstPort<<std::endl
            <<"tcpText: "<<this->tcpText<<std::endl<<std::endl;
}
void TcpMessage::showUdp()
{
    std::cout<<"Current UDP message is:"<<std::endl;
    std::cout
            <<"udpSrcPort: "<<this->tcpSrcPort<<std::endl
            <<"udpDstPort: "<<this->tcpDstPort<<std::endl
            <<"udpText: "<<this->tcpText<<std::endl<<std::endl;
}
