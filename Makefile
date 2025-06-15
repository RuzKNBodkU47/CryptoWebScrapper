# Nombre del ejecutable
TARGET = CryptoWebScrapper

# Archivos fuente
SRCS = main.c mail.c GetData.c Bitsotracker.c

# Archivos objeto generados
OBJS = $(SRCS:.c=.o)

# Flags de compilación
CFLAGS = -Wall -Wextra -O2
LDFLAGS = -lcurl

# Regla principal
all: $(TARGET)

# Cómo compilar el ejecutable
$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET) $(LDFLAGS)

# Compilar archivos .c a .o
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Limpiar archivos generados
clean:
	rm -f $(OBJS) $(TARGET)

# Limpieza total (incluyendo backup/temporal)
distclean: clean
	rm -f *~ *.bak

.PHONY: all clean distclean
