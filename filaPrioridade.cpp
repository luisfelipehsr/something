#include <iostream>
#include <vector>
#include <queue>
#include <cstdlib>

#include "filaPrioridade.h"

using namespace std;

// classe Noh
/* construtor padrao Noh */
Noh::Noh() {
	cena = 0;
	dia = 0;
	limite = 0;
	anteriores.clear();
	posteriores.clear();
}

/* construtor Noh */
Noh::Noh(int cena_noh, int dia_noh, int limite_noh,
		 vector<int> &dias_anteriores, vector<int> &dias_posteriores) {
		cena = cena_noh;
		dia = dia_noh;
		limite = limite_noh;
		anteriores = dias_anteriores;
		posteriores = dias_posteriores;
}


// classe Fila_Prioridade_Noh
/* transforma a fila em heap a partir da posicao index.
 * a chave de ordenacao eh o limitante inferior dos nohs */
void Fila_Prioridade_Noh::minHeapify(int index) {
	int esq, dir, menor, aux;

	/* estabelece filho esquerdo, direito e indice do noh menor */
	esq = 2*index + 1;
	dir = 2*index + 2;
	menor = index;

	/* testa qual filho eh menor, se algum for */
	if (esq < fim_fila &&
		gerados[fila[esq]].limite < gerados[fila[menor]].limite)
		menor = esq;
	if (dir < fim_fila &&
		gerados[fila[dir]].limite < gerados[fila[menor]].limite)
		menor = dir;

	/* se o menor noh eh um dos filhos, troca o pai com ele.
	 * Transforma a partir do filho num heap */
	if (menor != index) {

		//cout << "Pai " << gerados[index].limite << " Filho " <<
		//	gerados[menor].limite << endl;
	
		aux = fila[index];
		fila[index] = fila[menor];
		fila[menor] = aux;

		minHeapify(menor);
	}
} // fim minHeapify

/* Devolve pai do elemento no indice index da fila heap */
int Fila_Prioridade_Noh::pai(int index) {
	return (index - 1)/2;
}

/* Construtores */
Fila_Prioridade_Noh::Fila_Prioridade_Noh() {
	gerados.clear();
	fila.clear();
	capacidade = 0;
	fim_fila = 0;
	fim_gerados = 0;
}

Fila_Prioridade_Noh::Fila_Prioridade_Noh(int size) {
	gerados.resize(size);
	fila.resize(size);
	capacidade = size;
	fim_fila = 0;
	fim_gerados = 0;
}

/* Insere novo elemento a fila, ou seja, adiciona um novo noh gerado e adi-
 * ciona a fila o indice deste novo noh ativo */
void Fila_Prioridade_Noh::insere(Noh noh_novo) {
	int index, aux;

	/* Adiciona novo noh ao conjunto de noh gerados */
	index = fim_gerados;
	gerados[index] = noh_novo;

	/* Adiciona indice para o novo noh no fim da fila */
	index = fim_fila;
	fila[index] = fim_gerados;
	fim_gerados = fim_gerados + 1;
	fim_fila = fim_fila + 1;
		
	/* Conserta heap */
	//cout << "Inserindo " << gerados[index].limite << endl;
	while (index != 0 &&
		   gerados[fila[pai(index)]].limite > gerados[fila[index]].limite) {
		aux = fila[pai(index)];
		fila[pai(index)] = fila[index];
		fila[index] = aux;

		//cout << "Depois " << gerados[fila[pai(index)]].limite << " " << gerados[fila[index]].limite << endl;
		
		index = pai(index);
	}

	/* Expande estruturas se necessario dobrando seu tamanho */
	if (fim_gerados == capacidade) {
		gerados.resize(2*capacidade);
		fila.resize(2*capacidade);
		capacidade = 2*capacidade;
			
		//cout << "Vector tamanho " << capacidade/2 << " foi aumentado para CAPACIDADE " << fila.capacity() << endl;
	}
} // fim insere_elemento
		
			
Noh Fila_Prioridade_Noh::obtem_menor() {
	int menor_elemento;

	/* Uso indevido de obter elemento */
	if (fim_fila <= 0) {
		cout << "ERRO: tentativa de remover elemento de fila vazia" << endl;
		exit(0);
	}

	/* Caso especial de fila com um unico elemento */
	if (fim_fila == 1) {
		fim_fila = fim_fila - 1;
		return gerados[fila[0]];
	}

	/* salva primeiro elemento e poe o ultimo em seu lugar */
	menor_elemento = fila[0];
	fim_fila = fim_fila - 1;
	fila[0] = fila[fim_fila];

	/* conserta fila */
	minHeapify(0);

	return gerados[menor_elemento];
} // fim obtem_menor_elemento

int Fila_Prioridade_Noh::vazio() {
	if (fim_fila <= 0)
		return 1;
	else
		return 0;
}

void Fila_Prioridade_Noh::imprime() {
	int i, j, nivel;

	nivel = 1;
	j = 0;
	for (i = 0; i < fim_fila; i++) {
		j++;
		cout << gerados[fila[i]].cena << " ";
		if (j == nivel) {
			cout << endl;
			nivel = nivel * 2;
			j = 0;
		}
	}

		
	cout << endl;
}
// fim class Fila_Prioridade_Noh
