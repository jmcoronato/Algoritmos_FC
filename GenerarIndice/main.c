#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include "Indice.h"
#include "Fecha.h"
#include "Socios.h"
#include "funciones.h"



int main() {

      t_indice ind;

      ind_crear(&ind,sizeof(long),cmpLong);

      generarIndice(&ind);

//      ind_cargar(&ind,"socios.idx");
//
//      ind_recorrer(&ind,mostrar_clave,NULL);


    return 0;
}

