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
    static SchedInfo si; // Cria uma variável si do tipo SchedInfo e a torna estática dentro da função

    // Copia o nome do algoritmo para a estrutura de escalonador
    strncpy(si.name, lottName, MAX_NAME_LEN);
    si.name[MAX_NAME_LEN] = '\0';  // Garante terminação nula correta

    // Define as funções que implementam o algoritmo
    si.initParamsFn = lottInitSchedParams;              // Inicializa os parâmetros do processo
    si.scheduleFn = lottSchedule;                       // Seleciona o próximo processo
    si.releaseParamsFn = lottReleaseParams;             // Libera os parâmetros quando o processo termina
    si.notifyProcStatusChangeFn = lottNotifyProcStatusChange; // Notifica mudança de status

    // Registra o escalonador no sistema
    schedRegisterScheduler(&si);
}

/**
 * Inicializa os parâmetros de escalonamento de um processo.
 * Essa função é chamada quando o processo entra no escalonador Lottery.
 */
void lottInitSchedParams(Process *p, void *params) {
    if (!p || !params) return;  // Verifica se ponteiros são válidos
    processSetSchedParams(p, params);  // Associa os parâmetros ao processo
}

/**
 * Notifica mudanças no estado do processo (executando, pronto, bloqueado, etc.).
 * Essa função pode ser usada no futuro para adaptação dinâmica.
 */
void lottNotifyProcStatusChange(Process *p) {
    // Atualmente não realizamos nenhuma ação com a mudança de status
    // Esta função é necessária para compatibilidade com o sistema
    (void)p; // Supressão de warning de parâmetro não usado
}

/**
 * Escolhe o próximo processo a ser executado com base no algoritmo Lottery.
 * Cada processo possui uma quantidade de "tickets" e a seleção é aleatória proporcional.
 */
Process* lottSchedule(Process *plist) {
    int total_tickets = 0;
    Process *p = plist;

    // Soma todos os tickets dos processos prontos (PROC_READY)
    while (p != NULL) {
        if (processGetStatus(p) == PROC_READY) {
            LotterySchedParams *params = (LotterySchedParams*) processGetSchedParams(p);
            total_tickets += params->num_tickets;
        }
        p = processGetNext(p); // Próximo processo
    }

    // Se não há processos prontos, retorna NULL
    if (total_tickets == 0) return NULL;

    // Sorteia um número entre 1 e o total de tickets
    int sorteado = (rand() % total_tickets) + 1;
    int acumulado = 0;

    // Percorre a lista até encontrar o processo vencedor
    p = plist;
    while (p != NULL) {
        if (processGetStatus(p) == PROC_READY) {
            LotterySchedParams *params = (LotterySchedParams*) processGetSchedParams(p);
            acumulado += params->num_tickets;

            if (acumulado >= sorteado) {
                return p; // Processo escolhido
            }
        }
        p = processGetNext(p);
    }

    // Não deveria chegar aqui se os tickets foram somados corretamente
    return NULL;
}

/**
 * Transfere um certo número de tickets de um processo para outro.
 * Útil para simular prioridades ou processos cooperando entre si.
 */
int lottTransferTickets(Process *src, Process *dst, int tickets) {
    if (!src || !dst || tickets <= 0) return 0; // Parâmetros inválidos

    // Obtém os parâmetros dos dois processos
    LotterySchedParams *src_params = (LotterySchedParams*) processGetSchedParams(src);
    LotterySchedParams *dst_params = (LotterySchedParams*) processGetSchedParams(dst);

    // Verifica se há tickets suficientes para transferir
    if (!src_params || !dst_params || src_params->num_tickets < tickets)
        return 0;

    // Realiza a transferência
    src_params->num_tickets -= tickets;
    dst_params->num_tickets += tickets;

    return tickets; // Retorna quantos foram transferidos
}

/**
 * Libera os parâmetros associados ao processo no Lottery Scheduling.
 * Chamado quando o processo termina ou muda de escalonador.
 */
int lottReleaseParams(Process *p) {
    if (!p) return -1;

    // Libera a memória e desvincula os parâmetros
    free(processGetSchedParams(p));
    processSetSchedParams(p, NULL);

    return 0;
}
