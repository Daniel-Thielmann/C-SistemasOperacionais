#include <stdio.h>
#include "lottery.h"
#include "process.h"

int main() {
    Process *p1 = processCreate(NULL);
    LotterySchedParams *p1_params = malloc(sizeof(LotterySchedParams));
    p1_params->num_tickets = 5000;
    lottInitSchedParams(p1, p1_params);

    Process *p2 = processCreate(p1);
    LotterySchedParams *p2_params = malloc(sizeof(LotterySchedParams));
    p2_params->num_tickets = 100;
    lottInitSchedParams(p2, p2_params);

    printf("Antes da transferência: P1 (%d tickets), P2 (%d tickets)\n",
           p1_params->num_tickets, p2_params->num_tickets);
    
    int transferred = lottTransferTickets(p1, p2, 2000);
    printf("Transferidos %d tickets de P1 para P2\n", transferred);

    printf("Depois da transferência: P1 (%d tickets), P2 (%d tickets)\n",
           p1_params->num_tickets, p2_params->num_tickets);
    
    return 0;
}
