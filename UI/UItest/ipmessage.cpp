#include "ipmessage.h"
#include <iostream>
#include <string>

IpMessage::IpMessage():
    ver(),
    len(),
    uProto(),  // 6 for TCP, 17 for UDP, 1 for ICMP
    chkSum(),
    TTL(),
    ipSrc(),
    ipDst()
{

}

void IpMessage::ipSetVer(int val)
{
    this->ver = val;
}

void IpMessage::ipSetLen(int val)
{
    this->len = val;
}

void IpMessage::ipSetUProto(int val)
{
    this->uProto = val;
}

void IpMessage::ipSetChkSum(int val)
{
    this->chkSum = val;
}

void IpMessage::ipSetTTL(int val)
{
    this->TTL = val;
}

void IpMessage::ipSetSrc(QString str)
{
    this->ipSrc = str.toStdString();
}

void IpMessage::ipSetDst(QString str)
{
    this->ipDst = str.toStdString();
}

void IpMessage::showIp()
{
    std::cout<<"Current IP message is:"<<std::endl;
    std::cout
            <<"ipSrc: "<<this->ipSrc<<std::endl
            <<"ipDst: "<<this->ipDst<<std::endl<<std::endl;
}
