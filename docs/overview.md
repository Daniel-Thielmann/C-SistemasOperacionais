# Visão Geral do Projeto - Lottery Scheduling

## Introdução

Este projeto implementa o algoritmo **Lottery Scheduling** para escalonamento de processos em um sistema operacional hipotético. Ele faz parte do **Trabalho Prático B** da disciplina **Sistemas Operacionais (DCC062)** na **UFJF**.

## Como Funciona o Lottery Scheduling?

O Lottery Scheduling é um algoritmo de escalonamento **probabilístico**, onde:

1. Cada processo recebe **um número variável de tickets**.
2. A cada ciclo de escalonamento, **um ticket é sorteado aleatoriamente**.
3. O processo que possui o ticket sorteado é **escolhido para execução**.
4. **Tickets podem ser transferidos** entre processos, ajustando suas chances de serem escalonados.

## Estrutura do Projeto

O projeto é composto pelos seguintes arquivos principais:

- `lottery.c` - Implementação do algoritmo Lottery Scheduling.
- `lottery.h` - Cabeçalho com a API do Lottery Scheduling.
- `main.c` - Simulador do sistema (não pode ser modificado).
- `sched.c/h` - API do escalonador (não pode ser modificada).
- `process.c/h` - API de processos (não pode ser modificada).

## Funcionalidades Implementadas

- **Sorteio baseado em tickets**: Processos com mais tickets têm mais chances de serem escolhidos.
- **Transferência de tickets**: Permite que processos passem tickets para outros.
- **Respeito a estados dos processos**: Um processo bloqueado não participa do sorteio.
