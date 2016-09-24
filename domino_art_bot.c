/*
	Universidade Federal da Fronteira Sul
	Jogo de dominó
	Feito por: Artur Constanzi Sponchiado e Kadu Grando
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include "domino_func_declara.h"

int main(){
	TppecaDomino *monte, *jogador = NULL, *aux, *bot = NULL, *mesa = NULL, *pecajogada;
	Asciiart *desenho_jogador = inicializaasc(), *desenho_mesa = inicializaasc();
	int i, cont = 0, cont2 = 0, escolha_lado, numero_pecas, tam, random;
	monte = cria_pecas();
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

	TppecaDomino *aux_mao_bot = bot;
	system("reset");
	logo_uffs();
	getchar();
	//Interatividade do jogador
	int flag_jogo = 1;
	int flag_jogador = 1;
	while(flag_jogo){
		while(flag_jogador){
			imprime_info(mesa, jogador, bot, monte);
			printf("Mesa\n");
			desenho_mesa = chamardesenho(mesa);
			printar(desenho_mesa);
			printf("Mão do jogador\n");
			desenho_jogador = chamardesenho(jogador);
			printar(desenho_jogador);
			int pecaescolhida;
			numero_pecas = contar_elementos(jogador);
			if(numero_pecas == 0){
				quem_ganhou(jogador, bot, monte);
				flag_jogo = 0;
				break;
			}else if(contar_elementos(bot) == 0){
				quem_ganhou(jogador, bot, monte);
				flag_jogo = 0;
				break;
			}else if((testa_pecas(jogador, mesa) == 0 || testa_pecas(bot, mesa) == 0) && monte == NULL){
				quem_ganhou(jogador, bot, monte);
				flag_jogo = 0;
				break;
			}
			printf("Informe o índice da peça que deseja jogar ou 0 para pescar: ");
			while(pecaescolhida != 1){ // Só deixa o jogador inserir números inteiros.
				scanf("%d", &pecaescolhida);
				getchar();
			}				
			if(pecaescolhida >= 1 && pecaescolhida <= numero_pecas && numero_pecas != 0){
				pecajogada = jogador;
				for(i = 1; i<pecaescolhida; i++){ pecajogada = pecajogada->right; }
				pecaescolhida = valida_jogada(mesa, pecajogada);
				if(pecaescolhida == 1){
					mesa = insere_mesa(mesa, pecajogada, 0);
					jogador = remove_peca_jogada(jogador, pecajogada);
					imprime_info(mesa, jogador, bot, monte);
					printf("Mesa\n");
					desenho_mesa = chamardesenho(mesa);
					printar(desenho_mesa);
					printf("Mão do jogador\n");
					desenho_jogador = chamardesenho(jogador);
					printar(desenho_jogador);
					flag_jogador = 0;
				}else if(pecaescolhida == 2){
					int flag_lado = 1;
					while(flag_lado){
						printf("Em qual lado deseja inserir?\n1 = Esquerdo | 2 = Direito\n");
						scanf("%d", &escolha_lado);
						if(escolha_lado == 1){
							mesa = insere_mesa(mesa, pecajogada, 1);
							jogador = remove_peca_jogada(jogador, pecajogada);
							imprime_info(mesa, jogador, bot, monte);
							printf("Mesa\n");
							desenho_mesa = chamardesenho(mesa);
							printar(desenho_mesa);
							printf("Mão do jogador\n");
							desenho_jogador = chamardesenho(jogador);
							printar(desenho_jogador);
							flag_jogador = 0;
							break;
						}else if(escolha_lado == 2){
							mesa = insere_mesa(mesa, pecajogada, 2);
							jogador = remove_peca_jogada(jogador, pecajogada);
							imprime_info(mesa, jogador, bot, monte);
							printf("Mesa\n");
							desenho_mesa = chamardesenho(mesa);
							printar(desenho_mesa);
							printf("Mão do jogador\n");
							desenho_jogador = chamardesenho(jogador);
							printar(desenho_jogador);
							flag_jogador = 0;
							break;
						}else{
							printf("Erro. Escolha 1 ou 2.\n");						
						}									
					}
				}else{
					if(testa_pecas(jogador, mesa) == 1){
						printf("Peça inválida, por favor, insira outro índice ou pesque.\n\n");
						sleep(2);					
					}else if(testa_pecas(jogador, mesa) == 0 && monte != NULL){
						printf("Você não possui peças válidas. Digite 0 para pescar.\n");
						sleep(2);
					}else{
						printf("Você não tem mais peças válidas para esse turno e o monte está vazio.\nPassando a vez...\n");
						sleep(2);
						flag_jogador = 0;
					}			
				}
			}else if(pecaescolhida == 0){
				if(contar_elementos(monte) > 0){
					int pesca_escolha = 0;
					do{
						system("clear");
						while(pesca_escolha != 0 && pesca_escolha != 1){
							printf("Opção inválida.\n0 = Pescar | 1 = Cancelar\n");
							scanf("%d", &pesca_escolha);
						}
						if(pesca_escolha == 1){
							break;
						}
						tam = contar_elementos(monte);
						random = abs(rand()%(tam));
						aux = copiar(monte, random);
						jogador = insere_fim(jogador, aux->numberLeft, aux->numberRight);
						monte = excluir(monte, aux->numberLeft, aux->numberRight);
						imprime_info(mesa, jogador, bot, monte);
						printf("Mesa\n");
						desenho_mesa = chamardesenho(mesa);
						printar(desenho_mesa);
						printf("Mão do jogador\n");
						desenho_jogador = chamardesenho(jogador);
						printar(desenho_jogador);
						if(monte){
							printf("Continuar pescando?\nSim = 0 / Não = 1\n");
							scanf("%d", &pesca_escolha);
							if(pesca_escolha != 0 && pesca_escolha != 1){
								printf("Erro. Escolha 0 para pescar ou 1 para cancelar.\n");
							}
						}else{
							free(monte);
							break;					
						}		
					}while(pesca_escolha != 1);				
				} else {
					system("clear");
					printf("Erro. Não há mais peças para pescar.\n\n");
					sleep(1);
				}		
			} else {
				printf("\nErro. Insira um índice entre 1 e %d\n", numero_pecas);
				sleep(2);				
			}			
		} // fecha while flag_jogador
		//VEZ DO BOT JOGAR
		aux_mao_bot = bot;
		printf("\nBOT JOGANDO...\n\n");
		sleep(1);
		while(valida_jogada(mesa, aux_mao_bot) == 0 && aux_mao_bot->right != NULL){
			aux_mao_bot = aux_mao_bot->right;				
		}
		while(monte != NULL){
			if(aux_mao_bot->right == NULL && valida_jogada(mesa, aux_mao_bot) == 0){
				printf("BOT PESCANDO...\n");
				tam = contar_elementos(monte);
				random = abs(rand()%(tam));
				aux = copiar(monte, random);
				bot = insere_fim(bot, aux->numberLeft, aux->numberRight);
				monte = excluir(monte, aux->numberLeft, aux->numberRight);
				aux_mao_bot = bot;				
			}
			break;
		}
		if(valida_jogada(mesa, aux_mao_bot) != 0){				
			mesa = insere_mesa(mesa, aux_mao_bot, 0);
			bot = remove_peca_jogada(bot, aux_mao_bot);			
		}
		flag_jogador = 1;
	} // fecha while flag_jogo
	return 0;
}
