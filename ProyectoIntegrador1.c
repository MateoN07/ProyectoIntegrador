#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_UBICACIONES 6

struct Zona
{
    char nombre[50];
    float pm25;
    float co;
    float so2;
    float no2;
};


void evaluarContaminacion(struct Zona *zona)
{
    printf("\nEvaluando contaminacion en: %s\n", zona->nombre);
    if (zona->pm25 <= 15)
    {
        printf("PM2.5: %.2f ug/m3 - Bueno\n", zona->pm25);
    }
    else
    {
        printf("PM2.5: %.2f ug/m3 - Alto, supera el limite aceptable\n", zona->pm25);
        printf("Recomendacion: Reducir actividades al aire libre y evitar el uso excesivo de vehiculos.\n");
    }

    if (zona->co <= 3490)
    {
        printf("CO: %.2f ppb - Bueno\n", zona->co);
    }
    else
    {
        printf("CO: %.2f ppb - Alto, supera el limite aceptable\n", zona->co);
        printf("Recomendacion: Reducir el uso de vehiculos de gasolina y optar por transporte publico.\n");
    }

    if (zona->so2 <= 15.27)
    {
        printf("SO2: %.2f ppb - Bueno\n", zona->so2);
    }
    else
    {
        printf("SO2: %.2f ppb - Alto, supera el limite aceptable\n", zona->so2);
        printf("Recomendacion: Limitar emisiones industriales y el uso de combustibles fosiles.\n");
    }

    if (zona->no2 <= 13.29)
    {
        printf("NO2: %.2f ppb - Bueno\n", zona->no2);
    }
    else
    {
        printf("NO2: %.2f ppb - Alto, supera el limite aceptable\n", zona->no2);
        printf("Recomendacion: Reducir el uso de combustibles fosiles.\n");
    }
}


const char *predecirCambio(struct Zona *zona)
{
    if (zona->pm25 > 15 && zona->co > 3490 && zona->so2 > 15.27 && zona->no2 > 13.29)
    {
        return "Aumentara";
    }
    else if (zona->pm25 <= 15 && zona->co <= 3490 && zona->so2 <= 15.27 && zona->no2 <= 13.29)
    {
        return "Disminuira";
    }
    else
    {
        return "Se mantendra estable";
    }
}

const char *predecirContaminacion(float temperatura, float velocidadViento, float humedad, float contaminacionActual)
{
    if (contaminacionActual > 100 && velocidadViento < 5 && humedad > 70)
    {
        return "Aumentara";
    }
    else if (contaminacionActual < 50 && velocidadViento > 10)
    {
        return "Disminuira";
    }
    else if (temperatura > 30 && humedad < 50 && velocidadViento < 5)
    {
        return "Aumentara";
    }
    else
    {
        return "Se mantendra estable";
    }
}

void guardarDatos(struct Zona *zonas, int totalZonas)
{
    FILE *archivo = fopen("reporte_contaminacion.txt", "w");
    if (archivo == NULL)
    {
        printf("Error al abrir el archivo para guardar los datos.\n");
        return;
    }

    fprintf(archivo, "Reporte de Contaminacion\n\n");
    for (int i = 0; i < totalZonas; i++)
    {
        fprintf(archivo, "Zona: %s\n", zonas[i].nombre);
        fprintf(archivo, "PM2.5: %.2f ug/m3\n", zonas[i].pm25);
        fprintf(archivo, "CO: %.2f ppb\n", zonas[i].co);
        fprintf(archivo, "SO2: %.2f ppb\n", zonas[i].so2);
        fprintf(archivo, "NO2: %.2f ppb\n", zonas[i].no2);
        fprintf(archivo, "Prediccion: %s\n\n", predecirCambio(&zonas[i]));
    }

    fclose(archivo);
    printf("\nDatos guardados en reporte_contaminacion.txt\n");
}

int main()
{
    struct Zona zonas[MAX_UBICACIONES] = {
        {"Tumbaco", 7, 215, 3, 11},
        {"El Recreo", 17, 504, 4, 15},
        {"Centro Historico", 12, 520, 4, 14},
        {"La Carolina", 15, 265, 4, 13},
        {"Sangolqui", 10, 219, 13, 12}};

    int totalZonas = 5;
    int opcion;

    do
    {
        printf("\nMenu Principal:\n");
        printf("1. Mostrar los 5 sitios seleccionados\n");
        printf("2. Agregar otro sitio\n");
        printf("3. Prediccion basada en parametros ambientales\n");
        printf("4. Guardar datos y salir\n\n");
        printf("Seleccione una opcion: ");
        scanf("%d", &opcion);

        switch (opcion)
        {
        case 1:
            printf("\nNiveles de contaminacion en las distintas ubicaciones en los ultimos 30 dias\n");
            for (int i = 0; i < totalZonas; i++)
            {
                printf("\nZona: %s\nPM2.5: %.2f ug/m3\nCO: %.2f ppb\nSO2: %.2f ppb\nNO2: %.2f ppb\n",
                       zonas[i].nombre, zonas[i].pm25, zonas[i].co, zonas[i].so2, zonas[i].no2);
                evaluarContaminacion(&zonas[i]); // Usar puntero
                printf("Prediccion: %s\n", predecirCambio(&zonas[i])); 
            }
            break;

        case 2:
            if (totalZonas < MAX_UBICACIONES)
            {
                struct Zona *nuevaZona = &zonas[totalZonas]; 
                printf("Ingrese el nombre de la nueva zona: ");
                getchar(); 
                fgets(nuevaZona->nombre, sizeof(nuevaZona->nombre), stdin);
                nuevaZona->nombre[strcspn(nuevaZona->nombre, "\n")] = '\0';

                printf("PM2.5 (ug/m3): ");
                scanf("%f", &nuevaZona->pm25);
                printf("CO (ppb): ");
                scanf("%f", &nuevaZona->co);
                printf("SO2 (ppb): ");
                scanf("%f", &nuevaZona->so2);
                printf("NO2 (ppb): ");
                scanf("%f", &nuevaZona->no2);

                totalZonas++;
                evaluarContaminacion(nuevaZona); 
                printf("Prediccion: %s\n", predecirCambio(nuevaZona));
            }
            else
            {
                printf("Se ha alcanzado el numero maximo de zonas.\n");
            }
            break;

        case 3:
        {
            float temperatura, velocidadViento, humedad, contaminacionActual;
            printf("Prediccion de contaminacion ambiental en 24 horas\n");
            printf("Ingrese la temperatura actual en centigrados: ");
            scanf("%f", &temperatura);
            printf("Ingrese la velocidad del viento en km/h: ");
            scanf("%f", &velocidadViento);
            printf("Ingrese la humedad actual: ");
            scanf("%f", &humedad);
            printf("Ingrese la concentracion actual de contaminantes en µg/m³: ");
            scanf("%f", &contaminacionActual);

            const char *resultado = predecirContaminacion(temperatura, velocidadViento, humedad, contaminacionActual);
            printf("La prediccion para la contaminacion en 24 horas es: %s\n", resultado);
            break;
        }

        case 4:
        {
            printf("Saliendo del programa\n");
            guardarDatos(zonas, totalZonas);
            break;
        }

        default:
            printf("Opcion invalida\n");
        }
    } while (opcion != 4);

    return 0;
}
