#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include<sys/shm.h>
#include<signal.h>
#include<sys/ipc.h>
int main()
{

 printf("reading and searching the data....\n");
 clock_t start;
 FILE *fptr,*fr;
 fptr=fopen("numbers.txt","r"); // opens the number file
 start=clock();   //time starts
 // Linear search algorithm starts
  int  c,search,count=0;
   printf("Enter the number to search\n");
   scanf("%d",&search);
	int iter = 0;
	for(c=0; fscanf(fptr, "%d", &iter) && !feof(fptr);c++)
	{
		if(iter==search)
	    {
        	printf("%d is present at %d location.\n",search,c+1);
        	count++;
      	     }
	}
	fclose(fptr);
   if(count==0)
      printf("%d is not present in the file.\n",search);
   else
      printf("%d is present %d times in the file.\n",search,count);
//Linear search algorithm ends
fr=fopen("shared.txt","w");
fprintf(fr,"The Entered number is found %d time\n",count);
fclose(fr);
printf("Searching Complete...\n");
clock_t endtime = clock();
clock_t totalclocktime=endtime- start;
double tis = totalclocktime/(double) CLOCKS_PER_SEC;
printf("\n\ntotal time is: %lf\n",tis);
//system("pkill fillingw");  //terminating by sending signal
}
