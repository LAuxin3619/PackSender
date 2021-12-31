#include "FuncForSend.h"
#include <iostream>

using namespace std;

int main()
{
    cout << "Hello !"<<endl;

    u_char srcMac[6]={0x00,0x0c,0x29,0x3e,0x4b,0x91};
    u_char dstMac[6]={0x3C,0x91,0x80,0x48,0xFC,0x11};
    cout << SendTCP("192.168.220.132","192.168.220.132","220.181.38.148",srcMac,dstMac,"Hello World!",50000,80);

    return 0;
}