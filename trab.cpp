//  Trabalho 1 - Métodos Numéricos Computacionais
//  
//  Grupo: 
//			Gabriel Vieira
//			Leonardo Silva de Oliveira
//			Renan Scatolino Mesquita

// PRECISA MODIFICAR AS ROTINAS DE NEWTON E NEWTON MODIFICADO

#include <math.h>
#include <stdio.h>
#include <conio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <locale.h>
#include <windows.h>

int global_func = 2; 	//Variavel global para selecionar a função de opção do usuario
//Rotina para posicionar o curso na tela
void gotoxy(int x, int y){
     SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),(COORD){x-1,y-1});
}

/******************************************************************************
					ROTINAS DE CÁLCULOS MATEMÁTICOS SIMPLES
*******************************************************************************/
//Função para começar a implementar 
float f(float x){	
	if(global_func == 1)	return (x + 2*cos(x)); 
	if(global_func == 2)	return (pow(x,3) - 4*(pow(x,2)) + x + 6);
	if(global_func == 3)	return (pow(x,5) - (10/9)*pow(x,3) + (5/21)*x);	
	//return pow(sin(x),2);
}
//Funçãoo para verificar a convergência
int conve(float a,float b, float func (float v)){						
	float fa = func(a), fb = func(b);
	if((fa*fb) < 0)
		return 1; 
	else return 0; 
}
//FUNÇÃO PARA RETORNAR O MODULO DE UM VALOR 
float modulo(float x){		
	if(x < 0) 
		return x * (-1);
	else 
		return x; 
}
//FUNÇÃO PARA RETORNAR O MODULO DE UM INTERVALO 
float moduloIntervalo(float b, float a){	
	
	if(b - a < 0)
		return (b-a) * (-1);
	else return b - a;
}
//Função para calcular média
float media(float a, float b){ 	
	return ((a+b)/2);
}
//Função para calcular a média ponderada
float mediaPonderada(float a, float b, float fa, float fb){	// 0 - Não divide nada, 1 - f(a)/2, 2 - f(b)/2
	return (a*fb - b*fa) / (fb - fa); }
//Função para retornar valor maior que 1, ou 1 
float max(float x){		
	if(modulo(x) > 1)
		return x; 
	else return 1.0; 
}
//Arredonda o valor
int arredonda(double number){
	
    return (number >= 0) ? (int)(number + 0.5) : (int)(number - 0.5);
}
/*******************************************************************************
							DIFERENCIAÇÃO NUMÉRICA
*******************************************************************************/
//Equação para o cálculo da derivada primera
float derivada_da_primeira(float x, float h,float func(float v)){
	return (func(x+h) - func(x-h))/(2*h);		
}
//Equação para o cálculo da derivada segunda
float derivada_da_segunda(float x, float h,float func (float v)){
	return ((func(x + (2*h))) - 2*(func(x)) + (func(x - (2*h))))/((2*h)*(2*h));	
}
//Função para calcular derivada primeira
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
//Função para calcular derivada segunda
float df2(float pre, int max_ite, float func(float v), float x){
	float fx, fx_ant, erro_ant,erro, h = 1; 
	int ver=0, ite_fi = 0; 
	while(ite_fi != max_ite && ver == 0){
		fx_ant = fx;
		fx = derivada_da_segunda(x,h,func);
		if(ite_fi > 0){ // calculo das condiçoes de parada
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
void Jacobiano(int vetor_X, int num_equacoes, float funcN(float v), int v[], int jaco[10][10]){
	
}
//Procedimento Hessiana
void Hessiana(int vetor_x, float funcN(float v), int v[], int hess[][10]){
	
}
/******************************************************************************
						CÁLCULO DOS ZEROS DE FUNÇÕES
******************************************************************************/
//Método da bisseção 
int bissecao(float pre, int ite, float fun(float v), float a, float b, int *ite_fi, float *x){	//Parametros colocados de acordo com o documento do trabalho
	
	(*ite_fi)++;
	if(*ite_fi >= ite) 
			return 0; 
	
	if((conve(a,b,fun)) ==  1){			//Tem um intervalo v?lido 
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
	}else {
		printf("\n\tn?o ? possivel"); 
	}		
}
//Método Posição Falsa
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
		
	}else printf("n?o ? possivel");	
}
//Método da Posiçãoo Falsa modificada
int PosicaoFalsaModificada(float pre, int max_ite,float func(float v),float a, float b, int *ite_fi, float *x){
	

}
//Método de Newton
int Newton (float pre, int ite_max, float func(float v), float *x0, int *ite_fi, float *x){
	(*ite_fi)++; 		//Somando 1 no n?mero de itera??es 
	if((*ite_fi) >= ite_max)
		return 0; 				//N?mero de itera??es excedeu o limite
	if(df(pre,20,func,*x0) != 0){	//Verifica se a derivada da fun??o ? diferente de 0
		(*x) =  (*x0) - ((f(*x0))/df(pre,20,func,*x0));		//Atribui o novo valor a x, dependendo do valor anterior
		if(modulo(f(*x)) < pre)		//Verificar se o primeiro criterio de parada foi atendido
			return 1;		//Retorna
		if((modulo((*x) - (*x0))/max(*x)) < pre)	//Verifica se o segundo criterio de parada foi atendido
			return 1; 		//Retorna	
		(*x0) = (*x);		//Atribui o valor de x para o x0 
		return Newton(pre,ite_max,f,&(*x0),&(*ite_fi),&(*x));	//Chama newton novamente	
	}else printf("n?o ? possivel");
	return 0;		//Derivada da fun??o ? = 0, falha no processamento
}
//M?todo Newton Modificado
float NewtonModificado(float pre,int ite_max, float func(float v), float *x0, int *ite_fi, float *x){
	
	(*ite_fi)++; 
	if((*ite_fi) >= ite_max)
		return 0; 
	if(df(pre,20,func,*x0) != 0){
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
	}else printf("n?o ? possivel");
}
/*****************************************************************************
						COLETA DE DADOS DO USUARIO
*****************************************************************************/
//Coleta de dados da bisse??o, cordas, e cordas modificados
void coleta_dados(float *precisao, int *maximo_iteracoes, float *lim_inferior, float *lim_superior){
	
	float aux; 	
	printf("\n\n\tDigite a precis?o:\n");
	printf("\tDigite o numero maximo de itera??es:\n");
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
	
	do{		//Numero maximo de iteracoes
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
	
	printf("\n\tDigite a precis?o: "); 	 
	printf("\n\tDigite o numero maximo de itera??es: "); 	
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

void coleta_dados_der(float *precisao, int *max_ite, float *x){
	
	printf("\n\tDigite a precis?o: "); 
	printf("\n\tDigite o numero maximo de itera??es: ");
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

//Fun??o para mostrar o menu principal para o usuario
int menu(char s[]){
	
	int x; 
	system("cls");
	printf("\n\tTrabalho de MNC - Ci?ncias da Computa??o");
	printf("\n\tFun??o atual escolhida: %s",s);
	printf("\n\n\tEscolha o m?todo a ser utilizado:\n");
	printf("\n\t1 - Bisse??o");
	printf("\n\t2 - Posi??o Falsa"); 
	printf("\n\t3 - Posi??o Falsa Modificada");
	printf("\n\t4 - Newton");
	printf("\n\t5 - Newton Modificado");
	printf("\n\t6 - Derivada primeira");
	printf("\n\t7 - Derivada segunda");
	printf("\n\t8 - Jacobiano");
	printf("\n\t9 - Hessiana");
	printf("\n\t10 - Definir fun??o");
	printf("\n\t11- Sair do programa!");
	printf("\n\n\tOp??o: ");
	
	do{			
		gotoxy(17,19); 
		printf("              "); 
		gotoxy(17,19);
		scanf("%d",&x);
		if(x <= 0 || x > 11){
			gotoxy(1,24); 
			printf("\n\tOp??o Invalida! Digite novamente!"); 
		}
			
	}while(x <= 0 || x > 11);
	
	gotoxy(1,24); 
	printf("\n\t                                                 ");
	gotoxy(1,20); 
	return x; 
}
//Escreve a tela que o usuario escolheu no menu principal
void tela(int op,char s[], float *e, int *iteracoes, float *lim_inf, float *lim_sup){	//Op??o selecionada, String da fun??o, Precis?o, 
																						//Numero de itera??es, limite inferior e superior																				
	system("cls");
	printf("\n\t ");
	switch(op){
		case 1: 	printf("M?todo da Bisse??o");
					printf("\n\n\tFun??o utilizada: %s",s); 
					coleta_dados(&(*e),&(*iteracoes),&(*lim_inf),&(*lim_sup)); //Fun??o de coleta dos dados do usuario
									
					printf("\n\t"); 
					system("pause");					
					break;
					
		case 2: 	printf("M?todo da Posi??o Falsa");
					printf("\n\n\tFun??o utilizada: %s",s); 
					coleta_dados(&(*e),&(*iteracoes),&(*lim_inf),&(*lim_sup)); //Fun??o de coleta dos dados do usuario
					
					printf("\n\t"); 
					system("pause");
					break; 
					
		case 3: 	printf("M?todo da Posi??o Falsa Modificada");
					printf("\n\n\tFun??o utilizada: %s",s); 
					coleta_dados(&(*e),&(*iteracoes),&(*lim_inf),&(*lim_sup)); 					
					printf("\n\t"); 
					system("pause");
					break; 
					
		case 4: 	printf("M?todo de Newton"); 
					printf("\n\n\tFun??o utilizada: %s",s); 
					coleta_dados2(&(*e),&(*iteracoes),&(*lim_inf));
					printf("\n\t"); 
					system("pause"); 
					break; 
					
		case 5: 	printf("M?todo de Newton Modificado"); 
					printf("\n\n\tFun??o utilizada: %s",s);
					coleta_dados2(&(*e),&(*iteracoes),&(*lim_inf)); 
					printf("\n\t"); 
					system("pause");
					break;
					
		case 6: 	printf("C?lculo da derivada primeira"); 
					printf("\n\n\tFun??o utilizada: %s",s); 
					coleta_dados_der(&(*e),&(*iteracoes),&(*lim_inf)); 
					printf("\n\t"); 
					system("pause");
					break; 
					
		case 7: 	printf("C?lculo da derivada segunda"); 
					printf("\n\n\tFun??o utilizada: %s",s); 
					coleta_dados_der(&(*e),&(*iteracoes),&(*lim_inf)); 
					printf("\n\t"); 
					system("pause");
					break; 
		case 8: 	printf("C?lculo da matriz Jacobiana!"); 
					printf("\n\n\tFun??o utilizada: %s", s); 
					printf("\n\n\t\t\tAinda em desenvolvimento!!!"); 
					printf("\n\t"); 
					//system("pause"); 
					break; 
		case 9: 	printf("C?lculo da matriz Hessiana!"); 
					printf("\n\n\tFun??o utilizada: %s", s); 
					printf("\n\n\t\t\tAinda em desenvolvimento!!!"); 
					printf("\n\t"); 
					//system("pause"); 
					break; 						
	}
}
//Muda a string da fun??o escolhida
void defini_func (char s[]){	
	if(global_func == 1)	
		strcpy(s,"f(x) = x + 2cos(x)"); 
	if(global_func == 2)
		strcpy(s,"f(x) = x^3 - 4x^2 + x + 6");
	if(global_func == 3)
		strcpy(s,"f(x) = x^5 - (10/9)x^3 + (5/21)x");	
}
/****************************************************************************
			IMPRESS?O DOS RESULTADOS NA TELA PARA O USUARIO
****************************************************************************/

//Mostra os resultados, tamb?m mostra os valores digitados pelo usuario (bisse??o, cordas e cordas modificado)
void mostra_resultado(int flag, float precisao, int max_ite, float a, float b, int iteracoes, float raiz){
	
	system("cls");
	printf("\n\tDados fornecidos pelo usuario: \n"); 
	printf("\n\tPrecis?o: %f",precisao); 
	printf("\n\tN?mero m?ximo de itera??es: %d",max_ite); 
	printf("\n\tLimite Inferior: %.2f e Limite Superior: %.2f",a,b); 
	if(flag == 0){
		printf("\n\n\tN?O HOUVE CONVERG?NCIA NO RESULTADO!"); 
		printf("\n\tN?MERO MAXIMO DE ITERA??ES ULTRAPASSADAS\n"); 
	}
	
	printf("\n\n\tRESULTADOS OBTIDOS:\n"); 
	printf("\n\tRaiz: %f\n\tNumero de itera??es: %d\n\t",raiz,iteracoes);
	printf("Numero arredondado para inteiro: %d\n\n\t", arredonda(raiz));

}
//Mostra os resultados de Newton e Newton modificado
void mostra_resultado2(int flag, float precisao, int max_ite, float x0, int iteracoes, float raiz){
	
	system("cls");
	printf("\n\tDados fornecidos pelo usuario: \n"); 
	printf("\n\tPrecis?o: %f",precisao); 
	printf("\n\tN?mero m?ximo de itera??es: %d",max_ite); 
	printf("\n\tValor de x0: %f",x0); 
	if(flag == 0){
		printf("\n\n\tN?O HOUVE CONVERG?NCIA NO RESULTADO!"); 
		printf("\n\tN?MERO MAXIMO DE ITERA??ES ULTRAPASSADAS\n"); 
	}
	
	printf("\n\n\tRESULTADOS OBTIDOS:\n"); 
	printf("\n\tRaiz: %f\n\tNumero de itera??es: %d\n\t",raiz,iteracoes);
	printf("Numero arredondado para inteiro: %d\n\n\t", arredonda(raiz));

}
//Mostra o resultado da derivada primeira
void mostra_der(float precisao, int max_ite, float x){
	
	system("cls"); 
	printf("\n\tPrecis?o: %f",precisao); 
	printf("\n\tMaximo de itera??es: %d",max_ite); 
	
	printf("\n\n\tValor da derivada: %f",x); 
	printf("\n\t"); 	
}
// Fun??o main
int main(){

	setlocale(LC_ALL,"Portuguese");
	int op, ite; 
	float x, pre, l_inf, l_sup;// n_sei;
	//Resultados: 
	int ite_fim, aux;
	float raiz, aux2, derivada1, derivada2; 
	//String da fun??o
	char s_func[30]; 
	//strcpy(s_func, "x^3 - 4x^2 + x + 6");	//Fun??o padr?o s? pra teste
	
	do{
		defini_func(s_func);
		op = menu(s_func); 
		ite_fim = 0; 
		raiz = 0;
		switch(op){
			case 1: 	// M?TODO DA BISSE??O 	
						tela(op,s_func,&pre,&ite,&l_inf,&l_sup);
						//Chama o m?todo da bisse??o 
						aux = bissecao(pre,ite,f,l_inf,l_sup,&ite_fim,&raiz);
						
						//Mostra o resultado de acordo com os dados digitados
					    mostra_resultado(aux,pre,ite,l_inf,l_sup,ite_fim,raiz);	//Impress?o do resultado na tela
						system("pause");										//Espera o usuario apertar qualquer tecla						
						break;
						
			case 2: 	//M?TODO DA POSI??O FALSA
						tela(op,s_func,&pre,&ite,&l_inf,&l_sup);
						//Chama o m?todo da Posi??? Falsa
						aux = PosicaoFalsa(pre,ite,f,l_inf,l_sup,&ite_fim,&raiz);
						
						//Mostra o resultado de acordo com os dados digitados
						mostra_resultado(aux,pre,ite,l_inf,l_sup,ite_fim,raiz);	//Impress?o do resultado na tela
						system("pause");					 //Espera o usuario apertar qualquer tecla
						break; 
						
			case 3: 	//M?TODO DA POSI??O FALSA MODIFICADA
						tela(op,s_func,&pre,&ite,&l_inf,&l_sup);
						//Chama o m?todo da Posi??o Falsa Modificada
						aux = PosicaoFalsaModificada(pre,ite,f,l_inf,l_sup,&ite_fim,&raiz);						
						//Mostra o resultado de acordo com os dados digitados
						mostra_resultado(aux,pre,ite,l_inf,l_sup,ite_fim,raiz);	//Impress?o do resultado na tela
						system("pause");
						break; 
			case 4: 	//M?TODO DE NEWTON
						tela(op,s_func,&pre,&ite,&l_inf,&l_sup);
						aux2 = l_inf; 
						aux = Newton(pre,ite,f,&l_inf,&ite_fim,&raiz);
						mostra_resultado2(aux,pre,ite,aux2,ite_fim,raiz);
						system("pause");
						break; 
						
			case 5: 	//M?TODO DE NEWTON MODIFICADO
						tela(op,s_func,&pre,&ite,&l_inf,&l_sup); 
						aux2 = l_inf; 
						aux = NewtonModificado(pre,ite,f,&l_inf,&ite_fim,&raiz); 
						mostra_resultado2(aux,pre,ite,aux2,ite_fim,raiz); 
						system("pause");
						break;
						
			case 6: 	//C?LCULO DA DERIVADA
						tela(op,s_func,&pre,&ite,&l_inf,&l_sup);
						derivada1 = df(pre,ite,f,l_inf); 
						//printf("Valor da derivada 1: %f",derivada1); 
						//system("pause");
						mostra_der(pre,ite,derivada1); 
						system("pause");
						break; 
						
			case 7: 	//C?LCULO DA DERIVADA SEGUNDA
						tela(op,s_func,&pre,&ite,&l_inf,&l_sup); 
						derivada2 = df2(pre,ite,f,l_inf); 
						mostra_der(pre,ite,derivada2); 
						system("pause"); 
						break; 
						
			case 8: 	//C?LCULO DA MATRIZ JACOBIANA
						tela(op,s_func,&pre,&ite,&l_inf,&l_sup);
						system("pause"); 
						break; 
						
			case 9: 	//C?LCULO DA MATRIZ HESSIANA
						tela(op,s_func,&pre,&ite,&l_inf,&l_sup);
						system("pause"); 
						break; 	
						
			case 10: 	system("cls"); 
						printf("\n\tEscolha a fun??o a ser computada:\n");
						printf("\n\t1 - f(x) = x + 2cos(x)"); 
						printf("\n\t2 - f(x) = x^3 - 4x^2 + x + 6"); 
						printf("\n\t3 - f(x) = x^5 - (10/9)x^3 + (5/21)x");
						printf("\n\n\tOp??o: ");
						do{
							scanf("%d",&global_func); 
						}while(global_func < 1 || global_func > 3); 
						printf("\n\tFun??o Escolhida com sucesso!\n\t"); 
						system("pause");
						break; 					
		}
	}while(op != 11);
	
	printf("\n\n\tFim do programa!");
}

