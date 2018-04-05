// Leonardo Oliveira

#include <math.h>
#include <stdio.h>
#include <conio.h>
#include <ctype.h>
#include <stdlib.h>
#include <locale.h>

int vetor_global[3] = {0,0,0}; 
int aux_global = 0; 

float f(float x, float y, float z){
	if(aux_global == 1)
		return (3*x + 2*x*y + y*y);	
	if(aux_global == 2)
		return (2*pow(x,3) - 3*pow(y,2) + z*x*y);	
	if(aux_global == 3)
		return (3*z + 2*x*y + y*y);	
}

float parcial (float x, float y, float z, float h[]){
	return ((f(x + h[0],y + h[1],z + h[2]) - f(x - h[0],y - h[1],z - h[2]))/(2*(h[0]+h[1]+h[2])));  
}

float modulo (float x){
	if(x < 0)
		return x * (-1); 
	else return x; 
}

float max (float x){
	if(modulo(x) < 1)
		return 1; 
	else return modulo(x); 
}


void gradiente (int qtd, float v[], float grad[]){
	
	float h[3] = {0,0,0}; 
	float der_ant, erro, erro_ant;  
	int cont = 0; 
	
	for (int i=0; i < qtd; i++){
		h[i] = 1; 
		cont = 0; 
		while(true){
			cont++; 
			grad[i] = parcial(v[0],v[1],v[2],h);
			//printf("\nDerivada: %f\n",grad[i]);
			//system("pause");
			if(cont >= 2){
				erro = modulo (grad[i] - der_ant) / max(grad[i]); 
				if(erro < 0.001)
					break;
				
				if(cont > 2){
					if(erro > erro_ant)
						break; 
				}
				erro_ant = erro; 
			}
			
			der_ant = grad[i]; 
			h[i] = h[i] / 2; 
		}
		h[i] = 0; 			
	}	
}

void Jacobiana (int qtd, int qq, float v[], float ja[][3]){
	
	for(int i = 0; i < qtd; i++){
			
	if(vetor_global[i] == 0)
			continue; 
	aux_global++; 		
	gradiente(qtd,v,ja[i]); 
	}
	
	aux_global = 0; 
}

void printa_vet(float v[], int n){
	for(int i = 0; i < n; i++)
		printf("  %f   ",v[i]); 
}

void printa_matriz (float v[][3],int n){
	for(int i = 0; i < n; i++){
		printf("\n"); 
		for(int j = 0; j < n; j++)
			printf("   %f    ",v[i][j]);
	}
	
}

int main(){

	setlocale(LC_ALL,"Portuguese");
	int qtd = 3; 
	float vetor[3] = {1,7,1}; 
	float grad[3] = {0,0,0}; 	
	float jaco[3][3] = {0,0,0,
						0,0,0,
						0,0,0};
	int x; 
	
	
	//gradiente(qtd,vetor,grad); 
	//printa_vet(grad,qtd); 
	
	int cont = 0;
	
	do{
		printf("digite um numero entre 1 e 3 (-1 pra sair): "); 	
		scanf("%d",&x); 
		if(x >= 1 && x <= 3){
			if(vetor_global[x-1] != 1){
				vetor_global[x-1] = 1; 
				cont++; 
			}			
		}
			
	}while(x != -1 && cont < 3);
	
	for(int i=0; i<cont; i++){
		printf("Digite um valor de x: "); 
		scanf("%f",&vetor[i]);
	}
	
	Jacobiana(cont,0,vetor,jaco); 	
	
	printa_matriz(jaco,cont);
	

}

