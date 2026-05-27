# Compilador e flags de otimização (-Isrc adicionado para encontrar o oracle.h)
CC = gcc
CFLAGS = -Wall -Wextra -O3 -Isrc

# Arquivos fonte e objetos
SRC = main.c src/oracle.c src/brute_force.c src/divide_conquer.c src/dynamic.c src/genetic.c
OBJ = $(SRC:.c=.o)

# Nome do executável final (conforme exigido no documento)
EXEC = cracker

# Regra padrão
all: $(EXEC)

# Regra para linkar os objetos e criar o executável
$(EXEC): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

# Regra para compilar os arquivos .c em .o
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Regra para limpar os arquivos compilados (útil para recompilar do zero)
clean:
	rm -f $(OBJ) $(EXEC)