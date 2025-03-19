# Testes e Resultados

## Objetivo

Os testes têm o objetivo de validar que:

1. Processos com **mais tickets são escolhidos com mais frequência**.
2. A **transferência de tickets** altera a probabilidade de escalonamento.
3. Processos **bloqueados não participam** do sorteio.

## Testes Realizados

### Teste 1: Distribuição de Escolha

**Cenário:**

- Criamos 3 processos com **diferentes quantidades de tickets**.
- Executamos **1000 ciclos** e contamos quantas vezes cada processo foi escolhido.

**Resultado esperado:**

- O número de escolhas deve ser **proporcional ao número de tickets**.

---

### Teste 2: Transferência de Tickets

**Cenário:**

- Criamos **dois processos**:
  - Processo A com **5000 tickets**.
  - Processo B com **100 tickets**.
- Transferimos **2000 tickets** de A para B.
- Monitoramos quantas vezes cada um é escolhido antes e depois da transferência.

**Resultado esperado:**

- O processo B deve ser escalonado **com mais frequência** após receber os tickets.

---

### Teste 3: Processos Bloqueados

**Cenário:**

- Criamos **2 processos** e bloqueamos um deles.
- O processo bloqueado **não deve ser escolhido** até ser desbloqueado.

**Resultado esperado:**

- Enquanto um processo está **bloqueado**, ele nunca recebe CPU.
- Após ser desbloqueado, volta a competir normalmente.

---

## Análise dos Resultados

- **Se a distribuição for proporcional ao número de tickets, o escalonador está correto.**
- **Se processos bloqueados forem escalonados, há um erro na implementação.**
- **Se a transferência de tickets não alterar a frequência de escolha, a função `lottTransferTickets` precisa ser revisada.**

## Conclusão

Os testes ajudam a verificar **se o Lottery Scheduling funciona conforme esperado** e se há ajustes necessários para garantir um comportamento correto.
