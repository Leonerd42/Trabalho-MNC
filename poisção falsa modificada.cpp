//posi�ao falsa modificada
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
//
float moduloIntervalo(float b, float a){	//FUN��O PARA RETORNAR O MODULO DE UM INTERVALO 
	
	if(b - a < 0)
		return (b-a) * (-1);
	else return b - a;
}
//Fun��o para come�ar a implementar 
float f(float x){	
	return (pow(x,3) - 4*(pow(x,2)) + x + 6);	
}
//Fun��o para calcular a m�dia ponderada
float mediaPonderada(float a, float b, float fa, float fb){	// 0 - N�o divide nada, 1 - f(a)/2, 2 - f(b)/2
	return (a*fb - b*fa) / (fb - fa);
}
//Fun��o para verificar a converg�ncia
int conve(float a,float b){				
	float fa = f(a), fb = f(b);
	if((fa*fb) < 0)
		return 1; 
	else return 0; 
}
//
//M�todo Posi��o Falsa
/*
float PosicaoFalsaModificada(float pre, int ite_max, float func(float v), float a, float b, int *ite_fi, float *x){
	(*ite_fi)++; 
	if(*ite_fi >= ite_max) return 0;
	printf("\t%d", *ite_fi); //=========so pra ver quantas vezes
	if((conve(a,b)) == 1){ 
		(*x) = mediaPonderada(a,b,func(a),func(b));
		if(modulo(func(*x)) < pre)
			return 1; 
		else if(moduloIntervalo(b,a) < pre)
			return 1; 
		else{
			if(conve(a,(*x)) == 1){
				if(conve(a,(*x)) == 1) return PosicaoFalsaModificada(pre,ite_max,func,a,(*x),&(*ite_fi),&(*x)); // ===================== aqui
				else return PosicaoFalsaModificada(pre,ite_max,func,a/2,(*x),&(*ite_fi),&(*x)); // ==================aqui
			}else{
				if(conve((*x),b) == 1) return PosicaoFalsaModificada(pre,ite_max,func,(*x),b,&(*ite_fi),&(*x)); // ===============aqui
				else return PosicaoFalsaModificada(pre,ite_max,func,(*x),b/2,&(*ite_fi),&(*x)); // ================aqui
				} 
			}			
	}else printf("n�o � possivel");	
}*/

float x_ant_global = 0; 

float PosicaoFalsaModificada(float pre, int max_ite, float func(float v), float a, float b, int *ite_fi, float *x){
	
	(*ite_fi)++;
	if((*ite_fi) >= max_ite)
		return 0; 
	if(conve(a,b) == 1){
		if((*ite_fi) == 1)
			(*x) = mediaPonderada(a,b,func(a),func(b)); 
		else{
			
		}
	}else printf("n�o � possivel");
}


//
int main(){
	float aux,raiz=0, pre = 0.01, l_inf = 2.8, l_sup = 1.3;
	int ite = 50,ite_fim = 0;
	//Chama o m�todo da Posi��o Falsa Modificada
	aux = PosicaoFalsaModificada(pre,ite,f,l_inf,l_sup,&ite_fim,&raiz);
	printf("\n\n\n----->>> %.7f <<<<",raiz);
	system("pause");
}
