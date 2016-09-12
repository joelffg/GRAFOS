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

//PILHA
template <typename Tipo>
struct Pilha{											//Estrutura que representa uma pilha
    No<Tipo> *inicio;
    int tamanho;
};

template <typename Tipo>
Pilha<Tipo>* criar_pilha(){								//Função que cria uma nova pilha
	Pilha<Tipo> * nova  = new Pilha<Tipo>;
	nova->tamanho = 0;
	nova->inicio = NULL;
	return nova;
}

template <typename Tipo>
void empilhar(Pilha<Tipo> *pilha, Tipo no){				//Função que empilha um nó em uma pilha
	No<Tipo> *novo =  new No<Tipo>;
	novo->dado = no;
	novo->proximo = pilha->inicio;
	pilha->inicio = novo;
	pilha->tamanho++;
}

template <typename Tipo>
int desempilhar(Pilha<Tipo> *pilha, Tipo *retorno){		//Função que desempilha um nó de uma pilha
	if(pilha->inicio){
		*retorno = pilha->inicio->dado;
		No<Tipo> *aux = pilha->inicio;
		pilha->inicio = aux->proximo;
		delete aux;
		return 1;
	}
	return 0;
}

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

Grafo* construir_grafo_dirigido(){
	int tam;
	cin >> tam;
	vector<Vertice*> vertices;
	vector<Adj*> adjs;
	
	for(int i = 0; i < tam - 1; i++){
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
	}
	Grafo *grafo = new Grafo;
	grafo->adj = adjs;
	grafo->vertices = vertices;
	return grafo;
}

Grafo* construir_grafo_nao_dirigido(){
	int tam, peso;
	cin >> tam;
	cin >> peso;
	vector<Vertice*> vertices;
	vector<Adj*> adjs;
	
	for(int i = 0; i < tam - 1; i++){
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
	return grafo;
}

void bfs(Grafo *g, Vertice *s){
	for(vector<Vertice*>::iterator it = g->vertices.begin(); it != g->vertices.end(); it++){
		if(*it != s){
			Vertice *u = (*it);
			u->cor = 'b';
			u->distancia = 0;
			u->pai = NULL;
		}
	}
	
	s->cor = 'c';
	s->distancia = 0;
	s->pai = NULL;
	
	Fila<Vertice*> *fila = criar_fila<Vertice*>();
	enfileirar(fila, s); 
	
	Vertice *u;
	while(desenfileirar(fila, &u)){
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
				v->cor = 'c';
				v->distancia = u->distancia + adj->peso;
				v->pai = u;
				enfileirar(fila, v);
			}
		}
		u->cor = 'p';
	}
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

void dfs(Grafo *g){
	for(vector<Vertice*>::iterator it = g->vertices.begin(); it != g->vertices.end(); it++){
		Vertice *u = (*it);
		u->cor = 'b';
		u->pai = NULL;
	}
	int tempo = 0;
	for(vector<Vertice*>::iterator it = g->vertices.begin(); it != g->vertices.end(); it++){
		Vertice *u = (*it);
		if(u->cor == 'b')
			dfs_visit(g, u, tempo);
	}
}

int main(){
	int tam, peso;
	cin >> tam;
	cin >> peso;
	vector<Vertice*> vertices;
	vector<Adj*> adjs;
	int matriz[100][100] = {0};
	for(int i = 0 ; i < tam; i++){
		int coordenada1, coordenada2;
		cin >> coordenada1 >> coordenada2;
		matriz[coordenada1][coordenada2] = 1;
		for(int i = coordenada1 - 5; i < coordenada1; i++){
			for(int j = coordenada2 - 5; j < coordenada2; j++){
				if(i >= 0 && j >= 0)
					matriz[i][j] = 1;
			}
		}
	}
	
	for(int i = 0; i < 1000; i++){
		for(int j = 0; j < 1000; j++){
			if(matriz[i][j] == 1){
				int num1, num2;
				num1 = i;
				num2 = j;
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
		}
	}
	Grafo *grafo = new Grafo;
	grafo->adj = adjs;
	grafo->vertices = vertices;
	
//	dfs(grafo);
	
	return 0;
}
