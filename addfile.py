def copy (dest, cad)
  dest = cad
 
for line in archivoAcomodado
  datos = split(line,"\t")
  copy(ip, datos[0])
  copy(tiempo,datos[1])
  #free(datos)

#C implementacion

//wrapper copiar
void copiar (char* destino, const char *cadena){
	strcpy(destino, cadena);
}

//carga los tiempos del archivo al hash
bool cargar_tiempos(char* archivo, hash_t* hash ){
	FILE* f1;

  	if((f1 = fopen(argv[1],"r")) == NULL) return false;
	
	char* linea_f1 = NULL; 
	size_t capacidad_f1 = 0;
	
	for (int i= 0; getline(&linea, &capacidad, stdin)>0; i++ ){
		char **datos = split(linea, '\t');
		char* ip;
		char* tiempo;
		
		//copio los tiempos
		copiar(ip, linea[0]);
		copiar(tiempo, linea[1]);
		
		guardar_tiempos(hash,ip,tiempo);
		
		free_strv(datos);
		
	}
	return true;
}
