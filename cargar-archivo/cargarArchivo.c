/*
  lee el archivo
    +carga con datos ABB(ver visitantes)
      +queda la referencia activa

    +carga hash
      +Verifica DOS

    +mensaje OK final

    +Cierro archivo
    +elimino el hash
      
*/
void cargar_archivo(char* archivo, abb_t* visitantes){
  FILE* f;

  if ( (f = fopen(archivo),"r") == NULL ) return;

  char *linea = NULL;
  size_t capacidad = 0;
  ssize_t read;

  hash_t* hash = hash_crear() //nesesito una funcion que elimine listas con elementos dinamicos

  //leo archivo
  while ( ( read = getline(&linea, &capacidad, f) ) != -1){
    char** datos = split(linea,'\t');

    if(!datos){
      fclose(f); //archivo
      free(linea);
      return;
    }

    size_t tam = strlen(datos[0]);
    char* ip_dos = malloc( sizeof(char) * ( tam + 1 ) );

    if (!ip_dos){
      fclose(f); //archivo
      free_strv(datos); //datos
      free(linea);//linea
      return;
    }

    char* ip_visitantes = malloc( sizeof(char) * ( tam + 1 ) );

    if (!ip_visitantes){
      fclose(f); //archivo
      free_strv(datos); //datos
      free(linea);//linea
      free(ip_dos);//ip
      return;
    }

    char* tiempo = malloc( sizeof(char) * ( strlen(datos[1]) + 1) );

    if (!tiempo){
      fclose(f); //archivo
      free_strv(datos); //datos
      free(linea);//linea
      free(ip_dos);//ip
      free(ip_visitantes); //ip2
      return;
    }

    //todo OK creo copias para las siguientes estructuras
    strcpy(ip_dos, datos[0]);
    strcpy(ip_visitantes, datos[0]);
    strcpy(tiempo, datos[1]);

    //para el DOS
    cargar_tiempo(hash,ip_dos,tiempo);

    //para Ver-visitantes
    cargar_visitantes(visitantes,ip_visitantes); //hay q programarlo

    //limpio registros
    free_strv(datos);
  }

  dos(hash); //VERIFICA DOS

  fprintf(stdout, "%s\n",ok); //ok final

  fclose(f); //archivo
  hash_destruir(hash); //destruyo hash
}
