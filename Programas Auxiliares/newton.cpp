//Newton
//
//
//
#include <math.h>
#include <stdio.h>
#include <conio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <locale.h>
#include <windows.h>
float modulo(float x){		//FUN��O PARA RETORNAR O MODULO DE UM VALOR 
	if(x < 0) 
		return x * (-1);
	else 
		return x; 
}
//Fun��o para come�ar a implementar 
float f(float x){	
	return (pow(x,3) - 4*(pow(x,2)) + x + 6);	
}
float derivada_da_funcao(float x){
	return (3*pow(x,2) - 8*x + 1);	
}

float max(float x){	
	if(modulo(x) > 1)
		return x; 
	else return 1.0; 
}

int Newton (float pre, int ite_max, float func(float v), float *x0, int *ite_fi, float *x){
	(*ite_fi)++; 		//Somando 1 no n�mero de itera��es 
	if((*ite_fi) > ite_max)
		return 0; 				//N�mero de itera��es excedeu o limite
	if(derivada_da_funcao(*x0) != 0){	//Verifica se a derivada da fun��o � diferente de 0
		(*x) =  (*x0) - ((f(*x0))/derivada_da_funcao(*x0));		//Atribui o novo valor a x, dependendo do valor anterior
		if(f(*x) < pre)		//Verificar se o primeiro criterio de parada foi atendido
			return 1;		//Retorna
		if(((*x) - (*x0)/max(*x)) < pre)	//Verifica se o segundo criterio de parada foi atendido
			return 1; 		//Retorna	
		(*x0) = (*x);		//Atribui o valor de x para o x0 
		return Newton(pre,ite_max,f,&(*x0),&(*ite_fi),&(*x));	//Chama newton novamente	
	}else printf("n�o � possivel");
	return 0;		//Derivada da fun��o � = 0, falha no processamento
}
//
int main(){
	float aux, pre = 0.01, x0_1=2.8, x0_2 = 1.5;
	float x; 
	int ite = 50,ite_fim = 0;
	//Chama o m�todo Newton
	aux = Newton(pre,ite,f,&x0_1,&ite_fim,&x); // ===================== aqui
	printf(" ----->>> %.7f <<<<", x);
	printf("\n");
		//Chama o m�todo Newton
	aux = Newton(pre,ite,f,&x0_2,&ite_fim,&x); // ===================== aqui
	printf(" ----->>> %.7f <<<<\n", x);
	system("pause");
}
