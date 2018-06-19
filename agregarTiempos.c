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
