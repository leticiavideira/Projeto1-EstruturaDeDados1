# Nome do executável
TARGET = ted

# Nome do aluno
ALUNO = leticiavg

# Compilador
CC = gcc

# Flags de compilação
CFLAGS = -std=c99 -fstack-protector-all -Wall -Wextra -O0 -g -ggdb

#Diretórios adicionais
ESTRUTURAS_DIR = estruturas
FORMAS_DIR = formas
GERAIS_DIR = gerais

# Bibliotecas adicionais 
LIBS = -lm

# Lista de arquivos de origem
SRCS = main.c \
       $(wildcard $(ESTRUTURAS_DIR)/*.c) \
       $(wildcard $(FORMAS_DIR)/*.c) \
       $(wildcard $(GERAIS_DIR)/*.c)

# Lista de arquivos de objeto
OBJS = $(SRCS:.c=.o)

# Incluir diretórios
INC_FLAGS = -I. -I$(ESTRUTURAS_DIR) -I$(FORMAS_DIR) -I$(GERAIS_DIR)

# Regra de compilação dos arquivos de objeto
%.o: %.c
	$(CC) $(CFLAGS) $(INC_FLAGS) -c $< -o $@

# Regra de compilação do executável
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBS) -o $(TARGET)

# Limpar arquivos intermediários e o executável
clean:
	rm -f $(OBJS) $(TARGET)

# Falso alvo para evitar conflitos com arquivos chamados "clean"
.PHONY: clean

pack: $(TARGET)
	rm -f ../$(ALUNO).zip
	echo $(ALUNO)
	date >> .entrega
	cd ..; zip $(ALUNO).zip -r src Makefile LEIA-ME.txt .entrega