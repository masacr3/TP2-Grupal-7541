#include <stdbool.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include "lista.h"
#include "hash.h"
#include <timer.h>

/********************************
*				*
*	funciones auxiliares	*
*				*
********************************/
//wrapeer para copiar cadenas
void copíar(char*, const char*);

//verifica si el tiempo es sospecho
//si es sospechoso por q la diferncia
//es de menos de 2 segundos
//pre: las cadenas tienen el formato iso8601
bool tiempo_sospechoso( char*, char*);

/****************************************
*					*
*	implementacion hash		*
*					*
****************************************/
//carga los tiempos de los ip al hash
//pre: los tiempos estan ordenados de menor a mayor
//post: el hash es modificado
bool agregar_tiempos(hash_t* hash, const char*,const char*);


//abre el archivo y carga el ip con sus respectivos tiempos
//pre: el archivo esta ordenado de menor a mayor por sus tiempos
//post: el hash es modificado
bool cargar_archivo(char* archivo, hash_t* hash);

/****************************************
*					*
*	implementacion dos		*
*					*
****************************************/

//verifica si en la lista de tiempos hay
//un ataque dos
//pre: la lista esta ordenada de menor a mayor
//pre: los tiempos tienen el formato iso8601
bool dos_attack( lista_t*);

//verifica si algun ip hizo un ataque D.O.S
//Pre: los tiempos de los ips estan ordenados de menor a mayor y en formato iso8601
//post: el heap es modificado, y es llenado con los ip que realizaron el DOS ordenados de menor a mayor.
void DOS ( hash_t*, heap_t*);
