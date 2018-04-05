//	Função pra calcular hessiana
//
// Leonardo Oliveira

#include <math.h>
#include <stdio.h>
#include <conio.h>
#include <ctype.h>
#include <stdlib.h>
#include <locale.h>

// f(x1,x2) = 2*x1^3 - 3*x2^2 - x1^2*x2

float func(float x1, float x2, float x3){	
	return (2*pow(x1,3) - 3*pow(x2,2) - pow(x1,2)*x2);
}

float derivada_segunda_x1 (float v1, float v2, float v3, float h){	
	return ((func(v1 + 2*h,v2,v3) - 2*func(v1,v2,v3) + func(v1 - 2*h,v2,v3))/2*h);	
}

float derivada_segunda_x2 (float v1, float v2, float v3, float h){	
	return ((func(v1,v2 + 2*h,v3) - 2*func(v1,v2,v3) - func(v1,v2 - 2*h,v3))/2*h);	
}

float derivada_segunda_x1x2 (float v1, float v2, float v3, float h){
	return (func(v1+h,v2+h,v3) - func(v1+h,v2-h,v3) - func(v1-h,v2+h,v3) + func(v1-h,v2-h,v3))/(4*pow(h,2)); 
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

float df1 (int vetor_x, float v[]){
	
	float pre = 0.001; 
	float erro, erro_ant; 
	float der, ant; 
	int cont = 0; 
	float h = 1; 
	
	while(true){
		cont++; 
		der = derivada_segunda_x1(v[0],v[1],v[2],h); 
	
		if(cont != 1){
			erro = modulo (der - ant) / max (der); 
			if(erro < pre)
				return der;
			else {
				//erro_ant = erro; 
				if(cont > 2){
					if(erro_ant > erro)
						return der; 
					
				}
			}
			erro_ant = erro; 
		}		
		h = h / 2; 
		ant = der; 
	}	
}

float df2 (int vetor_x, float v[]){
	
	float pre = 0.001; 
	float erro, erro_ant; 
	float der, ant; 
	int cont = 0; 
	float h = 1; 
	
	while(true){
		cont++; 
		der = derivada_segunda_x1x2(v[0],v[1],v[2],h); 
	
		if(cont != 1){
			erro = modulo (der - ant) / max (der); 
			if(erro < pre)
				return der;
			else {
				//erro_ant = erro; 
				if(cont > 2){
					if(erro_ant > erro)
						return der; 
					
				}
			}
			erro_ant = erro; 
		}		
		h = h / 2; 
		ant = der; 
	}	
}
void Hessiana(int vetor_x, float funcN(float v1, float v2, float v3), float v[], float hess[][3]){
	
	float aux; 
	
	for(int i = 0; i < vetor_x;i++){				//Andando na linha da matriz
		for(int j = 0; j < vetor_x; i++){			//Andando na coluna da matriz
			if(i == j)
				hess[i][j] = df1(vetor_x,v);  
			else hess[i][j] = df2(vetor_x,v);				
		}		
	}	
}

void printa_matriz (float hes[][3]){
	
	for (int i=0; i < 3; i++){
		printf("\n"); 
		for(int j=0; j<3; j++){
			printf(" %f ",hes[i][j]); 
		}
	}
}
int main(){

	setlocale(LC_ALL,"Portuguese");
	
	float vetor[3]; 
	float hess[3][3]; 
	vetor[0] = 1; 
	vetor[1] = -1; 
	
	Hessiana(2,func,vetor,hess);
	printa_matriz(hess); 
}

