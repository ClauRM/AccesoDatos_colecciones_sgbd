#include <stdio.h>
#include <string.h> //libreria para tratamiento de texto

// ARGUMENTOS: TIPO DE OPERACION, NOMBRE DE LA BASE DE DATOS, NOMBRE DE LA TABLA Y DATO A ALMACENAR
// LEER Y ALMACENAR

int main(int argc, char *argv[]) // pasar datos por parametro
{
    FILE *archivo; // creamos un elemento de tipo file denominado archivo

    char *operacion = argv[1];   // tipo de operacion
    char *basededatos = argv[2]; // nombre de la base de datos
    char *coleccion = argv[3];   // nombre de la coleccion
    char *documento = argv[4];   // nombre del fichero

    char registro[200]; // variable para almacenar la cadena que hay en cada linea del fichero

    char rutaarchivo[100];            // defino variable para almacenar la ruta completa
    strcpy(rutaarchivo, basededatos); // copio el nombre de la base de datos en la rutaarchivo
    strcat(rutaarchivo, "/");         // concateno la rutaarchivo con /
    strcat(rutaarchivo, coleccion);   // concateno la rutaarchivo con nombre de la coleccion
    strcat(rutaarchivo, "/");         // concateno con otra /
    strcat(rutaarchivo, documento);   // concateno la rutaarchivo con el nombre del fichero
    strcat(rutaarchivo, ".json");     // concateno con la extension

    if (strcmp(operacion, "select") == 0) // strcmp compara dos string, si el resultado es 0 son iguales
    {
        // MODIFICAR LEER TODOS LOS ARCHIVOS DE UNA CARPETA
        archivo = fopen(rutaarchivo, "r"); // abro fichero con paramentros: nombre del fichero y modo (si es "a" lo aniade)
        int numero = 1;                    // variable para indicar el numero de registros que hay
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
        archivo = fopen(rutaarchivo, "w");   // modo write para insertar un nuevo registro unico
        char *texto = argv[5];               // dato a almacenar o buscar en el fichero
        fputs(strcat(texto, "\n"), archivo); // puts guarda el texto en el fichero
        fclose(archivo);
    }

    else if (strcmp(operacion, "where") == 0)
    {
        archivo = fopen(rutaarchivo, "r");
        char *texto = argv[5];                        // dato a almacenar o buscar en el fichero
        while (fgets(registro, 200, archivo) != NULL) // mientras que haya un registro a leer en el fichero, toma la longitud de max caracteres y no sea null
        {
            if (strstr(registro, texto) != NULL)
            { // busca el texto en el registro actual leido. Si encuentra coincidencia devuelve distinto de NULL
                printf("Localizado registro: %s \n", registro);
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