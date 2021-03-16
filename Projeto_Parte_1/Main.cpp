/****************

LAED1 - Projeto Parte 1

Alunos(as):Vitor Brandão Raposo e Gabriel Bernalle

Data:19/03/21

****************/

#include <stdio.h>

void procurarPadrao(int* elementosLista, int tamanho)
{
    int padrao = 0;
    int resultado;

    for (int i = 0; i < tamanho; i++)
    {
        //Um case para cada etapa do padrão
        switch (padrao)
        {
            //Procura o primeiro item do padrao: 1
            case 0:
                switch (elementosLista[i])
                {
                case 1:
                    padrao++;
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
                    padrao++;
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
                    padrao++;
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
                    padrao++;
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
                    padrao++;
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
    
    switch (resultado)
    {
    case 1:
        printf("Resultado: Padrao encontrado.\n");
        break;
    
    default:
        printf("Resultado: Padrao nao encontrado.\n");
        break;
    }
}


//Estamos buscando a sequência 1 3 2 3 1 em um arquivo texto
int main () 
{
    FILE *arquivo;
    char nomeArquivo[100];
    int qtdItens;
    int elementosLista[qtdItens];

	printf("Digite o nome do arquivo: ");
	scanf("%s", nomeArquivo);
	arquivo = fopen(nomeArquivo, "r");

    //Escaneia a quantidade de itens
	fscanf(arquivo, "%d", &qtdItens);

    //Escaneia cada elemento e insere no vetor
	for (int i = 0; i < qtdItens; i++)
    {
        fscanf(arquivo, "%d", &elementosLista[i]);
    }
    
    procurarPadrao(elementosLista, qtdItens);
}
