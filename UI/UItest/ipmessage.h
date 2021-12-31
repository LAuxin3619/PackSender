#ifndef IPMESSAGE_H
#define IPMESSAGE_H

#include <QString>
#include <string>

class IpMessage
{
public:
    IpMessage();

    void showIp();
    void ipSetSrc(QString str);
    void ipSetDst(QString str);

// protected:
    std::string ipSrc;
    std::string ipDst;
    u_char macSrc[6];
    u_char macDst[6];


};

#endif // IPMESSAGE_H
