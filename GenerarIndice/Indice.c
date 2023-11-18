#include "Indice.h"

void ind_crear (t_indice* ind, size_t tam_clave, Cmp cmp)
{
    crear_lista(&(ind->lista));
    ind->tam_clave = tam_clave;
    ind->cmp = cmp;
    ind->reg_ind = malloc(ind->tam_clave+sizeof(unsigned));
}

int ind_insertar (t_indice* ind, void *clave, unsigned nro_reg)
{
    int r;

    memcpy(ind->reg_ind,clave,ind->tam_clave);
    memcpy(ind->reg_ind+ind->tam_clave,&nro_reg,sizeof(unsigned));

    r = insertar_en_orden_lista(&(ind->lista),ind->reg_ind,(ind->tam_clave+sizeof(unsigned)),ind->cmp);

    return r==1 ? OK : ERROR;
}

int ind_eliminar (t_indice* ind, void *clave, unsigned* nro_reg)
{
    int r;

    memcpy(ind->reg_ind,clave,ind->tam_clave);

    r = sacar_de_lista_ordenada(&ind->lista,ind->reg_ind,(ind->tam_clave+sizeof(unsigned)),ind->cmp);

    if(r==NO_EXISTE)
        return ERROR;

    memcpy(nro_reg,ind->reg_ind+ind->tam_clave,sizeof(unsigned));

    return OK;
}

int ind_buscar (const t_indice* ind, void *clave, unsigned* nro_reg)
{
    int r;

    memcpy(ind->reg_ind,clave,ind->tam_clave);

    r = buscar_en_lista(&ind->lista,ind->reg_ind,(ind->tam_clave+sizeof(unsigned)),ind->cmp);

    if(r==NO_EXISTE)
        return ERROR;

    memcpy(nro_reg,ind->reg_ind+ind->tam_clave,sizeof(unsigned));

    return OK;
}

void ind_vaciar (t_indice* ind)
{
    vaciar_lista(&(ind->lista));
    free(ind->reg_ind);
    ind = NULL;
}

int ind_grabar (const t_indice* ind, const char* path)
{
    FILE* arch = fopen(path,"wb");

    size_t tam_reg = ind->tam_clave + sizeof(unsigned);

    if(!arch)
        return ERROR;

    recorrerLista(&(ind->lista),grabarRegistro,arch,&tam_reg);

    fclose(arch);

    return OK;
}

int ind_cargar(t_indice* ind, const char* path)
{
    FILE *pf = fopen(path,"rb");

    size_t tam = ind->tam_clave+sizeof(unsigned);

    void *dato = malloc(tam);

    if(!pf)
        return ERROR;

    fread(dato,sizeof(tam),1,pf);

    while(!feof(pf))
    {
        insertar_en_orden_lista(&(ind->lista),dato,(ind->tam_clave+sizeof(unsigned)),ind->cmp);
        fread(dato,sizeof(tam),1,pf);
    }

    fclose(pf);
    free(dato);

    return OK;
}

int ind_recorrer (const t_indice* ind, void (*accion)(const void *, unsigned, void *),void* param)
{
   size_t tam_reg = ind->tam_clave+sizeof(unsigned);
   recorrer_lista_ind(&ind->lista,accion,tam_reg,param);
   return OK;
}

void mostrar_clave(const void* dato, unsigned tam, void* param)
{
   int* clave = (int*)dato;
   unsigned* reg = (unsigned*)(dato+sizeof(int));
   printf("Clave: %d Registro: %d\n",*clave,*reg);
}
