# Nome do executável
EXEC = main.out

# Compilador
CC = gcc

# Flags de compilação
CFLAGS = -Wall -Wextra -std=c99 -Wno-unused-variable

# Arquivos-fonte
SRCS = src/main.c src/process.c src/sched.c src/lottery.c
OBJS = $(SRCS:.c=.o)

# Regra padrão: compila tudo
$(EXEC): $(OBJS)
	$(CC) $(CFLAGS) -o $(EXEC) $(OBJS)

# Regra para compilar arquivos individuais
src/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Regra para limpar os arquivos compilados
clean:
	rm -f src/*.o $(EXEC)
