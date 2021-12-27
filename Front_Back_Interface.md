## 前端类

### MainWindow 类

主窗口类，窗口逻辑在上面实现

类方法：

- setEquip: 获取设备列表并显示

### IP 类

类方法：

- showIP: 返回IP源地址、目的地址，格式为std::string

### TCP/UDP 类

类方法：

- showTCP: 返回源端口、目的端口、报文内容，端口格式为int；报文内容格式为std::string

## 后端函数

\*string getSubnetMask(); /*获取可用网卡名称*/

void SendTCP(
    char *device,   /*可用网卡名称*/
    char *src_ip_str,   /*源IP地址，点分十进制*/
    char *dst_ip_str,   /*目的IP地址*/ 
    u_char src_mac[6],  /*源mac地址，6个十六进制数*/
    u_char dst_mac[6],  /*目的mac地址*/
    char *message,  /*消息内容*/
    uint16_t src_port,  /*源端口号*/
    uint16_t dst_port   /*目的端口号*/
);

void SendUDP(
    char *device,   /*可用网卡名称*/
    char *src_ip_str,   /*源IP地址，点分十进制*/
    char *dst_ip_str,   /*目的IP地址*/ 
    u_char src_mac[6],  /*源mac地址，6个十六进制数*/
    u_char dst_mac[6],  /*目的mac地址*/
    char *message,  /*消息内容*/
    uint16_t src_port,  /*源端口号*/
    uint16_t dst_port   /*目的端口号*/
);