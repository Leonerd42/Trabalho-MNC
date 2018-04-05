//	Função pra calcular hessiana
//
// Leonardo Oliveira

#include <stdio.h>
#include <conio.h>
#include <ctype.h>
#include <stdlib.h>
#include <locale.h>

// f(x1,x2) = 2*x1^3 - 3*x2^2 - x1^2*x2

float fN(float x1, float x2, float x3){
	
	return (2*pow(x1,3) - 3*pow(x2,2) - pow(x1,2)*x2);
}

float derivada_primeira_parcial (float v1, float v2, float v3, float h, float func(float x1, float x2, float x3)){
	
	return ( (func(v1,v2,v3) - func(v1,v2,v3))/2*h);
	
}

float derivada_segunda_parcial_xixj (float v1, float v2, float v3, float h, float func(float x1, float x2, float x3)){
	
	
	
	
}

float derivada_segunda_parcial_xi (float v1, float v2, float v3, float h, float func(float x1, float x2, float x3)){
	
	
	return (func())
	
}

int main(){

	setlocale(LC_ALL,"Portuguese");

}

