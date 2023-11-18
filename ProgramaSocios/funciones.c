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
            printf("Formato de fecha incorrecto");

         fechaBaja = ingresarFecha();

       }while(esFechaValida(fechaBaja));

         reg.fecha_baja = fechaBaja;
//        printf("Ingrese fecha de baja(dd/mm/aa): ");
//        scanf("%d/%d/%d",&reg.fecha_baja.dia,&reg.fecha_baja.mes,&reg.fecha_baja.anio);
        reg.estado='I';
        fseek(pf,(long)-sizeof(Socio),SEEK_CUR);
        fwrite(&reg,sizeof(Socio),1,pf);
        fseek(pf,0,SEEK_SET);
        printf("\n Socio dado de baja exitosamente.\n");
    }
    else
        printf("Socio ya dado de baja\n");

}

void leer_socios(const char* nombre_archivo)
{
    FILE* archivo = fopen(nombre_archivo, "rb");

    if (archivo != NULL)
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

        fclose(archivo);
    }
    else
    {
        printf("No se pudo abrir el archivo.\n");
    }
}

void modificarNombreSocio(FILE *pf,t_indice *ind)
{
   long int nroSocio;
   unsigned nroReg;
   Socio reg;
   char apynom[100];

    printf("Ingrese Numero de Socio que modificar el nombre:");

    scanf("%ld",&nroSocio);

    if((ind_buscar(ind,&nroSocio,&nroReg))== ERROR)
    {
        printf("Socio no encontrado\n");
        return;
    }

    fseek(pf,nroReg*(sizeof(Socio)),SEEK_SET);
    fread(&reg,sizeof(Socio),1,pf);

    puts("Ingrese el nuevo nombre y apellido con el formato 'Apellido, Nombre'");/// FALTA LA VALIDACION DEL FORMATO DEL NOMBRE
    fflush(stdin);
    gets(apynom);
    strcpy(reg.apynom,apynom);

   fseek(pf,(long)-sizeof(Socio),SEEK_CUR);
   fwrite(&reg,sizeof(Socio),1,pf);
   fseek(pf,0,SEEK_SET);
   printf("\nNombre de socio modificado exitosamente.\n");

}

int cmpLong(const void* a, const void* b)
{
   return *(long*)a - *(long*)b;
}

