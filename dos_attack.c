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
		void* tiempo1 = lista_iter_ver_actual(primero);
		void* tiempo2 = lista_iter_ver_actual(ultimo);
		
		es_DOS = diferencia_de_tiempo(tiempo2,tiempo1) < 2;
		
		if ( es _DOS ) break;
	}
	
	lista_iter_destruir(primero);
	lista_iter_destruir(segundo);
	
	return es_DOS;
}
