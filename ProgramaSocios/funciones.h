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
void leer_socios(FILE* archivo);
int cmpLong(const void* a, const void* b);
int esNombreValido(const char *cadena);
void normalizarCadena(char *cadena);

void leerSociosAlta(FILE* archivo, t_indice* ind);
void mostrarSocioAlta(const void* reg,unsigned tam_reg, void* pf);

void leerSociosBaja(FILE* archivo, t_indice* ind);
void mostrarSocioBaja(const void* reg,unsigned tam_reg, void* pf);

#endif // FUNCIONES_H_INCLUDED
