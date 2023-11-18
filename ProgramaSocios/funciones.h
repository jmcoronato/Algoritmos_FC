#ifndef FUNCIONES_H_INCLUDED
#define FUNCIONES_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "../GenerarIndice/Indice.h"
#include "../GenerarIndice/Socios.h"
#include "../GenerarIndice/Fecha.h"

void bajaSocio(FILE *pf, t_indice *ind);
void modificarNombreSocio(FILE *pf,t_indice *ind);
void leer_socios(const char* nombre_archivo);
int cmpLong(const void* a, const void* b);

#endif // FUNCIONES_H_INCLUDED
