#include <stdint.h>


// Set sp to max memory address
asm("lui $29,0x2400");  

int32_t getc();
void putc(int32_t );
int binarySearch(int arr[], int l, int r, int x);





const int arr[] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20};


// Put the entry-point function first
int entry() {

  //= {1,2,3,4,5,10,11,12,13}; 
  int32_t x;
  int32_t n = sizeof(arr)/ sizeof(arr[0]);

  x = binarySearch(arr, 0, n-1, 16);
  return x;
}




int binarySearch(int arr[], int l, int r, int x)
{
   if (r >= l)
   {
        int mid = l + (r - l)/2;
        // If the element is present at the middle itself
        if (arr[mid] == x)  return mid;
        // If element is smaller than mid, then it can only be present
        // in left subarray
        if (arr[mid] > x) return binarySearch(arr, l, mid-1, x);
        // Else the element can only be present in right subarray
        return binarySearch(arr, mid+1, r, x);
   }
 
   // We reach here when element is not present in array
   return -1;
}

