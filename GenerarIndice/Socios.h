#ifndef SOCIOS_H_INCLUDED
#define SOCIOS_H_INCLUDED

#include "Fecha.h"

typedef struct
{
    long nro_socio;
    char apynom[61];
    long dni;
    Fecha fecha_nac;
    char sexo;
    Fecha fecha_afiliacion;
    char categoria[11];
    Fecha fecha_pago;
    char estado;
    Fecha fecha_baja;
} Socio;

#endif // SOCIOS_H_INCLUDED
