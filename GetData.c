#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "GetData.h"


//#define FILE "Mailinfo"
#define MAX 128
#define MAX_LINEA 256


void quitar_salto_linea(char *str){
    str[strcspn(str, "\r\n")] = '\0';
}

char* GetRemitente(int menu){
    char* valor_fin = malloc (sizeof(char)*MAX);
    
    if(!valor_fin){
        perror("Error en Malloc GetData.c");
        return NULL;
    }

    FILE *archivo = fopen("Mailinfo","r");
    if(archivo == NULL){
        perror("Error en abrir archivo de datos de correo..");
        return NULL;
    }   
    
    char linea[MAX_LINEA];

    while (fgets(linea, sizeof(linea), archivo)){
        quitar_salto_linea(linea);

        char *clave = strtok(linea,"=");
        char *valor = strtok(NULL,"=");

        if(!clave || !valor) continue;

        if ((strcmp(clave, "Remitente") == 0 && menu==1) ||
            (strcmp(clave, "Token") == 0 && menu==2) ||
            (strcmp(clave, "Destinatario") == 0 && menu==3) ||
            (strcmp(clave, "Protocolo") == 0 && menu==4) ||
            (strcmp(clave, "Asunto") == 0 && menu==5)) {
            
            strncpy(valor_fin, valor, MAX);
            fclose(archivo);
            return valor_fin;
        
            }
       
    }
    return NULL;
}