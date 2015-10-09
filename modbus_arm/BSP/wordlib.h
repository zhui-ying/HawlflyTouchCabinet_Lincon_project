#ifndef __WORDLIB_H_
#define __WORDLIB_H_

typedef struct wordCh{
unsigned char msk[24];//�����ģ��12*12
u8 index[3];//��ź��� 
}CHWORD;

typedef struct wordChar{
unsigned char msk[12];//�����ģ��12*6
u8 index[2];//����ַ� 
}ASCWORD;


u8 const noGood16[] = {
0xFE,0x02,0x02,0x02,0x02,0x02,0x02,0xFE,0x7F,0x40,0x40,0x40,0x40,0x40,0x40,0x7F
};

u8 const haveGood16[] ={
0xFE,0x02,0xF2,0xF2,0xF2,0xF2,0x02,0xFE,0x7F,0x40,0x4F,0x4F,0x4F,0x4F,0x40,0x7F
};

const CHWORD cha_code[]=
{
0x8C,0x00,0x45,0x00,0xF5,0x07,0x55,0x05,0x55,0x05,0xEF,0x07,0x45,0x05,0x55,0x05,
0x55,0x05,0x55,0x05,0x0C,0x04,0x00,0x00,"��",//0
0x02,0x04,0x02,0x04,0x7A,0x04,0x4A,0x02,0xCA,0x01,0x4F,0x00,0xCA,0x07,0x4A,0x04,
0x7A,0x04,0x02,0x04,0x02,0x07,0x00,0x00,"��",//1
0x08,0x00,0x06,0x00,0xCA,0x07,0x7A,0x05,0x6A,0x05,0xEB,0x07,0x6A,0x05,0x6A,0x05,
0x7A,0x05,0xCA,0x07,0x06,0x00,0x00,0x00,"��",//2
0x42,0x04,0x4A,0x04,0x5A,0x02,0x6F,0x01,0xCA,0x00,0xFE,0x07,0xCA,0x00,0x6F,0x01,
0x5A,0x02,0x4A,0x04,0x42,0x04,0x00,0x00,"��",//3
0x80,0x01,0x7F,0x00,0xE5,0x03,0x25,0x00,0xFD,0x07,0x25,0x02,0xE7,0x03,0x00,0x00,
0xFE,0x05,0x00,0x04,0xFF,0x07,0x00,0x00,"ˢ",//0
0x10,0x00,0x10,0x00,0x10,0x00,0x10,0x00,0xFF,0x07,0x52,0x00,0x52,0x00,0x92,0x00,
0x92,0x00,0x12,0x01,0x10,0x00,0x00,0x00,"��",//1
0x20,0x04,0x22,0x04,0x22,0x02,0xFE,0x01,0x22,0x00,0x22,0x00,0x22,0x00,0xFE,0x07,
0x22,0x00,0x23,0x00,0x22,0x00,0x00,0x00,"��",//0
0x24,0x01,0xA2,0x00,0xFB,0x07,0xA6,0x00,0x22,0x00,0xF4,0x07,0x52,0x05,0x53,0x05,
0x56,0x05,0xF2,0x07,0x02,0x00,0x00,0x00,"��",//19


0x10,0x04,0x11,0x04,0x11,0x02,0x91,0x01,0x71,0x00,0x1F,0x00,0xF1,0x07,0x11,0x04,
0x11,0x04,0x11,0x04,0x10,0x07,0x00,0x00,"��",//0
0x24,0x04,0x14,0x02,0x4D,0x01,0x86,0x00,0x6C,0x03,0x14,0x04,0x08,0x02,0x7F,0x01,
0x84,0x01,0x7C,0x02,0x04,0x04,0x00,0x00,"Ч",//1
0x40,0x04,0x48,0x04,0xA4,0x02,0xA2,0x05,0x97,0x04,0xEA,0x07,0x9A,0x00,0xA6,0x01,
0xA2,0x02,0x40,0x04,0x40,0x00,0x00,0x00,"��",//2
0x11,0x04,0x16,0x02,0xF0,0x01,0x04,0x02,0x14,0x04,0x64,0x04,0x04,0x05,0x04,0x05,
0xFF,0x05,0x04,0x04,0x04,0x04,0x00,0x00,"��",//3
0x82,0x04,0xFF,0x02,0xAA,0x01,0xAA,0x00,0xFF,0x01,0x82,0x02,0x00,0x04,0xFF,0x03,
0x49,0x00,0x49,0x04,0xFF,0x07,0x00,0x00,"��",//4
0x20,0x00,0x21,0x00,0x21,0x00,0x21,0x04,0x21,0x04,0xF9,0x07,0x29,0x00,0x25,0x00,
0x23,0x00,0x31,0x00,0x20,0x00,0x00,0x00,"��",//0
0x19,0x01,0xE2,0x07,0x14,0x00,0xEA,0x07,0x2A,0x01,0xFF,0x00,0xAA,0x02,0x2A,0x01,
0xFF,0x04,0x2A,0x05,0xEA,0x07,0x00,0x00,"��",//1
0x20,0x04,0x30,0x04,0x2E,0x02,0x24,0x01,0xA4,0x00,0x7F,0x00,0xA4,0x00,0x24,0x01,
0x24,0x02,0x24,0x04,0x20,0x04,0x00,0x00,"ʧ",//0
0xFF,0x04,0x01,0x03,0xFD,0x00,0x01,0x01,0xFF,0x02,0x10,0x04,0x7C,0x02,0x87,0x01,
0x84,0x01,0x7C,0x02,0x04,0x04,0x00,0x00,"��",//1
0x40,0x04,0x44,0x04,0x44,0x02,0x45,0x01,0xC6,0x00,0x7C,0x00,0xC4,0x00,0x46,0x01,
0x45,0x02,0x44,0x04,0x40,0x04,0x00,0x00,"��",//0
0x00,0x00,0xFC,0x07,0x11,0x01,0x92,0x00,0x50,0x02,0x31,0x02,0xFD,0x03,0x11,0x00,
0x11,0x04,0x01,0x04,0xFF,0x07,0x00,0x00,"��",//1
0x00,0x04,0x00,0x03,0xFE,0x00,0x0A,0x00,0xC9,0x07,0x49,0x02,0x49,0x02,0x49,0x02,
0x49,0x02,0xC9,0x07,0x08,0x00,0x00,0x00,"��",//0
0x82,0x00,0x42,0x00,0xF2,0x07,0x0A,0x00,0x4F,0x00,0x4A,0x04,0x4A,0x04,0xEA,0x07,
0x5A,0x00,0x4A,0x00,0x42,0x00,0x00,0x00,"��",//0
0x01,0x01,0xFF,0x01,0x29,0x01,0xA9,0x00,0xFF,0x07,0x81,0x04,0x7E,0x02,0x82,0x01,
0x42,0x01,0x3E,0x02,0x00,0x04,0x00,0x00,"ȡ",//1
0x10,0x00,0xF1,0x03,0x06,0x02,0x00,0x01,0x22,0x04,0x32,0x05,0xAE,0x02,0x63,0x02,
0x22,0x01,0x9A,0x02,0x42,0x04,0x00,0x00,"��",//0
0x20,0x02,0x24,0x02,0x24,0x01,0xA4,0x00,0x64,0x00,0xFF,0x07,0x64,0x00,0xA4,0x00,
0x26,0x01,0x24,0x02,0x20,0x02,0x00,0x00,"δ",//1
0x04,0x02,0xF4,0x02,0x54,0x02,0x54,0x01,0xF4,0x05,0x04,0x05,0x7F,0x02,0x84,0x01,
0x45,0x01,0x36,0x02,0x04,0x07,0x00,0x00,"��",//2
0x44,0x04,0x24,0x04,0xFF,0x07,0x14,0x00,0x26,0x04,0xE2,0x04,0x3A,0x05,0x23,0x03,
0xA2,0x01,0x62,0x02,0x26,0x04,0x00,0x00,"��",//0
0x4C,0x00,0xFB,0x07,0x4A,0x02,0xD2,0x04,0x1E,0x03,0xF2,0x02,0xAA,0x04,0xFF,0x07,
0xAA,0x04,0xBE,0x04,0x88,0x04,0x00,0x00,"��",//0
0x44,0x04,0x24,0x04,0xFF,0x07,0x14,0x00,0x00,0x04,0xF7,0x05,0x15,0x02,0xD5,0x01,
0x15,0x01,0x17,0x02,0xF0,0x05,0x00,0x00,"��",//0
0x08,0x01,0xFF,0x00,0x88,0x02,0x08,0x01,0x82,0x00,0x42,0x00,0x32,0x00,0xFE,0x07,
0x22,0x00,0x43,0x00,0x82,0x01,0x00,0x00,"��",//1
0xFE,0x07,0x00,0x00,0xFC,0x03,0x00,0x00,0xFF,0x0F,0x00,0x00,0xF9,0x09,0x0D,0x04,
0xEB,0x03,0x09,0x04,0xF9,0x09,0x00,0x00,"˳",//0
0x86,0x00,0xA2,0x00,0x92,0x0F,0xAE,0x05,0x4A,0x05,0x4B,0x05,0x4A,0x05,0xAA,0x05,
0x9A,0x0F,0x82,0x00,0x86,0x00,0x00,0x00,"��",//1
0xFE,0x0F,0x12,0x01,0xEE,0x00,0x00,0x09,0xD4,0x08,0x96,0x0A,0xAB,0x0A,0xEA,0x0F,
0xAA,0x0A,0x96,0x0A,0x90,0x08,0x00,0x00,"¡",//2
0x50,0x00,0x4C,0x01,0x53,0x02,0x64,0x05,0xC8,0x00,0x01,0x04,0xFD,0x02,0x07,0x01,
0xF5,0x01,0x05,0x02,0xFD,0x04,0x00,0x00,"��",//0
0xFC,0x04,0xAB,0x04,0xFA,0x02,0xAE,0x02,0xF8,0x02,0x85,0x00,0xA6,0x00,0xA4,0x00,
0xFE,0x07,0xA5,0x00,0xA4,0x00,0x00,0x00,"��",//1
0x00,0x00,0x00,0x00,0xFE,0x07,0x92,0x04,0x92,0x04,0x93,0x04,0x92,0x04,0x92,0x04,
0x92,0x04,0xFE,0x07,0x00,0x00,0x00,0x00,"��",//2
0x44,0x04,0x24,0x04,0xFF,0x07,0x14,0x04,0x40,0x02,0xDF,0x01,0x55,0x02,0xD5,0x07,
0x55,0x05,0x5F,0x05,0x40,0x04,0x00,0x00,"��",//3
0x82,0x04,0x9A,0x04,0xAA,0x02,0xCF,0x01,0x8A,0x00,0xFA,0x07,0x8F,0x00,0xCA,0x01,
0xBA,0x02,0x8A,0x04,0x82,0x04,0x00,0x00,"��",//4
0x02,0x02,0xFE,0x01,0x2A,0x01,0xFE,0x07,0x82,0x04,0x29,0x02,0x2A,0x01,0xFC,0x00,
0x2A,0x01,0x29,0x02,0x28,0x04,0x00,0x00,"��",//0
0x10,0x00,0xF8,0x07,0x16,0x04,0x91,0x04,0xF2,0x04,0x04,0x04,0x00,0x07,0xFC,0x00,
0x00,0x04,0x00,0x04,0xFF,0x07,0x00,0x00,"��",//1
0x10,0x00,0x10,0x00,0xF8,0x07,0xAC,0x04,0xAA,0x02,0xAD,0x02,0xAA,0x01,0xAC,0x02,
0xF8,0x05,0x10,0x04,0x10,0x00,0x00,0x00,"ʳ",//0
0x18,0x00,0xFF,0x07,0x08,0x00,0x10,0x00,0x08,0x00,0xFF,0x07,0x94,0x04,0x94,0x04,
0xFF,0x07,0x94,0x04,0x94,0x04,0x00,0x00,"Ω",//1
0x10,0x04,0x11,0x04,0x11,0x02,0x11,0x01,0xD1,0x00,0x3F,0x00,0xD1,0x00,0x11,0x01,
0x11,0x02,0x11,0x04,0x10,0x04,0x00,0x00,"��",//2
0x80,0x04,0x80,0x04,0xFE,0x04,0xAA,0x02,0x9B,0x01,0xFE,0x00,0x9A,0x01,0xAE,0x02,
0x8A,0x04,0xFE,0x04,0x80,0x04,0x00,0x00,"��",//0
0x10,0x04,0x11,0x04,0x11,0x02,0x11,0x01,0xD1,0x00,0x3F,0x00,0xD1,0x00,0x11,0x01,
0x11,0x02,0x11,0x04,0x10,0x04,0x00,0x00,"��",//1
0x08,0x01,0x8C,0x00,0x44,0x00,0xE4,0x07,0x14,0x04,0x0F,0x02,0x34,0x02,0xC4,0x00,
0x24,0x01,0x1C,0x02,0x00,0x02,0x00,0x00,"ũ",//2
0x08,0x03,0x08,0x01,0xFF,0x00,0x88,0x00,0x49,0x05,0x91,0x02,0x79,0x01,0x95,0x04,
0x73,0x04,0x11,0x06,0xF0,0x01,0x00,0x00,"��",//3
0x00,0x06,0xFE,0x01,0x02,0x00,0x02,0x00,0x02,0x00,0x03,0x00,0x02,0x00,0x02,0x00,
0x02,0x00,0x02,0x00,0x02,0x00,0x00,0x00,"��",//0
0x20,0x04,0x10,0x02,0xFF,0x01,0x00,0x00,0x10,0x00,0x20,0x00,0xFE,0x03,0x10,0x00,
0x20,0x00,0xFF,0x07,0x00,0x00,0x00,0x00,"��",//1
0x10,0x00,0x10,0x00,0x88,0x07,0x94,0x04,0x92,0x04,0x91,0x04,0x92,0x04,0x94,0x04,
0x88,0x07,0x10,0x00,0x10,0x00,0x00,0x00,"��",//2
0x82,0x04,0x92,0x02,0x92,0x01,0xFF,0x00,0x92,0x00,0x92,0x00,0x00,0x00,0xFF,0x07,
0x01,0x01,0x39,0x01,0xC7,0x01,0x00,0x00,"��",//3


0x80,0x00,0x00,0x01,0x00,0x03,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,"��",//0
0x00,0x00,0xFA,0x07,0x12,0x04,0x12,0x04,0x12,0x04,0x12,0x04,0x12,0x04,0x12,0x04,
0x1F,0x04,0x02,0x04,0x80,0x07,0x00,0x00,"��",//0
0x20,0x00,0x20,0x00,0x2F,0x00,0xE9,0x00,0xA9,0x00,0xA9,0x04,0xA9,0x04,0xA9,0x04,
0xAF,0x03,0x20,0x00,0x20,0x00,0x00,0x00,"��",//0
0x10,0x00,0xF1,0x07,0x02,0x02,0x00,0x01,0x2A,0x00,0xEA,0x07,0xAA,0x02,0xBF,0x02,
0xAA,0x02,0xEA,0x07,0x2A,0x00,0x00,0x00,"��",//1
0x34,0x01,0x2F,0x01,0xF4,0x07,0xA4,0x00,0xE8,0x07,0xA4,0x02,0xEA,0x07,0x09,0x00,
0xEA,0x01,0x04,0x04,0xE8,0x07,0x00,0x00,"��",//2
0x00,0x04,0x00,0x02,0x00,0x01,0xC1,0x00,0x31,0x00,0x0E,0x00,0x30,0x00,0xC0,0x00,
0x00,0x01,0x00,0x02,0x00,0x04,0x00,0x00,"��",//3
0x1C,0x00,0x0A,0x00,0xEB,0x07,0xAE,0x04,0xAA,0x04,0xAC,0x04,0xAA,0x04,0xEB,0x04,
0x8E,0x07,0x0A,0x00,0x1A,0x00,0x00,0x00,"��",//4
0x12,0x02,0x12,0x02,0xFE,0x01,0x12,0x05,0x3F,0x04,0xA5,0x04,0xA5,0x04,0xFF,0x07,
0xA5,0x04,0xA5,0x04,0x3F,0x04,0x00,0x00,"��",//5
0x00,0x04,0x00,0x04,0xF7,0x05,0x15,0x04,0x15,0x02,0xD5,0x01,0x15,0x01,0x15,0x02,
0x17,0x04,0xF0,0x05,0x00,0x00,0x00,0x00,"Ա",//6
0x44,0x00,0x56,0x00,0x4A,0x07,0x3A,0x04,0x62,0x04,0x57,0x07,0x4A,0x04,0x76,0x04,
0x02,0x04,0x12,0x07,0x26,0x00,0x00,0x00,"��",//7
0x21,0x00,0xFF,0x03,0x11,0x01,0xF1,0x03,0x80,0x00,0xA1,0x00,0xBD,0x00,0xA1,0x04,
0xA1,0x04,0x3F,0x04,0xE0,0x03,0x00,0x00,"��",//8
0x58,0x00,0xF7,0x07,0x54,0x02,0x40,0x01,0x14,0x00,0xD4,0x07,0x5F,0x05,0x54,0x05,
0x5F,0x05,0xD4,0x07,0x14,0x00,0x00,0x00,"��",//9
0x10,0x00,0xF1,0x07,0x06,0x02,0x80,0x05,0xA0,0x04,0xAF,0x02,0xA9,0x01,0xE9,0x00,
0xA9,0x01,0xAF,0x02,0xA0,0x04,0x00,0x00,"��",//10
0x04,0x04,0x05,0x05,0xF5,0x05,0x55,0x05,0x55,0x05,0xFF,0x07,0x55,0x05,0x55,0x05,
0xF5,0x05,0x05,0x05,0x04,0x04,0x00,0x00,"��",//11
0x52,0x02,0xD6,0x01,0x5A,0x04,0xF3,0x07,0xDE,0x00,0x52,0x05,0x00,0x02,0xFE,0x01,
0x12,0x00,0xF1,0x07,0x11,0x00,0x00,0x00,"��",//12
0x81,0x00,0x81,0x00,0xFD,0x07,0xA5,0x00,0xA5,0x00,0xFF,0x00,0xA5,0x00,0xA5,0x04,
0xA5,0x04,0xFD,0x07,0x81,0x00,0x00,0x00,"��",//13
0x81,0x00,0xC2,0x07,0x34,0x00,0x00,0x04,0x10,0x02,0x0C,0x01,0xF7,0x00,0x84,0x00,
0x04,0x01,0x14,0x02,0x0C,0x04,0x00,0x00,"��",//14
0x10,0x00,0xFC,0x07,0x03,0x00,0xFC,0x01,0x28,0x04,0xA4,0x04,0x57,0x05,0xAA,0x02,
0x56,0x02,0x22,0x01,0x20,0x00,0x00,0x00,"��",//15
0xF1,0x03,0x11,0x02,0x11,0x02,0x1F,0x01,0x20,0x05,0x18,0x04,0x67,0x02,0x82,0x01,
0x42,0x01,0x3E,0x02,0x02,0x04,0x00,0x00,"��",//16
0x00,0x04,0xFC,0x03,0x24,0x01,0x24,0x02,0xE4,0x01,0x04,0x04,0x7F,0x02,0x84,0x01,
0x45,0x02,0x36,0x04,0x04,0x07,0x00,0x00,"��",//17
0x02,0x01,0x02,0x01,0xFE,0x00,0x82,0x04,0x82,0x04,0x08,0x02,0x88,0x01,0x7F,0x04,
0x08,0x04,0x08,0x04,0xF8,0x03,0x00,0x00,"��",//18
0x00,0x00,0xFC,0x07,0x01,0x00,0x06,0x00,0x00,0x00,0x02,0x00,0x02,0x00,0x02,0x00,
0x02,0x04,0x02,0x04,0xFE,0x07,0x00,0x00,"��",//20
0xA5,0x04,0x96,0x05,0xCC,0x02,0xBF,0x02,0x96,0x03,0xA5,0x04,0x18,0x04,0x67,0x02,
0x84,0x01,0x7C,0x02,0x04,0x04,0x00,0x00,"��",//21
0x04,0x02,0x75,0x02,0x86,0x01,0x74,0x01,0x04,0x01,0xC0,0x07,0x40,0x02,0x7F,0x02,
0x44,0x02,0xC4,0x07,0x04,0x00,0x00,0x00,"վ",//22
0x00,0x06,0xFF,0x01,0x49,0x00,0x49,0x00,0x49,0x00,0xFF,0x07,0x49,0x00,0x49,0x04,
0x49,0x04,0xFF,0x07,0x00,0x00,0x00,0x00,"��",//0
0x00,0x04,0x00,0x03,0xFE,0x00,0x22,0x00,0x22,0x00,0x22,0x00,0x23,0x00,0x22,0x00,
0x22,0x00,0x3E,0x00,0x00,0x00,0x00,0x00,"��",//1
0x10,0x00,0x11,0x00,0xF2,0x03,0x20,0x05,0x10,0x04,0x6F,0x04,0xA1,0x02,0x21,0x01,
0xAF,0x02,0x68,0x04,0x08,0x04,0x00,0x00,"��",//2
0x10,0x04,0x17,0x04,0xF5,0x07,0x55,0x05,0x57,0x05,0x5D,0x05,0x57,0x05,0x55,0x05,
0xF5,0x07,0x17,0x04,0x10,0x04,0x00,0x00,"��",//3
0xC4,0x00,0x34,0x00,0xFF,0x07,0x24,0x00,0x01,0x05,0x7D,0x05,0x57,0x03,0xD5,0x01,
0x57,0x03,0x7D,0x05,0x01,0x05,0x00,0x00,"ģ",//4
0x24,0x04,0x24,0x04,0x24,0x04,0xE4,0x03,0x24,0x02,0x24,0x02,0x7F,0x00,0x84,0x01,
0x05,0x02,0x06,0x04,0x04,0x07,0x00,0x00,"ʽ",//5
0x74,0x03,0x85,0x01,0x76,0x01,0x04,0x01,0xD6,0x07,0x54,0x00,0xF4,0x03,0x57,0x00,
0xD4,0x03,0x54,0x04,0xD6,0x07,0x00,0x00,"��",//6
0x00,0x00,0xFE,0x03,0x02,0x01,0x02,0x01,0x02,0x01,0x02,0x01,0x02,0x01,0x02,0x01,
0x02,0x01,0xFE,0x03,0x00,0x00,0x00,0x00,"��",//7
0x00,0x04,0x02,0x02,0x4A,0x01,0xCA,0x04,0x6E,0x04,0xDA,0x07,0x49,0x00,0xC9,0x00,
0x65,0x01,0x41,0x02,0x00,0x04,0x00,0x00,"ϵ",//8
0x48,0x02,0x6C,0x02,0x5B,0x01,0x4C,0x05,0x00,0x04,0x32,0x02,0xEA,0x01,0x27,0x00,
0xE2,0x07,0x32,0x04,0x22,0x07,0x00,0x00,"ͳ",//9
0xFE,0x03,0x22,0x01,0x22,0x01,0xFE,0x03,0x04,0x00,0x14,0x00,0x64,0x04,0x04,0x04,
0xFF,0x07,0x04,0x00,0x04,0x00,0x00,0x00,"ʱ",//10
0xFC,0x07,0x01,0x00,0x02,0x00,0xF8,0x01,0x29,0x01,0x29,0x01,0x29,0x01,0xF9,0x01,
0x01,0x04,0xFF,0x07,0x00,0x00,0x00,0x00,"��",//11
0x22,0x04,0x22,0x04,0xF2,0x05,0x5A,0x05,0x56,0x05,0x5F,0x05,0x52,0x05,0x56,0x05,
0xFA,0x05,0x12,0x04,0x22,0x04,0x00,0x00,"��",//12
0x10,0x00,0xF1,0x03,0x02,0x02,0x08,0x01,0x04,0x00,0xFB,0x01,0x4A,0x01,0x4A,0x05,
0xFA,0x05,0x02,0x04,0xFE,0x03,0x00,0x00,"ѯ",//13
0x10,0x00,0x08,0x00,0xFE,0x07,0x01,0x04,0x7A,0x04,0xCA,0x02,0x4A,0x01,0xFF,0x02,
0x4A,0x04,0x4A,0x04,0x7A,0x04,0x00,0x00,"ʹ",//14
0x00,0x06,0xFF,0x01,0x49,0x00,0x49,0x00,0x49,0x00,0xFF,0x07,0x49,0x00,0x49,0x04,
0x49,0x04,0xFF,0x07,0x00,0x00,0x00,0x00,"��",//15
0x10,0x00,0x11,0x00,0xF6,0x07,0x00,0x02,0x00,0x01,0xF2,0x07,0x22,0x04,0x22,0x04,
0x22,0x04,0x3F,0x04,0x02,0x07,0x00,0x00,"��",//16
0x10,0x02,0x11,0x02,0x35,0x01,0x55,0x05,0x95,0x04,0xF5,0x07,0x55,0x00,0x95,0x00,
0x5F,0x01,0x30,0x02,0x10,0x02,0x00,0x00,"¼",//17
0x1C,0x00,0xFF,0x07,0x08,0x00,0x82,0x04,0x62,0x04,0x1F,0x02,0x42,0x01,0xFA,0x00,
0x42,0x01,0x22,0x02,0x12,0x04,0x00,0x00,"��",//18
0x08,0x04,0x04,0x05,0x3E,0x05,0xEB,0x04,0xAA,0x05,0xAA,0x02,0xAA,0x02,0xAA,0x05,
0xBE,0x04,0x03,0x04,0x02,0x04,0x00,0x00,"��",//19
0x00,0x00,0xDE,0x07,0x10,0x04,0x10,0x04,0x10,0x04,0xFF,0x07,0x10,0x04,0x10,0x04,
0x10,0x04,0xDE,0x07,0x00,0x00,0x00,0x00,"��",//20
0x00,0x06,0xFF,0x01,0x01,0x00,0x01,0x00,0x01,0x00,0x01,0x00,0x01,0x00,0x01,0x00,
0x01,0x00,0x01,0x00,0x01,0x00,0x00,0x00,"��",//21
0x11,0x06,0xF6,0x01,0x00,0x02,0x00,0x02,0xFF,0x05,0x15,0x05,0x55,0x05,0x55,0x04,
0x95,0x04,0x5F,0x05,0x00,0x04,0x00,0x00,"��",//22
0x00,0x00,0xDE,0x07,0x10,0x04,0x10,0x04,0x10,0x04,0xFF,0x07,0x10,0x04,0x10,0x04,
0x10,0x04,0xDE,0x07,0x00,0x00,0x00,0x00,"��",//23
0x31,0x01,0xC6,0x07,0x30,0x00,0x04,0x04,0x44,0x04,0x45,0x04,0xFE,0x07,0x44,0x04,
0x44,0x04,0x46,0x04,0x04,0x04,0x00,0x00,"ע",//24
0x10,0x04,0xFF,0x03,0x11,0x00,0x11,0x04,0xFF,0x07,0x10,0x04,0xFF,0x03,0x11,0x04,
0x11,0x04,0xFF,0x07,0x10,0x00,0x00,0x00,"��",//25
0x58,0x00,0x57,0x00,0xF4,0x07,0x54,0x02,0x00,0x00,0xFE,0x07,0xA8,0x00,0xAF,0x00,
0xA8,0x04,0xAC,0x04,0xFA,0x07,0x00,0x00,"��",//26
0x44,0x04,0x44,0x04,0xFF,0x07,0x24,0x00,0x00,0x00,0xDF,0x07,0x54,0x05,0x54,0x05,
0x52,0x05,0xD2,0x07,0x1C,0x00,0x00,0x00,"ָ",//27
0x04,0x04,0x16,0x02,0xD2,0x01,0x12,0x01,0x12,0x02,0xF3,0x03,0x92,0x04,0x92,0x04,
0x92,0x04,0x92,0x04,0x06,0x04,0x00,0x00,"��",//28
0x09,0x01,0xD2,0x07,0x20,0x00,0x22,0x00,0xEA,0x07,0xAA,0x02,0xBF,0x02,0xAA,0x02,
0xAA,0x02,0xEA,0x07,0x22,0x00,0x00,0x00,"��",//29
0xFF,0x07,0x81,0x00,0x9D,0x00,0xE3,0x04,0x48,0x02,0x54,0x01,0x52,0x04,0xF1,0x07,
0x52,0x00,0x54,0x01,0x48,0x06,0x00,0x00,"��",//30
0x58,0x00,0xF7,0x03,0x54,0x02,0x54,0x05,0x00,0x04,0xFE,0x04,0x08,0x02,0xEF,0x01,
0x0C,0x02,0xFA,0x02,0x00,0x04,0x00,0x00,"��",//31
0x00,0x04,0x02,0x04,0x02,0x04,0x02,0x04,0x02,0x04,0xFE,0x07,0x02,0x04,0x02,0x04,
0x03,0x04,0x02,0x04,0x00,0x04,0x00,0x00,"��",//0
0x10,0x00,0x08,0x00,0xFC,0x07,0x13,0x00,0x08,0x00,0x04,0x00,0xFF,0x07,0x24,0x01,
0x24,0x01,0x24,0x01,0x04,0x01,0x00,0x00,"��",//1
0x10,0x04,0x10,0x05,0xFF,0x05,0x55,0x05,0x55,0x05,0xF5,0x07,0x55,0x05,0x55,0x05,
0xFF,0x05,0x10,0x05,0x10,0x04,0x00,0x00,"��",//0
0x44,0x04,0x44,0x04,0xFF,0x07,0x24,0x00,0x24,0x00,0x02,0x00,0x02,0x04,0x02,0x04,
0xFE,0x07,0x02,0x00,0x02,0x00,0x00,0x00,"��",//1
0x00,0x06,0xFE,0x01,0x4A,0x00,0x49,0x04,0x79,0x02,0x80,0x01,0x7E,0x00,0x12,0x00,
0x12,0x00,0xF1,0x07,0x11,0x00,0x00,0x00,"��",//2
0x42,0x00,0x22,0x00,0x12,0x00,0xFA,0x07,0x4E,0x01,0x4B,0x01,0x4A,0x01,0x4A,0x05,
0xFA,0x07,0x02,0x00,0x02,0x00,0x00,0x00,"��",//3
0x08,0x06,0xFE,0x01,0xAB,0x00,0xFE,0x07,0xAA,0x04,0xF8,0x07,0xAA,0x00,0xA6,0x00,
0xFA,0x07,0xAA,0x00,0xAE,0x00,0x00,0x00,"��",//4
0x44,0x00,0x24,0x00,0xF7,0x07,0x2C,0x00,0x50,0x04,0x02,0x02,0xC2,0x01,0x3E,0x04,
0x02,0x04,0x02,0x06,0xFE,0x01,0x00,0x00,"��",//1
0x84,0x04,0xFC,0x02,0x07,0x01,0xFC,0x01,0x04,0x02,0x18,0x00,0xD4,0x07,0x53,0x02,
0x50,0x02,0x54,0x02,0xD8,0x07,0x00,0x00,"ʼ",//2
0x20,0x00,0x10,0x00,0xFC,0x07,0x83,0x00,0x80,0x00,0x40,0x00,0xFF,0x07,0x20,0x04,
0x10,0x04,0x0C,0x04,0x00,0x07,0x00,0x00,"��",//3
0x00,0x00,0x7C,0x00,0x44,0x00,0x44,0x00,0x44,0x00,0xFF,0x07,0x44,0x00,0x44,0x00,
0x44,0x00,0x7C,0x00,0x00,0x00,0x00,0x00,"��",//0
0x00,0x00,0x0C,0x00,0x0E,0x00,0x02,0x00,0x62,0x03,0x72,0x03,0x1E,0x00,0x0C,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,"��",//0
0x46,0x04,0x42,0x04,0x4A,0x02,0xCA,0x01,0x4A,0x00,0x4B,0x00,0xCA,0x07,0x4A,0x04,
0x4A,0x04,0x42,0x04,0x46,0x07,0x00,0x00,"��",//1
0x00,0x04,0xF8,0x07,0x00,0x02,0xFF,0x03,0x10,0x01,0x10,0x01,0x00,0x00,0xFF,0x07,
0x10,0x04,0x08,0x04,0x04,0x07,0x00,0x00,"��",//0
0x08,0x01,0xD1,0x07,0x3A,0x00,0x00,0x04,0x30,0x04,0xEF,0x02,0x21,0x01,0x21,0x01,
0xEF,0x02,0x10,0x04,0x10,0x04,0x00,0x00,"û",//1

0x20,0x00,0x10,0x00,0xFC,0x0F,0x03,0x00,0x08,0x00,0x07,0x00,0xFC,0x0F,0x24,0x01,
0x24,0x01,0x24,0x01,0x04,0x01,0x00,0x00,"��",//0
0x90,0x00,0x94,0x00,0xD4,0x0F,0x54,0x05,0x74,0x05,0x5F,0x05,0x54,0x05,0x5C,0x05,
0x54,0x05,0xD2,0x0F,0x10,0x00,0x00,0x00,"��",//1
0x00,0x08,0xFE,0x07,0x90,0x00,0x9F,0x0F,0x10,0x04,0xFE,0x03,0x12,0x08,0xF2,0x05,
0x12,0x02,0x91,0x05,0x71,0x08,0x00,0x00,"��",//2
0x04,0x02,0x04,0x01,0x84,0x02,0x64,0x02,0x14,0x02,0xFF,0x0F,0x14,0x02,0x64,0x02,
0x84,0x02,0x04,0x01,0x04,0x02,0x00,0x00,"��",//3
0x10,0x08,0x92,0x0F,0x12,0x08,0xF2,0x07,0x92,0x04,0x92,0x04,0x10,0x00,0xFF,0x00,
0x10,0x03,0x12,0x04,0x14,0x0E,0x00,0x00,"��",//4
0x11,0x04,0x22,0x02,0x00,0x09,0x02,0x08,0x3E,0x04,0xC2,0x02,0x02,0x01,0x82,0x02,
0x62,0x04,0x1E,0x08,0x00,0x08,0x00,0x00,"��",//5


0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,"\0",
};

const ASCWORD  asc_code[]=
{
0xF8,0x01,0x04,0x02,0x04,0x02,0x04,0x02,0xF8,0x01,0x00,0x00,"0",//0
0x00,0x00,0x08,0x02,0xFC,0x03,0x00,0x02,0x00,0x00,0x00,0x00,"1",//1
0x18,0x03,0x84,0x02,0x44,0x02,0x24,0x02,0x18,0x02,0x00,0x00,"2",//2
0x08,0x01,0x04,0x02,0x24,0x02,0x24,0x02,0xD8,0x01,0x00,0x00,"3",//3
0x40,0x00,0xB0,0x00,0x88,0x00,0xFC,0x03,0x80,0x02,0x00,0x00,"4",//4
0x3C,0x01,0x24,0x02,0x24,0x02,0x24,0x02,0xC4,0x01,0x00,0x00,"5",//5
0xF8,0x01,0x24,0x02,0x24,0x02,0x2C,0x02,0xC0,0x01,0x00,0x00,"6",//6
0x0C,0x00,0x04,0x00,0xE4,0x03,0x1C,0x00,0x04,0x00,0x00,0x00,"7",//7
0xD8,0x01,0x24,0x02,0x24,0x02,0x24,0x02,0xD8,0x01,0x00,0x00,"8",//8
0x38,0x00,0x44,0x03,0x44,0x02,0x44,0x02,0xF8,0x01,0x00,0x00,"9",//9

0x00,0x08,0x00,0x06,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,",",//0
0x00,0x00,0x00,0x02,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,".",//1
0x00,0x04,0x80,0x03,0x60,0x00,0x1C,0x00,0x02,0x00,0x00,0x00,"/",//2
0x00,0x00,0x0E,0x00,0x30,0x00,0xC0,0x01,0x00,0x02,0x00,0x00,"\\",//3
0x00,0x00,0x0C,0x00,0x02,0x00,0x0C,0x00,0x02,0x00,0x00,0x00,"\"",//4
0x00,0x00,0x00,0x00,0x10,0x02,0x00,0x00,0x00,0x00,0x00,0x00,":",//5
0x00,0x00,0x00,0x00,0x20,0x00,0xDE,0x07,0x02,0x04,0x00,0x00,"{",//6
0x00,0x00,0x02,0x04,0xDE,0x07,0x20,0x00,0x00,0x00,0x00,0x00,"}",//7
0x20,0x00,0x20,0x00,0xFC,0x01,0x20,0x00,0x20,0x00,0x00,0x00,"+",//8
0x20,0x00,0x20,0x00,0x20,0x00,0x20,0x00,0x20,0x00,0x00,0x00,"-",//9
0x00,0x08,0x00,0x08,0x00,0x08,0x00,0x08,0x00,0x08,0x00,0x08,"_",//10
0x00,0x00,0x00,0x00,0x00,0x00,0xF8,0x01,0x04,0x02,0x02,0x04,"(",//11
0x00,0x00,0x02,0x04,0x04,0x02,0xF8,0x01,0x00,0x00,0x00,0x00,")",//12
0x90,0x00,0x60,0x00,0xF8,0x01,0x60,0x00,0x90,0x00,0x00,0x00,"*",//13
0x02,0x00,0x01,0x00,0x02,0x00,0x04,0x00,0x04,0x00,0x02,0x00,"~",//14
0x00,0x00,0x00,0x00,0xFC,0x02,0x00,0x00,0x00,0x00,0x00,0x00,"!",//15
0x90,0x00,0xD0,0x03,0xBC,0x00,0xD0,0x03,0xBC,0x00,0x90,0x00,"#",//16
0x18,0x00,0x24,0x03,0xD8,0x00,0xB0,0x01,0x4C,0x02,0x80,0x01,"%",//17
0x0C,0x00,0x04,0x02,0xFC,0x03,0x04,0x02,0x0C,0x00,0x00,0x00,"T",//0
0x08,0x00,0x06,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,"'",//0


0x00,0x00,0xC0,0x01,0x20,0x02,0x20,0x0A,0xE0,0x0F,0x00,0x08,"q",//0
0x60,0x00,0x80,0x03,0xE0,0x00,0x80,0x03,0x60,0x00,0x00,0x00,"w",//1
0x00,0x00,0xC0,0x01,0xA0,0x02,0xA0,0x02,0xC0,0x02,0x00,0x00,"e",//2
0x20,0x02,0xE0,0x03,0x40,0x02,0x20,0x00,0x20,0x00,0x00,0x00,"r",//3
0x00,0x00,0x20,0x00,0xF8,0x01,0x20,0x02,0x00,0x02,0x00,0x00,"t",//4
0x20,0x08,0xE0,0x08,0x20,0x07,0x80,0x01,0x60,0x00,0x20,0x00,"y",//5
0x20,0x00,0xE0,0x01,0x00,0x02,0x20,0x02,0xE0,0x03,0x00,0x02,"u",//6
0x00,0x00,0x20,0x02,0xE4,0x03,0x00,0x02,0x00,0x00,0x00,0x00,"i",//7
0x00,0x00,0xC0,0x01,0x20,0x02,0x20,0x02,0xC0,0x01,0x00,0x00,"o",//8
0x20,0x08,0xE0,0x0F,0x20,0x0A,0x20,0x02,0xC0,0x01,0x00,0x00,"p",//9
0x00,0x00,0x40,0x01,0xA0,0x02,0xA0,0x02,0xC0,0x03,0x00,0x02,"a",//10
0x00,0x00,0x60,0x02,0xA0,0x02,0xA0,0x02,0x20,0x03,0x00,0x00,"s",//11
0x00,0x00,0xC0,0x01,0x20,0x02,0x24,0x02,0xFC,0x03,0x00,0x02,"d",//12
0x00,0x00,0x20,0x02,0xF8,0x03,0x24,0x02,0x24,0x02,0x04,0x00,"f",//13
0x00,0x00,0x40,0x07,0xA0,0x0A,0xA0,0x0A,0x60,0x0A,0x20,0x04,"g",//14
0x04,0x02,0xFC,0x03,0x20,0x02,0x20,0x00,0xC0,0x03,0x00,0x02,"h",//15
0x00,0x08,0x00,0x08,0x20,0x08,0xE4,0x07,0x00,0x00,0x00,0x00,"j",//16
0x04,0x02,0xFC,0x03,0x80,0x02,0xE0,0x00,0x20,0x03,0x20,0x02,"k",//17
0x04,0x02,0x04,0x02,0xFC,0x03,0x00,0x02,0x00,0x02,0x00,0x00,"l",//18
0x00,0x00,0x20,0x02,0xA0,0x03,0x60,0x02,0x20,0x02,0x00,0x00,"z",//19
0x20,0x02,0x60,0x03,0x80,0x00,0x60,0x03,0x20,0x02,0x00,0x00,"x",//20
0x00,0x00,0xC0,0x01,0x20,0x02,0x20,0x02,0x60,0x02,0x00,0x00,"c",//21
0x20,0x00,0xE0,0x00,0x20,0x03,0x80,0x01,0x60,0x00,0x20,0x00,"v",//22
0x04,0x00,0xFC,0x03,0x20,0x02,0x20,0x02,0xC0,0x01,0x00,0x00,"b",//23
0x20,0x02,0xE0,0x03,0x20,0x02,0x20,0x00,0xC0,0x03,0x00,0x02,"n",//24
0xE0,0x03,0x20,0x00,0xE0,0x03,0x20,0x00,0xC0,0x03,0x00,0x00,"m",//25

0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,"\0",
};

#endif
