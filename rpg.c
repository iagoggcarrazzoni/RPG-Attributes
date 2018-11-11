/***************************************************************************
 *   rpg.c                                    Version 20180915.214818      *
 *                                                                         *
 *   Distribution of skill points.                                         *
 *   Copyright (C) 2018         by Iago Gade Gusmao Carrazzoni             *
 ***************************************************************************
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; version 2 of the License.               *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************
 *   To contact the author, please write to:                               *
 *   Iago Gade Gusmao Carrazzoni                                           *
 *   Email: iagocarrazzoni@gmail.com                                       *
 *   Phone: +55 (81) 99479-0584                                            *
 ***************************************************************************/

/* includes */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/* limits */
#define H 6 /* numero de habilidades */
#define M 20 /* maximo */
#define C 12 /* numero de classes */
#define MOEDA 27 /* numero inicial de moedas */

/* PROTOTIPOS */
/*--------------------*/
void clear(int habval[H]); /* prototipo da funcao que limpa a tabela */
void tabela(const char *phab[H], int habval[H], int mod[H], int moeda); /* prototipo da funcao que imprime a tabela */
int coin(int n1, int n2, int habval[H], int moeda); /* prototipo da funcao que converte pontos em moedas */
int habilidades(int n1, int n2, int habval[H], int moeda); /* prototipo da funcao que seleciona as habilidades */
void sugclass(const char *pclasse[C], int habval[H]); /* prototipo da funcao que sugereas classes de acordo com os pontos de habilidade */
int retcoin(int n1, int moeda, int habval[H]); /* prototipo da funcao para se forem trocados os pontos de uma habilidades, as moedas se organizam */

/* MAIN */
/*--------------------*/
int main(void)
{
    const char *pclasse[C]={"barbaro", "bardo", "bruxo", "clerigo", "druida", "feiticeiro", "guerreiro", "ladino", "mago", "monge", "paladino", "patrulheiro"}; /* string para as classes */
    const char *phab[H]={"forca", "destreza", "constituicao", "inteligencia", "sabedoria", "carisma"}; /* string para as habilidades */
    int habval[H]; /* valores iniciais das habilidades */
    int mod[H]={0}; /* modificador */
    int moeda; /* variavel para as moedas */
    int i, pt[8]={8,9,10,11,12,13,14,15}, md[8]={0,1,2,3,4,5,7,9}; /* variaveis para imprimir tabela de pontos */
    int rep1=1; /* variavel do laco de repeticao */
    int n1=0, n2=0; /* variaveis de entrada */

    printf("DISTRIBUICAO DE PONTOS DE HABILIDADE\n");
    printf("|PONTOS|MOEDAS|\n"); /* para imprimir a tabela de pontos */
    for(i=0; i<8; i++)
        printf("|%-6d|%-6d|\n", pt[i], md[i]);

    do /* laco para refazer a tabela */
    {
        moeda=27; /*valor inicial da tabela */
        clear(habval); /* limpa a tabela */

        do /* laco para preencher a tabela */
        {
            tabela(phab, habval, mod, moeda); /* imprime a tabela */
            moeda=habilidades(n1, n2, habval, moeda); /* faz a conversao de pontos e moedas */
            sugclass(pclasse, habval); /* imprime a sugestao das classes */
        }
        while(moeda!=M);

        printf("Deseja refazer a tabela? Digite 1 para sim e 0 para nao: ");
        scanf("%d", &rep1); /* alteracao da variavel do laco de refazer a tabela */
    }
    while(rep1==1);

    return EXIT_SUCCESS;
}

/* FUNCTIONS */
/*--------------------*/
void clear(int habval[H]) /* funcao para limpar a tabela */
{
    int i;

    for(i=0; i<H; i++)  /* valores iniciais das habilidades */
        habval[i]=8;

    return;
}

/*--------------------*/
void tabela(const char *phab[H], int habval[H], int mod[H], int moeda) /* funcao para imprimir a tabela */
{
    int i;

    for(i=0; i<H; i++)
    {
        mod[i]=(habval[i]-10)/2; /* calculo do modificador, mod=(valor-10)/2 */
        mod[i]=floor(mod[i]); /* o modificador, se der um decimal, eh arredondado para baixo */
    }

    printf("\n-------------------------\n");
    for(i=0; i<H; i++) /* laco para imprimir as 6 habilidades */
        printf("%d . %-13s=%2d (%+2d)\n", i+1, phab[i], habval[i], mod[i]);
    printf("moedas = %d\n", moeda);
    printf("-------------------------\n");

    return;
}

/*--------------------*/
int coin(int n1, int n2, int habval[H], int moeda) /* funcao que converte pontos em moedas e controla o numero de moedas */
{
    n1--;

    switch(n2) /* pontos desejados */
    {
        case 8:
            {
                moeda=retcoin(n1, moeda, habval); /* chamada da funcao para retornar as moedas caso uma mesma habilidade for alterada */
                habval[n1]=8; /* atribuicao dos pontos desejados no valor da habilidade */
                moeda=moeda; /* quantidade de moedas utilizadas */
                break;
            }
        case 9:
            {
                moeda=retcoin(n1, moeda, habval);
                habval[n1]=9;
                moeda-=1;
                break;
            }
        case 10:
            {
                moeda=retcoin(n1, moeda, habval);
                habval[n1]=10;
                moeda-=2;
                break;
            }
        case 11:
            {
                moeda=retcoin(n1, moeda, habval);
                habval[n1]=11;
                moeda-=3;
                break;
            }
        case 12:
            {
                moeda=retcoin(n1, moeda, habval);
                habval[n1]=12;
                moeda-=4;
                break;
            }
        case 13:
            {
                moeda=retcoin(n1, moeda, habval);
                habval[n1]=13;
                moeda-=5;
                break;
            }
        case 14:
            {
                moeda=retcoin(n1, moeda, habval);
                habval[n1]=14;
                moeda-=7;
                break;
            }
        case 15:
            {
                moeda=retcoin(n1, moeda, habval);
                habval[n1]=15;
                moeda-=9;
                break;
            }
        default:
            {
                printf("INVALIDO\n");
            }
    }
    return moeda;
}

/*--------------------*/
int habilidades(int n1, int n2, int habval[H], int moeda) /* funcao que possui as entradas e segue o processo de escolha das habilidades */
{
    printf("Habilidade: ");
    scanf("%d", &n1); /* linha */

    if(n1==7)
    {
        moeda=M;
        return moeda;
    }
    else
    {
        printf("Pontos: ");
        scanf("%d", &n2); /* numero de pontos */

        switch(n1) /* escolha da habilidade */
        {
            case 1: /* forca */
                {
                    moeda=coin(n1, n2, habval, moeda); /* chama a funcao moeda para fazer a conversao */
                    break;
                }
            case 2: /* destreza */
                {
                    moeda=coin(n1, n2, habval, moeda);
                    break;
                }
            case 3: /* constituicao */
                {
                    moeda=coin(n1, n2, habval, moeda);
                    break;
                }
            case 4: /* inteligencia */
                {
                    moeda=coin(n1, n2, habval, moeda);
                    break;
                }
            case 5: /* sabedoria */
                {
                    moeda=coin(n1, n2, habval, moeda);
                    break;
                }
            case 6: /* carisma */
                {
                    moeda=coin(n1, n2, habval, moeda);
                    break;
                }
            default:
                {
                    printf("INVALIDO\n");
                }
        }
        if(moeda<0) /* se o numero de moedas der menor que zero, repete o processo */
        {
            printf("INVALIDO\n\n");
            moeda=habilidades(n1, n2, habval, moeda);
        }
    }
    return moeda;
}

/*--------------------*/
void sugclass(const char *pclasse[C], int habval[H]) /* funcao que compara os valores das habilidades e sugere as classes */
{
    /*
     * HABILIDADES
     * habval[0]=forca, habval[1]=destreza, habval[2]=constituicao, habval[3]=inteligencia, habval[4]=sabedoria, habval[5]=carisma.
     *
     * CLASSES
     * pclasse[0]=barbaro, pclasse[1]=bardo, pclasse[2]=bruxo, pcalsse[3]=clerigo, pclasse[4]=druida, pclasse[5]=feiticeiro,
     * pclasse[6]=guerreiro, pclasse[7]=ladino, pclasse[8]=mago, pclasse[9]=monge, pclasse[10]=paladino, pclasse[11]=patrulheiro.
     *
     */

    if((habval[0]>habval[1]) && (habval[0]>habval[2]) && (habval[0]>habval[3]) && (habval[0]>habval[4]) && (habval[0]>habval[5]))
        printf("Sugestao: %s, %s\n\n", pclasse[0], pclasse[6]); /* maior forca, barbaro e guerreiro */

    if((habval[0]>habval[5]) && (habval[5]>habval[1]) && (habval[5]>habval[2]) && (habval[5]>habval[3]) && (habval[5]>habval[4]))
        printf("Sugestao: %s\n\n", pclasse[10]); /* maior forca e segundo carisma, paladino */

    if((habval[1]>habval[0]) && (habval[1]>habval[2]) && (habval[1]>habval[3]) && (habval[1]>habval[4]) && (habval[1]>habval[5]))
        printf("Sugestao: %s\n\n", pclasse[7]); /* maior destreza, ladino */

    if((habval[1]>habval[4]) && (habval[4]>habval[0]) && (habval[4]>habval[2]) && (habval[4]>habval[3]) && (habval[4]>habval[5]))
        printf("Sugestao: %s, %s\n\n", pclasse[9], pclasse[11]); /* maior destreza e segundo sabedoria, monge e patrulheiro */

    if((habval[3]>habval[0]) && (habval[3]>habval[1]) && (habval[3]>habval[2]) && (habval[3]>habval[4]) && (habval[3]>habval[5]))
        printf("Sugestao: %s\n\n", pclasse[8]); /* maior inteligencia, mago */

    if((habval[4]>habval[0]) && (habval[4]>habval[1]) && (habval[4]>habval[2]) && (habval[4]>habval[3]) && (habval[4]>habval[5]))
        printf("Sugestao: %s, %s\n\n", pclasse[3], pclasse[4]); /* maior sabedoria, clerigo e druida */

    if((habval[5]>habval[0]) && (habval[5]>habval[1]) && (habval[5]>habval[2]) && (habval[5]>habval[3]) && (habval[5]>habval[4]))
        printf("Sugestao: %s, %s, %s\n\n", pclasse[1], pclasse[2], pclasse[5]); /* maior carisma, bardo, bruxo, feiticeiro */

    if((habval[2]>habval[0]) && (habval[2]>habval[1]) && (habval[2]>habval[3]) && (habval[2]>habval[4]) && (habval[2]>habval[5]))
        printf("Sugestao: %s, %s, %s\n", pclasse[0], pclasse[6], pclasse[10]); /* maior constituicao, barbaro, guerreiro, paladino*/

    return;
}

/*--------------------*/
int retcoin(int n1, int moeda, int habval[H]) /* funcao para caso forem trocados os pontos de uma habilidades, as moedas se organizam */
{
    if(habval[n1]==9) /* se a habilidade ja tiver sido utilizada, as moedas que foram usadas antes sao somadas para retornar ao valor anterior */
        moeda+=1;
    if(habval[n1]==10)
        moeda+=2;
    if(habval[n1]==11)
        moeda+=3;
    if(habval[n1]==12)
        moeda+=4;
    if(habval[n1]==13)
        moeda+=5;
    if(habval[n1]==14)
        moeda+=7;
    if(habval[n1]==15)
        moeda+=9;

    return moeda;
}
