#include <libnet.h>

int SendTCP(
    char *device,   /* 可用网卡名称 */
    char *src_ip_str,   /* 源IP地址，点分十进制 */
    char *dst_ip_str,   /* 目的IP地址 */ 
    u_char src_mac[6],  /* 源mac地址，6个十六进制数 */
    u_char dst_mac[6],  /* 目的mac地址 */
    char *message,  /* 消息内容 */
    uint16_t src_port,  /* 源端口号 */
    uint16_t dst_port   /* 目的端口号 */
);

int SendUDP(
    char *device,   /* 可用网卡名称 */
    char *src_ip_str,   /* 源IP地址，点分十进制 */
    char *dst_ip_str,   /* 目的IP地址 */ 
    u_char src_mac[6],  /* 源mac地址，6个十六进制数 */
    u_char dst_mac[6],  /* 目的mac地址 */
    char *message,  /* 消息内容 */
    uint16_t src_port,  /* 源端口号 */
    uint16_t dst_port   /* 目的端口号 */
);

int SendARP(
    char *device,   /* 可用网卡名称 */
    char *src_ip_str,   /* 源IP地址，点分十进制 */
    char *dst_ip_str,   /* 目的IP地址 */ 
    u_char src_mac[6] /* 源mac地址，6个十六进制数 */
);

int SendICMP(
    char *device,   /* 可用网卡名称 */
    char *src_ip_str,   /* 源IP地址，点分十进制*/
    char *dst_ip_str,   /* 目的IP地址 */
    char *message   /* 消息内容 */
);