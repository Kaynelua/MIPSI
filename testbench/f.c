#include <stdint.h>

int32_t getc();
void putc(int32_t );

// Put the entry-point function first

int entry() {
	//int32_t x=getc();
	//putc(x+1);
	int sum;
	int a = 5;
	for(int i=0;i<5;i++){
		sum = sum + a;
	}
	return sum;
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

