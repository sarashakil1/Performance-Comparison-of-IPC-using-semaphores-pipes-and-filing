#include <fcntl.h>//O_create,O_EXEC
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/shm.h>


#define n 50000

int main()
{

    int arr[50000];
    int fd;
    //char * myfifo = "/tmp/myfifo";

    fflush(stdin);
   mkfifo( "/tmp/myfifo", 0666);

    printf("\nWaiting for the other process\n");
    
    FILE *ff;
    ff = fopen("numbers.txt","r"); //open the file in which numbers are stored

    for (int c = 0 ; c < n  ; c++ )
  	{
        int num;
        fscanf(ff, "%d",&num);
        arr[c]=num;
  	}
    
  fd = open("/tmp/myfifo", O_WRONLY);
    
    write(fd,arr,sizeof(arr));  //writes the data
    
    close(fd);


    //unlink(myfifo);

    return 0;
}

