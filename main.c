#include <stdio.h>
#include "mail.h"
#include "GetData.h"
#include "Bitsotracker.h"
int main() {
    const char *de = GetRemitente(1);
    const char *para = GetRemitente(3);
    const char *usuario = GetRemitente(1);
    const char *contrasena = GetRemitente(2);
    const char *smtp = GetRemitente(4);

    const char *asunto = GetRemitente(5);
    const char *mensaje;

    //printf("%s \t %s \t %s \t %s \t %s \t %s",de,para,usuario,contrasena,smtp,asunto );
    printf("\n Iniciando CryptoWebScrapper...");

    printf("\n Iniciando consulta en Bitso...");
    if(BitsoTracker_main()==0){
        perror("\nError en BitsoTracker.");
        return 0;
    }

    
    if (enviar_correo(de, para, usuario, contrasena, smtp, asunto, mensaje) == 0) {
        printf("Correo enviado correctamente.\n");
    } else {
        printf("Fallo al enviar el correo.\n");
    }

    return 0;
}
