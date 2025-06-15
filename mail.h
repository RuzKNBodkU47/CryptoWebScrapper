#ifndef MAIL_H
#define MAIL_H

int enviar_correo(const char *de, const char *para, const char *usuario, const char *contrasena, const char *smtp_url, const char *asunto, const char *mensaje);

#endif // MAIL_H
