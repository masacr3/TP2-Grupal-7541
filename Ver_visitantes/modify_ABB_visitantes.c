struct abb_iter{
  pila_t* pila;
  const char* inicio; //add
  const char* fin; //add
};



//modify to implementation for Ver-visitantes
void apilar_hijos_izquierdos(abb_t* arbol, abb_iter_t* it, pila_t* pila,abb_nodo_t* nodo){

  if (!nodo) return;

  // clave >= inicio  && clave <= fin
  bool esta_en_rango = arbol->comparar_clave(nodo->clave,it->inicio) <= 0 && arbol->comparar_clave(nodo->clave,it->fin) >= 0;

  if (esta_en_rango){
    //apilar
    pila_apilar(pila, nodo->clave);
    return apilar_hijos_izquierdos(arbol, it, pila, nodo->izquierda);
  }

  //clave >= inicio
  if (arbol->comparar_clave(nodo->clave,it->inicio) <= 0) return apilar_hijos_izquierdos(arbol, it, pila, nodo->izquierda);

  else return apilar_hijos_izquierdos(arbol, it, pila, nodo->derecha);

}

//modify add ip_inicio, add_fin limits for iteration
abb_iter_t* abb_iter_in_crear(const abb_t* arbol, const char* ip_inicio, const char* ip_fin){
  abb_iter_t* iter=malloc(sizeof(abb_iter_t));

  if (!iter) return NULL;

  iter->pila=pila_crear();
  iter->inicio = ip_inicio;
  iter->fin = ip_fin;
  apilar_hijos_izquierdos(arbol,iter,iter->pila,arbol->raiz);
  return iter;
}
