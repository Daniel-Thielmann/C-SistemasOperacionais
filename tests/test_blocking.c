#include <stdio.h>
#include <stdlib.h>
#include "process.h"
#include "lottery.h"
#include "sched.h"

int main() {
    Process *plist = NULL;

    // Criando primeiro processo
    plist = processCreate(plist);
    LotterySchedParams *p1_params = malloc(sizeof(LotterySchedParams));
    if (!p1_params) {
        fprintf(stderr, "Erro ao alocar memória para p1_params.\n");
        return 1;
    }
    p1_params->num_tickets = 3000;
    lottInitSchedParams(plist, p1_params);

    // Criando segundo processo
    Process *p2 = processCreate(plist);
    LotterySchedParams *p2_params = malloc(sizeof(LotterySchedParams));
    if (!p2_params) {
        fprintf(stderr, "Erro ao alocar memória para p2_params.\n");
        return 1;
    }
    p2_params->num_tickets = 5000;
    lottInitSchedParams(p2, p2_params);

    printf("🔍 Testando bloqueio de processos...\n");
    printf("Antes do bloqueio:\n");
    
    // Testando escalonamento antes do bloqueio
    for (int i = 0; i < 10; i++) {
        Process *chosen = lottSchedule(plist);
        if (chosen)
            printf("Iteração %d: Processo %d escalonado\n", i, processGetPid(chosen));
    }

    // Obtendo P2 de forma segura
    p2 = processGetNext(plist);
    if (p2) {
        printf("🔒 Bloqueando P2 (PID %d)...\n", processGetPid(p2));
        processSetStatus(p2, PROC_WAITING);
    } else {
        fprintf(stderr, "Erro: P2 não encontrado na lista de processos.\n");
        return 1;
    }

    printf("Após o bloqueio:\n");

    // Testando escalonamento após o bloqueio
    for (int i = 0; i < 10; i++) {
        Process *chosen = lottSchedule(plist);
        if (chosen)
            printf("Iteração %d: Processo %d escalonado\n", i, processGetPid(chosen));
    }

    // Liberando memória dos parâmetros de escalonamento
    free(p1_params);
    free(p2_params);

    return 0;
}
