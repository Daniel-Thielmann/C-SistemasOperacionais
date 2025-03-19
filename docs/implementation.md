# Implementação do Lottery Scheduling

## Estrutura do Código

A implementação do Lottery Scheduling está contida em dois arquivos principais:

- **`lottery.h`** - Declaração da API do Lottery Scheduling.
- **`lottery.c`** - Implementação das funções do escalonador.

## Funções Implementadas

### `void lottInitSchedInfo(void)`

- Registra o Lottery Scheduling no sistema.
- Define as funções de inicialização, escalonamento e liberação de recursos.

### `void lottInitSchedParams(Process *p, void *params)`

- Define o número de tickets para um processo recém-criado.

### `void lottNotifyProcStatusChange(Process* p)`

- Atualmente não é usada, mas pode ser utilizada no futuro para reagir a mudanças de estado dos processos.

### `Process* lottSchedule(Process *plist)`

- **Soma os tickets** dos processos prontos (`PROC_READY`).
- **Sorteia um número aleatório** e seleciona o processo correspondente.
- **Retorna o processo escolhido** para execução.

### `int lottReleaseParams(Process *p)`

- Libera a memória dos parâmetros do Lottery Scheduling de um processo removido.

### `int lottTransferTickets(Process *src, Process *dst, int tickets)`

- Permite que um processo **transfira tickets** para outro.
- Garante que um processo **não doe mais tickets do que possui**.
