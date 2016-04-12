#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <omp.h>
#include <time.h>
int main(int argc, char *argv[])
{
	FILE *fp;
	struct timespec start, end;
	char *line= NULL;
	char *line2=NULL;
	size_t len,len2=0;
	ssize_t read,read2;
	fp = fopen("output4","r");
    int n,n2=0;
    while((read = getline(&line2, &len2, fp)) != -1)
    {
      n2++;
    }
	if(fp==NULL){
		exit(EXIT_FAILURE);
	}

    const char temp[2] = " ";
    
    int j;
    int count=0;
    char *token;
    float temp2;
    fp = fopen("output4","r");
    
    omp_set_num_threads(2);
    FILE *out = fopen("test","w");
    
    
    
    clock_gettime(CLOCK_MONOTONIC,  &start);
    
for(j=0;j<n2;j++){	
    read = getline(&line, &len, fp);
    token = strtok(line,temp);
    int c=0,b=0;
		
    while(token != NULL){
    	temp2 = atof(token);
    	if(temp2<30 && temp2>12)
    	{
		b++;
    	}
    	token = strtok(NULL,temp);
         
    }

    if(b==3){
	count++;
    }

    }
    
    clock_gettime (CLOCK_MONOTONIC, &end);
}

    
    const int DAS_NANO_SECONDS_IN_SEC = 1000000000;
    long timeElapsed_s = end.tv_sec -start.tv_sec;
    long timeElapsed_n = end.tv_nsec-start.tv_nsec;
    if ( timeElapsed_n < 0 ) {timeElapsed_n = DAS_NANO_SECONDS_IN_SEC + timeElapsed_n; 
    	timeElapsed_s--;}
printf("Time: %ld.%09ld secs \n",timeElapsed_s,timeElapsed_n);
printf("%d",count);
    
    

    return 0;

}
