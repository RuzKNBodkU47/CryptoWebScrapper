#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>

//Estructura que almacenara el json que arroja la consulta curl
struct string{
    char *ptr;
    size_t len;
};

//Funcion que inicializa la estructura string
void init_string(struct string *s){
    s->len = 0;
    s->ptr = malloc(1);
    if(s->ptr == NULL){
        perror("\nError en Malloc BitsoTracker.c");
        exit(EXIT_FAILURE);
    }
    s->ptr[0] = '\0';
}

size_t writefunc(void *ptr, size_t size, size_t nmemb, struct string *s){
    size_t new_len = s->len + size * nmemb;
    s->ptr = realloc(s->ptr, new_len+1);
    if(s->ptr ==NULL){
        fprintf(stderr, "\nError en Realloc BitsoTracker.c");
        exit(EXIT_FAILURE);
    }
    memcpy(s->ptr + s->len,  ptr, size * nmemb);
    s->ptr[new_len]= '\0';
    s->len = new_len;

    return size * nmemb;
}

int BitsoTracker_main (){
    FILE *archivo = fopen("archivo.txt","w");
    CURL *curl;
    CURLcode res;
    struct string response;
    if(!archivo){
        perror("\nError al generar el archivo.txt");
        return 0;
    }
    init_string(&response);

    curl = curl_easy_init();
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, "https://api.bitso.com/v3/ticker?book=btc_mxn");
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writefunc);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
        curl_easy_setopt(curl, CURLOPT_USERAGENT, "Mozilla/5.0");
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
        res = curl_easy_perform(curl);
        if (res != CURLE_OK)
            fprintf(stderr, "curl_easy_perform() fallo: %s\n", curl_easy_strerror(res));
        else
            fprintf(archivo,"Respuesta:\n%s\n", response.ptr);

        curl_easy_cleanup(curl);
    }
    fclose(archivo);
    free(response.ptr);
    return 1; 
}