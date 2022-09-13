#include <stdio.h>
#include <stdlib.h>
#include <math.h>

FILE *arq;

#define N 100
#define max 0.9
#define min 0.1

double mapa(double x,double mi);

int main()
{ 
  int i,n,soma;
  double xv[N+5],xn[N+5],mi[N+5],e;

 arq=fopen("logredeglobal.dat","wt");
    
 e=0.03;

 for(i=1;i<=N;i++){
    xn[i]= min+(rand()/(RAND_MAX/(max-min)));
    mi[i]=3.98;
 }

 for(n=1;n<=1000;n++){
    
     for(i=1;i<=N;i++)
         xv[i]=xn[i];
     
     soma=0.0;
     for(i=1;i<N;i++)
         soma=soma+mapa(xv[i],mi[i]);
      
     for(i=1;i<=N;i=i+1){
         xn[i]=(1.0-e)*mapa(xv[i],mi[i])+(e/N)*soma;
         if(n>900) 
             fprintf(arq,"%d \t %f\n",i,xn[i]);
      }
   }

 fclose(arq);
   
 return 0;
}

double mapa(double x,double mi)
{
 return(mi*x*(1.0-x));
}
