/****************
LAED1 - Projeto Parte 2
Alunos(as): Vitor Brandão Raposo e Gabriel Bernalle
Data: 26/03/21
****************/
#include <stdlib.h>
#include <stdio.h>

//Estamos buscando a sequência “1 3 1 3 1 3 1 3 1 3 1 3 1" nessa ordem
void procurarPadrao(int* elementosLista, int qtdItens)
{
    int padrao = 0, resultado = 0;

    for (int i = 0; i < qtdItens; i++)
    {
        if (padrao == 13)
        {
            resultado = 1;
        }
        
        switch (padrao)
        {
        case 0:
            if (elementosLista[i] == 1)
            {
                padrao++;
            }
            else
            {
                padrao = 0;
            }
            break;
        
        default:
            if (elementosLista[i] == 1 && elementosLista[i - 1] == 3)
            {
                padrao++;
            }
            else if (elementosLista[i] == 3 && elementosLista[i - 1] == 1)
            {
                padrao++;
            }
            else
            {
                padrao = 0;
            }
            break;
        }
        
    }
    
    if (resultado == 1)
    {
        printf("Resultado: Padrao de faixa de pedestres encontrado.\n");
    } 
    else
    {
        printf("Resultado: Padrao de faixa de pedestres nao encontrado.\n");
    }
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
    FILE *arquivo;
    char nomeArquivo[100];
    int qtdItens;

	printf("Digite o nome do arquivo: ");
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
}