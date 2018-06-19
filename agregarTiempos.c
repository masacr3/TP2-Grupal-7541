/*
	Agrega los tiempos al hash
	pre: los tiempos estan ordenados de menor a mayor
*/

bool agregar_tiempos(hash_t* hash, const char* ip, time_t* tiempo){
	
	bool esta = hash_pertenece( hash, ip );
	
	if ( esta ) {
		
		lista_t* lista = hash_obtener(hash, ip);
		lista_insertar_ultimo( lista, tiempo );
	}
	else{
		
		lista_t* lista = lista_crear();
		
		if(!lista) return false;
		
		lista_insertar_ultimo( lista, tiempo );
		hash_guardar ( hash, ip, lista );
	}
	
return true;
}


bool tiempo_sospechoso( char* tiempo1, char* tiempo2 ){
	time_t t1 = iso8601_to_time(tiempo1);
	time_t t2 = iso8601_to_time(tiempo1);
	return ( difftime(t1,t2) < 2 );
}

bool cargar_archivo(char* archivo){
	hash_t* hash = hash_crear();
	if (!hash) return false;
	
	FILE* f1;
	
	char* linea = NULL;
	size_t capacidad = 0;
	
	
	if((f1 = fopen(archivo,"r")) == NULL){
		hash_destruir(hash);
		return false;
	}
	
	//cargo los tiempos al hash
	for (int i= 0; getline(&linea, &capacidad, f1)>0; i++ ){
		char** ip_tiempo_metodo_recurso = split(linea,'\t');
		char* ip = ip_tiempo_metodo_recurso[0];
		char* tiempo = ip_tiempo_metodo_recurso[1];
		agregar_tiempos( hash, ip, tiempo);
	}
	
	//verico los atackes
	
	DOS( hash ) ;
	
	free(linea);
	fclose(f1);
	
	
  }
	
