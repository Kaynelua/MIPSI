#include <stdint.h>

int32_t getc();
void putc(int32_t );
int32_t factorial(int32_t x);
int32_t shell(int32_t x);

// Put the entry-point function first

asm("lui $29,0x2400");  //put your mips instructions here

int entry() {
	int32_t x = getc();
	//putc(x+58);
	x = shell(x);

	return x;
}


int32_t shell(int32_t x){
	return factorial(x);
}

int32_t factorial(int32_t x){
	if(x == 0){
		return 1;
	}
	else{
		return x*factorial(x-1);
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

