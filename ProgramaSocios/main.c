#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "funciones.h"

int main()
{
   char opcion;
   char pathSocios[51] = "../GenerarIndice/socios.dat";
   char pathInd[51] = "../GenerarIndice/socios.idx";
   int flag = 1;
   t_indice ind;

   ind_crear(&ind,sizeof(long),cmpLong);

   ind_cargar(&ind,pathInd);

    FILE* archSocios = fopen(pathSocios,"r+b");

    if(!archSocios)
      return ERROR;

    do {
        if (flag) {
            printf("Bienvenido al sistema de Algoritmos FC!\n\n");
            flag = 0;
        }
        printf("Que desea hacer?\n\n");
        printf("(A) Dar de alta un nuevo socio.\n");
        printf("(M) Modificar el campo 'Apellido, Nombre' a partir de un Nro. Socio a buscar.\n");
        printf("(B) Dar de baja un socio cargando el Nro. Socio a eliminar.\n");
        printf("(L) Listar todos los socios dados de baja ordenados por Nro. Socio.\n");
        printf("(V) Visualizar todos los socios ordenados (sin mostrar los dados de baja) por Nro. Socio.\n");
        printf("(P) Listar los 10 socios con mayor retraso en la fecha de pago de la cuota.\n");
        printf("(S) Salir\n");

        printf("Ingrese la opcion: ");
        fflush(stdin);
        scanf("%c", &opcion);
        printf("\n");

        switch (tolower(opcion)) {
            case 'a':
                altaSocio(archSocios,&ind);
                break;
            case 'm':
                modificarNombreSocio(archSocios,&ind);
                break;
            case 'b':
                bajaSocio(archSocios,&ind);
                break;
            case 'l':
                leerSociosBaja(archSocios,&ind);
                break;
            case 'v':
                leerSociosAlta(archSocios,&ind);
                break;
            case 'p':
                mostrarMax10SociosMasDeudores(archSocios,cmpFecha);
                break;
            case 's':
                printf("\nSaliendo del sistema, que tenga un excelente dia!\n");
                fclose(archSocios);
                ind_grabar(&ind,pathInd);
                ind_vaciar(&ind);
                break;
            default:
                printf("Opcion no valida. Por favor, ingrese una opción valida.\n");
        }
    } while (opcion != 'S' && opcion != 's');
}
