//derivada da primeira e derivada da segunda
//
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
float f(float x){	
	//return (pow(x,4) - 3*pow(x,3));	
	return pow(sin(x),2);
}
float derivada_da_primeira(float x, float h){
	return (f(x+h) - f(x-h))/(2*h);
		
}
float derivada_da_segunda(float x, float h){
	//printf("%.4f\n", + (f(x+h)) - (f(x)) + (f(x-h))  );
	return ((f(x + (2*h))) - 2*(f(x)) + (f(x - (2*h))))/((2*h)*(2*h));	
}
//
float d1(float pre, int ite_max, float func(float v), int *ite_fi, float *h, float x){ // ===================== aqui 
	float fx, fx_ant, erro_ant,erro;
	int ver=0;
	while(*ite_fi != ite_max && ver == 0){
		fx_ant = fx;
		fx = derivada_da_primeira(x,*h);
		//
		if(*ite_fi > 0){ // calculo das condiçoes de parada
			erro_ant = erro;
			if(modulo(fx) > 1) 
				erro  = modulo((fx - fx_ant)/fx); 
			else erro  = modulo((fx - fx_ant)/1);  
			if(erro < pre) 
				ver = 1;
			if(*ite_fi > 1 && erro > erro_ant) 
				ver = 2;
		}
		*h = (*h)/2;
		(*ite_fi)++;
	}
	
	if(ver==0) return 0;
	else if(ver==1) return fx;
	else return fx_ant;
}
//
float d2(float pre, int ite_max, float func(float v), int *ite_fi, float *h, float x){ // ===================== aqui 
	float fx, fx_ant, erro_ant,erro;
	int ver=0;
	while(*ite_fi != ite_max && ver == 0){
		fx_ant = fx;
		fx = derivada_da_segunda(x,*h);
		//
		if(*ite_fi > 0){ // calculo das condiçoes de parada
			erro_ant = erro;
			if(modulo(fx) > 1) erro  = modulo((fx - fx_ant)/fx); 
			else erro  = modulo((fx - fx_ant)/1);  
			if(erro < pre) ver = 1;
			if(*ite_fi > 1 && erro > erro_ant) ver = 2;
		}
		*h = (*h)/2;
		(*ite_fi)++;
	}
	
	if(ver==0) return 0;
	else if(ver==1) return fx;
	else return fx_ant;
}
//
int main(){
	float aux, pre = 0.01,h=1;
	int ite = 50,ite_fim = 0;
	//Chama o método dervada da primeira
	aux = d1(pre,ite,f,&ite_fim,&h,0.523598775598); // ===================== aqui
	printf("----->>> %.7f <<<<--%d--", aux,ite_fim);
	printf("\n");
		//Chama o método derivada segunda
	h = 1;
	ite_fim = 0;
	aux = d2(pre,ite,f,&ite_fim,&h,1.04719755119659); // ===================== aqui
	printf("----->>> %.7f <<<<--%d--", aux,ite_fim);
	system("pause");
}
