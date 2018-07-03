/*
	funciones de comparacion para el heap
*/

int cmp_cadenas(const char* a, const char* b){
	int res = strcmp(a, b);
	
	if (res == 0 ) return 0;
	
	return res > 0 ? -1 : 1;
}

int cmp_numeros(const int a, const int b){
	if (a < b) return -1;
	
        if (a > b) return 1;
	
        return 0;
}

int cmp_ips(char* ip1, char* ip2){
	char** vector_ip1 = split(ip1, '.');
	char** vector_ip2 = split(ip2, '.');
	
	/*off
		+bad logic
		+fix remove vector_ips
		
	for (int i = 0; i < 4; i++){
		int resultado = cmp_numeros(atoi(vector_ip1[i]), atoi(vector_ip2[i]);
		if (resultado > 0) return resultado;
					    
		if (resultado < 0) return resultado;
					    
	}
	*/
	//refactor
	//@Leonel R.
	int res = 0;
	
	for( int i=0; i<4 ; i++){
		res = cmp_numeros( atoi(vector_ip1), atoi(vector_ip2) );
		if (res) break;
	}
	
	free_strv(vector_ip1);			    
	free_strv(vector_ip2);
	
	return res;
}

int cmp_tiempos(const char* a, const char* b){
	time_t t1 = iso8601_to_time(a);
	time_t t2 = iso8601_to_time(b);
	double res = difftime(t1,t2);
	
	if (res == 0.0) return 0;
	
	return res > 0.0 ? 1 : -1;
}

int cmp(char** arr, char **arr2){
	char* tiempo1 = arr[1];
	char* tiempo2 = arr2[1];
	
	int res = cmp_tiempos(tiempo1,tiempo2);
	
	if ( res == 0 ){
		int pos[] = {0,3}
		for (int i=0; i<2; i++){
			int resultado;
			if (i == 0) resultado = cmp_ips(arr[ pos[i] ],arr2[ pos[i] ]);
			else resultado = cmp_cadenas( arr[ pos[i] ], arr2[ pos[i] ]);
			if ( resultado != 0) return resultado;
		}
	}
	return res;
}
					    
int cmp_registros(const void* a, const void* b){
	char** vector_a = split((char*)a, '\t');
	char** vector_b = split((char*)b, '\t');
	int resultado = cmp(vector_a, vector_b);
	free_strv(vector_a);
	free_strv(vector_v);
	return resultado;
}
	
int cmp_ad_hoc(const void* a, const void* b){
	char* registro_a = ad_hoc_obtener_registro(a);
	char* registro_b = ad_hoc_obtener_registro(b);
	return cmp_registros(registro_a, registro_b);
}
