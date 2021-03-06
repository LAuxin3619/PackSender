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

void TcpMessage::tcpSetText(std::string txt)
{
    this->tcpText = txt;
}

std::string* TcpMessage::tcpEquipList()
{
    std::string *p=&equipList[0];
    return p;
}

void TcpMessage::showTcp()
{
    std::cout<<"Current TCP message is:"<<std::endl;
    std::cout
            <<"tcpSrcPort: "<<this->tcpSrcPort<<std::endl
            <<"tcpDstPort: "<<this->tcpDstPort<<std::endl
            <<"tcpDstPort: "<<this->tcpText<<std::endl<<std::endl;
}
