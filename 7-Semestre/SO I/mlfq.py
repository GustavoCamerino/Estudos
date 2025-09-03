
#!/usr/bin/env python3

import sys
from optparse import OptionParser
import random

# Encontra a fila de maior prioridade não vazia
def encontrar_fila():
    q = fila_mais_alta
    while q > 0:
        if len(filas[q]) > 0:
            return q
        q -= 1
    if len(filas[0]) > 0:
        return 0
    return -1

def abaixar_prioridade(job_atual, fila_atual, usou_io):
    if fila_atual > 0:
        job[job_atual]['prioridadeAtual'] = fila_atual - 1
        if not usou_io:
            filas[fila_atual - 1].append(job_atual)
        job[job_atual]['ticksRestantes'] = quantuns[fila_atual - 1]
    else:
        if not usou_io:
            filas[fila_atual].append(job_atual)
        job[job_atual]['ticksRestantes'] = quantuns[fila_atual]

def abortar(msg):
    sys.stderr.write(msg + '\n')
    sys.exit(1)

# Argumentos de linha de comando
parser = OptionParser()
parser.add_option('-s', '--seed', default=0, help='semente para geração aleatória',
                  action='store', type='int', dest='seed')
parser.add_option('-n', '--numQueues', help='número de filas no MLFQ (se não usar -Q)', default=3,
                  action='store', type='int', dest='numQueues')
parser.add_option('-q', '--quantum', help='quantum padrão (se não usar -Q)', default=10,
                  action='store', type='int', dest='quantum')
parser.add_option('-Q', '--quantumList', help='lista de quantuns por nível de prioridade, ex: 10,20,30',
                  default='', action='store', type='string', dest='quantumList')
parser.add_option('-j', '--numJobs', default=3, help='número de jobs',
                  action='store', type='int', dest='numJobs')
parser.add_option('-m', '--maxlen', default=100, help='duração máxima dos jobs (se gerando aleatoriamente)',
                  action='store', type='int', dest='maxlen')
parser.add_option('-M', '--maxio', default=10, help='frequência máxima de I/O (se gerando aleatoriamente)',
                  action='store', type='int', dest='maxio')
parser.add_option('-B', '--boost', default=0, help='tempo entre boosts de prioridade',
                  action='store', type='int', dest='boost')
parser.add_option('-i', '--iotime', default=5, help='tempo fixo de duração de uma I/O',
                  action='store', type='int', dest='ioTime')
parser.add_option('-S', '--stay', default=False, help='resetar ticks e manter prioridade após I/O',
                  action='store_true', dest='stay')
parser.add_option('-I', '--iobump', default=False, help='coloca job no topo da fila após I/O',
                  action='store_true', dest='iobump')
parser.add_option('-l', '--jlist', default='', help='lista de jobs no formato x,y,z:x,y,z...',
                  action='store', type='string', dest='jlist')
parser.add_option('-c', help='computar a saída automaticamente', action='store_true', default=False, dest='solve')

(options, args) = parser.parse_args()
random.seed(options.seed)

# Configuração do MLFQ
num_filas = options.numQueues
quantuns = {}

if options.quantumList != '':
    lista_q = options.quantumList.split(',')
    num_filas = len(lista_q)
    qc = num_filas - 1
    for i in range(num_filas):
        quantuns[qc] = int(lista_q[i])
        qc -= 1
else:
    for i in range(num_filas):
        quantuns[i] = int(options.quantum)

fila_mais_alta = num_filas - 1
tempo_io = int(options.ioTime)

io_concluidos = {}
job = {}

# Criação dos jobs
job_id = 0
if options.jlist != '':
    todos = options.jlist.split(':')
    for j in todos:
        info = j.split(',')
        if len(info) != 3:
            abortar('Formato inválido de job. Esperado x,y,z:x,y,z...')
        start, run, freq = map(int, info)
        job[job_id] = {'prioridadeAtual': fila_mais_alta, 'ticksRestantes': quantuns[fila_mais_alta],
                       'inicio': start, 'duracao': run, 'tempoRestante': run, 'frequenciaIO': freq,
                       'fazendoIO': False, 'primeiraExecucao': -1}
        io_concluidos.setdefault(start, []).append((job_id, 'INÍCIO JOB'))
        job_id += 1
else:
    for j in range(options.numJobs):
        start, run, freq = 0, random.randint(1, options.maxlen), random.randint(1, options.maxio)
        job[job_id] = {'prioridadeAtual': fila_mais_alta, 'ticksRestantes': quantuns[fila_mais_alta],
                       'inicio': start, 'duracao': run, 'tempoRestante': run, 'frequenciaIO': freq,
                       'fazendoIO': False, 'primeiraExecucao': -1}
        io_concluidos.setdefault(start, []).append((job_id, 'INÍCIO JOB'))
        job_id += 1

total_jobs = len(job)

# Exibir informações iniciais
print(f'Total de jobs: {total_jobs}')
for i in range(len(quantuns) - 1, -1, -1):
    print(f'Quantum da fila {i}: {quantuns[i]}')
print(f'Boost a cada: {options.boost}')
print(f'Tempo fixo de I/O: {options.ioTime}')
print(f'Permanece na prioridade após I/O? {options.stay}')
print(f'Enfileira no topo após I/O? {options.iobump}')
print('\nJobs:')
for i in range(total_jobs):
    j = job[i]
    print(f'  Job {i}: início {j["inicio"]}, duração {j["duracao"]}, IO a cada {j["frequenciaIO"]}')

if not options.solve:
    print('\nExecute com -c para ver o rastreamento completo.')
    sys.exit(0)

# Simulação
filas = {i: [] for i in range(num_filas)}
tempo_atual = 0
finalizados = 0

print('\nRastreamento da execução:\n')

while finalizados < total_jobs:
    if options.boost > 0 and tempo_atual != 0 and tempo_atual % options.boost == 0:
        print(f'[ tempo {tempo_atual} ] BOOST (a cada {options.boost})')
        for q in range(num_filas - 1):
            for j in filas[q]:
                if not job[j]['fazendoIO']:
                    filas[fila_mais_alta].append(j)
            filas[q] = []
        for j in job:
            if job[j]['tempoRestante'] > 0:
                job[j]['prioridadeAtual'] = fila_mais_alta
                job[j]['ticksRestantes'] = quantuns[fila_mais_alta]

    if tempo_atual in io_concluidos:
        for (j, tipo) in io_concluidos[tempo_atual]:
            job[j]['fazendoIO'] = False
            fila = job[j]['prioridadeAtual']
            print(f'[ tempo {tempo_atual} ] {tipo} do JOB {j}')
            if options.iobump:
                filas[fila].insert(0, j)
            else:
                filas[fila].append(j)

    fila_atual = encontrar_fila()
    if fila_atual == -1:
        print(f'[ tempo {tempo_atual} ] OCIOSO')
        tempo_atual += 1
        continue

    job_atual = filas[fila_atual][0]
    j = job[job_atual]

    if j['prioridadeAtual'] != fila_atual:
        abortar(f'Erro de prioridade: esperado {fila_atual}, atual {j["prioridadeAtual"]}')

    j['tempoRestante'] -= 1
    j['ticksRestantes'] -= 1

    if j['primeiraExecucao'] == -1:
        j['primeiraExecucao'] = tempo_atual

    print(f'[ tempo {tempo_atual} ] Executando JOB {job_atual} na PRIORIDADE {fila_atual} [ TICKS {j["ticksRestantes"]} RESTANTE {j["tempoRestante"]} ]')

    tempo_atual += 1

    if j['tempoRestante'] == 0:
        print(f'[ tempo {tempo_atual} ] JOB {job_atual} FINALIZADO')
        finalizados += 1
        j['fim'] = tempo_atual
        filas[fila_atual].pop(0)
        continue

    fez_io = False
    if j['frequenciaIO'] > 0 and ((j['duracao'] - j['tempoRestante']) % j['frequenciaIO'] == 0):
        print(f'[ tempo {tempo_atual} ] INÍCIO DE E/S do JOB {job_atual}')
        fez_io = True
        filas[fila_atual].pop(0)
        j['fazendoIO'] = True
        if options.stay:
            j['ticksRestantes'] = quantuns[fila_atual]
        io_concluidos.setdefault(tempo_atual + tempo_io, []).append((job_atual, 'FIM DE E/S'))

    if j['ticksRestantes'] == 0 and not fez_io:
        filas[fila_atual].pop(0)
        abaixar_prioridade(job_atual, fila_atual, fez_io)

# Estatísticas
print('\nEstatísticas finais:')
soma_resposta = 0
soma_turnaround = 0
for i in range(total_jobs):
    j = job[i]
    resposta = j['primeiraExecucao'] - j['inicio']
    turnaround = j['fim'] - j['inicio']
    print(f'  Job {i}: resposta {resposta}, turnaround {turnaround}')
    soma_resposta += resposta
    soma_turnaround += turnaround

print(f'\nMédia: resposta {soma_resposta/total_jobs:.2f}, turnaround {soma_turnaround/total_jobs:.2f}\n')
