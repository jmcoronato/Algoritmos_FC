#include "Lista.h"

int poner_al_final_lista(t_lista *pl,const void *pd, size_t tam)    /// Si le saco el while, es igual al poner en pila dinamica!!!
{
    t_nodo* nue;

    while(*pl != NULL)  /// Mientras exista la lista voy a recorrer
        pl = &(*pl)->sig; /// Quiero la direccion del siguiente nodo al que apunta la lista

     nue = (t_nodo*)malloc(sizeof(t_nodo));

     if(!nue)
        return LISTA_LLENA;

     nue->info = malloc(tam);

     if(!nue->info)
     {
         free(nue);
         return LISTA_LLENA;
     }

    nue->sig = NULL; /// *pl

    nue->tam = tam;

    memcpy(nue->info,pd,tam);

    *pl = nue;  /// Hago que la direccion que apuntaba el que antes era el ultimo nodo, ahora apunte al nuevo nodo (t_nodo*)
                /// Hago el "ENGANCHE" de la lista

    return OK;
}

int insertar_en_lista(t_lista *pl,const void *pd, size_t tam, unsigned pos)    /// Si le saco el while, es igual al poner en pila dinamica!!!
{
    t_nodo* nue;

    while(*pl != NULL && pos != 0)
    {
        pl = &(*pl)->sig;
        pos--;
    }


     nue = (t_nodo*)malloc(sizeof(t_nodo));

     if(!nue)
        return LISTA_LLENA;

     nue->info = malloc(tam);

     if(!nue->info)
     {
         free(nue);
         return LISTA_LLENA;
     }

    nue->sig = *pl; /// En el contenido de pl tengo la direccion del siguiente nodo al que quiero insertar

    nue->tam = tam;

    memcpy(nue->info,pd,tam);

    *pl = nue;

    return OK;
}

int insertar_en_orden_lista(t_lista *pl,const void *pd, size_t tam, Cmp cmp)
{
    t_nodo* nue;
    int comp;

    while(*pl != NULL && (comp = cmp(pd, (*pl)->info))>0)
    {
        pl = &(*pl)->sig;
        if(*pl && !comp)
            return DUPLICADO;   /// Si hay datos y la comparacion a 0 no inserta y retorna duplicado
    }


     nue = (t_nodo*)malloc(sizeof(t_nodo));

     if(!nue)
        return LISTA_LLENA;

     nue->info = malloc(tam);

     if(!nue->info)
     {
         free(nue);
         return LISTA_LLENA;
     }

    nue->sig = *pl;

    nue->tam = tam;

    memcpy(nue->info,pd,tam);

    *pl = nue;

    return OK;
}

int insertar_al_final_lista(t_lista *pl,const void *pd, size_t tam)
{
   t_nodo* nue;

    while(*pl)
        pl = &(*pl)->sig;

     nue = (t_nodo*)malloc(sizeof(t_nodo));

     if(!nue)
        return LISTA_LLENA;

     nue->info = malloc(tam);

     if(!nue->info)
     {
         free(nue);
         return LISTA_LLENA;
     }

    nue->sig = *pl;

    nue->tam = tam;

    memcpy(nue->info,pd,tam);

    *pl = nue;

    return OK;
}

int sacar_de_lista(t_lista *pl, void *pd, size_t tam, Cmp cmp)
{
    t_nodo* elim;

    while(*pl && cmp(pd,(*pl)->info) != 0 ) /// si ponemos > 0, saca de lista ordenada
        pl = &(*pl)->sig;

    if(!*pl)
        return NO_EXISTE;

    elim = *pl;

    *pl = elim->sig;

    memcpy(pd,elim->info,min(tam,elim->tam));   /// Copio el dato a eliminar en el puntero del dato asi no perdemos la informacion

    free(elim->info);
    free(elim);

    return OK;
}

int sacar_de_lista_ordenada(t_lista *pl, void *pd, size_t tam, Cmp cmp)
{
    int comp;
    t_nodo* elim;

    while(*pl && (comp = cmp(pd,(*pl)->info) > 0 )) /// si ponemos > 0, saca de lista ordenada
        pl = &(*pl)->sig;

    if(!*pl || comp)
        return NO_EXISTE;

    elim = *pl;

    *pl = elim->sig;

    memcpy(pd,elim->info,min(tam,elim->tam));   /// Copio el dato a eliminar en el puntero del dato asi no perdemos la informacion

    free(elim->info);
    free(elim);

    return OK;
}

int buscar_en_lista(const t_lista *pl, void *pd, size_t tam, Cmp cmp)
{
    t_nodo* busc;

    while(*pl && cmp(pd,(*pl)->info) != 0 )
        pl = &(*pl)->sig;

    if(!*pl)
        return NO_EXISTE;

    busc = *pl;

    memcpy(pd,busc->info,min(tam,busc->tam));

    return OK;
}

int devolver_posicion_de_lista(t_lista *pl, void *pd, size_t tam, Cmp cmp)
{
    int i = 0;

    while(*pl && cmp(pd,(*pl)->info) != 0 )
    {
        pl = &(*pl)->sig;
        i++;
    }


    if(!*pl)
        return NO_EXISTE;

    return i;
}

int lista_vacia(t_lista *pl)
{
    return !*pl;
}

void crear_lista(t_lista *pl)
{
    *pl = NULL;
}

void vaciar_lista(t_lista *pl)
{
    t_nodo* nae;

    while(*pl)
    {
        nae = *pl;      /// 1: Nodo a eliminar que apunte al tope que se va a eliminar
        *pl = nae->sig;  ///2: La lista apunta al nodo debajo del que se va a eliminar
        free(nae->info);
        free(nae);
    }
}

void ordenarLista(t_lista* pl, Cmp cmp, int sentido)
{
   t_lista listaOrd = NULL; /// Arranco con una lista vacia
   t_lista* plOrd;
   t_nodo* nodo;

   while(*pl) /// Mientras haya elementos en la lista desordenada desengancho de esa lista y lo inserto de manera ordenada en lista ordenada
   {
      /// Desenganchar
      nodo = *pl; // 1
      *pl = nodo->sig; // 2

      plOrd = &listaOrd; /// Se vuelve a apuntar al inicio

      /// Insertar en lista ordenada
      while(*plOrd && cmp(nodo->info, (*plOrd)->info) * sentido > 0)  /// Mientras la lista ordenada apunte a algo
         plOrd = &(*plOrd)->sig;

      /// Una vez que corte el ciclo, engancho

      /// Enganchar
      nodo->sig = *plOrd; // 1
      *plOrd = nodo;      // 2
   }

   *pl = listaOrd;   /// A la lista orig le asigno direc del primer nodo de la lista ordenada
}

void recorrerLista(const t_lista* pl, Accion accion, void* extra, void* extra2)
{
   while(*pl)
   {
      accion((*pl)->info,extra,extra2);
      pl = &(*pl)->sig;
   }
}

void invertirLista(t_lista *pl,Cmp cmp)
{
    int num_elim;
    t_lista *pl_aux = pl;

    if(!*pl) return;

    while((*pl_aux)->sig)
      pl_aux = &(*pl_aux)->sig;

    num_elim = *(int*)(*pl_aux)->info;

    printf("%d ", num_elim);

    sacar_de_lista(pl,&num_elim,sizeof(num_elim),cmp);

    invertirLista(pl,cmp);
}

void crearListaInvertida(t_lista *pl,t_lista *pl2, Cmp cmp)
{
    int num_elim;
    t_lista *pl_aux = pl;

    if(!*pl) return;

    while((*pl_aux)->sig)
      pl_aux = &(*pl_aux)->sig;

    num_elim = *(int*)(*pl_aux)->info;

    sacar_de_lista(pl,&num_elim,sizeof(num_elim),cmp);

    insertar_al_final_lista(pl2,&num_elim,sizeof(num_elim));

    crearListaInvertida(pl,pl2,cmp);
}

void grabarRegistro(void* reg_ind, void* arch, void* tam_dato)
{
    size_t* tam = (size_t*)tam_dato;
    FILE* pf = (FILE*)arch;
    fwrite(reg_ind,*tam,1,pf);
}

void recorrer_lista_ind(const t_lista* pl,void (*accion)(const void *, unsigned, void *), size_t tam, void* param)
{
   while(*pl)
   {
      accion((*pl)->info,tam,param);
      pl = &(*pl)->sig;
   }
}

int sacar_primero_de_lista(t_lista *pl,void *pd,size_t tam)
{
    t_nodo* elim=*pl;
    if(!*pl)
        return 0;
    *pl=elim->sig;
    memcpy(pd,elim->info,min(tam,elim->tam));
    free(elim->info);
    free(elim);
    return 1;
}
