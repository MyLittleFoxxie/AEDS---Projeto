/****************
LAED1 - Projeto Parte 2
Alunos(as): Vitor Brandão Raposo e Gabriel Bernalle
Data: 26/03/21
****************/
#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>
#define MAX 10

/* ========================================================================= */

typedef int TipoChave;
typedef struct {
  int Chave;
  /* outros componentes */
} TipoItem;

typedef struct TipoCelula *TipoApontador;

typedef struct TipoCelula {
  TipoItem Item;
  TipoApontador Prox;
} TipoCelula;

typedef struct {
  TipoApontador Primeiro, Ultimo;
} TipoLista;

/* ========================================================================= */

void FLVazia(TipoLista *Lista)
{ Lista -> Primeiro = (TipoApontador) malloc(sizeof(TipoCelula));
  Lista -> Ultimo = Lista -> Primeiro;
  Lista -> Primeiro -> Prox = NULL;
}

int Vazia(TipoLista Lista)
{ return (Lista.Primeiro == Lista.Ultimo);
}

void Insere(TipoItem x, TipoLista *Lista)
{ Lista -> Ultimo -> Prox = (TipoApontador) malloc(sizeof(TipoCelula));
  Lista -> Ultimo = Lista -> Ultimo -> Prox;
  Lista -> Ultimo -> Item = x;
  Lista -> Ultimo -> Prox = NULL;
}

void Retira(TipoApontador p, TipoLista *Lista, TipoItem *Item)
{ /*  ---   Obs.: o item a ser retirado e  o seguinte ao apontado por  p --- */
  TipoApontador q;
  if (Vazia(*Lista) || p == NULL || p -> Prox == NULL) 
  { printf(" Erro   Lista vazia ou posi  c   a o n  a o existe\n");
    return;
  }
  q = p -> Prox;
  *Item = q -> Item;
  p -> Prox = q -> Prox;
  if (p -> Prox == NULL) Lista -> Ultimo = p;
  free(q);
}

void Imprime(TipoLista Lista)
{ TipoApontador Aux;
  Aux = Lista.Primeiro -> Prox;
  while (Aux != NULL) 
    { printf("%d\n", Aux -> Item.Chave);
      Aux = Aux -> Prox;
    }
}
/* ========================================================================== */

//Estamos buscando a sequência “1 3 1 3 1 3 1 3 1 3 1 3 1" nessa ordem
void procurarPadrao(int* elementosLista, int qtdItens)
{
    int padrao = 0, resultado = 0;

    for (int i = 0; i < qtdItens; i++)
    {
        if (padrao == 12)
            resultado = 1;
        
        switch (padrao)
        {
        case 0:
            if (elementosLista[i] == 1)
                padrao++;

            else
                padrao = 0;

            break;
        
        default:
            if (elementosLista[i] == 1 && elementosLista[i - 1] == 3)
                padrao++;

            else if (elementosLista[i] == 3 && elementosLista[i - 1] == 1)
                padrao++;

            else
                padrao = 0;

            break;
        }
    }
    
    if (resultado == 1)
        printf("Resultado: Padrao de faixa de pedestres encontrado.\n");

    else
        printf("Resultado: Padrao de faixa de pedestres nao encontrado.\n");       
}


void mapeiaPadrao(int* elementosLista, int qtdItens)
{
	int listaFinal[qtdItens];

	for(int i = 0; i < qtdItens; i++){
		if(elementosLista[i] == 0) listaFinal[i] = 1; 
		if(elementosLista[i] == 128) listaFinal[i] = 2; 
		if(elementosLista[i] == 255) listaFinal[i] = 3; 
	}

	procurarPadrao(listaFinal, qtdItens);
}


void reduzPadrao(int* elementosLista, int qtdItens)
{
	int *auxList;
	auxList = (int*) malloc(qtdItens * sizeof (int));
	auxList[0] = elementosLista[0];
	int aux = elementosLista[0];
	int j = 0;

	for(int i = 0; i < qtdItens; i++){
		if(elementosLista[i] != aux){
			j++;
			auxList[j] = elementosLista[i];
			aux = elementosLista[i];
		}
	}

    qtdItens = j + 1;

	mapeiaPadrao(auxList, qtdItens);
}


int main () 
{
	struct timeval t;

    FILE *arquivo;
    char nomeArquivo[100];
    int qtdItens;

/*	printf("Digite o nome do arquivo: ");
	scanf("%s", nomeArquivo);
	arquivo = fopen(nomeArquivo, "r");

    if (arquivo == NULL){
        printf("\nERROR: IMPOSSIBLE TO OPEN THE FILE");
        exit(1);
    }

    //Escaneia a quantidade de itens
	fscanf(arquivo, "%d", &qtdItens);

    int elementosLista[qtdItens];

    //Escaneia cada elemento e insere no vetor
	for (int i = 0; i < qtdItens; i++)
    {    
        fscanf(arquivo, "%d", &elementosLista[i]);
    }

	reduzPadrao(elementosLista,qtdItens);

    fclose(arquivo);
*/

	TipoLista lista;
  	TipoItem item;
  	int vetor[MAX];
	TipoApontador p;
  	int i, j, k, n;
  	float  tamanho=0;
  	gettimeofday(&t,NULL);
  	srand((unsigned int)t.tv_usec);
  	FLVazia(&lista);

  
  	/*Gera uma permutacao aleatoria de chaves entre 1 e MAX*/
  	for(i = 0; i < MAX; i++) vetor[i] = i + 1;
  	for(i = 0; i < MAX; i++){ 
		k =  (int) (10.0 * rand()/(RAND_MAX + 1.0));
      	j =  (int) (10.0 * rand()/(RAND_MAX + 1.0));
      	n = vetor[k];
      	vetor[k] = vetor[j];
      	vetor[j] = n;
    }

  	/*Insere cada chave na lista */
  	for (i = 0; i < MAX; i++)
    {
		item.Chave = vetor[i];
      	Insere(item, &lista);
      	tamanho++;
      	printf("Inseriu: %d \n", item.Chave);
    }
  	
	Imprime(lista);

  	/*Retira cada chave da lista */
  	for(i = 0; i < MAX; i++)
    { /*escolhe uma chave aleatoriamente */
    	k = (int) ((tamanho) * rand() / (RAND_MAX + 1.0));
      	p = lista.Primeiro;
      	/*retira chave apontada */
      	Retira(p, &lista, &item);
      	tamanho--;
      	printf("Retirou: %d\n", item.Chave);
    }
  	
	Imprime (lista);
  	
	return(0);
}