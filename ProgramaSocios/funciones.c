#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "funciones.h"
#include "../GenerarIndice/Indice.h"
#include "../GenerarIndice/Socios.h"
#include "../GenerarIndice/Fecha.h"

void bajaSocio(FILE *pf, t_indice *ind)
{

    long int nroSocio;
    unsigned nroReg;
    Socio reg;

    printf("Ingrese Numero de Socio que desea dar de baja:");

    scanf("%ld",&nroSocio);

    if((ind_buscar(ind,&nroSocio,&nroReg))== ERROR)
    {
        printf("Socio no encontrado\n");
        return;
    }

    fseek(pf,nroReg*(sizeof(Socio)),SEEK_SET);
    fread(&reg,sizeof(Socio),1,pf);


    if(reg.estado=='A')
    {
       int flag = 1;
       Fecha fechaBaja;
       do
       {
         if(flag)
            flag = 0;
         else
            printf("\nFormato de fecha incorrecto\n\n");

         printf("\nIngrese la fecha de baja (DD/MM/AAAA)\n\n");

         fechaBaja = ingresarFecha();

       }while(!(esFechaValida(fechaBaja)));

         reg.fecha_baja = fechaBaja;
//        printf("Ingrese fecha de baja(dd/mm/aa): ");
//        scanf("%d/%d/%d",&reg.fecha_baja.dia,&reg.fecha_baja.mes,&reg.fecha_baja.anio);
        reg.estado='I';
        fseek(pf,(long)-sizeof(Socio),SEEK_CUR);
        fwrite(&reg,sizeof(Socio),1,pf);
        fseek(pf,0,SEEK_SET);
        printf("\nSocio dado de baja exitosamente.\n");
    }
    else
        printf("Socio ya dado de baja\n");

}

void leer_socios(FILE* archivo)
{
        Socio socio;

        while (fread(&socio, sizeof(Socio), 1, archivo) == 1)
        {
            printf("Numero de Socio: %ld\n", socio.nro_socio);
            printf("Nombre y Apellido: %s\n", socio.apynom);
            printf("DNI: %ld\n", socio.dni);
            printf("Fecha de Nacimiento: %d/%d/%d\n", socio.fecha_nac.dia, socio.fecha_nac.mes, socio.fecha_nac.anio);
            printf("Sexo: %c\n", socio.sexo);
            printf("Fecha de Afiliacion: %d/%d/%d\n", socio.fecha_afiliacion.dia, socio.fecha_afiliacion.mes, socio.fecha_afiliacion.anio);
            printf("Categoria: %s\n", socio.categoria);
            printf("Fecha de Pago: %d/%d/%d\n", socio.fecha_pago.dia, socio.fecha_pago.mes, socio.fecha_pago.anio);
            printf("Estado: %c\n", socio.estado);
            printf("Fecha de Baja: %d/%d/%d\n\n", socio.fecha_baja.dia, socio.fecha_baja.mes, socio.fecha_baja.anio);
        }
}

void leerSociosAlta(FILE* archivo, t_indice* ind)
{
   ind_recorrer(ind,mostrarSocioAlta,archivo);
}

void mostrarSocioAlta(const void* reg,unsigned tam_reg, void* pf)
{
   FILE* archivo = (FILE*)pf;
   Socio socio;
   unsigned nroReg = *(unsigned*)(reg+sizeof(int));

   fseek(archivo,nroReg*sizeof(Socio),SEEK_SET);
   fread(&socio,sizeof(Socio),1,archivo);
   if(socio.estado == 'A')
   {
            printf("Numero de Socio: %ld\n", socio.nro_socio);
            printf("Nombre y Apellido: %s\n", socio.apynom);
            printf("DNI: %ld\n", socio.dni);
            printf("Fecha de Nacimiento: %d/%d/%d\n", socio.fecha_nac.dia, socio.fecha_nac.mes, socio.fecha_nac.anio);
            printf("Sexo: %c\n", socio.sexo);
            printf("Fecha de Afiliacion: %d/%d/%d\n", socio.fecha_afiliacion.dia, socio.fecha_afiliacion.mes, socio.fecha_afiliacion.anio);
            printf("Categoria: %s\n", socio.categoria);
            printf("Fecha de Pago: %d/%d/%d\n", socio.fecha_pago.dia, socio.fecha_pago.mes, socio.fecha_pago.anio);
            printf("Estado: %c\n", socio.estado);
            printf("Fecha de Baja: %d/%d/%d\n\n", socio.fecha_baja.dia, socio.fecha_baja.mes, socio.fecha_baja.anio);
   }
}

void leerSociosBaja(FILE* archivo, t_indice* ind)
{
   ind_recorrer(ind,mostrarSocioBaja,archivo);
}

void mostrarSocioBaja(const void* reg,unsigned tam_reg, void* pf)
{
   FILE* archivo = (FILE*)pf;
   Socio socio;
   unsigned nroReg = *(unsigned*)(reg+sizeof(int));

   fseek(archivo,nroReg*sizeof(Socio),SEEK_SET);
   fread(&socio,sizeof(Socio),1,archivo);
   if(socio.estado == 'I')
   {
            printf("Numero de Socio: %ld\n", socio.nro_socio);
            printf("Nombre y Apellido: %s\n", socio.apynom);
            printf("DNI: %ld\n", socio.dni);
            printf("Fecha de Nacimiento: %d/%d/%d\n", socio.fecha_nac.dia, socio.fecha_nac.mes, socio.fecha_nac.anio);
            printf("Sexo: %c\n", socio.sexo);
            printf("Fecha de Afiliacion: %d/%d/%d\n", socio.fecha_afiliacion.dia, socio.fecha_afiliacion.mes, socio.fecha_afiliacion.anio);
            printf("Categoria: %s\n", socio.categoria);
            printf("Fecha de Pago: %d/%d/%d\n", socio.fecha_pago.dia, socio.fecha_pago.mes, socio.fecha_pago.anio);
            printf("Estado: %c\n", socio.estado);
            printf("Fecha de Baja: %d/%d/%d\n\n", socio.fecha_baja.dia, socio.fecha_baja.mes, socio.fecha_baja.anio);
   }
}

void modificarNombreSocio(FILE *pf,t_indice *ind)
{
   long int nroSocio;
   unsigned nroReg;
   int flag = 1;
   Socio reg;
   char apellido[30];
   char nombre[31];

    printf("Ingrese Numero de Socio que modificar el nombre:");

    scanf("%ld",&nroSocio);

    if((ind_buscar(ind,&nroSocio,&nroReg))== ERROR)
    {
        printf("Socio no encontrado\n");
        return;
    }

    fseek(pf,nroReg*(sizeof(Socio)),SEEK_SET);
    fread(&reg,sizeof(Socio),1,pf);

    do
   {
      if(flag)
         flag = 0;
      else
         printf("Nombre invalido\n");

      puts("Ingrese el o los nombres del Socio:");
      fflush(stdin);
      gets(nombre);
      normalizarCadena(nombre);
   }while(!(esNombreValido(nombre)));
   flag = 1;
    do
   {
      if(flag)
         flag = 0;
      else
         printf("Apellido invalido\n");

      puts("Ingrese el Apellido del Socio:");
      fflush(stdin);
      gets(apellido);
      normalizarCadena(apellido);
   }while(!(esNombreValido(apellido)));
   strcpy(reg.apynom,apellido);
   strcat(reg.apynom,", ");
   strcat(reg.apynom,nombre);

   fseek(pf,(long)-sizeof(Socio),SEEK_CUR);
   fwrite(&reg,sizeof(Socio),1,pf);
   fseek(pf,0,SEEK_SET);
   printf("\nNombre de socio modificado exitosamente.\n");

}

int cmpLong(const void* a, const void* b)
{
   return *(long*)a - *(long*)b;
}

int esNombreValido(const char *cadena) {
    // Verificar si la cadena está vacía
    if (cadena == NULL || *cadena == '\0') {
        return 0;  // No es un nombre válido
    }

    // Recorrer la cadena para verificar cada carácter
    while (*cadena != '\0') {
        // Verificar si el carácter no es una letra
        if ((!isalpha(*cadena)) && *cadena != ' ') {
            return 0;  // No es un nombre válido
        }
        cadena++;  // Mover al siguiente carácter
    }

    return 1;  // Es un nombre válido
}

void normalizarCadena(char *cadena) {
    // Verificar si la cadena está vacía
    if (cadena == NULL || *cadena == '\0') {
        return;  // No hay nada que normalizar
    }

    // Convertir la primera letra a mayúscula
    *cadena = toupper(*cadena);

    // Recorrer la cadena para convertir las demás letras a minúsculas
    while (*(++cadena) != '\0') {
        *cadena = tolower(*cadena);
        if(*cadena == ' ')
        {
           cadena++;
           *cadena = toupper(*cadena);
        }
    }
}

