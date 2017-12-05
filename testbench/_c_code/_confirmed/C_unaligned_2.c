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
int returnData(int n, unAlignedStruct a);


int entry() {

  unAlignedStruct a = { .Data0 = 42858, .Data1 = 215, .Data2 = 3952748706, .Data3 = 39518, .Data4 = 98 };

  int32_t x = 0;
  for(int i =0;i<5;i++){
  	x = x + returnData(i,a);
  }
  // x = 3952831395
  // lower 8 bits = d'163

  return x;
}



int returnData(int n, unAlignedStruct a){
	if(n == 0){
		return a.Data0;
	}
	else if(n == 1){
		return a.Data1;
	}
	else if(n == 2){
		return a.Data2;
	}
	else if(n == 3){
		return a.Data3;
	}
	else{
		return a.Data4;
	}

}