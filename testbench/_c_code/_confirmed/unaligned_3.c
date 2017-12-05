#include <stdint.h>


// Set sp to max memory address
asm("lui $29,0x2400");  

typedef struct{
	 int16_t Data0;		//2 Bytes
     int8_t  Data1;		//1 Byte
     int32_t Data2;		//4 Bytes
     int16_t Data3;		//2 Bytes
     int8_t  Data4;		//1 Byte
}__attribute__((packed, aligned(1))) unAlignedStruct;


int32_t getc();
void putc(int32_t );


int entry() {

  unAlignedStruct a = { .Data0 = 42858, .Data1 = 215, .Data2 = 3952748706, .Data3 = 39518, .Data4 = 98};

 int32_t x = 0;
 x = a.Data0 + a.Data1 + a.Data2 + a.Data3 + a.Data4;
 //x =;
 // l 8 bits = ;
  return x;
}