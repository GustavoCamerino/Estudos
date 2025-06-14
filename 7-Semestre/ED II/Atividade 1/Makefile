# Nome do compilador
CC = gcc

# Flags de compilação (avisos e padrões C mais seguros)
CFLAGS = -Wall -Wextra -std=c99

# Nome do executável final
EXEC = BST

# Fonte principal
SRC = BST.c

# Regra padrão
all: $(EXEC)

# Regra para compilar o executável
$(EXEC): $(SRC)
	$(CC) $(CFLAGS) -o $(EXEC) $(SRC)

# Limpar arquivos gerados
clean:
	rm -f $(EXEC)
