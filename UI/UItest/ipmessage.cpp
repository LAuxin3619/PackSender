#include "ipmessage.h"
#include <iostream>
#include <string>

IpMessage::IpMessage():
    ipSrc(),
    ipDst()
{

}

void IpMessage::ipSetSrc(QString str)
{
    this->ipSrc = str.toStdString();
}

void IpMessage::ipSetDst(QString str)
{
    this->ipDst = str.toStdString();
}

std::string* IpMessage::ipEquipList()
{
    std::string *p=&equipList[0];
    return p;
}

void IpMessage::showIp()
{
    std::cout<<"Current IP message is:"<<std::endl;
    std::cout
            <<"ipSrc: "<<this->ipSrc<<std::endl
            <<"ipDst: "<<this->ipDst<<std::endl<<std::endl;
}
