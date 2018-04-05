//  Trabalho 1 - M�todos Num�ricos Computacionais
//  
//  Grupo: 
//			Gabriel Vieira
//			Leonardo Silva de Oliveira
//			Renan Scatolino Mesquita

#include <math.h>
#include <stdio.h>
#include <conio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <locale.h>
#include <windows.h>

int global_func = 2; 	//Variavel global para selecionar a fun��o de op��o do usuario
int aux_global = 1; 
int vetor_global[3] = {0,0,0};

//Rotina para posicionar o curso na tela
void gotoxy(int x, int y){
     SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),(COORD){x-1,y-1});
}
/*******************************************************************************
			AS ROTINAS DAS FUN��ES MAT�MATICAS DE 1 OU MAIS VARIAVEIS 
*******************************************************************************/
//Nessa parte do c�digo ficam as fun��es que s�o alteradas pelas variaveis globais 
//global_func e global_funcN... Essa fun��es s�o chamadas durante a execu��o dos
//m�todos, logo alterando essas fun��es, far� com que os m�todos trabalhem com 
//a fun��o alterada
// -----------------    Fun��es polinomiais e trigonometricas
float f(float x){	
	if(global_func == 1)	return (x + 2*cos(x)); 
	if(global_func == 2)	return (pow(x,3) - 4*(pow(x,2)) + x + 6);
	if(global_func == 3)	return (pow(x,5) - (10/9)*pow(x,3) + (5/21)*x);	
	//return pow(sin(x),2);
}
// -----------------    Muda a string da fun��o escolhida
void defini_func (char s[]){	
	if(global_func == 1)	
		strcpy(s,"f(x) = x + 2cos(x)"); 
	if(global_func == 2)
		strcpy(s,"f(x) = x^3 - 4x^2 + x + 6");
	if(global_func == 3)
		strcpy(s,"f(x) = x^5 - (10/9)x^3 + (5/21)x");	
}
// -----------------    Fun��es de mais de uma variaveis (max 3)
float fN(float x, float y, float z){
	if(aux_global == 1)
		return (3*x + 2*x*y + y*y);	
	if(aux_global == 2)
		return (2*pow(x,3) - 3*pow(y,2) + z*x*y);	
	if(aux_global == 3)
		return (3*z + 2*x*y + y*y);	
}
// -----------------    Muda a string da fun��o de mais de uma variavel escolhida
void defini_funcN (char sN[]){	
	strcpy(sN,"f(x) = x1^2 + 2*x1*x2 + x2^3");
}
/******************************************************************************
					ROTINAS DE C�LCULOS MATEM�TICOS SIMPLES
*******************************************************************************/
//Fun��o para verificar a converg�ncia
int conve(float a,float b, float func (float v)){						
	float fa = func(a), fb = func(b);
	if((fa*fb) < 0)
		return 1; 
	else return 0; 
}
//FUN��O PARA RETORNAR O MODULO DE UM VALOR 
float modulo(float x){		
	if(x < 0) 
		return x * (-1);
	else 
		return x; 
}
//FUN��O PARA RETORNAR O MODULO DE UM INTERVALO 
float moduloIntervalo(float b, float a){	
	if(b - a < 0)
		return (b-a) * (-1);
	else return b - a;
}
//Fun��o para calcular m�dia
float media(float a, float b){ 	
	return ((a+b)/2);
}
//Fun��o para calcular a m�dia ponderada
float mediaPonderada(float a, float b, float fa, float fb){	// 0 - N�o divide nada, 1 - f(a)/2, 2 - f(b)/2
	return (a*fb - b*fa) / (fb - fa); }
//Fun��o para retornar valor maior que 1, ou 1 
float max(float x){		
	if(modulo(x) > 1)
		return x; 
	else return 1.0; 
}
//Arredonda o valor
int arredonda(double number){	
    return (number >= 0) ? (int)(number + 0.5) : (int)(number - 0.5);
}

float parcial (float x, float y, float z, float h[]){
	return ((fN(x + h[0],y + h[1],z + h[2]) - fN(x - h[0],y - h[1],z - h[2]))/(2*(h[0]+h[1]+h[2])));  
}
void gradiente (int qtd, float v[], float grad[]){
	
	float h[3] = {0,0,0}, der_ant, erro, erro_ant;  
	int cont = 0; 
	
	for (int i=0; i < qtd; i++){
		h[i] = 1; 
		cont = 0; 
		while(true){
			cont++; 
			grad[i] = parcial(v[0],v[1],v[2],h);
			if(cont >= 2){
				erro = modulo (grad[i] - der_ant) / max(grad[i]); 
				if(erro < 0.001) break;
				
				if(cont > 2)
					if(erro > erro_ant) break; 
				erro_ant = erro; 
			}			
			der_ant = grad[i]; 
			h[i] = h[i] / 2; 
		}
		h[i] = 0; 			
	}	
}
/*******************************************************************************
							DIFERENCIA��O NUM�RICA
*******************************************************************************/
//Equa��o para o c�lculo da derivada primera
float derivada_da_primeira(float x, float h,float func(float v)){
	return (func(x+h) - func(x-h))/(2*h);		
}
//Equa��o para o c�lculo da derivada segunda
float derivada_da_segunda(float x, float h,float func (float v)){
	return ((func(x + (2*h))) - 2*(func(x)) + (func(x - (2*h))))/((2*h)*(2*h));	
}
//Fun��o para calcular derivada primeira
float df(float pre, int max_ite, float func(float v), float x){
	int ite_fi = 0;
	float fx, fx_ant, erro_ant,erro, h = 1; 
	int ver=0;
	while(ite_fi != max_ite && ver == 0){
		fx_ant = fx;
		fx = derivada_da_primeira(x,h,func);
		//
		if(ite_fi > 0){ // calculo das condi?oes de parada
			erro_ant = erro;
			erro = modulo(fx - fx_ant) / max(fx);
			if(erro < pre) 
				ver = 1;
			if(ite_fi > 1 && erro > erro_ant) 
				ver = 2;
		}
		h = h/2;
		ite_fi++;
	}
	
	if(ver==0) 	
		return 0;
	if(ver==1) 
		return fx;
	return fx_ant;
		
}
//Fun��o para calcular derivada segunda
float df2(float pre, int max_ite, float func(float v), float x){
	float fx, fx_ant, erro_ant,erro, h = 1; 
	int ver=0, ite_fi = 0; 
	while(ite_fi != max_ite && ver == 0){
		fx_ant = fx;
		fx = derivada_da_segunda(x,h,func);
		if(ite_fi > 0){ // calculo das condi�oes de parada
			erro_ant = erro;
			erro = modulo (fx - fx_ant)/ max(x);
			if(erro < pre) 
				ver = 1;
			if(ite_fi > 1 && erro > erro_ant) 
				ver = 2;
		}
		h /= 2;
		ite_fi++;
	}
	
	if(ver==0) 
		return 0;
	if(ver==1) 
		return fx;
	return fx_ant;
}
//Procedimento Jacobiano
void Jacobiano (int qtd, int qq, float v[], float ja[][3]){
	
	for(int i = 0; i < qtd; i++){
			
	if(vetor_global[i] == 0)
			continue; 
	aux_global = i+1; 		
	gradiente(qtd,v,ja[i]); 
	}
	
	aux_global = 0; 
}
//Procedimento Hessiana
void Hessiana(int vetor_x, float funcN(float v), int v[], int hess[][10]){
	
}
/******************************************************************************
						C�LCULO DOS ZEROS DE FUN��ES
******************************************************************************/
//M�todo da bisse��o 
int bissecao(float pre, int ite, float fun(float v), float a, float b, int *ite_fi, float *x){	//Parametros colocados de acordo com o documento do trabalho
	
	(*ite_fi)++;
	if(*ite_fi >= ite) 
			return 0; 
	
	if((conve(a,b,fun)) ==  1){			//Tem um intervalo v�lido 
		(*x) = media(a,b);
		if (modulo(fun(*x)) < pre)
			return 1; 
		else if(moduloIntervalo(b,a) < pre)
				return 1; 
			else{
				if(conve(a,(*x),fun) == 1)
					return bissecao(pre,ite,fun,a,(*x),&(*ite_fi),&(*x));
				else return bissecao(pre,ite,fun,(*x),b,&(*ite_fi),&(*x));
			}
	}else return -1; 		
}
//M�todo Posi��o Falsa
int PosicaoFalsa(float pre, int ite_max, float func(float v), float a, float b, int *ite_fi, float *x){
	
	(*ite_fi)++; 
	if(*ite_fi >= ite_max)
		return 0;
		
	if((conve(a,b,func)) == 1){
		(*x) = mediaPonderada(a,b,func(a),func(b));
		if(modulo(func(*x)) < pre)
			return 1; 
		else if(moduloIntervalo(b,a) < pre)
			return 1; 
			else {
				if(conve(a,(*x),func) == 1)
					return PosicaoFalsa(pre,ite_max,func,a,(*x),&(*ite_fi),&(*x));
				else return PosicaoFalsa(pre,ite_max,func,(*x),b,&(*ite_fi),&(*x));
			}
		
	}else return -1; 
}
//M�todo da Posi��oo Falsa modificada
int PosicaoFalsaModificada(float pre, int max_ite,float func(float v),float a, float b, int *ite_fi, float *x){
	
	(*ite_fi) = 0; 
	int ver = 0; 
	float x0 = a, aux; 	
	float a_ant, b_ant; 
		
	if(conve(a,b,func) == 1){
		
		(*ite_fi)++; 		//1� itera��o da rotina
		(*x) = mediaPonderada(a,b,func(a),func(b));		//Calcula x com a media ponderada normalmente 
		a_ant = a; b_ant = b; 							//Atribui os primeiros valores de a e b pras variaveis anteriores
					
		if(func(a) * func(*x) < 0)			//Verifica o novo intervalo 
			b = (*x); 
		else a = (*x); 
		
		if(modulo(func(*x)) < pre || moduloIntervalo(b,a) < pre)	//Verifica o crit�rio de parada
			return 1; 
		
		while (ver == 0){		//Ver � a variavel de verifica��o de erros 
			(*ite_fi)++; 
			if((*ite_fi) > max_ite) 
				return 0;
				
			aux = (*x); 	//Armaneza o valor de x
			
			if((func(x0) * func(*x)) > 0){		//Verifica se fx0 e fx > 0
				if(a_ant == a)					//Verifica se o ponto fixo � o a
					(*x) = mediaPonderada(a,b,func(a)/2,func(b));
				if(b_ant == b)					//Verifica se o ponto fixo � o b
					(*x) = mediaPonderada(a,b,func(a),func(b)/2);
			}else (*x) = mediaPonderada(a,b,func(a),func(b)); 		//Calcula normamente se fx0 e fx > 0 = false
			
			a_ant = a; b_ant = b; 		//Armazena os valores de a e b 
				
			if(func(a) * func(*x) < 0)			//Verifica o novo intervalo 
				b = (*x); 
			else a = (*x);
				
			x0 = aux; 					//Atribui para x0 o valor de x antes do novo c�lculo 
			
			if(modulo(func(*x)) < pre || moduloIntervalo(b,a) < pre)  // Verifica os crit�rios de parada
				return 1; 				
		}		//Final do while
	}else return -1;
	system("pause");
	}
//M�todo de Newton
int Newton (float pre, int ite_max, float func(float v), float *x0, int *ite_fi, float *x){
	(*ite_fi)++; 		//Somando 1 no n�mero de itera��es 
	if((*ite_fi) >= ite_max)
		return 0; 				//N�mero de itera��es excedeu o limite
	if(df(pre,20,func,*x0) != 0){	//Verifica se a derivada da fun��o � diferente de 0
		(*x) =  (*x0) - ((f(*x0))/df(pre,20,func,*x0));		//Atribui o novo valor a x, dependendo do valor anterior
		if(modulo(f(*x)) < pre)		//Verificar se o primeiro criterio de parada foi atendido
			return 1;		//Retorna
		if((modulo((*x) - (*x0))/max(*x)) < pre)	//Verifica se o segundo criterio de parada foi atendido
			return 1; 		//Retorna	
		(*x0) = (*x);		//Atribui o valor de x para o x0 
		return Newton(pre,ite_max,f,&(*x0),&(*ite_fi),&(*x));	//Chama newton novamente	
	}else return -1;
	return 0;		//Derivada da fun��o � = 0, falha no processamento
}
//M�todo Newton Modificado
float NewtonModificado(float pre,int ite_max, float func(float v), float *x0, int *ite_fi, float *x){
	
	(*ite_fi)++; 
	if((*ite_fi) >= ite_max)
		return 0; 
	if(df(pre,20,func,*x0) != 0){		//Verifica se a derivada da fun��o � diferente de 0
		float x_anterior = (*x); 
		if((*ite_fi) == 1)
			(*x) = (*x0) - (f(*x0)/df(pre,20,func,*x0)); 
		else (*x) = x_anterior - (f(x_anterior)/df(pre,20,func,*x0)); 
	if(modulo(f(*x)) < pre)
		return 1; 
	if((modulo((*x) - x_anterior)/max(*x)) < pre)
		return 1;  
	if((*ite_fi) % 5 == 0)
		if(df(pre,20,func,*x) != 0)
			(*x0) = (*x);
	return NewtonModificado(pre,ite_max,f,&(*x0),&(*ite_fi),&(*x));		
	}else return -1; 
}
/*****************************************************************************
						COLETA DE DADOS DO USUARIO
*****************************************************************************/
//Coleta de dados da bisse��o, cordas, e cordas modificados
void coleta_dados(float *precisao, int *maximo_iteracoes, float *lim_inferior, float *lim_superior){
	
	float aux; 	
	printf("\n\n\tDigite a precis�o:\n");
	printf("\tDigite o numero maximo de itera��es:\n");
	printf("\tDigite os limites\n");
	printf("\t   Inferior:          Superior: \n");
	
	do{		//precisao
		gotoxy(28,6);
		printf("           ");
		gotoxy(28,6); 
		scanf("%f",&(*precisao));
		if((*precisao) < 0){
			gotoxy(5,15);
			printf("\n\tValor negativo! Dado Invalido!");
		}			
	}while((*precisao) < 0);
	
	gotoxy(5,15); 
	printf("\n                                              ");
	
	do{		//Numero maximo de itera�oes
		gotoxy(46,7); 
		printf("         "); 
		gotoxy(46,7);
		scanf("%d",&(*maximo_iteracoes));
		if((*maximo_iteracoes) <= 0){
			gotoxy(5,15); 
			printf("\n\tValor Negativo ou igual a zero! Dado Invalido!");
		}
	}while((*maximo_iteracoes) <= 0); 
	
	gotoxy(5,15); 
	printf("\n                                                          ");
	
	do{		//Limite inferior
		gotoxy(22,9); 
		printf("        ");
		gotoxy(22,9); 				
	}while(!scanf("%f",&(*lim_inferior)));
	
	do{		//Limite superior
		gotoxy(41,9); 
		printf("        "); 
		gotoxy(41,9); 
	} while(!scanf("%f",&(*lim_superior)));
	
	if((*lim_superior) < (*lim_inferior)){				//Verifica??o caso o usuario digite os valores invertidos
		gotoxy(5,15); 
		printf("\n\tLimites invertidos! Limites trocados!");
		aux = (*lim_inferior); 
		(*lim_inferior) = (*lim_superior); 
		(*lim_superior) = aux; 
	}	
	gotoxy(5,10);
}
//Coleta de dados de Newton e Newton Modificado
void coleta_dados2(float *precisao,int *maximo_iteracoes, float *x0){
	
	printf("\n\tDigite a precis�o: "); 	 
	printf("\n\tDigite o numero maximo de itera��es: "); 	
	printf("\n\tDigite um x0: "); 
	
	do{
		gotoxy(28,5); 
		printf("                               ");
		gotoxy(28,5); 
		scanf("%f",&(*precisao));
		if((*precisao) <= 0){
			gotoxy(1,20); 
			printf("\n\tValor Invalido! Digite novamente!"); 
		}			
	}while((*precisao) <= 0); 
	
	gotoxy(1,20); 
	printf("\n\t                                                   "); 
	
	do{
		gotoxy(46,6); 
		printf("                                 "); 
		gotoxy(46,6); 
		scanf("%d",&(*maximo_iteracoes)); 
		if((*maximo_iteracoes) <= 0){
			gotoxy(1,20); 
			printf("\n\tValor Invalido! Digite Novamente!");
		}
	}while((*maximo_iteracoes) <= 0); 
	
	gotoxy(1,20); 
	printf("\n\t                                                   "); 
	
	do{
		gotoxy(23,7); 
		printf("                                 ");
		gotoxy(23,7); 
	}while(!scanf("%f",&(*x0)));
	
	//printf("\n")
}
//Coleta de dados para o c�lculo das derivadas
void coleta_dados_der(float *precisao, int *max_ite, float *x){
	
	printf("\n\tDigite a precis�o: "); 
	printf("\n\tDigite o numero maximo de itera��es: ");
	printf("\n\tDigite o valor de x: "); 
	
	do{
		gotoxy(30,5); 
		printf("                               "); 
		gotoxy(30,5); 
		scanf("%f",&(*precisao)); 		
	}while((*precisao) <= 0); 
	
	do{
		gotoxy(46,6); 
		printf("                               "); 
		gotoxy(46,6); 
		scanf("%d",&(*max_ite)); 
	}while((*max_ite) <= 0); 
	
	do{
		gotoxy(30,7); 
		printf("                               "); 
		gotoxy(30,7); 
	}while(!scanf("%f",&(*x)));
}
/*****************************************************************************
					ROTINAS DA INTERFACE COM O USUARIO
*****************************************************************************/
//Fun��o para mostrar o menu principal para o usuario
int menu(char s[],char sN[]){
	
	int x; 
	system("cls");
	printf("\n\tTrabalho de MNC - Ci�ncias da Computa��o\n");
	printf("\n\tFun��o de uma variavel escolhida atualmente:      %s",s);
	printf("\n\tFun��o de duas variaveis escolhida atualmanete:   %s",sN);
	printf("\n\n\tEscolha o m�todo a ser utilizado (digite em decimal):\n");
	printf("\n\t1  -  Bisse��o");
	printf("\n\t2  -  Posi��o Falsa (cordas)"); 
	printf("\n\t3  -  Posi��o Falsa Modificada (cordas modificado)");
	printf("\n\t4  -  Newton");
	printf("\n\t5  -  Newton Modificado");
	printf("\n\t6  -  Derivada primeira");
	printf("\n\t7  -  Derivada segunda");
	printf("\n\t8  -  Jacobiano");
	printf("\n\t9  -  Hessiana");
	printf("\n\tA  -  Definir fun��o de uma vari�vel");
	printf("\n\tB  -  Definir fun��o de duas vari�veis");
	printf("\n\tC  -  Sair do programa!");
	printf("\n\n\tOp��o: ");
	
	do{			
		gotoxy(17,22); 
		printf("              "); 
		gotoxy(17,22);
		scanf("%d",&x);
		if(x <= 0 || x > 11){
			gotoxy(1,26); 
			printf("\n\tOp��o Invalida! Digite novamente!"); 
		}
			
	}while(x <= 0 || x > 12);
	
	gotoxy(1,26); 
	printf("\n\t                                                 ");
	gotoxy(1,23); 
	return x; 
}
//Fun��o somente pra printar 1 string (fun��o)
void print_fx(char s[]){
	printf("\n\n\tFun��o utilizada: %s",s); 
}
//Escreve a tela que o usuario escolheu no menu principal
void tela(int op,char s[], float *e, int *iteracoes, float *lim_inf, float *lim_sup){	//Op??o selecionada, String da fun??o, Precis?o, 
																						//Numero de itera??es, limite inferior e superior																				
	system("cls");
	printf("\n\t ");
	switch(op){
		case 1: 	printf("M�todo da Bisse��o");
					print_fx(s);
					coleta_dados(&(*e),&(*iteracoes),&(*lim_inf),&(*lim_sup)); //Fun??o de coleta dos dados do usuario
									
					printf("\n\t"); 
					system("pause");					
					break;
					
		case 2: 	printf("M�todo da Posi��o Falsa");
					print_fx(s); 
					coleta_dados(&(*e),&(*iteracoes),&(*lim_inf),&(*lim_sup)); //Fun??o de coleta dos dados do usuario
					
					printf("\n\t"); 
					system("pause");
					break; 
					
		case 3: 	printf("M�todo da Posi��o Falsa Modificada");
					print_fx(s);
					coleta_dados(&(*e),&(*iteracoes),&(*lim_inf),&(*lim_sup)); 					
					printf("\n\t"); 
					system("pause");
					break; 
					
		case 4: 	printf("M�todo de Newton"); 
					print_fx(s);
					coleta_dados2(&(*e),&(*iteracoes),&(*lim_inf));
					printf("\n\t"); 
					system("pause"); 
					break; 
					
		case 5: 	printf("M�todo de Newton Modificado"); 
					print_fx(s);
					coleta_dados2(&(*e),&(*iteracoes),&(*lim_inf)); 
					printf("\n\t"); 
					system("pause");
					break;
					
		case 6: 	printf("C�lculo da derivada primeira"); 
					print_fx(s);
					coleta_dados_der(&(*e),&(*iteracoes),&(*lim_inf)); 
					printf("\n\t"); 
					system("pause");
					break; 
					
		case 7: 	printf("C�lculo da derivada segunda"); 
					print_fx(s);
					coleta_dados_der(&(*e),&(*iteracoes),&(*lim_inf)); 
					printf("\n\t"); 
					system("pause");
					break; 
		case 8: 	printf("C�lculo da matriz Jacobiana!"); 
					print_fx(s);
					printf("\n\n\t\t\tAinda em desenvolvimento!!!"); 
					printf("\n\t"); 
					//system("pause"); 
					break; 
		case 9: 	printf("C�lculo da matriz Hessiana!"); 
					print_fx(s); 
					printf("\n\n\t\t\tAinda em desenvolvimento!!!"); 
					printf("\n\t"); 
					//system("pause"); 
					break; 						
	}
}
/****************************************************************************
			IMPRESS�O DOS RESULTADOS NA TELA PARA O USUARIO
****************************************************************************/
//Mostra os resultados, tamb�m mostra os valores digitados pelo usuario (bisse��o, cordas e cordas modificado)
void mostra_resultado(int flag, float precisao, int max_ite, float a, float b, int iteracoes, float raiz){
	
	system("cls");
	printf("\n\tDados fornecidos pelo usuario: \n"); 
	printf("\n\tPrecis�o: %f",precisao); 
	printf("\n\tN�mero maximo de itera��es: %d",max_ite); 
	printf("\n\tLimite Inferior: %.2f e Limite Superior: %.2f",a,b); 
	
	if(flag != -1)	{		
		if(flag == 0){
			printf("\n\n\tN�O HOUVE CONVERG�NCIA NO RESULTADO!"); 
			printf("\n\tN�MERO M�XIMO DE ITERA��ES ULTRAPASSADAS\n"); 
		}
		
		printf("\n\n\tRESULTADOS OBTIDOS:\n"); 
		printf("\n\tRaiz: %f\n\tNumero de itera��es: %d\n\t",raiz,iteracoes);
		printf("Numero arredondado para inteiro: %d\n\n\t", arredonda(raiz));
	}else {		
		printf("\n\n\tM�todo n�o convergiu!"); 
		printf("\n\tC�lculo n�o efetuado..."); 
		printf("\n\n\tPor favor tente novamente com um novo intervalo.\n\n\t");		
	}
}
//Mostra os resultados de Newton e Newton modificado
void mostra_resultado2(int flag, float precisao, int max_ite, float x0, int iteracoes, float raiz){
	
	system("cls");
	printf("\n\tDados fornecidos pelo usuario: \n"); 
	printf("\n\tPrecis�o: %f",precisao); 
	printf("\n\tN�mero m�ximo de itera��es: %d",max_ite); 
	printf("\n\tValor de x0: %f",x0); 
	if(flag != -1){
		if(flag == 0){
			printf("\n\n\tN�O HOUVE CONVERG�NCIA NO RESULTADO!"); 
			printf("\n\tN�MERO MAXIMO DE ITERA��ES ULTRAPASSADAS\n"); 
		}
		
		printf("\n\n\tRESULTADOS OBTIDOS:\n"); 
		printf("\n\tRaiz: %f\n\tNumero de itera��es: %d\n\t",raiz,iteracoes);
		printf("Numero arredondado para inteiro: %d\n\n\t", arredonda(raiz));
	}else {
		printf("\n\n\tCrit�rio de converg�ncia n�o atendido!"); 
		printf("\n\tC�lculo n�o foi efetuado!"); 
		
		printf("\n\n\tPor favor tente novamente com uma nova fun��o!\n\n\t"); 
	}

}
//Mostra o resultado da derivada primeira
void mostra_der(float precisao, int max_ite, float x){
	
	system("cls"); 
	printf("\n\tPrecis�o: %f",precisao); 
	printf("\n\tMaximo de itera��es: %d",max_ite); 
	
	printf("\n\n\tValor da derivada: %f",x); 
	printf("\n\t"); 	
}

void printa_matriz (float v[][3],int n){
	for(int i = 0; i < n; i++){
		printf("\n"); 
		for(int j = 0; j < n; j++)
			printf("   %f    ",v[i][j]);
	}
	
}
// Fun��o main
int main(){

	setlocale(LC_ALL,"Portuguese");
	int op, ite; 
	float x, pre, l_inf, l_sup;// n_sei;
	//Resultados: 
	int ite_fim, aux;
	float raiz, aux2, derivada1, derivada2; 
	//String da fun��o
	char s_func[30], s_funcN[30]; 
	
	do{
		defini_func(s_func);
		defini_funcN(s_funcN);
		op = menu(s_func,s_funcN); 
		ite_fim = 0; 
		raiz = 0;
		switch(op){
			case 1: 	// M�TODO DA BISSE��O 	
						tela(op,s_func,&pre,&ite,&l_inf,&l_sup);					
						aux = bissecao(pre,ite,f,l_inf,l_sup,&ite_fim,&raiz); 	//Chama o m�todo da bisse��o 
					    mostra_resultado(aux,pre,ite,l_inf,l_sup,ite_fim,raiz);	//Impress�o do resultado na tela
						system("pause");																
						break;
						
			case 2: 	//M�TODO DA POSI��O FALSA
						tela(op,s_func,&pre,&ite,&l_inf,&l_sup);
						aux = PosicaoFalsa(pre,ite,f,l_inf,l_sup,&ite_fim,&raiz);
						mostra_resultado(aux,pre,ite,l_inf,l_sup,ite_fim,raiz);	//Impress�o do resultado na tela
						system("pause");					 
						break; 
						
			case 3: 	//M�TODO DA POSI��O FALSA MODIFICADA
						tela(op,s_func,&pre,&ite,&l_inf,&l_sup);
						aux = PosicaoFalsaModificada(pre,ite,f,l_inf,l_sup,&ite_fim,&raiz);						
						mostra_resultado(aux,pre,ite,l_inf,l_sup,ite_fim,raiz);	//Impress�o do resultado na tela
						system("pause");
						break; 
						
			case 4: 	//M�TODO DE NEWTON
						tela(op,s_func,&pre,&ite,&l_inf,&l_sup);
						aux2 = l_inf; 
						aux = Newton(pre,ite,f,&l_inf,&ite_fim,&raiz);
						mostra_resultado2(aux,pre,ite,aux2,ite_fim,raiz);		//Impress�o do resultado na tela
						system("pause");
						break; 
						
			case 5: 	//M�TODO DE NEWTON MODIFICADO
						tela(op,s_func,&pre,&ite,&l_inf,&l_sup); 
						aux2 = l_inf; 
						aux = NewtonModificado(pre,ite,f,&l_inf,&ite_fim,&raiz); 
						mostra_resultado2(aux,pre,ite,aux2,ite_fim,raiz); 		//Impress�o do resultado na tela
						system("pause");
						break;
						
			case 6: 	//C�LCULO DA DERIVADA
						tela(op,s_func,&pre,&ite,&l_inf,&l_sup);
						derivada1 = df(pre,ite,f,l_inf); 
						mostra_der(pre,ite,derivada1); 							//Impress�o do resultado na tela
						system("pause");
						break; 
						
			case 7: 	//C�LCULO DA DERIVADA SEGUNDA
						tela(op,s_func,&pre,&ite,&l_inf,&l_sup); 
						derivada2 = df2(pre,ite,f,l_inf); 
						mostra_der(pre,ite,derivada2); 							//Impress�o do resultado na tela
						system("pause"); 
						break; 
						
			case 8: 	//C�LCULO DA MATRIZ JACOBIANA
						tela(op,s_func,&pre,&ite,&l_inf,&l_sup);
						system("pause"); 
						break; 
						
			case 9: 	//C�LCULO DA MATRIZ HESSIANA
						tela(op,s_func,&pre,&ite,&l_inf,&l_sup);
						system("pause"); 
						break; 	
						
			case 10: 	system("cls"); 
						printf("\n\tEscolha a fun��o de uma variavel a ser computada:\n");
						printf("\n\t1 - f(x) = x + 2cos(x)"); 
						printf("\n\t2 - f(x) = x^3 - 4x^2 + x + 6"); 
						printf("\n\t3 - f(x) = x^5 - (10/9)x^3 + (5/21)x");
						printf("\n\n\tOp��o: ");
						do{
							scanf("%d",&global_func); 
						}while(global_func < 1 || global_func > 3); 
						printf("\n\tFun��o Escolhida com sucesso!\n\t"); 
						system("pause");
						break; 		
						
			case 11: 	system("cls"); 
						int cont = 0, x, max_x = 2; 
						float valores_x[3], jaco[3][3];
						
						printf("\n\tEscolha a fun��o de mais de uma variavel a ser computada:\n");
						printf("\n\t1 - f(x,y,z) = 3x + 2xy + y^2"); 
						printf("\n\t2 - f(x,y,z) = 2x^3 - 3y^2 + zxy"); //(2*pow(x,3) - 3*pow(y,2) + z*x*y);	
						printf("\n\t3 - f(x,y,z) = 3z + 2xy + y^2");	//(3*z + 2*x*y + y*y);	
						printf("\n\n\tOp��o: ");
						do{
							gotoxy(17,8);
							printf("   "); 
							gotoxy(17,8);
							scanf("%d",&x);
							if(x >= 1 && x <= 3){
								if(vetor_global[x-1] != 1){
									if(x == 2 || x == 3)
										max_x = 3; 
									gotoxy(50,12+cont); 
									printf("\n\tFunc�o %d selecionada!",x);
									vetor_global[x-1] = 1; 
									cont++; 
								}			
							} 
						}while(x != -1 && cont < 3); 
						
						system("cls"); 
						
						printf("\n\n\tDigite os valores de x\n "); 
						for(int i=0; i<max_x; i++){
							printf("\tx%d: ",i+1); 
							scanf("%f",&valores_x[i]);
						}
						
						Jacobiano (cont,0,valores_x,jaco);						
						printa_matriz(jaco,3);
						
						for(int i=0; i<3; i++)
							vetor_global[i] = 0; 

						printf("\n\t");
						system("pause");
						break; 			
		}
	}while(op != 12);
	
	printf("\n\n\tFim do programa!");
}

