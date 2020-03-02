//Program to create multiple Producers and Consumers. Producers will fill an array of 25 items and consumers will consume it.
//Finally it will show which producer is the winner (which produces more elements in the array)
#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<unistd.h>
#include<string.h>
#include<time.h>

int nitems=25,count[7],count1[2],c[7],c2[7];
int buff[25],n=25;
void *produce(void *);
void *consume(void *);
int j=0;
struct{
	pthread_mutex_t mutex;
	int Xbuffer[25];
	int nput;
}shared={PTHREAD_MUTEX_INITIALIZER};  //structure for mutex and shared buffer

int main(void)
{
	int i,nthreads,x,d;
	pthread_t tid_produce[7], tid_consume[2], tid_consume2; //declaring thread id’s
	nthreads=7;
	srand(time(0));  //setting seed for random number generator
	for(i=0;i<nitems;i++)
		shared.Xbuffer[i]=-1;   //assigning -1 value to all shared buffer index intial
	printf("\n Shared buffer in the beginning");
	for(i=0;i<nitems;i++)
	{	
		printf("  %d", shared.Xbuffer[i]);
	}
	for(i=0;i<7;i++)
	{
		count[i]=i;    //creating 7 producer thread  
		pthread_create(&tid_produce[i], NULL, &produce, &count[i]);
	}
	
	for(i=0;i<7;i++)
	{ 	//waiting for producers to terminate
		pthread_join(tid_produce[i],NULL);
	}
	for(i=0;i<2;i++)
	{
		count1[i]=i;			//creating 2 consumer thread
		pthread_create(&tid_consume[i], NULL, &consume, &count1[i]);
	}
	
	for(i=0;i<2;i++)
	{
		pthread_join (tid_consume[i], NULL);
	}
	x=c[0];printf("\n");
	for(i=0;i<7;i++)
	{	
		printf("\n P%d produced %2d elements in buffer",i,c[i]);
		if (c[i] >x)         /*comparing the values in an array to find out which producer produces more elements */
		x=c[i];
	}
	for(i=0;i<7;i++) //loop to find index of big number in array
	{
		if(x==c[i])
    {
		  d=i; break;
		}	
	}
	printf("\n C1 consumes %d \n C2 consumes %d",c2[0],c2[1]);
	printf("\n\n Shared buffer after consumer work is done");
	for(i=0;i<nitems;i++)  	//printing buffer after consumes
	{	
		printf("   %d",shared.Xbuffer[i]);
	}
	printf("\n\n \t The winner is  P%d which produced %d elements in buffer\n\n", d, x);
}//end of main

void *produce(void *arg)
{
	//converting argument void type into int
	int a =*(int *)arg;
	int z=1;
	for(;;)       //infinite loop
	{	
		pthread_mutex_lock(&shared.mutex);     /*locking the mutex to perform operations on global variables. */
		if(shared.nput>=nitems) 	//if buffer is full, unock mutex and exit
		{
			pthread_mutex_unlock(&shared.mutex);
			return(NULL);
		}
		
		//random number generation using rand() function in between 1 and 100
		int random_number = rand() % 99 + 1;
		shared.Xbuffer[shared.nput]=random_number;	 //assign random number to buffer	 
		printf("\n Producer %d  insert %2d with    pid %ld", a, shared.Xbuffer[shared.nput], pthread_self()); 
		shared.nput++;		//incrementing index
		pthread_mutex_unlock(&shared.mutex);  //unlock to mutex
		c[a]=z;	    //storing how many times a producer generates a number in an array
		z++;
	}
}//end of producer function

void *consume(void *arg)
{
	int i,z=0;
	int a=*(int *)arg;   //conversion of argument void to int
	
	while(1)
	{	
		pthread_mutex_lock(&shared.mutex);    //lock the mutex
		if(n<0)		//if buffer is empty, then exit.
		{
			pthread_mutex_unlock(&shared.mutex);
			return(NULL);
		}
		shared.Xbuffer[n]=0; 		//assign ‘0’ to buffer
		//printf(" count = %d",a);		
		n--;				//decrement index
		pthread_mutex_unlock(&shared.mutex);		//unlocking the mutex
		c2[a]=z;       //storing how many times a consumer generates a number in an array
		z++;
	}
} //end of consumer function
