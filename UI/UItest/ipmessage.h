#ifndef IPMESSAGE_H
#define IPMESSAGE_H


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
    void ipSetSrc(int val);
    void ipSetDst(int val);

protected:
    int ver;
    int len;
    int uProto;
    int chkSum;
    int TTL;
    int ipSrc;
    int ipDst;

};

#endif // IPMESSAGE_H
