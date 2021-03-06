
asm("lui $29,0x2400");  //put your mips instructions here

#include <stdint.h>

int32_t getc();
void putc(int32_t );
int collatzsteps(int y );
int nextcollatz (int x);


// Put the entry-point function first
int entry() {
	int x = collatzsteps(12); //  Ans should should be 9
	return x;
}

int collatzsteps(int y ){		//number of steps
	int nextnum;
	int steps = 0;
	while (y!=1){
		nextnum = nextcollatz(y);
		y=nextnum;
		steps ++;
	}
	return steps;
}

int nextcollatz (int x){
	if (x%2==0){
		return x/2;
	}
	else{
		return x*3+1;
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

