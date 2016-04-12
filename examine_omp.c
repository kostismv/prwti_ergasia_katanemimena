#include <stdlib.h>
#include <stdio.h>
#include <omp.h>
#include <time.h>
#include <string.h>
#include <time.h>

#define UPLIMIT 30
#define DOWNLIMIT 12

int main(int argc, char *argv[])
{
    
    
    FILE *fp;
    long size;
    const char temp[2] = " ";
    double temp2;
    long long count=0;
    size_t result;
    char *buffer;
    struct timespec start, end,middle1,middle2;
    const char *filename;
    filename = argv[1];
    fp = fopen(filename,"r");
    
    fseek(fp,0,SEEK_END);
    size = ftell(fp);
    rewind(fp);
    buffer = (char*) malloc (sizeof(char)*size);
    result = fread(buffer,1,size,fp);
    long long i;
    long long j=0;
    long long count2=0;
    int threads = atoi(argv[2]);
    printf("%d\n",threads);
    omp_set_num_threads(threads);
    int b;
    char *token;
    char **buffer2;
    int *mikos;
    clock_gettime(CLOCK_MONOTONIC,  &start);
    #pragma omp parallel shared(count)  private(b,token,temp2)
    {
      printf("%zu\n",result);
      #pragma omp for reduction(+:count2)
      for(i=0;i<result;i++)
      {
    
         if(buffer[i]=='\n')
         {
          count2++;
         }          
      }
    
    #pragma omp single
    {
     buffer2 = malloc (sizeof(char*)*count2);
    }
   
    
    
    #pragma omp single
    {   
    for(i=0;i<count2;i++)
    {

        buffer2[i] = malloc (sizeof(char)*31);
    }
    }
    
    
    #pragma omp single
    {
     int row=0;
     j=0;
     for(i=0;i<result;i++)
     {
      if(buffer[i]=='\n')
      { 
        row++;
        j=0;
      }
      else
      {
        buffer2[row][j]=buffer[i];
        j++;
      }

    }

    
    }
    
    
    
    
  
  
  
   
    #pragma omp for schedule(static) private(i) reduction(+:count)
    for(i=0;i<count2;i++)
    {
        b=0;
        
            
        token=strsep(&buffer2[i],temp);
        while(token!=NULL)
        {
           sscanf(token,"%lf",&temp2);
           
           if(temp2>DOWNLIMIT && temp2<UPLIMIT)
           {

              b++;
           }
           token=strsep(&buffer2[i],temp);
        }
        if(b==3)
        {
            count++;
        }
    }
    #pragma omp master
    clock_gettime (CLOCK_MONOTONIC, &end);
}
      
    
 




    const int DAS_NANO_SECONDS_IN_SEC = 1000000000;
    long timeElapsed_s = end.tv_sec -start.tv_sec;
    long timeElapsed_n = end.tv_nsec-start.tv_nsec;
    if ( timeElapsed_n < 0 ) {timeElapsed_n = DAS_NANO_SECONDS_IN_SEC + timeElapsed_n; 
        timeElapsed_s--;}
       printf("Time: %ld.%09ld secs \n",timeElapsed_s,timeElapsed_n);
       printf("%lld",count);




    
    
    return 0;
    }

