/*
*  lottery.c - Implementação do algoritmo Lottery Scheduling e sua API
*
*  Autores: SUPER_PROGRAMADORES_C && Daniel Thielmann
*  Projeto: Trabalho Prático I - Sistemas Operacionais
*  Organização: Universidade Federal de Juiz de Fora
*  Departamento: Dep. Ciência da Computação
*
*/

#include "lottery.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Nome único do algoritmo. Deve ter exatamente 4 caracteres.
const char lottName[] = "LOTT";

/**
 * Inicializa o escalonador Lottery Scheduling e o registra no sistema operacional.
 * Essa função é chamada durante a inicialização do sistema.
 */
void lottInitSchedInfo() {
    static SchedInfo si; // Cria uma variável si do tipo SchedInfo e a torna estática dentro da função lottInitSchedInfo.

    // Copia o nome do algoritmo para a estrutura de escalonador
    strncpy(si.name, lottName, MAX_NAME_LEN);
    si.name[MAX_NAME_LEN] = '\0';  // Garante que a string está corretamente terminada

    // Define as funções de controle do algoritmo
    si.initParamsFn = lottInitSchedParams;  // Inicializa parâmetros dos processos
    si.scheduleFn = lottSchedule;           // Escolhe o próximo processo a ser executado
    si.releaseParamsFn = lottReleaseParams; // Libera memória dos processos
    si.notifyProcStatusChangeFn = lottNotifyProcStatusChange; // Notifica mudanças no estado do processo
    
    // Registra o escalonador no sistema
    schedRegisterScheduler(&si);
}

/**
 * Inicializa os parâmetros de escalonamento de um processo.
 * Essa função é chamada quando um processo é associado ao escalonador Lottery Scheduling.
 */
void lottInitSchedParams(Process *p, void *params) {
    if (!p || !params) return;  // Verifica se os ponteiros são válidos
    processSetSchedParams(p, params);  // Define os parâmetros de escalonamento no processo
}

/**
 * Notifica que um processo teve seu estado alterado (por exemplo, foi bloqueado ou liberado).
 * Essa função pode ser usada para atualizar estatísticas internas do algoritmo.
 */
void lottNotifyProcStatusChange(Process* p) {
    (void)p; // Apenas para evitar warnings de parâmetro não utilizado
}

/**
 * Escolhe o próximo processo a ser executado com base no algoritmo Lottery Scheduling.
 * A escolha é feita de forma probabilística baseada no número de tickets de cada processo.
 */
Process* lottSchedule(Process *plist) {
    int total_tickets = 0;
    Process *p = plist;

    // Percorre a lista de processos e soma os tickets de todos os processos prontos
    while (p != NULL) {
        if (processGetStatus(p) == PROC_READY) {  // Verifica se o processo está pronto para execução
            LotterySchedParams *params = (LotterySchedParams*) processGetSchedParams(p);
            total_tickets += params->num_tickets;  // Soma o número total de tickets
        }
        p = processGetNext(p); // Avança para o próximo processo na lista
    }

    // Se não houver processos prontos, retorna NULL
    if (total_tickets == 0) return NULL;

    // Sorteia um número entre 1 e total_tickets para decidir qual processo será escalonado
    int sorteado = (rand() % total_tickets) + 1;
    int acumulado = 0;
    
    // Percorre a lista de processos novamente para selecionar o vencedor do sorteio
    p = plist;
    while (p != NULL) {
        if (processGetStatus(p) == PROC_READY) {
            LotterySchedParams *params = (LotterySchedParams*) processGetSchedParams(p);
            acumulado += params->num_tickets; // Acumula os tickets até atingir o número sorteado
            
            if (acumulado >= sorteado) {
                return p; // Processo escolhido para executar
            }
        }
        p = processGetNext(p);
    }

    return NULL; // Isso não deveria acontecer se a soma dos tickets foi feita corretamente
}

/**
 * Libera os parâmetros de escalonamento de um processo.
 * Essa função é chamada quando um processo deixa de usar o escalonador Lottery Scheduling.
 */
int lottReleaseParams(Process *p) {
    if (!p) return -1;  // Verifica se o processo é válido

    // Libera a memória dos parâmetros do processo
    free(processGetSchedParams(p));
    processSetSchedParams(p, NULL); // Remove os parâmetros do processo

    return 0;
}

/**
 * Transfere um certo número de tickets de um processo para outro.
 * Isso pode ser usado para "doação" de tempo de CPU entre processos cooperativos.
 */
int lottTransferTickets(Process *src, Process *dst, int tickets) {
    if (!src || !dst || tickets <= 0) return 0; // Verifica se os parâmetros são válidos

    // Obtém os parâmetros de escalonamento dos processos de origem e destino
    LotterySchedParams *src_params = (LotterySchedParams*) processGetSchedParams(src);
    LotterySchedParams *dst_params = (LotterySchedParams*) processGetSchedParams(dst);

    // Verifica se os processos possuem parâmetros válidos e se a origem tem tickets suficientes
    if (!src_params || !dst_params || src_params->num_tickets < tickets)
        return 0; // Não pode transferir mais tickets do que o processo possui

    // Transfere os tickets entre os processos
    src_params->num_tickets -= tickets;
    dst_params->num_tickets += tickets;

    return tickets; // Retorna o número de tickets efetivamente transferidos
}
