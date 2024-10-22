/*******************************************申明***************************************
本嵌入式操作系统未经授权，禁止应用于任何商业用途
版权所有，侵权必究
http://www.trtos.com/
**************************************************************************************/
/******************** (C) COPYRIGHT 2011 野火嵌入式开发工作室 ********************
 * 文件名  ：web_server.c
 * 描述    ：web服务程序应用函数库
 *          
 * 实验平台：野火STM32开发板
 * 硬件连接： ------------------------------------
 *           |PB13         ：ENC28J60-INT (没用到)|
 *           |PA6-SPI1-MISO：ENC28J60-SO          |
 *           |PA7-SPI1-MOSI：ENC28J60-SI          |
 *           |PA5-SPI1-SCK ：ENC28J60-SCK         |
 *           |PA4-SPI1-NSS ：ENC28J60-CS          |
 *           |PE1          ：ENC28J60-RST (没用)  |
 *            ------------------------------------
 * 库版本  ：ST3.0.0
 *
 * 作者    ：fire  QQ: 313303034
 * 博客    ：firestm32.blog.chinaunix.net
**********************************************************************************/
#include <..\USER\Prj_Prafire\NET\enc28j60.h>
#include <..\USER\Prj_Prafire\NET\ip_arp_udp_tcp.h>
#include <..\USER\Prj_Prafire\NET\net.h>
#include <..\USER\Prj_Prafire\NET\web_server.h>
#include <string.h>


#define PSTR(s) s	

/* LED1 亮灭宏定义 */
//#define LED1_ON()  GPIO_SetBits(GPIOC, GPIO_Pin_3);
//#define LED1_OFF()  GPIO_ResetBits(GPIOC, GPIO_Pin_3);


/* mac地址和ip地址在局域网内必须唯一，否则将与其他主机冲突，导致连接不成功 */
static unsigned char mymac[6] = {0x54,0x55,0x58,0x10,0x00,0x24};
static unsigned char myip[4] = {192,168,1,15};

/* ip地址(或者是DNS的名字，如果有DNS服务器的话)，ip地址必须以"/"结尾 */
static char baseurl[]="http://192.168.1.15/";

/* tcp/www监听端口号，范围为:1-254 */
static unsigned int mywwwport =80; 

/* udp 监听端口号，即本地(开发板)端口号 */
static unsigned int myudpport =1200; 

/* 发送数据缓冲区 */
#define Web_Buf_Size 2500
unsigned char Web_Buf[Web_Buf_Size+1];

/* 密码,不能大于9个字符(只有密码的前5位会被检测)，(字符限定为：a-z,0-9) */
static char password[]="123456"; 

/*
 * 函数名：verify_password
 * 描述  ：确认密码
 * 输入  ：str
 * 输出  ：无
 * 返回  ：
 */ 
unsigned char verify_password(char *str)
{
    // the first characters of the received string are
    // a simple password/cookie:
    if (strncmp(password,str,5)==0)
    {
        return(1);
    }
    return(0);
}

/*
 * 函数名：analyse_get_url
 * 描述  ：takes a string of the form password/commandNumber and analyse it
 * 输入  ：str
 * 输出  ：-1 invalid password, otherwise command number
 *         -2	no command given but password valid
 * 返回  ：
 */
int analyse_get_url(char *str)
{
    unsigned char i=0;
    if (verify_password(str)==0)
    {
        return(-1);
    }
    // find first "/"
    // passw not longer than 9 char:
    while(*str && i<10 && *str >',' && *str<'{')
    {
        if (*str=='/')
        {
            str++;
            break;
        }
        i++;
        str++;
    }
    if (*str < 0x3a && *str > 0x2f)
    {
        // is a ASCII number, return it
        return(*str-0x30);
    }
    return(-2);
}

/*
 * 函数名：print_webpage
 * 描述  ：将数据写到tcp的发送缓冲区(以实现一个网页)
 * 输入  ：-Web_Buf
 *         -on_off
 * 输出  ：无
 * 返回  ：-plen
 */

#define LOGIN "\
<html>\
<head>\
<meta http-equiv=\"Content-Type\" content=\"text/html; charset=gb2312\">\
<title>LWIP移植实验 </title>\
</head>\
</body>\
<form action=\"login\" method=\"post\">\
<p>  用户名:\
<input type=\"text\" name=\"UserName\">\
<p>	 密码:  \
<input type=\"password\" name=\"PassWord\">\
<p><input type=\"submit\" value=\"登录\"> \
</form>\
</body> \
</html>\
" 
unsigned int print_webpage(unsigned char *Web_Buf,unsigned char on_off)
{
    unsigned int plen;
		/* 新建一个网页，就像新建一个文件一样 */
	//plen=fill_tcp_data_p(Web_Buf,0,LOGIN);
	//return plen;
    plen=fill_tcp_data_p(Web_Buf,0,PSTR("HTTP/1.0 200 OK\r\nContent-Type: text/html\r\nPragma: no-cache\r\n\r\n"));
	
		/* 在网页正中央填写信息 */
    plen=fill_tcp_data_p(Web_Buf,plen,PSTR("<center><p> LED状态指示: "));

    if (on_off)
    {
        plen=fill_tcp_data_p(Web_Buf,plen,PSTR("<font color=\"#00FF00\"> 亮</font>"));
    }
    else
    {
        plen=fill_tcp_data_p(Web_Buf,plen,PSTR("灭"));
    }

    plen=fill_tcp_data_p(Web_Buf,plen,PSTR(" <small><a href=\""));
    plen=fill_tcp_data(Web_Buf,plen,baseurl);		 // 要在浏览器中输入的网址
    plen=fill_tcp_data(Web_Buf,plen,password);	 // 紧跟在网址后面的密码
    plen=fill_tcp_data_p(Web_Buf,plen,PSTR("\">[刷新]</a></small></p>\n<p><a href=\""));
    // the url looks like this http://baseurl/password/command
    plen=fill_tcp_data(Web_Buf,plen,baseurl);
    plen=fill_tcp_data(Web_Buf,plen,password);
    if (on_off)
    {
        plen=fill_tcp_data_p(Web_Buf,plen,PSTR("/0\">关闭3D动态演示</a><p>"));
    }
    else
    {
        plen=fill_tcp_data_p(Web_Buf,plen,PSTR("/1\">点亮3D动态演示</a><p>"));
    }
		plen=fill_tcp_data_p(Web_Buf,plen,PSTR("<left><font color=\"#00F0F0\">系统任务数:6<br>"));
		plen=fill_tcp_data_p(Web_Buf,plen,PSTR("外设个数:8<br>"));
		plen=fill_tcp_data_p(Web_Buf,plen,PSTR("CPU总占用率:32%<br>"));
		plen=fill_tcp_data_p(Web_Buf,plen,PSTR("WebServer服务占用CPU:7%<br>"));
		plen=fill_tcp_data_p(Web_Buf,plen,PSTR("</font><left/>"));
    plen=fill_tcp_data_p(Web_Buf,plen,PSTR("<center><hr><br>欢迎您使用TOS嵌入式操作系统\n"));
		plen=fill_tcp_data_p(Web_Buf,plen,PSTR("<br>Real Time Operating System\n"));
    //plen=fill_tcp_data_p(Web_Buf,plen,PSTR("这是一个 web 测试程序"));
    
    return(plen);
}

/*
 * 函数名：Web_Server
 * 描述  ：在浏览器上创建一个web服务器，通过web里面的命令来控制开发板上的LED的亮灭。
 * 输入  ：无
 * 输出  ：无
 * 返回  ：-0 运行成功
 * 应用  ：1 在PC机的DOS界面输入： ping 192.168.1.15 (看能否ping通)
 *         2 在IE浏览器中输入：http://192.168.1.15/123456 则会出现一个网页，通过网页
 *           中的命令可以控制开发板中的LED的亮灭
 */
void  Web_Server(void *Tags)
{   
	unsigned int plen, i1 = 0;
	unsigned int dat_p;
	unsigned char i = 0;
	int cmd;
	char *Web_Buf_P;
	unsigned int payloadlen = 0;
  SPI_Enc28j60_Init();
  /* 初始化 enc28j60 的MAC地址(物理地址),这个函数必须要调用一次 */
  enc28j60Init(mymac);

	/* PHY LED 配置,LED用来指示通信的状态 */	
  enc28j60PhyWrite(PHLCON,0x476);	
	
	/* 将enc28j60第三引脚的时钟输出改为：from 6.25MHz to 12.5MHz(本例程该引脚NC,没用到) */	
  enc28j60clkout(2);    
  
	/* 初始化以太网 IP 层 */
	init_ip_arp_udp_tcp(mymac,myip,mywwwport);

  while(1)
  {   
			Tos_TaskDelay(10);
			// get the next new packet:			
      plen = enc28j60PacketReceive(Web_Buf_Size, Web_Buf);      
     
		  
      // plen will ne unequal to zero if there is a valid packet (without crc error)			
      if(plen==0)
      { 
          continue;
      }
			USART_WriteDatas(USART2,(uint8 *)&Web_Buf[0],plen);
      // arp is broadcast if unknown but a host may also
      // verify the mac address by sending it to 
      // a unicast address.		     
      if(eth_type_is_arp_and_my_ip(Web_Buf,plen))
      {
          make_arp_answer_from_request(Web_Buf);          
          continue;
      }
      
      // check if ip packets are for us:			
      if(eth_type_is_ip_and_my_ip(Web_Buf,plen)==0) //检查这是不是我的IP
      {
          continue;
      }      
      
      if(Web_Buf[IP_PROTO_P]==IP_PROTO_ICMP_V && Web_Buf[ICMP_TYPE_P]==ICMP_TYPE_ECHOREQUEST_V)
      {
          // a ping packet, let's send pong  DOS 下的 ping 命令包		 
          make_echo_reply_from_request(Web_Buf, plen);          
          continue;
      }

/*-----------------tcp port www start, compare only the lower byte-----------------------------------*/
      if (Web_Buf[IP_PROTO_P]==IP_PROTO_TCP_V&&Web_Buf[TCP_DST_PORT_H_P]==0&&Web_Buf[TCP_DST_PORT_L_P]==mywwwport)
      {
          if (Web_Buf[TCP_FLAGS_P] & TCP_FLAGS_SYN_V)
          {
              make_tcp_synack_from_syn(Web_Buf);
              // make_tcp_synack_from_syn does already send the syn,ack
              continue;
          }
          if (Web_Buf[TCP_FLAGS_P] & TCP_FLAGS_ACK_V)
          {
              init_len_info(Web_Buf); // init some data structures
              // we can possibly have no data, just ack:
              dat_p=get_tcp_data_pointer();
              if (dat_p==0)
              {
                  if (Web_Buf[TCP_FLAGS_P] & TCP_FLAGS_FIN_V)
                  {
                      // finack, answer with ack
                      make_tcp_ack_from_any(Web_Buf);
                  }
                  // just an ack with no data, wait for next packet
                  continue;
              }
              if (strncmp("GET ",(char *)&(Web_Buf[dat_p]),4)!=0)
              {
                  // head, post and other methods:
                  //
                  // for possible status codes see:
                  // http://www.w3.org/Protocols/rfc2616/rfc2616-sec10.html
                  plen=fill_tcp_data_p(Web_Buf,0,PSTR("HTTP/1.0 200 OK\r\nContent-Type: text/html\r\n\r\n<h1>200 OK</h1>"));
                  goto SENDTCP;
              }
              if (strncmp("/ ",(char *)&(Web_Buf[dat_p+4]),2)==0)
              {
                  plen=fill_tcp_data_p(Web_Buf,0,PSTR("HTTP/1.0 200 OK\r\nContent-Type: text/html\r\n\r\n"));
                  plen=fill_tcp_data_p(Web_Buf,plen,PSTR("<p>Usage: "));
                  plen=fill_tcp_data(Web_Buf,plen,baseurl);
                  plen=fill_tcp_data_p(Web_Buf,plen,PSTR("password</p>"));
                  goto SENDTCP;
              }
              cmd=analyse_get_url((char *)&(Web_Buf[dat_p+5]));
              // for possible status codes see:
              // http://www.w3.org/Protocols/rfc2616/rfc2616-sec10.html
              if (cmd==-1)
              {
                  plen=fill_tcp_data_p(Web_Buf,0,PSTR("HTTP/1.0 401 Unauthorized\r\nContent-Type: text/html\r\n\r\n<h1>401 Unauthorized</h1>"));
                  goto SENDTCP;
              }
              if (cmd==1)	           // 用户程序
              {			
									//LED1(ON);
								
								Tos_TaskResume(3);
                  i=1;							 // 命令 = 1
              }
              if (cmd==0)						 // 用户程序
              {									
									//LED1(OFF);
								Tos_TaskStop(3);
                  i=0;							 // 命令 = 0
              }
              // if (cmd==-2) or any other value
              // just display the status:
              plen=print_webpage(Web_Buf,(i));
							
              
              SENDTCP:
              make_tcp_ack_from_any(Web_Buf);       // send ack for http get
              make_tcp_ack_with_data(Web_Buf,plen); // send data
              continue;
          }
      }
/*-------------------------------------- tcp port www end ---------------------------------------*/

/*--------------------- udp start, we listen on udp port 1200=0x4B0 -----------------------------*/
      if (Web_Buf[IP_PROTO_P]==IP_PROTO_UDP_V&&Web_Buf[UDP_DST_PORT_H_P]==4&&Web_Buf[UDP_DST_PORT_L_P]==0xb0)
      {
          payloadlen=	  Web_Buf[UDP_LEN_H_P];
          payloadlen=payloadlen<<8;
          payloadlen=(payloadlen+Web_Buf[UDP_LEN_L_P])-UDP_HEADER_LEN;
          //payloadlen=Web_Buf[UDP_LEN_L_P]-UDP_HEADER_LEN;
          
         // ANSWER:
          //while(1){
          for(i1=0; i1<payloadlen; i1++) Web_Buf_P[i1]=Web_Buf[UDP_DATA_P+i1];
          
          //make_udp_reply_from_request(Web_Buf,str,strlen(str),myudpport);
          make_udp_reply_from_request(Web_Buf,(char *)Web_Buf_P,payloadlen,myudpport);          
          //}
      }
/*----------------------------------------udp end -----------------------------------------------*/
  }
        //  return (0);
}
/******************* (C) COPYRIGHT 2011 野火嵌入式开发工作室 *****END OF FILE****/
