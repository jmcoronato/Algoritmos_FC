#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "funciones.h"

int main()
{
        char opcion;
    int flag = 1;

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
        scanf(" %c", &opcion);

        switch (tolower(opcion)) {
            case 'a':
                printf("Simulando dar de alta un nuevo socio...\n");
                break;
            case 'm':
                printf("Simulando modificar el campo 'Apellido, Nombre'...\n");
                break;
            case 'b':
                printf("Simulando dar de baja un socio...\n");
                break;
            case 'l':
                printf("Simulando listar socios dados de baja...\n");
                break;
            case 'v':
                printf("Simulando visualizar socios activos...\n");
                break;
            case 'p':
                printf("Simulando listar socios con retraso en el pago...\n");
                break;
            case 's':
                printf("\nSaliendo del sistema, que tenga un excelente dia!\n");
                break;
            default:
                printf("Opcion no valida. Por favor, ingrese una opción valida.\n");
        }
    } while (opcion != 'S' && opcion != 's');

}
