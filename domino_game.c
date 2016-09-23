#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "domino_funcoes.h"


int main(){
	system("reset");
	TppecaDomino *monte, *jogador = NULL, *aux, *bot = NULL, *mesa = NULL, *pecajogada;
	int i, cont = 0, cont2 = 0, escolha_lado, numero_pecas, jogo_ativo = 1;
	monte = cria_pecas();
	imprime(monte);
	printf("\n");
	srand(clock());
	
	while(cont < 6){ //Distribuição de 6 peças para o jogador.
		i = abs(rand()%(28-cont));
		aux = copiar(monte, i);
		jogador = insere_fim(jogador, aux->numberLeft, aux->numberRight);
		cont++;
		monte = excluir(monte, aux->numberLeft, aux->numberRight);
	}
	while(cont2 < 6){ //Distribuição de 6 peças para o bot.
		i = abs(rand()%(22-cont));
		aux = copiar(monte, i);
		bot = insere_fim(bot, aux->numberLeft, aux->numberRight);
		cont2++;
		monte = excluir(monte, aux->numberLeft, aux->numberRight);
	}

	i = abs(rand()%16); //Insere uma peça aleatória na mesa para o início do jogo.
	aux = copiar(monte, i);
	mesa = insere_fim(mesa, aux->numberLeft, aux->numberRight);
	monte = excluir(monte, aux->numberLeft, aux->numberRight);
	
	imprime(monte);
	printf("\n");
	printf("\tJOGADOR:\n");
	imprime(jogador);
	printf("\tBOT:\n");
	imprime(bot);
	printf("\tMESA:\n");
	imprime(mesa);

	while(jogo_ativo == 1){

		//Interatividade do jogador
		menu:
		printf("\nInforme o índice da peça que deseja jogar ou 0 para pescar: ");
		int pecaescolhida;
		numero_pecas = contar_elementos(jogador);
		while(scanf("%d", &pecaescolhida) != 1);					
		if(pecaescolhida >= 1 && pecaescolhida <= numero_pecas){
			pecajogada = jogador;
			for(i = 1; i<pecaescolhida; i++){ pecajogada = pecajogada->right; }
			pecaescolhida = valida_jogada(mesa, pecajogada);
			if(pecaescolhida == 1){
				mesa = insere_mesa(mesa, pecajogada, 0);
				jogador = remove_peca_jogada(jogador, pecajogada);
				system("clear");
				printf("\n\tMESA:\n");
				imprime(mesa);
				printf("\n\tMÃO DO JOGADOR:\n");
				imprime(jogador);
			}else if(pecaescolhida == 2){
				menu_lado:
				printf("Em qual lado deseja inserir?\n(1 = Esquerdo / 2 = Direito)\n");
				scanf("%d", &escolha_lado);
				if(escolha_lado == 1){
					mesa = insere_mesa(mesa, pecajogada, 1);
					jogador = remove_peca_jogada(jogador, pecajogada);
					system("clear");
					printf("\n\tMESA:\n");
					imprime(mesa);
					printf("\n\tMÃO DO JOGADOR:\n");
					imprime(jogador);
				}else if(escolha_lado == 2){
					mesa = insere_mesa(mesa, pecajogada, 2);
					jogador = remove_peca_jogada(jogador, pecajogada);
					system("clear");
					printf("\n\tMESA:\n");
					imprime(mesa);
					printf("\n\tMÃO DO JOGADOR:\n");
					imprime(jogador);
				}else{
					printf("Erro. Escolha 1 ou 2.\n");
					goto menu_lado;
				}
			}
		}else if(pecaescolhida == 0 && contar_elementos(monte)>0){
			int pesca_escolha = 0, random, tam;
			do{
				system("clear");
				tam = contar_elementos(monte);
				random = abs(rand()%(tam));
				aux = copiar(monte, random);
				jogador = insere_fim(jogador, aux->numberLeft, aux->numberRight);
				monte = excluir(monte, aux->numberLeft, aux->numberRight);
				printf("\n\tMONTE:\n");
				imprime(monte);
				printf("\n\tMESA:\n");
				imprime(mesa);
				printf("\n\tMÃO DO JOGADOR:\n");
				imprime(jogador);
				if(monte){
					printf("Continuar pescando?\n Sim = 1 / Não = 2\n");
					scanf("%d", &pesca_escolha);
					if(pesca_escolha != 1 && pesca_escolha != 2){
						printf("OPÇÃO INVÁLIDA\n");
					}
				}else{
					free(monte);
					printf("Monte vazio!\n");
					goto menu;
				}

			}while(pesca_escolha != 2);
		} else {
			printf("\nErro. Insira um índice entre 1 e %d\n", numero_pecas);
			goto menu;
		}
	}
	return 0;
}
