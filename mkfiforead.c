#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>
#include<time.h>
#define n 50000

int main()
{
   int c,i,search,count;
   int pipe;
   int arr[50000];

    printf("enter n to search:\n");
    scanf("%d",&search);

    clock_t st = clock();

   
   // open a named pipe
   pipe = open("/tmp/myfifo", O_RDONLY);

   // actually read out the data and close the pipe
   read(pipe,arr,sizeof(arr));


// search algorithm starts

for ( c = 0 ; c < n ; c++ )
   {
      if ( arr[c] == search )    
      {
      	
         printf("%d is present at location %d.\n", search, c+1);
         count++;
      }
   }
   if ( count == 0 )
      printf("%d is not present in array.\n", search);
   else
      printf("%d is present %d times in array.\n", search, count);
       
clock_t et = clock();
clock_t ctt = et - st;
double tis = ctt / (double) CLOCKS_PER_SEC;




printf("\n\ntotal time is: %lf\n\n",tis);

    // close the pipe
   close(pipe);
   return 0;
}
