#include <stdio.h>
#include <string.h> //libreria para tratamiento de texto

// ARGUMENTOS: TIPO DE OPERACION, NOMBRE DE LA BASE DE DATOS, NOMBRE DE LA TABLA Y DATO A ALMACENAR
// LEER Y ALMACENAR

int main(int argc, char *argv[]) // pasar datos por parametro
{
    FILE *archivo; // creamos un elemento de tipo file denominado archivo

    char *operacion = argv[1];     // tipo de operacion CRUD
    char *basededatos = argv[2];   // nombre de la base de datos
    char *nombrearchivo = argv[3]; // nombre de la tabla
    char *texto = argv[4];         // dato a almacenar o buscar en el fichero

    char registro[200]; // variable para almacenar la cadena que hay en cada linea del fichero

    char rutaarchivo[100];              // defino variable para almacenar la ruta completa
    strcpy(rutaarchivo, basededatos);   // copio el nombre de la base de datos en la rutaarchivo
    strcat(rutaarchivo, "-");           // aniado guion para separar base de datos y tabla
    strcat(nombrearchivo, ".txt");      // concateo con extension .txt
    strcat(rutaarchivo, nombrearchivo); // concateno ruta de archivo con nombre del archio

    if (strcmp(operacion, "select") == 0) // strcmp compara dos string, si el resultado es 0 son iguales
    {
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
        archivo = fopen(rutaarchivo, "a");   // modo "a" aniade
        fputs(strcat(texto, "\n"), archivo); // puts guarda el texto en el fichero
        fclose(archivo);
    }

    else if (strcmp(operacion, "where") == 0)
    {
        archivo = fopen(rutaarchivo, "r");
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