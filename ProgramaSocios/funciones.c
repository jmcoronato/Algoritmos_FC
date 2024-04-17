#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "funciones.h"
#include "../GenerarIndice/Indice.h"
#include "../GenerarIndice/Socios.h"
#include "../GenerarIndice/Fecha.h"

void altaSocio(FILE *pf,t_indice *ind)
{
    Socio reg;
    char catValidas[6][10]={"MENOR", "CADETE", "ADULTO", "VITALICIO","HONORARIO", "JUBILADO"};
    int flag = 1;
    unsigned nro_reg;
    char apellido[30];
    char nombre[31];

    do{
        if(flag)
            flag=0;
        else
            printf("Numero de socio invalido\n");
        printf("Ingrese Numero de socio: ");
        scanf("%ld",&reg.nro_socio);
    }while(1>=reg.nro_socio||reg.nro_socio>=10000000);

    flag=1;
    if(ind_buscar(ind,&reg.nro_socio,&nro_reg))
    {
       fseek(pf,sizeof(Socio)*nro_reg,SEEK_SET);
       fread(&reg,sizeof(Socio),1,pf);
       if((reg.estado) == 'A')   ///Socio activo
       {
         printf("Socio ya activo!\n");
         fseek(pf,0,SEEK_SET);
         return;
       }
       else /// Socio Inactivo
       {
          reg.estado = 'A';
          reg.fecha_baja.anio = 0;
          reg.fecha_baja.mes = 0;
          reg.fecha_baja.dia = 0;
          fseek(pf,-(long)sizeof(Socio),SEEK_CUR);
          fwrite(&reg,sizeof(Socio),1,pf);
          fseek(pf,0,SEEK_SET);
          printf("\nSocio Inactivo dado de Alta Exitosamente!\n");
          return;
       }
    }
    do{
        if(flag)
            flag=0;
        else
            printf("DNI invalido\n");
        printf("Ingrese DNI socio: ");
        scanf("%ld",&reg.dni);
    }while(10000>=reg.dni||reg.dni>=100000000);

    flag=1;
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

   flag = 1;
    do
       {
         if(flag)
            flag = 0;
         else
            printf("\nFormato de fecha incorrecto\n\n");

         printf("\nIngrese la fecha de nacimiento (DD/MM/AAAA)\n\n");

         reg.fecha_nac = ingresarFecha();

       }while(!(esFechaValida(reg.fecha_nac)));

    printf("Ingrese Sexo (M: Masculino/F: Femenino/O: Otro): ");
    fflush(stdin);
    scanf("%c",&reg.sexo);
    reg.sexo=toupper(reg.sexo);
    while(reg.sexo != 'M' && reg.sexo != 'F' && reg.sexo != 'O')
    {
      printf("Letra Incorrecta. Ingrese uno de los siguientes valores (M: Masculino/F: Femenino/O: Otro): ");
      fflush(stdin);
      scanf("%c",&reg.sexo);
      reg.sexo=toupper(reg.sexo);
    }

    flag = 1;

    do
       {
         if(flag)
            flag = 0;
         else
            printf("\nFormato de fecha incorrecto\n\n");

         printf("\nIngrese la fecha Afiliacion (DD/MM/AAAA)\n\n");

         reg.fecha_afiliacion = ingresarFecha();

       }while(!(esFechaValida(reg.fecha_afiliacion)));

       reg.fecha_pago = reg.fecha_afiliacion;

    printf("Ingrese categoria ('MENOR', 'CADETE', 'ADULTO', 'VITALICIO','HONORARIO', 'JUBILADO'): ");
    fflush(stdin);
    scanf("%s",reg.categoria);

    while(!buscarEnVec(catValidas,reg.categoria))
    {
        printf("Categoria invalida, ingrese nuevamenete ('MENOR', 'CADETE', 'ADULTO', 'VITALICIO','HONORARIO', 'JUBILADO'):");
        fflush(stdin);
        scanf("%s",reg.categoria);
    }
    mayusculaCadena(reg.categoria);

    reg.fecha_baja.anio = 0;
    reg.fecha_baja.mes = 0;
    reg.fecha_baja.dia = 0;

   reg.estado = 'A';
   fseek(pf,0,SEEK_END);
   nro_reg = (ftell(pf)/sizeof(Socio));
   ind_insertar(ind,&reg.nro_socio,nro_reg);
   fwrite(&reg,sizeof(Socio),1,pf);

    fseek(pf,0,SEEK_SET);
    printf("\nSocio dado de Alta Exitosamente!\n");
}

int buscarEnVec(char vec[][10],const char *categoria)
{
    int cmp,i=0;

    while((cmp=strcmpi(vec[i],categoria)) && i<6)
    {
       i++;
    }

    if(cmp==0)
        return 1;

    return 0;
}

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
       do
       {
         if(flag)
            flag = 0;
         else
            printf("\nFormato de fecha incorrecto\n\n");

         printf("\nIngrese la fecha de baja (DD/MM/AAAA)\n\n");

         reg.fecha_baja = ingresarFecha();

       }while(!(esFechaValida(reg.fecha_baja)));

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
   fseek(archivo,0,SEEK_SET);
}

void mostrarSocioAlta(const void* reg,unsigned tam_clave, void* pf)
{
   FILE* archivo = (FILE*)pf;
   Socio socio;
   unsigned nroReg = *(unsigned*)(reg+tam_clave);

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
            printf("Estado: %c\n\n", socio.estado);
   }
}

void leerSociosBaja(FILE* archivo, t_indice* ind)
{
   ind_recorrer(ind,mostrarSocioBaja,archivo);
   fseek(archivo,0,SEEK_SET);
}

void mostrarSocioBaja(const void* reg,unsigned tam_clave, void* pf)
{
   FILE* archivo = (FILE*)pf;
   Socio socio;
   unsigned nroReg = *(unsigned*)(reg+tam_clave);

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

      puts("Ingrese el o los Apellidos del Socio:");
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

void mayusculaCadena(char *cadena) {
    // Verificar si la cadena está vacía
    if (cadena == NULL || *cadena == '\0') {
        return;  // No hay nada que normalizar
    }

    // Recorrer la cadena para convertir las letras a minusculas
    while (*(cadena) != '\0')
    {
       *cadena = toupper(*cadena);
       cadena++;
    }

}

void mostrarMax10SociosMasDeudores(FILE* arch,int compararFecha(const void*,const void*))
{
    t_indice ind;
    unsigned nroReg=0,i=0;
    Socio reg,socio;
    void* clave=malloc(sizeof(Fecha));
    if(!clave)
        return;
    ind_crear(&ind,sizeof(Fecha),compararFecha);
    fread(&reg,sizeof(Socio),1,arch);
    while(!feof(arch))
    {
        ind_insertar(&ind,&reg.fecha_pago,nroReg++);
        fread(&reg,sizeof(Socio),1,arch);
    }
    while(i<10&&!ind_fin(&ind))
    {
        ind_primero(&ind,clave,&nroReg);
        fseek(arch,sizeof(reg)*nroReg,SEEK_SET);
        fread(&reg,sizeof(reg),1,arch);
        socio=reg;
        if(socio.estado=='A')
        {
            i++;
            printf("Numero de Socio: %ld\n", socio.nro_socio);
            printf("Nombre y Apellido: %s\n", socio.apynom);
            printf("DNI: %ld\n", socio.dni);
            printf("Fecha de Nacimiento: %d/%d/%d\n", socio.fecha_nac.dia, socio.fecha_nac.mes, socio.fecha_nac.anio);
            printf("Sexo: %c\n", socio.sexo);
            printf("Fecha de Afiliacion: %d/%d/%d\n", socio.fecha_afiliacion.dia, socio.fecha_afiliacion.mes, socio.fecha_afiliacion.anio);
            printf("Categoria: %s\n", socio.categoria);
            printf("Fecha de Pago: %d/%d/%d\n", socio.fecha_pago.dia, socio.fecha_pago.mes, socio.fecha_pago.anio);
            printf("Estado: %c\n\n", socio.estado);
        }
    }
    free(clave);
    ind_vaciar(&ind);
}

void mostrarDeudores(FILE* arch,Cmp cmp)
{
   t_lista lista;
   crear_lista(&lista);
   Socio socio;
   int i = 0;

   fread(&socio,sizeof(Socio),1,arch);

   while(!feof(arch))
   {
      insertar_en_orden_lista(&lista,&socio,sizeof(Socio),cmp);
      fread(&socio,sizeof(Socio),1,arch);
   }

   while(i<10 && !lista_vacia(&lista))
   {
      sacar_de_lista_ordenada(&lista,&socio,sizeof(Socio),cmp);
      if(socio.estado=='A')
        {
            i++;
            printf("Numero de Socio: %ld\n", socio.nro_socio);
            printf("Nombre y Apellido: %s\n", socio.apynom);
            printf("DNI: %ld\n", socio.dni);
            printf("Fecha de Nacimiento: %d/%d/%d\n", socio.fecha_nac.dia, socio.fecha_nac.mes, socio.fecha_nac.anio);
            printf("Sexo: %c\n", socio.sexo);
            printf("Fecha de Afiliacion: %d/%d/%d\n", socio.fecha_afiliacion.dia, socio.fecha_afiliacion.mes, socio.fecha_afiliacion.anio);
            printf("Categoria: %s\n", socio.categoria);
            printf("Fecha de Pago: %d/%d/%d\n", socio.fecha_pago.dia, socio.fecha_pago.mes, socio.fecha_pago.anio);
            printf("Estado: %c\n\n", socio.estado);
        }
   }
   vaciar_lista(&lista);
}

int cmpFecha(const void* e1,const void* e2)
{
   int r;
   Fecha f1 = *(Fecha*)e1;
   Fecha f2 = *(Fecha*)e2;

   if(f1.anio!=f2.anio)
      return f1.anio-f2.anio;

   if(f1.mes!=f2.mes)
      return f1.mes-f2.mes;
    r=f1.dia-f2.dia;
    r==0? r=-1 : r;
    return r;
}

int cmpLong(const void* a, const void* b)
{
   return *(long*)a - *(long*)b;
}
