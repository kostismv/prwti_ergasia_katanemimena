#include <stdlib.h>
#include <stdio.h>
int main(int argc, char *argv[])
{
  int utime;
  long int ltime;
  int i;
  
  int coordinate_index = atoi(argv[2]);
  float cords[coordinate_index][3];
  ltime = time(NULL);
  utime = (unsigned int) ltime/2;
  srand(utime);
  for(i=0;i<coordinate_index;i++)
  {
    cords[i][0]=(float)34*rand()/(RAND_MAX-1);
    cords[i][1]=(float)34*rand()/(RAND_MAX-1);
    cords[i][2]=(float)34*rand()/(RAND_MAX-1);
  }
  FILE *output = fopen(argv[1],"w");
  if (output == NULL)
  {
     printf("Error opening file!\n");
     return 1;
  }
  for(i=0;i<coordinate_index;i++)
  {
   fprintf(output,"%f ",cords[i][0]);
   fprintf(output,"%f ",cords[i][1]);
   fprintf(output,"%f\n",cords[i][2]);
  }

}
