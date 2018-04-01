// Interpretador de função

#include <stdio.h>
#include <conio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <locale.h>

int entende_valor(char n){
	switch(n){
		case '0': 
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9': return (n - 48);
		default: return -1; 
	}
}

void getString(char v[]){
	
	printf("\n\tDigite uma função: ");
	gets(v);
	
	printf("%d",entende_valor(v[0]));
}

void showString(char v[]){
	printf("\n\t%s\n\t",v);
}


int main(){

	setlocale(LC_ALL,"Portuguese");
	char string_func[40]; 
	
	getString(string_func); 
	
	showString(string_func);

}

