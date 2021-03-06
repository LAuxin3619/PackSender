#include "FuncForSend.h"

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

    /* IP字符串转换成网络序 */
    dst_ip_int = libnet_name2addr4(handle, dst_ip_str, LIBNET_RESOLVE);
    src_ip_int = libnet_name2addr4(handle, src_ip_str, LIBNET_RESOLVE);

    /* 初始化libnet句柄 */
    if ( (handle = libnet_init(LIBNET_LINK, device, error)) == NULL ) {
        printf("%s\n", error);
        return -1;  /* 网卡或IP错误，初始化失败 */
    };

    /* 创建消息内容 */
    strncpy((char*)payload, message, sizeof(payload)-1);
    /* 计算消息长度 */
    payload_s = strlen((char*)payload);

    /* 构建TCP报文 */
    tcp_tag = libnet_build_tcp(
        src_port,
        dst_port,
        1,                    /* 序列号 */
        2,                    /* 确认号 */
        TH_PUSH | TH_ACK,        /* Control flags*/
        14600,                    /* 窗口大小 */
        0,                        /* 校验和 */
        0,                        /* 紧急指针 */
        LIBNET_TCP_H + payload_s, /* 长度 */
        payload,                    /* 消息内容 */
        payload_s,                /*消息长度*/
        handle,
        0   /* 新建包 */
    );
    if (tcp_tag == -1) {
        return -2;  /* 构建TCP报文失败 */
    };

    /* 构建IP报文 */
    ip_tag = libnet_build_ipv4(
        LIBNET_IPV4_H + LIBNET_TCP_H + payload_s, /* IP块长度 */
        0,  /* tos */
        (u_short) libnet_get_prand(LIBNET_PRu16), /* id，随机生成0~65535 */
        0, /* 片偏移 */
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
        return -3;  /* 构建IP报文失败 */
    };

    /* 构建以太网协议块 */
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
        return -4;  /* mac错误 */
    };

    /* 发送已经构造的数据包 */
    packet_size = libnet_write(handle);
 
    /* 释放句柄 */
    libnet_destroy(handle);

    return 0;   /* 成功发送 */
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

    /* IP字符串转换成网络序 */
    dst_ip_int = libnet_name2addr4(handle, dst_ip_str, LIBNET_RESOLVE);
    src_ip_int = libnet_name2addr4(handle, src_ip_str, LIBNET_RESOLVE);

    /* 初始化libnet句柄 */
    if ( (handle = libnet_init(LIBNET_LINK, device, error)) == NULL ) {
        return -1;  /* 网卡或IP错误，初始化失败 */
    };

    /* 创建消息内容 */
    strncpy((char*)payload, message, sizeof(payload)-1);
    /* 计算消息长度 */
    payload_s = strlen((char*)payload);

    /* 构建UDP报文 */
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
        return -2;  /* 构建UDP报文失败 */
    };
 
    /* 构建IP报文 */
    ip_tag = libnet_build_ipv4(
        LIBNET_IPV4_H + LIBNET_UDP_H + payload_s, /* IP协议块长度 */
        0, /* tos */
        (u_short) libnet_get_prand(LIBNET_PRu16), /* id,随机生成0~65535 */
        0, /* 片偏移 */
        (u_int8_t)libnet_get_prand(LIBNET_PR8), /* ttl,随机生成0~255 */
        proto, /* 上层协议 */
        0, /* 校验和自动计算 */
        src_ip_int,
        dst_ip_int,
        NULL, /* 负载内容 */
        0, /* 负载内容的大小*/
        handle, /* Libnet句柄 */
        0 /* 协议块标记*/
    );
    if (ip_tag == -1) {
        return -3;  /* 构建IP报文失败 */
    };

    /* 构建以太网协议块 */
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
        return -4;  /* mac错误 */
    };

    /* 发送已经构造的数据包 */
    packet_size = libnet_write(handle);
    /* 释放句柄 */
    libnet_destroy(handle);

    return 0;   /*发送成功*/
}

int SendARP(char *device, char *src_ip_str, char *dst_ip_str, u_char src_mac[6]) {
    libnet_t *handle;
    u_long src_ip_int, dst_ip_int;
    u_char dst_mac[6] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF}; /* 目的mac,广播地址 */
    u_char rev_mac[6] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00}; /* 接收方mac */
    char error[LIBNET_ERRBUF_SIZE];

    libnet_ptag_t arp_tag, eth_tag;
    int packet_size;

    /* IP字符串转换成网络序 */
    dst_ip_int = libnet_name2addr4(handle, dst_ip_str, LIBNET_RESOLVE);
    src_ip_int = libnet_name2addr4(handle, src_ip_str, LIBNET_RESOLVE);
 
    /* 初始化Libnet句柄 */
    if ( (handle = libnet_init(LIBNET_LINK_ADV, device, error)) == NULL ) {
        return -1;  /* 网卡或IP错误，初始化失败 */
    };

    /* 构建arp报文 */
    arp_tag = libnet_build_arp(
                ARPHRD_ETHER,        /* 硬件类型 */ 
                ETHERTYPE_IP,        /* 询问IP地址 */ 
                6,                   /* 硬件地址长度 */ 
                4,                   /* IP地址长度 */ 
                ARPOP_REQUEST,       /* ARP请求 */ 
                src_mac,
                (u_int8_t *)&src_ip_int, 
                rev_mac,
                (u_int8_t *)&dst_ip_int, 
                NULL,                /* 消息内容为空 */ 
                0,                   /* 消息长度 */ 
                handle,              /* Libnet句柄 */ 
                0                    /* 协议块标记 */
    );
    if (arp_tag == -1)    {
        return -2; /* 构建ARP报文失败 */
    };
 
    /* 构建以太网协议块 */
    eth_tag = libnet_build_ethernet(
        dst_mac,
        src_mac,
        ETHERTYPE_ARP,   /* 以太网上层协议类型 */
        NULL,            /* 负载，这里为空 */ 
        0,               /* 负载长度 */
        handle,          /* Libnet句柄 */
        0                /* 协议块标记 */ 
    );
    if (eth_tag == -1) {
        return -3; /* 构建以太网协议块失败 */
    };
 
    /* 发送已经构造的数据包 */
    packet_size = libnet_write(handle);
 
    /* 释放句柄 */
    libnet_destroy(handle);
 
    return 0; /* 成功发送 */
}

int SendICMP(char *device, char *src_ip_str, char *dst_ip_str, char *message){
    libnet_t *handle;

    u_long src_ip_int;
    u_long dst_ip_int;
    char error[LIBNET_ERRBUF_SIZE];
    
    u_char payload[255] = {0};
    u_long payload_s = 0;

    libnet_ptag_t ip_tag, icmp_tag;
    u_short proto = IPPROTO_ICMP;
    int packet_size; 

    /* 初始化libnet句柄 */
    if ( (handle = libnet_init(LIBNET_RAW4, device, error)) == NULL ) {
        return -1;  /* 网卡或IP错误，初始化失败 */
    }; 

    /* IP字符串转换成网络序 */
    dst_ip_int = libnet_name2addr4(handle, dst_ip_str, LIBNET_RESOLVE);
    src_ip_int = libnet_name2addr4(handle, src_ip_str, LIBNET_RESOLVE);

    /* 创建消息内容 */
    strncpy((char*)payload, message, sizeof(payload)-1);
    /* 计算消息长度 */
    payload_s = strlen((char*)payload);

    /* 构建ICMP报文 */
    icmp_tag = libnet_build_icmpv4_echo(   
        ICMP_ECHO,  /* 类型，此时为ECHO request = 8 */   
        0, /* 代码 */   
        0, /* 校验和自动计算 */   
        1, /* 标识符 */   
        2, /* 序列号 */   
        payload,  /* 消息内容 */   
        payload_s, /* 消息长度 */   
        handle, /* libnet句柄 */   
        0  /* 协议块标记 */   
    ); 

    if (icmp_tag == -1)    {
        return -2; /* 构建ICMP报文失败 */
    };

    /* 构建IP报文 */
    ip_tag = libnet_build_ipv4( 
        LIBNET_IPV4_H + LIBNET_ICMPV4_ECHO_H + payload_s,   /* IP协议块的长度 */   
        0,  /* tos */   
        (u_short) libnet_get_prand(LIBNET_PRu16),  /* id,随机生成0~65535  */   
        0,  /* 片偏移 */   
        (u_int8_t)libnet_get_prand(LIBNET_PR8),  /* ttl,随机生成0~255 */   
        proto, /* 上层协议类型 */   
        0, /* 校验和自动计算 */   
        src_ip_int,  
        dst_ip_int, 
        NULL, /* 负载内容 */   
        0, /* 负载内容的大小 */   
        handle,/* libnet句柄 */   
        0 /* 协议块标记 */   
    );

    if (ip_tag == -1)    {
        return -3; /* 构建IP报文失败 */
    };

    /* 发送已经构造的数据包 */
    packet_size = libnet_write(handle);
 
    /* 释放句柄 */
    libnet_destroy(handle);
 
    return 0; /* 成功发送 */
}