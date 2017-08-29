/*******************************************����***************************************
��Ƕ��ʽ����ϵͳδ����Ȩ����ֹӦ�����κ���ҵ��;
��Ȩ���У���Ȩ�ؾ�
http://www.trtos.com/
**************************************************************************************/
/******************** (C) COPYRIGHT 2011 Ұ��Ƕ��ʽ���������� ********************
 * �ļ���  ��web_server.c
 * ����    ��web�������Ӧ�ú�����
 *          
 * ʵ��ƽ̨��Ұ��STM32������
 * Ӳ�����ӣ� ------------------------------------
 *           |PB13         ��ENC28J60-INT (û�õ�)|
 *           |PA6-SPI1-MISO��ENC28J60-SO          |
 *           |PA7-SPI1-MOSI��ENC28J60-SI          |
 *           |PA5-SPI1-SCK ��ENC28J60-SCK         |
 *           |PA4-SPI1-NSS ��ENC28J60-CS          |
 *           |PE1          ��ENC28J60-RST (û��)  |
 *            ------------------------------------
 * ��汾  ��ST3.0.0
 *
 * ����    ��fire  QQ: 313303034
 * ����    ��firestm32.blog.chinaunix.net
**********************************************************************************/
#include <..\USER\Prj_Prafire\NET\enc28j60.h>
#include <..\USER\Prj_Prafire\NET\ip_arp_udp_tcp.h>
#include <..\USER\Prj_Prafire\NET\net.h>
#include <..\USER\Prj_Prafire\NET\web_server.h>
#include <string.h>


#define PSTR(s) s	

/* LED1 ����궨�� */
//#define LED1_ON()  GPIO_SetBits(GPIOC, GPIO_Pin_3);
//#define LED1_OFF()  GPIO_ResetBits(GPIOC, GPIO_Pin_3);


/* mac��ַ��ip��ַ�ھ������ڱ���Ψһ������������������ͻ���������Ӳ��ɹ� */
static unsigned char mymac[6] = {0x54,0x55,0x58,0x10,0x00,0x24};
static unsigned char myip[4] = {192,168,1,15};

/* ip��ַ(������DNS�����֣������DNS�������Ļ�)��ip��ַ������"/"��β */
static char baseurl[]="http://192.168.1.15/";

/* tcp/www�����˿ںţ���ΧΪ:1-254 */
static unsigned int mywwwport =80; 

/* udp �����˿ںţ�������(������)�˿ں� */
static unsigned int myudpport =1200; 

/* �������ݻ����� */
#define Web_Buf_Size 2500
unsigned char Web_Buf[Web_Buf_Size+1];

/* ����,���ܴ���9���ַ�(ֻ�������ǰ5λ�ᱻ���)��(�ַ��޶�Ϊ��a-z,0-9) */
static char password[]="123456"; 

/*
 * ��������verify_password
 * ����  ��ȷ������
 * ����  ��str
 * ���  ����
 * ����  ��
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
 * ��������analyse_get_url
 * ����  ��takes a string of the form password/commandNumber and analyse it
 * ����  ��str
 * ���  ��-1 invalid password, otherwise command number
 *         -2	no command given but password valid
 * ����  ��
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
 * ��������print_webpage
 * ����  ��������д��tcp�ķ��ͻ�����(��ʵ��һ����ҳ)
 * ����  ��-Web_Buf
 *         -on_off
 * ���  ����
 * ����  ��-plen
 */

#define LOGIN "\
<html>\
<head>\
<meta http-equiv=\"Content-Type\" content=\"text/html; charset=gb2312\">\
<title>LWIP��ֲʵ�� </title>\
</head>\
</body>\
<form action=\"login\" method=\"post\">\
<p>  �û���:\
<input type=\"text\" name=\"UserName\">\
<p>	 ����:  \
<input type=\"password\" name=\"PassWord\">\
<p><input type=\"submit\" value=\"��¼\"> \
</form>\
</body> \
</html>\
" 
unsigned int print_webpage(unsigned char *Web_Buf,unsigned char on_off)
{
    unsigned int plen;
		/* �½�һ����ҳ�������½�һ���ļ�һ�� */
	//plen=fill_tcp_data_p(Web_Buf,0,LOGIN);
	//return plen;
    plen=fill_tcp_data_p(Web_Buf,0,PSTR("HTTP/1.0 200 OK\r\nContent-Type: text/html\r\nPragma: no-cache\r\n\r\n"));
	
		/* ����ҳ��������д��Ϣ */
    plen=fill_tcp_data_p(Web_Buf,plen,PSTR("<center><p> LED״ָ̬ʾ: "));

    if (on_off)
    {
        plen=fill_tcp_data_p(Web_Buf,plen,PSTR("<font color=\"#00FF00\"> ��</font>"));
    }
    else
    {
        plen=fill_tcp_data_p(Web_Buf,plen,PSTR("��"));
    }

    plen=fill_tcp_data_p(Web_Buf,plen,PSTR(" <small><a href=\""));
    plen=fill_tcp_data(Web_Buf,plen,baseurl);		 // Ҫ����������������ַ
    plen=fill_tcp_data(Web_Buf,plen,password);	 // ��������ַ���������
    plen=fill_tcp_data_p(Web_Buf,plen,PSTR("\">[ˢ��]</a></small></p>\n<p><a href=\""));
    // the url looks like this http://baseurl/password/command
    plen=fill_tcp_data(Web_Buf,plen,baseurl);
    plen=fill_tcp_data(Web_Buf,plen,password);
    if (on_off)
    {
        plen=fill_tcp_data_p(Web_Buf,plen,PSTR("/0\">�ر�3D��̬��ʾ</a><p>"));
    }
    else
    {
        plen=fill_tcp_data_p(Web_Buf,plen,PSTR("/1\">����3D��̬��ʾ</a><p>"));
    }
		plen=fill_tcp_data_p(Web_Buf,plen,PSTR("<left><font color=\"#00F0F0\">ϵͳ������:6<br>"));
		plen=fill_tcp_data_p(Web_Buf,plen,PSTR("�������:8<br>"));
		plen=fill_tcp_data_p(Web_Buf,plen,PSTR("CPU��ռ����:32%<br>"));
		plen=fill_tcp_data_p(Web_Buf,plen,PSTR("WebServer����ռ��CPU:7%<br>"));
		plen=fill_tcp_data_p(Web_Buf,plen,PSTR("</font><left/>"));
    plen=fill_tcp_data_p(Web_Buf,plen,PSTR("<center><hr><br>��ӭ��ʹ��TOSǶ��ʽ����ϵͳ\n"));
		plen=fill_tcp_data_p(Web_Buf,plen,PSTR("<br>Real Time Operating System\n"));
    //plen=fill_tcp_data_p(Web_Buf,plen,PSTR("����һ�� web ���Գ���"));
    
    return(plen);
}

/*
 * ��������Web_Server
 * ����  ����������ϴ���һ��web��������ͨ��web��������������ƿ������ϵ�LED������
 * ����  ����
 * ���  ����
 * ����  ��-0 ���гɹ�
 * Ӧ��  ��1 ��PC����DOS�������룺 ping 192.168.1.15 (���ܷ�pingͨ)
 *         2 ��IE����������룺http://192.168.1.15/123456 ������һ����ҳ��ͨ����ҳ
 *           �е�������Կ��ƿ������е�LED������
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
  /* ��ʼ�� enc28j60 ��MAC��ַ(�����ַ),�����������Ҫ����һ�� */
  enc28j60Init(mymac);

	/* PHY LED ����,LED����ָʾͨ�ŵ�״̬ */	
  enc28j60PhyWrite(PHLCON,0x476);	
	
	/* ��enc28j60�������ŵ�ʱ�������Ϊ��from 6.25MHz to 12.5MHz(�����̸�����NC,û�õ�) */	
  enc28j60clkout(2);    
  
	/* ��ʼ����̫�� IP �� */
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
      if(eth_type_is_ip_and_my_ip(Web_Buf,plen)==0) //������ǲ����ҵ�IP
      {
          continue;
      }      
      
      if(Web_Buf[IP_PROTO_P]==IP_PROTO_ICMP_V && Web_Buf[ICMP_TYPE_P]==ICMP_TYPE_ECHOREQUEST_V)
      {
          // a ping packet, let's send pong  DOS �µ� ping �����		 
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
              if (cmd==1)	           // �û�����
              {			
									//LED1(ON);
								
								Tos_TaskResume(3);
                  i=1;							 // ���� = 1
              }
              if (cmd==0)						 // �û�����
              {									
									//LED1(OFF);
								Tos_TaskStop(3);
                  i=0;							 // ���� = 0
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
/******************* (C) COPYRIGHT 2011 Ұ��Ƕ��ʽ���������� *****END OF FILE****/
