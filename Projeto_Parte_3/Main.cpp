/****************
LAED1 - Projeto Parte 3
Alunos(as): Vitor Brandão Raposo e Gabriel Bernalle
Data: 08/04/21
****************/
#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>
#define qtdLinhas 10

/* ========================================================================= */

typedef int TipoChave;

typedef struct {
  int Chave;
  const char* Resultado;
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
const char* procurarPadrao(int* elementosLista, int qtdItens)
{
    int padrao = 0, resultado = 0;

    for (int i = 0; i < qtdItens; i++)
    {
        //Encontra uma pista
        switch (padrao)
        {
            //Procura o primeiro item do padrao: 1
            case 0:
                switch (elementosLista[i])
                {
                    case 1:
                        padrao = 1;
                        break;

                    default:
                        padrao = 0;
                        break;
                }
                break;

            //Procura o segundo item do padrao: 3
            case 1:
                switch (elementosLista[i])
                {
                    case 3:
                        padrao = 2;
                        break;

                    case 1:
                        padrao = 1;
                        break;

                    default:
                        padrao = 0;
                        break;
                }
                break;

            //Procura o terceiro item do padrao: 2
            case 2:
                switch (elementosLista[i])
                {
                    case 2:
                        padrao = 3;
                        break;

                    case 1:
                        padrao = 1;
                        break;

                    default:
                        padrao = 0;
                        break;
                }
                break;

            //Procura o quarto item do padrao: 3
            case 3:
                switch (elementosLista[i])
                {
                    case 3:
                        padrao = 4;
                        break;

                    case 1:
                        padrao = 1;
                        break;

                    default:
                        padrao = 0;
                        break;
                }
                break;

            //Procura o quinto item do padrao: 1
            case 4:
                switch (elementosLista[i])
                {
                    case 1:
                        padrao = 5;
                        resultado = 1;
                        break;

                    default:
                        padrao = 0;
                        break;
                }
                break; 

            default:
                padrao = 0;
                break;
        } 
    }

    if (resultado == 1)
    {
    	const char *padrao = "Pista normal";
		return padrao;
	}   

    padrao = 0;
    resultado = 0;

    //Encontra uma faixa de pedestres
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
    {
    	const char *padrao = "Faixa de pedestres";
		return padrao;
	}

    else
    {
        const char *padrao = "Padrao nao identificado";
		return padrao;
	}      
}


const char* mapeiaPadrao(int* elementosLista, int qtdItens)
{
	int listaFinal[qtdItens];

	for(int i = 0; i < qtdItens; i++){
		if(elementosLista[i] == 0) listaFinal[i] = 1; 
		if(elementosLista[i] == 128) listaFinal[i] = 2; 
		if(elementosLista[i] == 255) listaFinal[i] = 3; 
	}

	const char *padrao = procurarPadrao(listaFinal, qtdItens);
	return padrao;
}


const char* reduzPadrao(int* elementosLista, int qtdItens)
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

    const char *padrao = mapeiaPadrao(auxList, qtdItens);
	return padrao;
}


int main () 
{
    TipoLista lista;
    TipoItem item;
    float  tamanho = 0;
    FLVazia(&lista);
    FILE *arquivo;
    char nomeArquivo[100];
    int qtdlinhas;
	int qtdItens;
    int resultado = 0;

	printf("Digite o nome do arquivo: ");
	  scanf("%s", nomeArquivo);
	  arquivo = fopen(nomeArquivo, "r");

    if (arquivo == NULL){
        printf("\nERROR: IMPOSSIBLE TO OPEN THE FILE");
        exit(1);
    }

	const char* padrao;
    //Escaneia a quantidade de itens
	fscanf(arquivo, "%d", &qtdlinhas);

	for(int contador1 = 0; contador1 < qtdlinhas; contador1++)
    {
		// Escaneia a quantidade de Linhas
    	fscanf(arquivo, "%d", &qtdItens);
		int elementosLista[qtdItens];

    	//Escaneia cada elemento e insere no vetor
	  	for (int contador2 = 0; contador2 < qtdItens; contador2++)
        {
            fscanf(arquivo, "%d", &elementosLista[contador2]);
        } 

        /*Insere cada chave e resultado na lista */
	  	padrao = reduzPadrao(elementosLista,qtdItens);
        item.Chave = contador1;
        item.Resultado = padrao;
        Insere(item, &lista);
        tamanho++;
	}
	
    const char* faixa;
    faixa = "Faixa de pedestres";
    TipoApontador Aux;
    
    Aux = lista.Primeiro -> Prox;

    while (Aux != NULL) 
    { 
        if (Aux -> Item.Resultado == faixa)
        {
            resultado = 1;
            break;
        }
        
        Aux = Aux -> Prox;
    }

    if (resultado == 1)
    {
        printf("Resultado: Pista com faixa de pedestres\n");
    }
    else
    {
        printf("Resultado: Pista sem faixa de pedestres\n");
    }

    fclose(arquivo);
	
	return(0);
}
