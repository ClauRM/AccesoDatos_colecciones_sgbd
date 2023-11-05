#include <stdio.h>
#include <string.h> //libreria para tratamiento de texto

int main(int argc, char *argv[])
{
    FILE *archivo;

    char *operacion = argv[1];   // tipo de operacion
    char *basededatos = argv[2]; // nombre de la base de datos
    char *coleccion = argv[3];   // nombre de la coleccion

    char rutacollection[100];
    strcpy(rutacollection, basededatos);
    strcat(rutacollection, "/");
    strcat(rutacollection, coleccion);

    if (strcmp(operacion, "select") == 0) // strcmp compara dos string, si el resultado es 0 son iguales
    {
        char *documento = argv[4]; // nombre del fichero
        char rutaarchivo[100];     // defino variable para almacenar la ruta completa
        strcpy(rutaarchivo, rutacollection);
        strcat(rutaarchivo, "/"); // a la ruta de archivo concatenar/documento.json
        strcat(rutaarchivo, documento);
        strcat(rutaarchivo, ".json");

        archivo = fopen(rutaarchivo, "r"); // abro fichero con paramentros: nombre del fichero y modo (si es "a" lo aniade)
        int numero = 1;                    // variable para indicar el numero de registros que hay
        char registro[200];                // variable para almacenar la cadena que hay en cada linea del fichero
        printf("Datos del fichero %s: \n", rutaarchivo);
        while (fgets(registro, 200, archivo) != NULL) // mientras que haya un registro a leer en el fichero, toma la longitud de max caracteres y no sea null
        {
            printf("%i: %s", numero, registro); // muestra el contenido
            numero++;
        }
        fclose(archivo); // cierro fichero
    }
    else if (strcmp(operacion, "insert") == 0)
    {
        char *documento = argv[4]; // nombre del fichero
        char *texto = argv[5];     // dato a almacenar o buscar en el fichero

        char rutaarchivo[100]; // defino variable para almacenar la ruta completa
        strcpy(rutaarchivo, rutacollection);
        strcat(rutaarchivo, "/"); // a la ruta de archivo concatenar/documento.json
        strcat(rutaarchivo, documento);
        strcat(rutaarchivo, ".json");

        archivo = fopen(rutaarchivo, "w");   // modo write para insertar un nuevo registro unico
        fputs(strcat(texto, "\n"), archivo); // puts guarda el texto en el fichero
        fclose(archivo);
    }
    else if (strcmp(operacion, "create_collection") == 0)
    {
        // crear nueva carpeta collection con mkdir
        if (mkdir(rutacollection, 0777) == 0)
        {
            printf("se ha creado collection");
        }
        else
        {
            printf("no se ha podido crear la collection");
        }
    }
    else if (strcmp(operacion, "where") == 0)
    {
        char *documento = argv[4]; // nombre del fichero
        char *texto = argv[5];     // dato a almacenar o buscar en el fichero

        char rutaarchivo[100]; // defino variable para almacenar la ruta completa
        strcpy(rutaarchivo, rutacollection);
        strcat(rutaarchivo, "/"); // a la ruta de archivo concatenar/documento.json
        strcat(rutaarchivo, documento);
        strcat(rutaarchivo, ".json");

        archivo = fopen(rutaarchivo, "r");

        char registro[200];                           // variable para almacenar la cadena que hay en cada linea del fichero
        while (fgets(registro, 200, archivo) != NULL) // mientras que haya un registro a leer en el fichero, toma la longitud de max caracteres y no sea null
        {
            if (strstr(registro, texto) != NULL)
            { // busca el texto en el registro actual leido. Si encuentra coincidencia devuelve distinto de NULL
                printf("Localizado registro: %s \n", registro);
            }
            else
            {
                printf("No se han localizado registros");
            }
        }
        fclose(archivo);
    }
    else
    {
        printf("ERROR. Opcion marcada no valida.");
    }

    return 0;
}