#ifndef FUNCOES_DOMINO
#define FUNCOES_DOMINO

typedef struct _pecaDomino{
	int numberRight;
	int numberLeft;
	struct _pecaDomino *right;
	struct _pecaDomino *left;
}TppecaDomino;

typedef struct _asciiart{
	int indice;
	char desenho[5][22];
	struct _asciiart *prox;
}Asciiart;

TppecaDomino *inicializa();
TppecaDomino *cria_pecas();
TppecaDomino *insere_inicio(TppecaDomino *l, int num1, int num2);
TppecaDomino *insere_fim(TppecaDomino *l, int m, int n);
TppecaDomino *excluir(TppecaDomino *l, int num1, int num2);
TppecaDomino *copiar(TppecaDomino *l, int num);
int valida_jogada(TppecaDomino *mesa, TppecaDomino *jogada);
TppecaDomino *insere_mesa(TppecaDomino *mesa, TppecaDomino *jogada, int lado);
TppecaDomino *remove_peca_jogada(TppecaDomino *mao, TppecaDomino *jogada);
Asciiart *inicializaasc();
void desenhar(Asciiart *peca, int valor, int x, int fazer);
Asciiart *alocardesenho(Asciiart *peca);
Asciiart *chamardesenho(TppecaDomino *l);
int contar_elementosasc(Asciiart *l);
void printar(Asciiart *peca);
int testa_pecas(TppecaDomino *l, TppecaDomino *mesa);
void imprime(TppecaDomino *l);
void imprime_info(TppecaDomino *mesa, TppecaDomino *mao_jogador, TppecaDomino *mao_bot, TppecaDomino *monte);
void quem_ganhou(TppecaDomino *jogador, TppecaDomino *bot, TppecaDomino *monte);
void logo_uffs();

#include "domino_funcoes.c"
#endif
