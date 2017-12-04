#include <stdint.h>


// Set sp to max memory address
asm("lui $29,0x2400");  

int32_t getc();
void putc(int32_t );
int looparray(char arr[], int n, char x);








// Put the entry-point function first
int entry() {

  char arr[10000];
  for(int i =0;i<10000;i++){
    arr[i] = i%255;
  }
  //= {1,2,3,4,5,10,11,12,13}; 
  int32_t x;
  int32_t n = sizeof(arr)/ sizeof(arr[0]);

  x = looparray(arr, n, 5);
  return x;
}




int looparray(char arr[], int n, char x)
{
    for(int i =0; i < n;i++){
      if(arr[i] == x){
        return i;
      }
    }
    return -1;
}

