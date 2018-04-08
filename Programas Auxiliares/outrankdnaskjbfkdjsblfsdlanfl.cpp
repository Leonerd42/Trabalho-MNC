//derivada da gradiente 
int F=1;
#include <math.h>
#include <stdio.h>
#include <conio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <locale.h>
#include <windows.h>
//funcao renan
float fN(float x1,float x2, float x3){
	if(F == 1) return ((2*x1*x1*x1) - (3*x2*x2) - (x1*x1*x2));
	else return ((x1*x1) + (x2*x2) + (x3*x3) - (7*x1*x2) + (5*x1) - (3*x3)); //AAAAAAAAAAAAAAQUIIIIIIIIIIIIIIIIIIIIIIII
//
}
float ParcialHess( float x[], float h, int i, int j){ // colocar qual fn vai trabalhar****************OBS IMPORTANTE LEOOOO OLHA AQUI!!!
	float soma=0,vet[4];
	vet[1] = x[1];
	vet[2] = x[2];
	vet[3] = x[3];
	
	if (i==j){	
		soma= (-2)*fN(vet[1], vet[2], vet[3]);
		vet[i]= vet[i]+2*h;	
		soma=soma+fN(vet[1],vet[2], vet[3]);	
		vet[i]= vet[i]-4*h;	
		soma=soma+fN(vet[1], vet[2], vet[3]);
		soma = soma/(4*pow(h,2));
        return soma; 
	}
	//
	else{
		vet[i]= vet[i]+h;
		vet[j]= vet[j]+h;
		soma=fN(vet[1],vet[2],vet[3]);
		vet[j]=vet[j]-(2*h);//SUBTRAI 2 POIS SOMOU 1 EM CIMA
		soma=soma-fN(vet[1],vet[2], vet[3]);
		vet[i]=vet[i]-(2*h); //SUB 2 POIS ESTAVA +1H
		vet[j]=vet[j]+(2*h);
		soma=soma-fN(vet[1], vet[2], vet[3]);
		vet[j]= vet[j]-(2*h);
		soma= soma+fN(vet[1], vet[2], vet[3]);
		soma = soma/(4*pow(h,2));
		return soma;
	}
}
//
float modulo(float x){		//FUNÇÃO PARA RETORNAR O MODULO DE UM VALOR 
	if(x < 0) 
		return x * (-1);
	else 
		return x; 
}
//
 int Hess(float pre, int ite_max, int *ite_fi, float *h,float x[], float JACO[][3], int n){ // ===================== aqui 
	float fx, fx_ant, erro;
	int ver,aux;
	for(int i=0; i<n; i++){
		for(int j=0; j<n; j++){
			ver = (*ite_fi) = 0;
			while(*ite_fi != ite_max && ver == 0){
				fx_ant = fx;
				fx = ParcialHess(x,*h,i+1,j+1);
				printf("---<<>>>%d,%d>>>%.4f<<<---\n",i+1,j+1,fx);
				//
				if(*ite_fi > 0){ // calculo das condiçoes de parada
					if(modulo(fx) > 1) erro  = modulo((fx - fx_ant)/fx); 
					else erro  = modulo((fx - fx_ant)/1);  
					if(erro < pre){
						JACO[i][j] = fx;
						ver = 1;
					}
				}
				*h = (*h)/2;
				(*ite_fi)++;
				if(*ite_fi == ite_max) return 0;//============alterar aqui // ultrapassou o limite de interações
			}		
		}
	}
	return 1;
}
//
int main(){
	float aux, pre = 0.01,h=1,JACO[3][3], x[4];
	int n=2,ite = 50,ite_fim = 0;
	x[1] = -1;
	x[2] = 1;
	x[3] = 0;
	Hess(pre,ite,&ite_fim,&h,x,JACO,n); // ===================== com 2
	for(int i =0; i<n; i++){
		for(int j=0; j<n; j++) printf("----->>> %.7f <<<<\t",JACO[i][j]);
		printf("\n");
	}
	
	F = 2; 
	n=3;
	x[1] = 1;  //AAAAAAAAAAAAAAQUIIIIIIIIIIIIIIIIIIIIIIII
	x[2] = 3;  //AAAAAAAAAAAAAAQUIIIIIIIIIIIIIIIIIIIIIIII
	x[3] = 2; //AAAAAAAAAAAAAAQUIIIIIIIIIIIIIIIIIIIIIIII
		Hess(pre,ite,&ite_fim,&h,x,JACO,n); // ===================== com 3
	for(int i=0; i<n; i++){
		for(int j=0; j<n; j++) printf("----->>> %.7f <<<<\t",JACO[i][j]);
		printf("\n");
	}
}
