#include "ipmessage.h"
#include <iostream>

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

void IpMessage::ipSetSrc(int val)
{
    this->ipSrc = val;
}

void IpMessage::ipSetDst(int val)
{
    this->ipDst = val;
}

void IpMessage::showIp()
{
    std::cout<<"Current TCP message is:"<<std::endl;
    std::cout
            <<"ipVer: "<<this->ver<<std::endl
            <<"ipLen: "<<this->len<<std::endl
            <<"ipUProto: "<<this->uProto<<std::endl
            <<"ipChkSum: "<<this->chkSum<<std::endl
            <<"ipTTL: "<<this->TTL<<std::endl
            <<"ipSrc: "<<this->ipSrc<<std::endl
            <<"ipDst: "<<this->ipDst<<std::endl<<std::endl;
}
