/*
	generador automatico de cadenas dinamicas
 
 	Leonel R. Rolon
	
	Facultad de Ingenieria Universidad de Buenos Aires
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

char* random_string(size_t tam){

	char caracteres[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
	
	char* cadena = malloc( sizeof(char) * (tam + 1) );
	
	if (!cadena) return NULL;
	
	srand(time(NULL));
	
	for (int i = 0; i < tam; i++) *cadena[i] = caracteres[ rand() % 62 + 1];
	
	*candena[tam] = '\0';
	
	return cadena;
}
