#include <stdio.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
   long array[1000000];
   long evenNum0 = 0;
   long oddNum0 = 0;
   long evenNumSum0 = 0;
   long oddNumSum0 = 0; 
   long evenNum1 = 0;
   long oddNum1 = 0;
   long evenNumSum1 = 0;
   long oddNumSum1 = 0; 

   long cnt = 0;

   int i=0;
   int N = 4;

   pid_t pid;
   //pid_t pid[N];


   for(i=0; i<1000000; i++)   
 	array[i]=i; 
 	
	 
   if (strcmp(argv[1],"0")==0) 
   {
	  pid = fork();
   	  for(i=0; i<1000000; i+=2){   
   	  	evenNum0 = evenNum0+i;
		evenNumSum0 = evenNumSum0 + evenNum0;
	  }
	  if(pid == 0) {
	  	printf("parent pid is %ld\n",getpid());
	  	printf("pid of parent is %ld, the total even numbers are %ld\n",getpid(),evenNum0 );
	  	printf("pid of parent is %ld, sum of even numbers are %ld\n",getpid(),evenNumSum0 );
	  }
   	  for(i=1; i<1000000; i+=2){   
   	  	oddNum0 = oddNum0+i;
		oddNumSum0 = oddNumSum0 + oddNum0;
	  }
	  pid = fork();
	  switch(pid) {
		case 0 : 
	  		printf("pid of child is %ld,th total  odd numbers are %ld\n",getpid(),oddNum0 );
		case 1 : 
	  		printf("pid of child is %ld, sum odd numbers are %ld\n",getpid(),oddNumSum0 );
	  }


   } else {
   
	cnt = 0;
	while(cnt < sizeof(array)/sizeof(array[0])) 
	{
		if(cnt%2 == 0) {
			evenNum1++;
			evenNumSum1 = evenNumSum1 + array[cnt];
		} else {
			oddNum1++;
			oddNumSum1 = oddNumSum1 + array[cnt];
		}
		cnt++;
	}
   	
	printf("the total even numbers are %d \n", evenNum1);
   	printf("the total odd numbers are %d \n", oddNum1);
   	printf("sum of even numbers is %lld \n", evenNumSum1);
   	printf("sum of odd numbers is %lld \n", oddNumSum1);
   } 
 
   return 0; 
}
