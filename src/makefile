# Nome do executável
TARGET = ted

# Nome do aluno
ALUNO = leticiavg

# Compilador
CC = gcc

# Flags de compilação
CFLAGS = -std=c99 -fstack-protector-all -Wall -Wextra -O0 -g -ggdb

# Diretório de código-fonte
SRC_DIR = ./src

# Diretório de cabeçalhos
INC_DIR = ./src/includes

# Diretório de testes
TEST_DIR = ./src/test

# Bibliotecas adicionais 
LIBS = -lm

# Lista de arquivos de origem
SRCS = $(wildcard $(SRC_DIR)/*.c) $(wildcard $(TEST_DIR)/*.c)

# Lista de arquivos de objeto
OBJS = $(SRCS:.c=.o)

# Incluir diretórios
INC_FLAGS = -I$(INC_DIR)

# Regra de compilação dos arquivos de objeto
$(SRC_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) $(INC_FLAGS) -c $< -o $@

# Regra de compilação do executável
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBS) -o $(TARGET)

# Limpar arquivos intermediários e o executável
clean:
	rm -f $(SRC_DIR)/*.o $(TEST_DIR)/*.o $(TARGET)

# Falso alvo para evitar conflitos com arquivos chamados "clean"
.PHONY: clean

pack: $(TARGET)
	rm -f ../$(ALUNO).zip
	echo $(ALUNO)
	date >> .entrega
	cd ..; zip $(ALUNO).zip -r src/*.c src/includes/*.h src/test/*.c src/Makefile LEIA-ME.txt .entrega