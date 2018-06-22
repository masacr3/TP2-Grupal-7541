/*
	funciones de comparacion para el heap
*/

int cmp_cadenas(const char* a, const char* b){
	int res = strcmp(a, b);
	
	if (res == 0 ) return 0;
	
	return res > 0 ? -1 : 1;
}

int cmp_tiempos(const char* a, const char* b){
	time_t t1 = iso8601_to_time(a);
	time_t t2 = iso8601_to_time(b);
	int res = difftime(t1,t2);
	
	if (res == 0) return 0;
	
	return res > 0 ? -1 : 1;
}
