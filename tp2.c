#define _POSIX_C_SOURCE 200809L
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>

#include "strutil.h"
#include "heap.h"
#include "lista.h"
#include "ad_hoc.h"

struct ad_hoc{
  char* registro;
  FILE* archivo;
};

ad_hoc_t* ad_hoc_crear(const char* linea, FILE* archivo){
  ad_hoc_t* ad_hoc = malloc(sizeof(ad_hoc_t));

  if (!ad_hoc) return NULL;

  size_t largo1 = strlen(linea);
  char* linea_copia = malloc(sizeof(char*) * largo1 + 2);

  if (!linea_copia){
    free(ad_hoc);
    return NULL;
  }

  strcpy(linea_copia, linea);
  ad_hoc->registro = linea_copia;
  ad_hoc->archivo = archivo;
  return ad_hoc;
}

char* ad_hoc_obtener_registro(ad_hoc_t* ad_hoc){
  return ad_hoc->registro;
}

FILE* ad_hoc_obtener_archivo(ad_hoc_t* ad_hoc){
  return ad_hoc->archivo;
}

void ad_hoc_destruir(ad_hoc_t* ad_hoc){
  free(ad_hoc->registro);
  free(ad_hoc);
}

// Imprime el mensaje recibido y devuelve 1.
int imprimir_mensaje(char* mensaje){
  fprintf(stderr, "%s\n", mensaje);
  return 1;
}

int imprimir_error_comando(char* mensaje, char* comando){
  fprintf(stderr, "%s %s\n", mensaje, comando);
  return 1;
}

int cmp_cadenas(const void* a, const void* b){
  return strcmp(a, b);
}

size_t len(char** vector){
  size_t cantidad=0;

  for (int i=0; vector[i]; i++) cantidad++;

  return cantidad;
}

int liberar_con_temporal(FILE* temporal, heap_t* heap, lista_t* lista_registros, char* linea, FILE* archivo1, lista_t* lista_nombres){
  fclose(temporal);
  heap_destruir(heap, free);
  lista_destruir(lista_registros, free);
  lista_destruir(lista_nombres, free);
  free(linea);
  fclose(archivo1);
  return imprimir_error_comando("Error en comando", "ordenar_archivo");
}

int liberar_sin_temporal(heap_t* heap, lista_t* lista_registros, char* linea; FILE* archivo1, lista_t* lista_nombres){
  heap_destruir(heap, free);
  lista_destruir(lista_registros, free);
  lista_destruir(lista_nombres, free);
  free(linea);
  fclose(archivo1);
  return imprimir_error_comando("Error en comando", "ordenar_archivo");
}

char* copiar_linea(char* linea){
  size_t largo = strlen(linea) + 2;
  char* cadena_auxiliar = malloc(sizeof(char) * largo);

  if (!cadena_auxiliar) return NULL;

  memcpy(cadena_auxiliar, &linea[0], largo);
  return cadena_auxiliar;
}
/*for(i = 0; i < 100; i++) {
    char name[12];
    sprintf(name, "file%d.txt", i);
    fp = fopen(name, "w");
}*/
char* obtener_nombre(int n){
  char* nombre = malloc(sizeof(char) * 20 + 1);// 20 por si se generan hasta un millon de particiones.

  if (!nombre) return NULL;

  sprintf(nombre, "temporal%d.log", n)  ;
  return nombre;
}

char** obtener_arreglo(lista_t* lista){
  size_t largo = lista_largo(lista);
  char** arreglo = malloc(sizeof(char*) * largo + 2);

  if (!arreglo) return NULL;

  char* mem = malloc(sizeof(char*));

  if (!mem){
    free(arreglo);
    return NULL;
  }

  arreglo[largo] = NULL;
  ssize_t memoria = 0;

  for (int i =0; i < largo && !lista_esta_vacia(lista); i++){
    char* registro = lista_borrar_primero(lista);
    ssize_t bytes = (ssize_t)strlen(registro) + 1;
    memoria += bytes
    arreglo[i] = registro;
  }

  sprintf(mem, "%zu", memoria)
  arreglo[largo+1] = mem;
  return arreglo;
}

void liberar_arreglo(char** arrglo, size_t largo){
  for (size_t i = 0; i <= largo; i++){

    if (!arreglo[i]) continue;

    free(arreglo[i]);
  }

  free(arreglo);
}

int ordenar_archivo(char* nombre_archivo, char* nombre_salida, ssize_t bytes){
  FILE* archivo1 = fopen(nombre_archivo, "r");

  if (!archivo1) return imprimir_error_comando("Error en comando", "ordenar_archivo");

  heap_t* heap = heap_crear(cmp_registros);

  if (!heap){
    fclose(archivo1);
    return imprimir_error_comando("Error en comando", "ordenar_archivo");
  }

  lista_t* lista_registros = lista_crear();

  if (!lista_registros){
    fclose(archivo1);
    heap_destruir(heap, NULL);
    return imprimir_error_comando("Error en comando", "ordenar_archivo");
  }

  int n = 0;
  char* nombre_temporal = obtener_nombre(n);

  if (!nombre_temporal){
    fclose(archivo1);
    heap_destruir(heap, NULL);
    lista_destruir(lista_registros, NULL);
    return imprimir_error_comando("Error en comando", "ordenar_archivo");
  }
  FILE* temporal = fopen(nombre_temporal, "w");

  if (!temporal){
    fclose(archivo1);
    heap_destruir(heap, NULL);
    lista_destruir(lista_registros, NULL);
    return imprimir_error_comando("Error en comando", "ordenar_archivo");
  }

  lista_t* lista_nombres = lista_crear();

  if (!lista_nombres){
    fclose(archivo1);
    fclose(temporal);
    heap_destruir(heap, NULL);
    lista_destruir(lista_registros, NULL);
    return imprimir_error_comando("Error en comando", "ordenar_archivo");
  }

  lista_insertar_ultimo(lista_nombres, nombre_temporal);

  char* linea = NULL;
  size_t capacidad = 0;
  ssize_t leidos;
  ssize_t cota_memoria = 0;

  while ( (leidos = getline(&linea, &capacidad, archivo1)) > 0 ){

    if (cota_memoria < bytes){
      cota_memoria += leidos;
      char* linea_copia = copiar_linea(linea);

      if (!linea_copia) return liberar_con_temporal(temporal, heap, lista_registros, linea, archivo1, lista_nombres);

      heap_encolar(heap, linea_copia);
      continue;
    }

    if (cota_memoria >= bytes && !heap_esta_vacio(heap)){ //https://goo.gl/RsXS7Y
      char* registro = heap_desencolar(heap);
      fprintf(temporal, "%s", registro);
      char* linea_copia = copiar_linea(linea);
      // Observar || https://goo.gl/ATZ9xs
      if (!linea_copia) return liberar_con_temporal(temporal, heap, lista_registros, linea, archivo1, lista_nombres);

      if (cmp_registros(&linea[0], registro) >= 0) heap_encolar(heap, linea_copia);

      else lista_insertar_ultimo(lista_registros, linea_copia);

      free(registro);
      continue;
    }

    if (heap_esta_vacio(heap)) fclose(temporal);

    n++;
    nombre_temporal = obtener_nombre(n);

    if (!nombre_temporal) return liberar_sin_temporal(heap, lista_registros, linea, archivo1, lista_nombres);

    temporal = fopen(nombre_temporal, "w");

    if (!temporal) return liberar_sin_temporal(heap, lista_registros, linea, archivo1, lista_nombres);

    if (lista_esta_vacia(lista_registros)){
      cota_memoria = 0;
      continue;
    }

    char** arreglo = obtener_arreglo(lista_registros);

    if (!arreglo) return liberar_con_temporal(temporal, heap, lista_registros, linea, archivo1, lista_nombres);

    heap_destruir(heap, NULL);
    size_t largo = lista_largo(lista_registros);
    heap = heap_crear_arr((void**)arreglo, largo, cmp_registros);
    liberar_arreglo(arreglo, largo+1);
    lista_insertar_ultimo(lista_nombres, nombre_temporal);
    cota_memoria = (ssize_t)atoi(arreglo[largo+1]);
  }

  free(linea);
  fclose(archivo1);

  while (!heap_esta_vacio(heap)){
    char* registro = heap_desencolar(heap);
    fprintf(temporal, "%s", registro);
    free(registro);
  }

  if (!lista_esta_vacia(lista_registros)){
    fclose(temporal);
    n++;
    nombre_temporal = obtener_nombre(n);

    if (!nombre_temporal) return liberar_sin_temporal(heap, lista_registros, linea, archivo1, lista_nombres);

    temporal = fopen(nombre_temporal, "w");

    if (!temporal) return liberar_sin_temporal(heap, lista_registros, linea, archivo1, lista_nombres);

    char** arreglo = obtener_arreglo(lista);

    if (!arreglo) return liberar_con_temporal(temporal, heap, lista_registros, linea, archivo1, lista_nombres);

    heap_destruir(heap, NULL);
    size_t largo = lista_largo(lista_registros);
    heap = heap_crear_arr((void**)arreglo, largo, cmp_registros);
    liberar_arreglo(arreglo, largo+1);
    lista_insertar_ultimo(lista_nombres, nombre_temporal);

    while (!heap_esta_vacio(heap)){
      char* registro = heap_desencolar(heap);
      fprintf(temporal, "%s", registro);
      free(registro);
    }

  }

  fclose(temporal);
  free(linea);
  lista_destruir(lista_registros, NULL);
  heap_destruir(heap, NULL);
  lista_t* lista_archivos = lista_crear();

  if (!lista_archivos){
    lista_destruir(lista_nombres, free);
    return imprimir_error_comando("Error en comando", "ordenar_archivo");
  }

  heap_t* heap_ordenar = heap_crear(cmp_ad_hoc);

  if (!heap_ordenar){
    lista_destruir(lista_nombres, free);
    lista_destruir(lista_archivos, NULL);
    return imprimir_error_comando("Error en comando", "ordenar_archivo");
  }

  FILE* archivo2 = fopen(nombre_salida, "w");

  if (!archivo2){
    lista_destruir(lista_archivos, NULL);
    lista_destruir(lista_nombres, free);
    return imprimir_error_comando("Error en comando", "ordenar_archivo");
  }

  lista_iter_t* iter = lista_iter_crear(lista_nombres);

  if (!iter){
    fclose(archivo2);
    lista_destruir(lista_archivos, NULL);
    heap_destruir(heap_ordenar, NULL);
    lista_destruir(lista_nombres, free);
    return imprimir_error_comando("Error en comando", "ordenar_archivo");
  }

  FILE* particion;

  while (!lista_iter_al_final(iter)){
    char* archivo_actual = lista_iter_ver_actual(iter);
    particion = fopen(archivo_actual, "r");
    lista_insertar_ultimo(lista_archivos, particion);
    lista_iter_avanzar(iter);
  }

  lista_iter_destruir(iter);
  char* linea = NULL;
  size_t capacidad = 0;
  ssize_t leidos;
  iter = lista_iter_crear(lista_archivos);

  if (!iter){
    fclose(archivo2);
    lista_destruir(lista_archivos, fclose);
    heap_destruir(heap_ordenar, NULL);
    lista_destruir(lista_nombres, free);
    return imprimir_error_comando("Error en comando", "ordenar_archivo");
  }

  while (!lista_iter_al_final(iter)){
    particion = lista_iter_ver_actual(iter);
    leidos = getline(&linea, &capacidad, particion);
    ad_hoc_t* ad_hoc = ad_hoc_crear(linea, particion);

    if (!ad_hoc){
      fclose(archivo2);
      lista_destruir(lista_archivos, fclose);
      lista_iter_destruir(iter);
      lista_destruir(lista_nombres, free);
      heap_destruir(heap_ordenar, ad_hoc_destruir);
      free(linea);
      fclose(particion);
      return imprimir_error_comando("Error en comando", "ordenar_archivo");
    }

    heap_encolar(heap_ordenar, ad_hoc);
    lista_iter_avanzar(iter);
  }

  lista_iter_destruir(iter);

  while (!heap_esta_vacio(heap_ordenar)){
    ad_hoc_t* actual = heap_desencolar(heap_ordenar);
    char* registro = ad_hoc_obtener_registro(actual);
    fprintf(archivo2, "%s", registro);
    particion = ad_hoc_obtener_archivo(actual);
    leidos = getline(&linea, &capacidad, particion);
    ad_hoc_destruir(actual);

    if (leidos == EOF){
      fclose(particion);
      continue;
    }

    ad_hoc_t* ad_hoc = ad_hoc_crear(linea, particion);

    if (!ad_hoc){
      fclose(archivo2);
      lista_destruir(lista_archivos, fclose);
      lista_destruir(lista_nombres, free);
      heap_destruir(heap_ordenar, ad_hoc_destruir);
      free(linea);
      fclose(particion);
      return imprimir_error_comando("Error en comando", "ordenar_archivo");
    }

    heap_encolar(heap_ordenar, ad_hoc);
  }

  heap_destruir(heap_ordenar, NULL);
  free(linea);
  fclose(archivo2);

  while (!lista_esta_vacia(lista_archivos)) lista_borrar_primero(lista_archivos);

  lista_destruir(lista_archivos, NULL);

  while (!lista_esta_vacia(lista_nombres)){
    char* nombre = lista_borrar_primero(lista_nombres);
    remove(nombre);
    free(nombre);
  }

  lista_destruir(lista_nombres, NULL);
  return 0;
}

int ejecutar_comandos(char** vector_comandos, char** comandos_validos, ssize_t bytes){
  char* comando = vector_comandos[0];

  if (strcmp(comando, comandos_validos[0]) == 0) return ordenar_archivo(vector_comandos[1], vector_comandos[2], bytes);

  if (strcmp(comando, comandos_validos[1]) == 0) return agregar_archivo(vector_comandos[1]);

  else return ver_visitantes(vector_comandos[1], vector_comandos[2]);
}

bool pertenece(char* comando, char** comandos_validos){
  for (int i = 0; i < 3; i++){

    if (strcmp(comando, comandos_validos[i]) == 0) return true;

  }

  return false;
}

bool es_invalido(char* mensaje, char* comando){
  imprimir_error_comando(mensaje, comando);
  return false;
}

bool es_valido(char** vector_comandos){
  if (strcmp("ordenar_archivo", vector_comandos[0]) == 0 && len(vector_comandos) != 3) return es_invalido("Error en comando", "ordenar_archivo");

  if (strcmp("agregar_archivo", vector_comandos[0]) == 0 && len(vector_comandos) != 2) return es_invalido("Error en comando", "agregar_archivo");

  if (strcmp("ver_visitantes", vector_comandos[0]) == 0 && len(vector_comandos) != 3) return es_invalido("Error en comando", "ver_visitantes");

  return true;
}

int consola(ssize_t bytes){
  char** comandos_validos = malloc(sizeof(char*)*3);

  if (!comandos_validos) return imprimir_mensaje("Ha ocurrido un error");

  comandos_validos[0] = "ordenar_archivo";
  comandos_validos[1] = "agregar_archivo";
  comandos_validos[2] = "ver_visitantes";
  char* linea = NULL;
  size_t capacidad = 0;
  ssize_t leidos;

  while ( (leidos = getline(&linea, &capacidad, stdin)) > 0 ){
    char** vector_comandos = split(linea,' ');
    char* comando = vector_comandos[0];

    if (!pertenece(comando, comandos_validos)) return imprimir_error_comando("Error en comando", comando);

    if (!es_valido(vector_comandos)) return 1;

    int resultado = ejecutar_comandos(vector_comandos, comandos_validos, bytes);

    resultado == 1 ? return 1 : continue;
  }

  free(linea);
  free(comandos_validos);
  free_strv(vector_comandos);
  return 0;
}

int main(int argc,char* argv[]){

  if (argc != 2) return imprimir_mensaje("Cantidad de parametros erronea");

  char* cadena_parametro = argv[1];
  size_t len = strlen(cadena_parametro);

  for (size_t i = 0; i < len; i++){

    if (isdigit(cadena_parametro[i]) == 0) return imprimir_mensaje("Tipo de parametro incorrecto");

  }

  ssize_t bytes = (ssize_t)atoi(argv[1]) * 1000;
  int resultado = consola(bytes);
  return resultado;
}
