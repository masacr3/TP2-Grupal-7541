#include "dos_attack.c"

void DOS ( hash_t* hash ){
	
	if (!hash) return;
	
    heap_t* heap = heap_crear();
	
	if (!heap) return;
	
	hash_iter_t * ips = hash_iter_crear(hash);
	
	if(!ips) return;
	
	//recorro el hash por IP y checkeo q las listas de tiempos no contenga atakes DOS
	//en caso de atake encolo en el heap el IP
	while ( !hash_iter_al_final(ips) ) {
		char* ip = hash_iter_ver_actual(ips);
		
		lista_t* lista_tiempos = hash_obtener( hash, ip ) ;
		
		if ( dos_attack(lista_tiempos) ) heap_encolar(heap, ip);
		
		hash_iter_avanzar(ips);
	}
	
	//mostrar los ip
	while ( !heap_esta_vacio(heap) ){
		//CODE
	} 
	
	heap_destruir(heap);
	hash_iter_destruir(ips);
}
