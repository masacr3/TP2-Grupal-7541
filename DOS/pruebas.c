#include "hash.h"
#include "dos.h"
#include "heap.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>  // For ssize_t in Linux.


void pruebas_DOS (){

  hash_t* hash = hash_crear(NULL);
  heap_t heap = heap_crear(strcmp);

  char* lista_ip[] = {"1","1","1","1","1"};
  char* tiempos[] = {"10","10","10","10","10"};

  for (int i=0; i<4; i++) hash_guardar(hast, lista_ip[i], tiempos[i]);

  DOS(hash,heap);

  fprintf(stdout, "%s\n", heap_esta_vacio(heap) ? "No hay ataque" : "Hay ataque D.O.S" );

  hash_destruir(hash,NULL);
  heap_destruir(heap,NULL);


}
