//derivada da gradiente 
#include <math.h>
#include <stdio.h>
#include <conio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <locale.h>
#include <windows.h>
float modulo(float x){		//FUNÇÃO PARA RETORNAR O MODULO DE UM VALOR 
	if(x < 0) 
		return x * (-1);
	else 
		return x; 
}
//Função para começar a implementar 
float f(float x1,float x2){
	return ((2*x1*x1*x1) - (3*x2*x2) - (x1*x1*x2));			//Funçao do exercicio 
}
float J_x1(float x1, float x2,float h){
	return (f(x1 + (2*h), x2) - (2 * f(x1,x2)) + f(x1 - (2*h), x2))/(4*h*h);
}
float J_x2(float x1, float x2, float h){
	return ( f(x1, x2 + (2*h)) - (2 * f(x1,x2)) + f(x1, x2 - (2*h)) )/(4*h*h);	
}
float J_x1x2(float x1, float x2, float h){
	return (f((x1 + h), (x2 + h)) - f((x1 + h), (x2 - h)) - f((x1 - h), (x2 + h)) + f((x1 - h), (x2 - h)))/(4*h*h);
}
//
 void jaco(float pre, int ite_max, int *ite_fi, float *h,float x[][1], float JACO[][2]){ // ===================== aqui 
	float fx, fx_ant, erro;
	int ver;
	for(int i=0; i<2; i++){
		for(int j=0; j<2; j++){
			ver = (*ite_fi) = 0;
			while(*ite_fi != ite_max && ver == 0){
				fx_ant = fx;
				if(i == 0 && j == 0) fx = J_x1(x[0][0],x[1][0],*h);
				else if(i == 0 && j == 1 || i == 1 && j == 0) fx = J_x1x2(x[0][0],x[1][0],*h); 
				else if(i ==1 && j == 1) fx = J_x2(x[0][0],x[1][0],*h);	
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
				if(*ite_fi == ite_max) return ;//============alterar aqui // ultrapassou o limite de interações
			}		
		}
	}
	return ;
}
//
int main(){
	float aux, pre = 0.01,h=1,JACO[2][2], x[2][1];
	int ite = 50,ite_fim = 0;
	x[0][0] = -1;
	x[1][0] = 1;
	//Chama o método dervada da primeira
	jaco(pre,ite,&ite_fim,&h,x,JACO); // ===================== aqui

	for(int i =0; i<2; i++){
		for(int j=0; j<2; j++) printf("----->>> %.7f <<<<\t",JACO[i][j]);
		printf("\n");
	}
}
