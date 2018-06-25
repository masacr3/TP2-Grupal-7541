#ifndef ADD_HOC_H
#define ADD_HOC_H

typedef struct ad_hoc ad_hoc_t;

ad_hoc_t* ad_hoc_crear(const char* linea, FILE* archivo);

char* ad_hoc_obtener_registro(ad_hoc_t* ad_hoc);

FILE* ad_hoc_obtener_archivo(ad_hoc_t* ad_hoc);

void ad_hoc_destruir(ad_hoc_t* ad_hoc);

#endif // ADD_HOC_H
