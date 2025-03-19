#include <stdio.h>
#include "lottery.h"
#include "process.h"

int main() {
    Process *plist = NULL;
    
    // Criando processos com diferentes tickets
    plist = processCreate(plist);
    LotterySchedParams *p1_params = malloc(sizeof(LotterySchedParams));
    p1_params->num_tickets = 100;
    lottInitSchedParams(plist, p1_params);
    
    plist = processCreate(plist);
    LotterySchedParams *p2_params = malloc(sizeof(LotterySchedParams));
    p2_params->num_tickets = 5000;
    lottInitSchedParams(plist, p2_params);
    
    plist = processCreate(plist);
    LotterySchedParams *p3_params = malloc(sizeof(LotterySchedParams));
    p3_params->num_tickets = 1000;
    lottInitSchedParams(plist, p3_params);

    printf("🔍 Teste de distribuição de escolha:\n");
    for (int i = 0; i < 1000; i++) {
        Process *chosen = lottSchedule(plist);
        printf("Iteração %d: Processo %d escalonado\n", i, processGetPid(chosen));
    }

    return 0;
}
