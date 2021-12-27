#ifndef IPMESSAGE_H
#define IPMESSAGE_H

#include <QString>
#include <string>

class IpMessage
{
public:
    IpMessage();

    void showIp();
    void ipSetVer(int val);
    void ipSetLen(int val);
    void ipSetUProto(int val);
    void ipSetChkSum(int val);
    void ipSetTTL(int val);
    void ipSetSrc(QString str);
    void ipSetDst(QString str);

protected:
    int ver;
    int len;
    int uProto;
    int chkSum;
    int TTL;
    std::string ipSrc;
    std::string ipDst;

};

#endif // IPMESSAGE_H
