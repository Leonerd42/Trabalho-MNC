//Newton Modificado
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
	return (pow(x,3) - 4*(pow(x,2)) + x + 6);	
}
float derivada_da_funcao(float x){
	return (3*pow(x,2) - 8*x + 1);	
}

float max(float x){
	if(modulo(x) > 1)
		return 1; 
	else return 1; 
}
//
//Método de Newton Modificado
/*
float NewtonModificado(float pre, int ite_max, float func(float v), int *ite_fi, float *x, float x_linha){ // ===================== aqui
	(*ite_fi)++; 
	if(*ite_fi >= ite_max) return 0;
	printf("\t%d", *ite_fi); //=========so pra ver quantas vezes chama bagui
	float x_antes = (*x),teste_2;
	 // definindo x anterior para calcular o segundo teste da CP2
	(*x) = (*x) - (func(*x)/x_linha);
	if(modulo(*x) > 1) teste_2 = ((*x) - x_antes)/(*x); //definindo o segundo teste da CP2
	else teste_2 = ((*x) - x_antes)/1; //definindo o segundo teste
	// definindo condição de parada e retorno
	if(modulo(func(*x)) < pre) return 1; //CP1 
	else if(modulo(teste_2) < pre) return 1; //CP2
	else return NewtonModificado(pre,ite_max,func,&(*ite_fi),&(*x),x_linha); // ==================aqui		
}*/

float NewtonModificado(float pre,int ite_max, float func(float v), float *x0, int *ite_fi, float *x){
	(*ite_fi)++; 
	if((*ite_fi) > ite_max)
		return 0; 
	if(derivada_da_funcao(*x0) != 0){
		float x_anterior = (*x); 
		if((*ite_fi) == 1)
			(*x) = (*x0) - (f(*x0)/derivada_da_funcao(*x0)); 
		else (*x) = x_anterior - (f(x_anterior)/derivada_da_funcao(*x0)); 
	if(modulo(f(*x)) < pre)
		return 1; 
	if((modulo((*x) - x_anterior)/max(*x)) < pre)
		return 1;  
	if((*ite_fi) % 5 == 0)
		if(derivada_da_funcao(*x) != 0)
			(*x0) = (*x);
	return NewtonModificado(pre,ite_max,f,&(*x0),&(*ite_fi),&(*x));		
	}else printf("não é possivel");
}


//
int main(){
	float aux, pre = 0.01, x0_1=2.8, x0_2 = 1.5;
	float x;
	int ite = 50,ite_fim = 0;
	if(derivada_da_funcao(x0_1) != 0){
		//Chama o método Newton Modificado
		aux = NewtonModificado(pre,ite,f,&x0_1,&ite_fim,&x); // ===================== aqui
		printf("----->>> %.7f <<<<", x);
			
	}else printf("não é possivel");	
	//
	printf("\n");
	//
	if(derivada_da_funcao(x0_2) != 0){
		//Chama o método Newton Modificado
		aux = NewtonModificado(pre,ite,f,&x0_2,&ite_fim,&x); // ===================== aqui
		printf("----->>> %.7f <<<<", x);
	}else printf("não é possivel");	
	system("pause");
}
