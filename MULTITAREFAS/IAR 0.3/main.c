#include <stdint.h>
#include <stdio.h>

#include "multitarefas.h"
#include <semaphore.h>
#define SIZE 10

semaforo_t cheio = 0;
semaforo_t vazio = N;
int buffer[SIZE];
int i=0;
int f=0;
/*
 * Prototipos das tarefas
 */
void tarefa_produtor(void);
void tarefa_consumidor(void);

/*
 * Configuracao dos tamanhos das pilhas
 */
#define TAM_PILHA_1		(TAM_MINIMO_PILHA + 24)
#define TAM_PILHA_2		(TAM_MINIMO_PILHA + 24)
#define TAM_PILHA_OCIOSA	(TAM_MINIMO_PILHA + 24)

/*
 * Declaracao das pilhas das tarefas
 */
uint32_t PILHA_TAREFA_1[TAM_PILHA_1];
uint32_t PILHA_TAREFA_2[TAM_PILHA_2];
uint32_t PILHA_TAREFA_OCIOSA[TAM_PILHA_OCIOSA];

/*
 * Funcao principal de entrada do sistema
 */
int main(void)
{

	/* Criacao das tarefas */
	/* Parametros: ponteiro, nome, ponteiro da pilha, tamanho da pilha, prioridade da tarefa */

	CriaTarefa(tarefa_produtor, "Tarefa Produtor", PILHA_TAREFA_1, TAM_PILHA_1, 1);

	CriaTarefa(tarefa_consumidor, "Tarefa Consumidor", PILHA_TAREFA_2, TAM_PILHA_2, 2);

	/* Cria tarefa ociosa do sistema */
	CriaTarefa(tarefa_ociosa,"Tarefa ociosa", PILHA_TAREFA_OCIOSA, TAM_PILHA_OCIOSA, 0);

	/* Configura marca de tempo */
	ConfiguraMarcaTempo();

	/* Inicia sistema multitarefas */
	IniciaMultitarefas();

	/* Nunca chega aqui */
	while (1)
	{
	}
}


void tarefa_produtor(void)
{
	while (true) {
        SemaforoAguarda(&vazio);
        f = (f+1)%N;
        buffer[f] = 1 + (rand() % 200); //enche o buffer com valores aleatorios
        SemaforoLibera(&cheio);
	}
}

void tarefa_consumidor(void)
{
    int read;
	while (true) {
        SemaforoAguarda(&cheio);
        i = (i+1)%N;
        read = buffer[i]; //le os dados do buffer
        SemaforoLibera(&vazio);
	}
}

