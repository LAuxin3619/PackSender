#include <libnet.h>
#include <cstdio>
#include <cstring>

/*-------声明-------*/

int SendTCP(
    char *device,   /*可用网卡名称*/
    char *src_ip_str,   /*源IP地址，点分十进制*/
    char *dst_ip_str,   /*目的IP地址*/
    u_char src_mac[6],  /*源mac地址，6个十六进制数*/
    u_char dst_mac[6],  /*目的mac地址*/
    char *message,  /*消息内容*/
    uint16_t src_port,  /*源端口号*/
    uint16_t dst_port   /*目的端口号*/
);

int SendUDP(
    char *device,   /*可用网卡名称*/
    char *src_ip_str,   /*源IP地址，点分十进制*/
    char *dst_ip_str,   /*目的IP地址*/
    u_char src_mac[6],  /*源mac地址，6个十六进制数*/
    u_char dst_mac[6],  /*目的mac地址*/
    char *message,  /*消息内容*/
    uint16_t src_port,  /*源端口号*/
    uint16_t dst_port   /*目的端口号*/
);

/*-----实现------*/

int SendTCP(char *device, char *src_ip_str, char *dst_ip_str, u_char src_mac[6], u_char dst_mac[6], char *message, uint16_t src_port, uint16_t dst_port)
{
    libnet_t *handle;
    u_long src_ip_int, dst_ip_int;
    char error[LIBNET_ERRBUF_SIZE];

    u_char payload[255] = {0};
    u_long payload_s = 0;

    libnet_ptag_t eth_tag, ip_tag, tcp_tag;
    u_short proto = IPPROTO_TCP;
    int packet_size;

    /*IP字符串转换成网络序*/
    dst_ip_int = libnet_name2addr4(handle, dst_ip_str, LIBNET_RESOLVE);
    src_ip_int = libnet_name2addr4(handle, src_ip_str, LIBNET_RESOLVE);

    /*初始化libnet句柄*/
    if ( (handle = libnet_init(LIBNET_LINK, device, error)) == NULL ) {
        return -1;  /*网卡或IP错误，初始化失败*/
    };

    /*创建消息内容*/
    strncpy((char*)payload, message, sizeof(payload)-1);
    /*计算消息长度*/
    payload_s = strlen((char*)payload);

    /*创建TCP协议块*/
    tcp_tag = libnet_build_tcp(
        src_port,
        dst_port,
        1,                    /*序列号*/
        2,                    /*确认号*/
        TH_PUSH | TH_ACK,        /*Control flags*/
        14600,                    /*窗口大小*/
        0,                        /*校验和*/
        0,                        /*紧急指针*/
        LIBNET_TCP_H + payload_s, /*长度*/
        payload,                    /*消息*/
        payload_s,                /*消息长度*/
        handle,
        0   /*新建包*/
    );
    if (tcp_tag == -1) {
        return -2;  /*构建TCP报文失败*/
    };

    /*创建IP协议块*/
    ip_tag = libnet_build_ipv4(
        LIBNET_IPV4_H + LIBNET_TCP_H + payload_s, /*IP块长度*/
        0,  /* tos */
        (u_short) libnet_get_prand(LIBNET_PRu16), /*id，随机生成0~65535*/
        0, /*片偏移*/
        (u_int8_t)libnet_get_prand(LIBNET_PR8), /* ttl，随机生成0~255 */
        proto, /* 上层协议 */
        0, /* 校验和自动计算 */
        src_ip_int,
        dst_ip_int,
        NULL, /* 负载内容 */
        0, /* 负载内容的大小*/
        handle, /* Libnet句柄 */
        0 /* 协议块标记 */
    );
    if (ip_tag == -1) {
        return -3;  /*构建IP报文失败*/
    };

    /* 创建以太网协议块 */
    eth_tag = libnet_build_ethernet(
        dst_mac,
        src_mac,
        ETHERTYPE_IP, /* 以太网上层协议类型 */
        NULL, /* 负载 */
        0, /* 负载大小 */
        handle, /* Libnet句柄 */
        0 /* 协议块标记 */
    );
    if (eth_tag == -1) {
        return -4;  /*mac错误*/
    };

    /* 发送已经构造的数据包*/
    packet_size = libnet_write(handle);

    /* 释放句柄 */
    libnet_destroy(handle);

    return 0;   /*成功发送*/
}

int SendUDP(char *device, char *src_ip_str, char *dst_ip_str, u_char src_mac[6], u_char dst_mac[6], char *message, uint16_t src_port, uint16_t dst_port)
{
    libnet_t *handle;
    u_long src_ip_int, dst_ip_int;
    char error[LIBNET_ERRBUF_SIZE];

    u_char payload[255] = {0};
    u_long payload_s = 0;

    libnet_ptag_t eth_tag, ip_tag, udp_tag;
    u_short proto = IPPROTO_UDP;
    int packet_size;

    /*IP字符串转换成网络序*/
    dst_ip_int = libnet_name2addr4(handle, dst_ip_str, LIBNET_RESOLVE);
    src_ip_int = libnet_name2addr4(handle, src_ip_str, LIBNET_RESOLVE);

    /*初始化libnet句柄*/
    if ( (handle = libnet_init(LIBNET_LINK, device, error)) == NULL ) {
        return -1;  /*网卡错误，初始化失败*/
    };

    /*创建消息内容*/
    strncpy((char*)payload, message, sizeof(payload)-1);
    /*计算消息长度*/
    payload_s = strlen((char*)payload);

    /* 创建UDP协议包 */
    udp_tag = libnet_build_udp(
        src_port,
        dst_port,
        LIBNET_UDP_H + payload_s, /* 长度 */
        0, /* 校验和 */
        payload, /* 消息内容 */
        payload_s, /* 消息长度 */
        handle, /* libnet句柄 */
        0 /* 新建包 */
    );
    if (udp_tag == -1) {
        return -2;  /*构建UDP报文失败*/
    };

    /* 创建IP协议块 */
    ip_tag = libnet_build_ipv4(
        LIBNET_IPV4_H + LIBNET_UDP_H + payload_s, /* IP协议块长度*/
        0, /* tos */
        (u_short) libnet_get_prand(LIBNET_PRu16), /* id,随机生成0~65535 */
        0, /* 片偏移 */
        (u_int8_t)libnet_get_prand(LIBNET_PR8), /* ttl,随机生成0~255 */
        proto, /* 上层协议 */
        0, /* 校验和，此时为0，表示由Libnet自动计算 */
        src_ip_int,
        dst_ip_int,
        NULL, /* 负载内容 */
        0, /* 负载内容的大小*/
        handle, /* Libnet句柄 */
        0 /* 协议块标记*/
    );
    if (ip_tag == -1) {
        return -3;  /*构建IP报文失败*/
    };

    /* 构造一个以太网协议块,只能用于LIBNET_LINK */
    eth_tag = libnet_build_ethernet(
        dst_mac,
        src_mac,
        ETHERTYPE_IP, /* 以太网上层协议类型，此时为IP类型 */
        NULL, /* 负载，这里为空 */
        0, /* 负载大小 */
        handle, /* Libnet句柄 */
        0 /* 协议块标记 */
    );
    if (eth_tag == -1) {
        return -4;  /*mac错误*/
    };

    /* 发送已经构造的数据包 */
    packet_size = libnet_write(handle);
    /* 释放句柄 */
    libnet_destroy(handle);

    return 0;   /*发送成功*/
}
