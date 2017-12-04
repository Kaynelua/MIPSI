#include <stdint.h>

int32_t getc();
void putc(int32_t );
int32_t factorial(int32_t x);
int32_t shell(int32_t x);

// Put the entry-point function first

asm("lui $29,0x2400");  //put your mips instructions here

int entry() {
	int32_t x = 4// 4 th element  getc();
	//putc(x+58);
	x = fibonacci(x);

	return x;
}


int32_t shell(int32_t x){
	return fibonacci(x);
}

int32_t fibonacci(int32_t x){
	if(x <= 1){
		return 0;
	}
	else if (x==2){
		return 1;
	}
	else{
		return fibonacci(x-2)+fibonacci(x-1);
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

