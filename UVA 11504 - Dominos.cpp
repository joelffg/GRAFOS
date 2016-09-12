#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <vector>

using namespace std;

template <typename Tipo>
struct No{												//Estrutura que representa um nó de uma fila ou de uma pilha
    Tipo dado;
    No *proximo;
};

//GRAFO
typedef struct vertice{
	int chave;
	char cor;
	vertice *pai;
	int distancia;
	int termino;
}Vertice;

typedef struct adj{
	Vertice *vertice;
	int peso;
	adj *proximo;
}Adj;

typedef struct grafo{
	vector<Vertice*> vertices;
	vector<Adj*> adj;
}Grafo;

//FILA
template <typename Tipo>
struct Fila{											//Estrutura que representa uma fila
    No<Tipo> *inicio;
    No<Tipo> *fim;
    int tamanho;
};

template <typename Tipo>
Fila<Tipo>* criar_fila(){								//Função que cria uma nova fila
	Fila<Tipo> *nova = new Fila<Tipo>;
	nova->tamanho = 0;
	nova->inicio = NULL;
	nova->fim = NULL;
	return nova;
}

template <typename Tipo>
void enfileirar(Fila<Tipo> *fila, Tipo num){			//Função que enfileira um nó em uma fila
	No<Tipo> *novo =  new No<Tipo>;
	novo->dado = num;
	novo->proximo = NULL;
	if(fila->fim == NULL)
		fila->inicio = novo;
	else
		fila->fim->proximo = novo;
	fila->fim = novo;
	fila->tamanho++;
}

template <typename Tipo>
int desenfileirar(Fila<Tipo> *fila, Tipo *num){			//Função que desenfileira um nó de uma fila
	if(fila->inicio){
		*num = fila->inicio->dado;
		No<Tipo> *aux = fila->inicio;
		fila->inicio = aux->proximo;
		delete aux;
		fila->tamanho--;
		if(fila->tamanho == 0)
			fila->fim = NULL;
		return 1;
	}
	return 0;
}

Vertice* vertice_no_grafo(int num, vector<Vertice*> adj){
	for(vector<Vertice*>::iterator it = adj.begin(); it != adj.end(); it++){
		if((*it)->chave == num)
			return *it;
	}
	return NULL;
}

Adj* adjacentes(int num, vector<Adj*> adj){
	for(vector<Adj*>::iterator it = adj.begin(); it != adj.end(); it++){
		if((*it)->vertice->chave == num)
			return *it;
	}
	return NULL;
}

void dfs_visit(Grafo *g, Vertice *u, int tempo){
	tempo = tempo + 1;
	u->distancia = tempo;
	u->cor = 'c';
	
	Adj *adj =  NULL;
	for(vector<Adj*>::iterator it = g->adj.begin(); it != g->adj.end(); it++){
		if((*it)->vertice == u){
			adj = *it;
			break;
		}
	}
	for (adj; adj != NULL && adj->proximo != NULL; adj = adj->proximo) {
		Vertice *v = adj->proximo->vertice;
		if(v->cor == 'b'){
			v->pai = u;
			dfs_visit(g, v, tempo);
		}
	}
	u->cor = 'p';
	tempo = tempo + 1;
	u->termino = tempo;
}

int dfs(Grafo *g){
	for(vector<Vertice*>::iterator it = g->vertices.begin(); it != g->vertices.end(); it++){
		Vertice *u = (*it);
		u->cor = 'b';
		u->pai = NULL;
	}
	int tempo = 0;
	int qtd = 0;
	for(vector<Vertice*>::iterator it = g->vertices.begin(); it != g->vertices.end(); it++){
		Vertice *u = (*it);
		if(u->cor == 'b'){
			dfs_visit(g, u, tempo);
			qtd++;
		}
	}
	return qtd;
}

int main(){
	int t, n, m;
	cin >> t;
	vector<Vertice*> vertices;
	vector<Adj*> adjs;
	
	for(int w = 0; w < t; w++){
		cin >> n >> m;
		for(int i = 0; i < m; i++){
			int num1, num2;
			cin >> num1 >> num2;
			Vertice *inicio = new Vertice;
			inicio->chave = num1;
			Vertice *fim = new Vertice;
			fim->chave = num2;
			
			Vertice *aux = vertice_no_grafo(num1, vertices);		
			if(aux == NULL)
				vertices.push_back(inicio);
			else
				inicio = aux;
			
			aux = vertice_no_grafo(num2, vertices);		
			if(aux == NULL)
				vertices.push_back(fim);
			else
				fim = aux;
			
			Adj *lista_adj = adjacentes(num1, adjs);
			
			if(lista_adj == NULL){
				Adj *a = new Adj;
				Adj *b = new Adj;
				b->vertice = fim;
				b->peso = 0;
				b->proximo = NULL;
				a->vertice = inicio;
				a->peso = 1;
				a->proximo = b;
				adjs.push_back(a);
			}
			else{
				Adj *aux = lista_adj->proximo;
				while(aux->proximo != NULL){
					aux = aux->proximo;
				}
				Adj *b = new Adj;
				b->vertice = fim;
				b->peso = 0;
				b->proximo = NULL;
				aux->peso = 1;
				aux->proximo = b;
			}
			
			lista_adj = adjacentes(num2, adjs);
			
			if(lista_adj == NULL){
				Adj *a = new Adj;
				Adj *b = new Adj;
				b->vertice = inicio;
				b->peso = 0;
				b->proximo = NULL;
				a->vertice = fim;
				a->peso = 1;
				a->proximo = b;
				adjs.push_back(a);
			}
			else{
				Adj *aux = lista_adj->proximo;
				while(aux->proximo != NULL){
					aux = aux->proximo;
				}
				Adj *b = new Adj;
				b->vertice = inicio;
				b->peso = 0;
				b->proximo = NULL;
				aux->peso = 1;
				aux->proximo = b;
			}
		}
		Grafo *grafo = new Grafo;
		grafo->adj = adjs;
		grafo->vertices = vertices;
		
		cout << dfs(grafo) << endl;
	}
	
	return 0;
}
