#include <stdlib.h>
#include <stdio.h>
#include <mpi.h>
#include <time.h>
#include <string.h>
#include <time.h>


#define UPLIMIT 30
#define DOWNLIMIT 12


int main(int argc,char *argv[])
{
    int tid,size;
    MPI_Status status;
    const char *filename;
    filename = argv[1];
    MPI_Init(&argc,&argv);
    MPI_Comm_rank(MPI_COMM_WORLD,&tid);
    MPI_Comm_size(MPI_COMM_WORLD,&size);
    struct timespec beg,end;
    if(tid==0)
    {
      clock_gettime(CLOCK_MONOTONIC,  &beg);
    }

    
    
    
    
    FILE *fp;
    char line[30];
    long size2;
    char seira[30];
    const char temp[2] = " ";
    double temp2;
    long count=0;
    size_t len,result;
    ssize_t read,read2;
    int n2;
    char *buffer;
   
    long plithos=0;
    int threads=size;
    
    unsigned long start;
    unsigned long workload_temp;
    long count2;
    long workload2;
    int tag1=2;
    int tag2=1;
    
    
    fp = fopen(filename,"r");
    
    fseek(fp,0,SEEK_END);
    size2 = ftell(fp);
    rewind(fp);
    buffer = (char*) malloc (sizeof(char)*size2);
    result = fread(buffer,1,size2,fp);
    
    int temp3;
    workload_temp = result/threads;
    int workload = (int) workload_temp;
    char *token;
    int b;
    
    long master_workload;
    

    if(tid==0)
    {
    
    
  
    
    long long i;
    long long j=0;
    
    if(result%threads!=0)
    {
       master_workload = workload + (result%threads);
       
       start=master_workload;
    }
    else
    {
      master_workload = workload;
    }
    
    char **buffer2;
    
    
    for(i=1;i<threads;i++)
    {

      
      MPI_Send(&start,2,MPI_UNSIGNED_LONG,i,tag1,MPI_COMM_WORLD);
      start = start + workload;
      
    }
    
   
     
   
    for(i=0;i<master_workload;i++)
    {
      if(buffer[i]=='\n')
        {
          
          plithos++;
        }
    }
      
    
    MPI_Reduce(&plithos,&count,1,MPI_LONG,MPI_SUM,0,MPI_COMM_WORLD);
    
    buffer2 = malloc (sizeof(char*)*count);
    for(i=0;i<count;i++)
    {

        buffer2[i] = malloc (sizeof(char)*31);
    }
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
    free(buffer);
    workload2=count/threads;
    start=workload2;
    temp3=(int) workload2;
    for(i=1;i<threads;i++)
    {
       MPI_Send(&start,2,MPI_UNSIGNED_LONG,i,tag2,MPI_COMM_WORLD);
       MPI_Send(&workload2,2,MPI_LONG,i,tag2,MPI_COMM_WORLD);
       for(j=start;j<start+workload2;j++)
       {
         char *tempk;
         tempk=buffer2[j];
         MPI_Send(&tempk[0],30,MPI_CHAR,i,tag1,MPI_COMM_WORLD);
       }
       
       start=start+workload2;
    }
  
    
    plithos=0;
    
    for(i=0;i<workload2;i++)
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
            plithos++;
        }
        
    }
  
    MPI_Reduce( &plithos, &count2, 1, MPI_LONG, MPI_SUM, 0, MPI_COMM_WORLD);
    printf("%ld\n",count2);
    }


    if(tid > 0)
    {
      
      
      long mystart,myworkload; 
      MPI_Recv(&mystart,2,MPI_UNSIGNED_LONG,0,tag1,MPI_COMM_WORLD,&status);
      char **temp_buffer;
      plithos=0;
      long i;
      
      for(i=mystart;i<mystart+workload;i++)
      {
        if(buffer[i]=='\n')
        {
          
          plithos++;
        }
      }
      MPI_Reduce( &plithos, &count, 1, MPI_LONG, MPI_SUM, 0, MPI_COMM_WORLD);
      
      MPI_Recv(&mystart,2,MPI_UNSIGNED_LONG,0,tag2,MPI_COMM_WORLD,&status);
      MPI_Recv(&myworkload,2,MPI_LONG,0,tag2,MPI_COMM_WORLD,&status);
      temp_buffer = malloc(sizeof(char*)*myworkload);
      for(i=0;i<myworkload;i++)
      {
        temp_buffer[i] = malloc(sizeof(char)*30);
      }
      int j;
      for(j=0;j<myworkload;j++)
       {
        char *btemp = malloc(sizeof(char)*30);

        MPI_Recv(&btemp[0],30,MPI_CHAR,0,tag1,MPI_COMM_WORLD,&status);
        
        temp_buffer[j]=btemp;
       }
           
      int b;
      plithos=0;
      char *token;
      
      for(i=0;i<myworkload;i++)
    {
        b=0;
       
        
        token=strsep(&temp_buffer[i],temp);
        while(token!=NULL)
        {
           sscanf(token,"%lf",&temp2);
           
           if(temp2>DOWNLIMIT && temp2<UPLIMIT)
           {

              b++;
           }
           token=strsep(&temp_buffer[i],temp);
        }
        if(b==3)
        {
            plithos++;
        }
        
    }
    
    MPI_Reduce( &plithos, &count2, 1, MPI_LONG, MPI_SUM, 0, MPI_COMM_WORLD);
    
    }
  

    
    
    if(tid==0)
    {
      clock_gettime(CLOCK_MONOTONIC,  &end);
      const int DAS_NANO_SECONDS_IN_SEC = 1000000000;
      long timeElapsed_s = end.tv_sec -beg.tv_sec;
      long timeElapsed_n = end.tv_nsec-beg.tv_nsec;
      if ( timeElapsed_n < 0 ) {timeElapsed_n = DAS_NANO_SECONDS_IN_SEC + timeElapsed_n; 
        timeElapsed_s--;}
       printf("Time: %ld.%09ld secs \n",timeElapsed_s,timeElapsed_n);
       fclose(fp);
       
      
   
    }
    MPI_Finalize();
  }

