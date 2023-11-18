#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include "Indice.h"
#include "Fecha.h"
#include "Socios.h"
#include "funciones.h"

int cmpLong(const void* a, const void* b)
{
   return *(long*)a - *(long*)b;
}

int archTxtABin(const char* nombreArchBin, const char* nombreArchTxt)
{
    FILE* archBin = fopen(nombreArchBin, "wb");

    if(!archBin)
        return ERROR;

    FILE* archTxt = fopen(nombreArchTxt, "rt");

    if(!archTxt)
        return ERROR;

    char* formatoTxt = "%ld|%[^|]|%ld|%d/%d/%d|%c|%d/%d/%d|%[^|]|%d/%d/%d|%c|%d/%d/%d\n";

    Socio socio;

    while
    (
        fscanf
        (
            archTxt,formatoTxt,
            &socio.nro_socio, socio.apynom, &socio.dni,
                    &socio.fecha_nac.dia, &socio.fecha_nac.mes, &socio.fecha_nac.anio,
                    &socio.sexo,
                    &socio.fecha_afiliacion.dia, &socio.fecha_afiliacion.mes, &socio.fecha_afiliacion.anio,
                    socio.categoria,
                    &socio.fecha_pago.dia, &socio.fecha_pago.mes, &socio.fecha_pago.anio,
                    &socio.estado,
                    &socio.fecha_baja.dia, &socio.fecha_baja.mes, &socio.fecha_baja.anio
        ) != EOF
    )
    {
		fwrite(&socio, sizeof(Socio), 1, archBin);
    }

    fclose(archBin);
    fclose(archTxt);

    return OK;
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

int binAindice(t_indice *ind, const char *path)
{
    FILE *pf;
    Socio reg;
    int nroReg=0;

    if(!(pf=fopen(path,"rb")))
        return -1;

    fread(&reg,sizeof(Socio),1,pf);
    while(!feof(pf))
    {
        ind_insertar(ind,&reg.nro_socio,nroReg++);
        fread(&reg,sizeof(Socio),1,pf);
    }

    fclose(pf);
    return 1;
}
