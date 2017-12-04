#include <stdint.h>

int32_t getc();
void putc(int32_t );
int32_t factorial(int32_t x);
int32_t shell(int32_t x);

// Put the entry-point function first

asm("lui $29,0x2400");  //put your mips instructions here

int entry() {
	int32_t x = 0;//= getc();
	//putc(x+58);
	x = euclidean(1071,462);

	return x;
}


int32_t shell(int32_t x){
	return euclidean(1071,462);	// fixed o/p = 21
}

int32_t euclidean(int32_t a, int32_t b){
	if (b == 0){
       		return a;
	} 
    	else {
	       return euclidean(b, a mod b);
	}
}



int32_t getc() {
  volatile int32_t *p=(int32_t *) 0x30000000;
  return *p;
}

void putc(int x)
{
  volatile int32_t *p=(int32_t *) 0x30000004;
  *p = x;
}

