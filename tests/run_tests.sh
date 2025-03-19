#!/bin/bash

chcp.com 65001 > nul

echo "Executando testes do Lottery Scheduling..."
echo "======================" > tests/results.log

# Compila o código
echo "Compilando código..."
mingw32-make clean && mingw32-make
if [ $? -ne 0 ]; then
    echo "Erro na compilação. Verifique os arquivos e tente novamente." | tee -a tests/results.log
    exit 1
fi

# Teste de distribuição
echo "[Test 1] Distribuicao de Escolha" | tee -a tests/results.log
(echo s; echo s; echo s; echo n) | ./main.exe > tests/test_distribution.log
cat tests/test_distribution.log >> tests/results.log
echo "----------------------" >> tests/results.log

# Teste de transferência de tickets
echo "[Test 2] Transferencia de Tickets" | tee -a tests/results.log
(echo s; echo s; echo s; echo n) | ./main.exe > tests/test_transfer.log
cat tests/test_transfer.log >> tests/results.log
echo "----------------------" >> tests/results.log

# Teste de bloqueio de processos
echo "[Test 3] Processos Bloqueados" | tee -a tests/results.log
(echo s; echo s; echo s; echo n) | ./main.exe > tests/test_blocking.log
cat tests/test_blocking.log >> tests/results.log
echo "======================" >> tests/results.log

echo "Testes concluídos. Os resultados estão disponíveis em tests/results.log"
