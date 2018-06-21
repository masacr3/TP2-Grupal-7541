//wrapper copiar
void copiar (char* destino, const char *cadena){
	strcpy(destino, cadena);
}

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

/*
	verifica si el tiempo es sospechoso de ataque DOS
*/
bool tiempo_sospechoso( char* tiempo1, char* tiempo2 ){
	time_t t1 = iso8601_to_time(tiempo1);
	time_t t2 = iso8601_to_time(tiempo1);
	return ( difftime(t1,t2) < 2 );
}

/*
	Chequea si una lista de tiempos de un Ip esta implementando un atacke DOS
*/
bool dos_attack( lista_t* time_list ){
	
	// si esta vacio o el largo de tiempos es menor a 5 no hay atacke
	if ( lista_esta_vacia(time_list) || lista_largo(time_list) < 5 ) return false;
	
	lista_iter_t* primero = lista_iter_crear(time_list);
	
	if (!primero) return false;
	
	lista_iter_t* ultimo = lista_iter_crear(time_list);
	
	if (!ultimo){
		lista_iter_destruir(primero);
		return false;
	}
	
	bool es_DOS = false;
	
	//avanzo hasta la 5ta posicion 
	for (int i=0; i < 5; i++) lista_iter_avanzar(ultimo);
	
	for ( int i = O; i <= lista_largo(time_list) - 5; i++ ){
		char* tiempo1 = lista_iter_ver_actual(primero);
		char* tiempo2 = lista_iter_ver_actual(ultimo);
		
		es_DOS = tiempo_sospechoso(tiempo2,tiempo1) ;
		
		if ( es _DOS ) break;
	}
	
	lista_iter_destruir(primero);
	lista_iter_destruir(segundo);
	
	return es_DOS;
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
		char **datos = split(linea, '\t');
		char* ip;
		char* tiempo;
		
		//copio los tiempos
		copiar(ip, linea[0]);
		copiar(tiempo, linea[1]);
		
		guardar_tiempos(hash,ip,tiempo);
		
		free_strv(datos);
	}
	
	
	free(linea);
	fclose(f1);
	
	return true;
  }


void DOS ( hash_t* hash, heap_t* heap ){
	hash_iter_t* iter = hash_iter_crear(hash);
	
	if (!iter) return ;
	
	while ( !hash_iter_al_final(iter) ){
		char* ip = hash_iter_ver_actual(iter);
		lista_t* lista_tiempos = hash_obtener(hash,ip);
		if ( dos_attack(lista_tiempos) ) 
	}
		
		
		
		
		
		
}
