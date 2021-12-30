#include "FuncForSend.h"

int main()
{
    char *device = (char *)malloc(sizeof(15));
    char *src_ip_str = (char *)malloc(sizeof(15));
    char *dst_ip_str = (char *)malloc(sizeof(15));
    char *message = (char *)malloc(sizeof(100));
    u_char src_mac[6] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
    u_char dst_mac[6] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
    uint16_t src_port = 0;
    uint16_t dst_port = 0;

    int choice = 0;
    char *ifQuit = (char *)malloc(sizeof(5));
    strcpy(ifQuit, "n");

    printf("%s\n%s\n%s\n%s\n%s\n", "Welcome! Which type of pack you  want to send?", "1-----TCP", "2-----UDP", "3-----ARP", "4----ICMP");
    while (*ifQuit == 'n')
    {
        printf("Please choose type:");
        scanf("%d", &choice);
        printf("\n");

        switch (choice)
        {
            case 1:
            {
                printf("Please enter source IP,such as  192.168.1.1:");
                scanf("%s", src_ip_str);
                device = src_ip_str;

                printf("Please enter destination IP:");
                scanf("%s", dst_ip_str);

                printf("Please enter source MAC,such as 0x00 0x23 0x17 0x2c 0x5d 0x32:");
                scanf("%s %s %s %s %s %s", &src_mac[0], &src_mac[1], &src_mac[2], &src_mac[3], &src_mac[4], &src_mac[5]);

                printf("Please enter destination MAC:");
                scanf("%s %s %s %s %s %s", &dst_mac[0], &dst_mac[1], &dst_mac[2], &dst_mac[3], &dst_mac[4], &dst_mac[5]);

                printf("Please enter source port,such as 30331:");
                scanf("%u", &src_port);

                printf("Please enter destination port:");
                scanf("%u", &dst_port);

                printf("Please enter message you want to send:");
                scanf("%s", message);

                SendTCP(device, src_ip_str, dst_ip_str, src_mac, dst_mac, message, src_port, dst_port);
                break;
            }
            case 2:
            {
                printf("Please enter source IP,such as  192.168.1.1:");
                scanf("%s", src_ip_str);
                device = src_ip_str;

                printf("Please enter destination IP:");
                scanf("%s", dst_ip_str);

                printf("Please enter source MAC,such as 0x00 0x23 0x17 0x2c 0x5d 0x32:");
                scanf("%s %s %s %s %s %s", &src_mac[0], &src_mac[1], &src_mac[2], &src_mac[3], &src_mac[4], &src_mac[5]);

                printf("Please enter destination MAC:");
                scanf("%s %s %s %s %s %s", &dst_mac[0], &dst_mac[1], &dst_mac[2], &dst_mac[3], &dst_mac[4], &dst_mac[5]);

                printf("Please enter source port,such as 30331:");
                scanf("%u", &src_port);

                printf("Please enter destination port:");
                scanf("%u", &dst_port);

                printf("Please enter message you want to send:");
                scanf("%s", message);

                SendUDP(device, src_ip_str, dst_ip_str, src_mac, dst_mac, message, src_port, dst_port);
                break;
            }
            case 3:
            {
                printf("Please enter source IP,such as  192.168.1.1:");
                scanf("%s", src_ip_str);
                device = src_ip_str;

                printf("Please enter destination IP:");
                scanf("%s", dst_ip_str);

                printf("Please enter source MAC,such as 0x00 0x23 0x17 0x2c 0x5d 0x32:");
                scanf("%s %s %s %s %s %s", &src_mac[0], &src_mac[1], &src_mac[2], &src_mac[3], &src_mac[4], &src_mac[5]);

                SendARP(device, src_ip_str, dst_ip_str, src_mac);
                break;
            }
            case 4:
            {
                printf("Please enter source IP,such as  192.168.1.1:");
                scanf("%s", src_ip_str);
                device = src_ip_str;

                printf("Please enter destination IP:");
                scanf("%s", dst_ip_str);

                printf("Please enter message you want to send:");
                scanf("%s", message);

                SendICMP(device, src_ip_str, dst_ip_str, message);
                break;
            }
            default:
            {
                printf("Wrong type......\n");
            }
        }

        printf("Want to quit?[y/n]:");
        scanf("%s", ifQuit);
    }

    free(src_ip_str);
    free(dst_ip_str);
    free(message);
    return 0;
}