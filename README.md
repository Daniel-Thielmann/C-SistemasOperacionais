# 📌 Lottery Scheduling - Trabalho Prático B (DCC062 - SO)

## 📌 Descrição do Projeto

Este projeto é a implementação do algoritmo **Lottery Scheduling** para escalonamento de processos em um sistema operacional hipotético. O código faz parte do **Trabalho Prático B** da disciplina **Sistemas Operacionais (DCC062)** na **UFJF**.

## 📌 Estrutura do Projeto

```
📂 lottery-scheduling
│── 📂 src               # Código-fonte principal
│   │── lottery.c        # Implementação do Lottery Scheduling
│   │── lottery.h        # Header do Lottery Scheduling
│   │── main.c           # Simulador do sistema (não modificar)
│   │── process.c        # API de processos (não modificar)
│   │── process.h        # Header da API de processos (não modificar)
│   │── sched.c          # API do escalonador (não modificar)
│   │── sched.h          # Header do escalonador (não modificar)
│── 📂 docs              # Documentação do projeto
│── 📂 tests             # Testes e logs de saída
│── .gitignore           # Arquivo para ignorar arquivos desnecessários
│── README.md            # Descrição do projeto
│── Makefile             # Script para compilação
```

## 📌 Como Funciona o Lottery Scheduling

O algoritmo **Lottery Scheduling** funciona da seguinte forma:

1. Cada processo recebe um número de **tickets**.
2. Um **ticket é sorteado** aleatoriamente.
3. O processo que possui esse ticket é **escolhido para execução**.
4. Os tickets podem ser **transferidos entre processos**.
5. Se um processo for **bloqueado**, ele não participa do sorteio até ser desbloqueado.

## 📌 Como Compilar e Executar

### 🔹 **Requisitos**

- **MinGW (Windows)** ou **GCC (Linux/Mac)**
- **Make** instalado

### 🔹 **Compilação**

Para compilar o código, execute o seguinte comando na raiz do projeto:

```bash
mingw32-make  # Para Windows
make           # Para Linux/Mac
```

Isso gerará um executável `main.out` na pasta raiz.

### 🔹 **Executando o Simulador**

No terminal, execute:

```bash
./main.out    # Linux/Mac
.\main.out    # PowerShell Windows
main.out      # Prompt de Comando Windows
```

O simulador executará o Lottery Scheduling e imprimirá o estado dos processos a cada iteração.

## 📌 Testes

Os testes são armazenados na pasta `tests/`. Para testar o código:

```bash
./main.out > tests/output.log
```

Isso salvará a saída do programa no arquivo `output.log`, permitindo análise posterior.

## 📌 Autores

- **Aluno:** Daniel Alves Thielmann
- **Professor:** Marcelo Moreno
- **Disciplina:** Sistemas Operacionais (DCC062) - UFJF
