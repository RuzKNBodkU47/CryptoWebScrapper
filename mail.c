#include <stdio.h>
#include <string.h>
#include <curl/curl.h>
#include "mail.h"

#define MAX_LINEAS 10

static const char *lineas[MAX_LINEAS];
static int linea_actual = 0;

static size_t payload_source(void *ptr, size_t size, size_t nmemb, void *userp) {
    if (lineas[linea_actual] == NULL) return 0;
    const char *data = lineas[linea_actual++];
    size_t len = strlen(data);
    memcpy(ptr, data, len);
    return len;
}

int enviar_correo(const char *de, const char *para, const char *usuario, const char *contrasena, const char *smtp_url, const char *asunto, const char *mensaje) {
    CURL *curl;
    CURLcode res;
    struct curl_slist *recipients = NULL;

    // Construir payload
    static char to_line[256], from_line[256], subject_line[256];

    snprintf(to_line, sizeof(to_line), "To: %s\r\n", para);
    snprintf(from_line, sizeof(from_line), "From: %s\r\n", de);
    snprintf(subject_line, sizeof(subject_line), "Subject: %s\r\n", asunto);

    linea_actual = 0;
    lineas[0] = to_line;
    lineas[1] = from_line;
    lineas[2] = subject_line;
    lineas[3] = "\r\n";         // Separador cabecera/cuerpo
    lineas[4] = mensaje;
    lineas[5] = NULL;

    curl = curl_easy_init();
    if (!curl) return 1;

    curl_easy_setopt(curl, CURLOPT_USERNAME, usuario);
    curl_easy_setopt(curl, CURLOPT_PASSWORD, contrasena);
    curl_easy_setopt(curl, CURLOPT_URL, smtp_url);
    curl_easy_setopt(curl, CURLOPT_USE_SSL, (long)CURLUSESSL_ALL);
    curl_easy_setopt(curl, CURLOPT_MAIL_FROM, de);

    recipients = curl_slist_append(recipients, para);
    curl_easy_setopt(curl, CURLOPT_MAIL_RCPT, recipients);
    curl_easy_setopt(curl, CURLOPT_READFUNCTION, payload_source);
    curl_easy_setopt(curl, CURLOPT_UPLOAD, 1L);
    curl_easy_setopt(curl, CURLOPT_USERAGENT, "C-MAILER/1.0");

    res = curl_easy_perform(curl);
    if (res != CURLE_OK) {
        fprintf(stderr, "Error al enviar correo: %s\n", curl_easy_strerror(res));
        return 2;
    }

    curl_slist_free_all(recipients);
    curl_easy_cleanup(curl);
    return 0;
}
