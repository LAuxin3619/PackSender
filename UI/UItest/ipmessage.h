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

    std::string* ipEquipList();

protected:
    std::string ipSrc;
    std::string ipDst;
    std::string equipList[10]={"Device1","Device2"};
    std::string chosenEquip;

};

#endif // IPMESSAGE_H
