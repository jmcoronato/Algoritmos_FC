#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include "Indice.h"
#include "Fecha.h"
#include "Socios.h"
#include "funciones.h"
#define TAM_SOCIOS 5



int main() {

   char pathTxt[11];
   char* pathBin = "socios.dat";
   char* pathInd = "socios.idx";

      t_indice ind;

      ind_crear(&ind,sizeof(long),cmpLong);

//      puts("Ingrese el path del archivo de texto");
//
//      gets(pathTxt);
//
//      archTxtABin(pathBin,pathTxt);
//
//      binAindice(&ind,pathBin);
//
//      ind_grabar(&ind,pathInd);

      ind_cargar(&ind,pathInd);

      ind_recorrer(&ind,mostrar_clave,NULL);


    return 0;
}

