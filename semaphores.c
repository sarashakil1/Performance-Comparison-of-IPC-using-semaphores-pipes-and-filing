#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <sys/ipc.h>
#include <semaphore.h>

sem_t mutex;
int arr[50000],n=50000;

int count = 0;

struct st{
 int start,end,num,search;
};


void func(void *ptr)
{
       FILE *fptr;
    fptr=fopen("numbers.txt","r");
     for(int c=0;c<n;c++)
      {
        fscanf(fptr,"%d",&arr[c]);

       }


    struct st x=*(struct st *)ptr;
     printf("\nSem[info]:Thread %d is waiting to be executing\n",x.num);

    //critical section starting
     sem_wait(&mutex);
      //linear search starts

        for(int c=x.start ; c<=x.end ;c++)
         {
          if(arr[c]==x.search)
          {
             printf("%d is present at location:%d\n",x.search,c+1);
		count++;
          }
        }
     sem_post(&mutex);

	printf("num: %d, count: %d\n",x.num,count);
        if(x.num==1){
		 if(count==0)
          	  printf("%d is not present\n",x.search);
       		else
          	printf("%d is present %d times\n",x.search,count);

         }

//linear search ends

}


int main()
{
  sem_init(&mutex,0,1);
  pthread_t threada,threadb;
  int s;
  

   struct st first,second;
    first.start=0;
    first.end=n/2;
    first.num=0;
    second.num=1;
    second.start=((n/2)+1);
    second.end=n;
     printf("Enter the number to search\n");
        scanf("%d",&s);
       second.search=first.search=s;
      clock_t start=clock();
 

      pthread_create(&threada,0,(void *)func,(void *)&first);
      pthread_create(&threadb,0,(void *)func,(void *)&second);
      pthread_join(threada,NULL);
      pthread_join(threadb,NULL);


        clock_t endt=clock();
        clock_t ctotaltime=endt-start;
        double finalt=ctotaltime/(double)CLOCKS_PER_SEC;
        printf("\ntotal time for searching is: %lf\n\n",finalt);



 return 0;
}
