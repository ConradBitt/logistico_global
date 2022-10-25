#include <stdio.h>
#include <stdlib.h>
#include <math.h>

FILE *arq;

#define n 100 // Tamnho da rede
#define theta 4.2
#define gamma -2.75

void network(double xout[], double x[], double sigma, int p);

int main(){

    int tf = 6000; // Número total de iterações
    int trans = tf - 2000; // Transiente
    int sample_size = tf - trans; // Tamanho
    double sigma = 0.58; // Intensidade do acoplamento
    double r = 0.35; // Raio do acoplamento
    int p = n*r; // Número de vizinhos acoplados
    double x[n], xout[n]; // Variáveis da rede
    double w = 0.01;
    int i, j, k;
   
    arq = fopen("quimera.dat", "wt");

    // Condição inicial
    for(i = 0; i < n; i++){
        x[i] = sin(w*i)*sin(w*i);
    }
    // Itera até o transiente
    for(i = 0; i < trans; i++){
        network(xout, x, sigma, p);
        for(j = 0; j < n; j++){
            x[j] = xout[j];
        }
    }
    // Itera após o transiente
    for(i = trans; i <= tf; i++){
        network(xout, x, sigma, p);
        for(j = 0; j < n; j++){
            x[j] = xout[j];
            fprintf(arq, "%i %i %.16f\n", j, i, x[j]);
        }
        fprintf(arq, "\n");
    }
    fclose(arq);
    arq = fopen("quimera_ultimo.dat", "wt");
    for(j = 0; j < n; j++){
        fprintf(arq, "%i %.16f\n", j, x[j]);
    }
    fclose(arq);
}

void network(double xout[], double x[], double sigma, int p){

    double f[n];
    double coup;
    int i, j, k;
   
    for(i = 0; i < n; i++){
        f[i] = theta/(1+pow(x[i],2))+gamma;
    }

    for(i = 0; i < n; i++){
        coup = 0;
        for(k = i - p; k <= i + p; k++){
            if(k == 0 || k == n){
                j = 0;
            } else{
                j = ((k % n) + n) % n;
            }
            coup += (f[j] - f[i]);
        }
        xout[i] = f[i] + sigma*coup/(2.0*p);
    }
}
