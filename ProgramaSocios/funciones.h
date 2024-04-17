#ifndef FUNCIONES_H_INCLUDED
#define FUNCIONES_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "../GenerarIndice/Indice.h"
#include "../GenerarIndice/Socios.h"
#include "../GenerarIndice/Fecha.h"

void altaSocio(FILE *pf,t_indice *ind);
int buscarEnVec(char vec[][10],const char *categoria);

void bajaSocio(FILE *pf, t_indice *ind);

void modificarNombreSocio(FILE *pf,t_indice *ind);

void leer_socios(FILE* archivo);

int esNombreValido(const char *cadena);
void normalizarCadena(char *cadena);
void mayusculaCadena(char *cadena);

void leerSociosAlta(FILE* archivo, t_indice* ind);
void mostrarSocioAlta(const void* reg,unsigned tam_clave, void* pf);

void leerSociosBaja(FILE* archivo, t_indice* ind);
void mostrarSocioBaja(const void* reg,unsigned tam_clave, void* pf);

void mostrarMax10SociosMasDeudores(FILE* arch,int compararFecha(const void*,const void*));
void mostrarDeudores(FILE* arch,Cmp cmp);


int cmpLong(const void* a, const void* b);
int cmpFecha(const void* e1,const void* e2);
#endif // FUNCIONES_H_INCLUDED
