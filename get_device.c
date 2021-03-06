#include <stdio.h>  
#include <ifaddrs.h>  
#include <arpa/inet.h>  

int getSubnetMask()
{
    struct sockaddr_in *sin = NULL;
    struct ifaddrs *ifa = NULL, *ifList;

    if (getifaddrs(&ifList) < 0)
    {
        return -1;
    }

    for (ifa = ifList; ifa != NULL; ifa = ifa->ifa_next)
    {
        if(ifa->ifa_addr->sa_family == AF_INET)
        {
            printf("interfaceName: %s\n", ifa->ifa_name);
        }
    }

    freeifaddrs(ifList);

    return 0;
}

int main(void)
{
    getSubnetMask();

    return 0;
}
