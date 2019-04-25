#ifndef  BASE_TYPE_H
#define  BASE_TYPE_H

typedef  unsigned char uchar8_t;
typedef  char  char8_t;
typedef  unsigned short uint16_t;
typedef  short int16_t;
typedef  unsigned int uint32_t;
typedef  int int32_t;
typedef  unsigned long  ulong64_t;
typedef  long long64_t;

const uint32_t MAX_MTU = 1500;          //设置最大MTU为1500

const int ETHER_DATA_MIN_SIZE = 28; //IP头长度 + UDP 长度

const int HTTP_PORT_NUMBER = 80;    //默认HTTP端口号


#endif
