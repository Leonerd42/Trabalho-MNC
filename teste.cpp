//
//

#include <stdio.h>
#include <conio.h>
#include <ctype.h>
#include <stdlib.h>
#include <locale.h>

float f(float b){
	return (b*2 + 4);
}

void teste (float func(float x)){
	
	printf("Valor: %f",func(3)); 
	
	
}


void qq(int x){
	
	printf("%d", x + x);
	system("pause");
	
}
int main(){

	setlocale(LC_ALL,"Portuguese");
	
	teste(f);

}

