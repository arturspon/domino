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
	TppecaDomino *monte, *jogador = NULL, *aux, *bot = NULL, *mesa = NULL, *pecajogada, *aux_mao_bot;
	Asciiart *desenho_jogador = inicializaasc(), *desenho_mesa = inicializaasc();
	int i, cont = 0, cont2 = 0, escolha_lado, numero_pecas, tam, random, flag_jogador = 1, jogo_ativo = 1, flag_lado = 1;
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
	aux_mao_bot = bot;
	system("clear");
	logo_uffs();
	sleep(1);

	//Interatividade do jogador
	do{
		while(flag_jogador == 1){
			imprime_info(mesa, jogador, bot, monte);
			printf("Mesa\n");
			desenho_mesa = chamardesenho(mesa);
			printar(desenho_mesa);
			printf("Mão do jogador\n");
			desenho_jogador = chamardesenho(jogador);
			printarjogador(desenho_jogador);
			int pecaescolhida;
			numero_pecas = contar_elementos(jogador);
			printf("Informe o índice da peça que deseja jogar ou 0 para pescar: ");
			while(scanf("%d", &pecaescolhida) != 1){ // Só deixa o jogador inserir números inteiros.
				printf("Erro. Digite um índice válido.\n");
				getchar();
			}		
			if(pecaescolhida >= 1 && pecaescolhida <= numero_pecas && numero_pecas != 0){ // Confere se o índice passado pelo jogador é válido.
				pecajogada = jogador;
				for(i = 1; i<pecaescolhida; i++){ // Encontra a peça escolhida pelo jogador.
					pecajogada = pecajogada->right;
				}
				pecaescolhida = valida_jogada(mesa, pecajogada); // Chama a função para validar ou não a jogada.
				if(pecaescolhida == 1){ // Se a jogada for válida em apenas um dos lados da mesa.
					mesa = insere_mesa(mesa, pecajogada, 0);
					jogador = remove_peca_jogada(jogador, pecajogada);
					imprime_info(mesa, jogador, bot, monte);
					printf("Mesa\n");
					desenho_mesa = chamardesenho(mesa);
					printar(desenho_mesa);
					printf("Mão do jogador\n");
					desenho_jogador = chamardesenho(jogador);
					printarjogador(desenho_jogador);
					flag_jogador = 0;
				}else if(pecaescolhida == 2){ // Se a jogada for válida em ambos os lados da mesa.
					while(flag_lado){
						printf("Em qual lado deseja inserir?\n1 = Esquerdo | 2 = Direito\n");
						while(scanf("%d", &escolha_lado) != 1){
							printf("Erro. Digite 1 ou 2.\n");
							getchar();
						}
						if(escolha_lado == 1){
							mesa = insere_mesa(mesa, pecajogada, 1);
							jogador = remove_peca_jogada(jogador, pecajogada);
							imprime_info(mesa, jogador, bot, monte);
							printf("Mesa\n");
							desenho_mesa = chamardesenho(mesa);
							printar(desenho_mesa);
							printf("Mão do jogador\n");
							desenho_jogador = chamardesenho(jogador);
							printarjogador(desenho_jogador);
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
							printarjogador(desenho_jogador);
							flag_jogador = 0;
							break;
						}else{
							printf("Erro. Escolha 1 ou 2.\n");						
						}									
					}
				}else{
					if(testa_pecas(jogador, mesa) == 1){
						printf("Peça inválida, por favor, insira outro índice ou pesque.\n\n");
						sleep(1.5);					
					}else if(testa_pecas(jogador, mesa) == 0 && monte != NULL){
						printf("Você não possui peças válidas. Digite 0 para pescar.\n");
						sleep(1.5);
					}else{
						printf("Você não tem mais peças válidas para esse turno e o monte está vazio.\nPassando a vez...\n");
						sleep(1.5);
						flag_jogador = 0;
					}			
				}
			}else if(pecaescolhida == 0){ // Código para o jogador pescar.
				if(valida_jogada(mesa, jogador) == 0 && monte == NULL){
						jogo_ativo = 0;
					}
				if(contar_elementos(monte) > 0){ // Verifica se ainda há peças para pescar.
					int pesca_escolha = 0;
					do{
						system("clear");
						while(pesca_escolha != 0 && pesca_escolha != 1){
							printf("Opção inválida.\n0 = Pescar | 1 = Cancelar\n");
							while(scanf("%d", &pesca_escolha) != 1){
								printf("Erro. Digite 0 ou 1.\n");
								getchar();
							}
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
						printarjogador(desenho_jogador);
						if(monte){
							printf("Continuar pescando?\nSim = 0 / Não = 1\n");
							while(scanf("%d", &pesca_escolha) != 1){
								printf("Erro. Digite 0 ou 1.\n");
								getchar();
							}
							if(pesca_escolha != 0 && pesca_escolha != 1){
								printf("Erro. Escolha 0 para pescar ou 1 para cancelar.\n");
							}
						}else{
							free(monte);
							break;					
						}		
					}while(pesca_escolha != 1);				
				} else {
					printf("Erro. Não há mais peças para pescar.\n\n");
					sleep(1);
					if(valida_jogada(mesa, jogador) == 0 && monte == NULL){
						jogo_ativo = 0;
					}
				}		
			} else {
				printf("\nErro. Insira um índice entre 1 e %d\n", numero_pecas);
				sleep(1.5);				
			}			
		} // fecha while flag_jogador
		if(jogador == NULL){
			break;
		}
		//VEZ DO BOT JOGAR
		aux_mao_bot = bot;
		printf("\nBOT JOGANDO...\n\n");
		sleep(1.5);
		while(valida_jogada(mesa, aux_mao_bot) == 0 && aux_mao_bot->right != NULL){
			aux_mao_bot = aux_mao_bot->right;				
		}
		
		while(valida_jogada(mesa, aux_mao_bot) == 0 && monte != NULL){
			printf("BOT PESCANDO...\n");
			tam = contar_elementos(monte);
			random = abs(rand()%(tam));
			aux = copiar(monte, random);
			bot = insere_fim(bot, aux->numberLeft, aux->numberRight);
			monte = excluir(monte, aux->numberLeft, aux->numberRight);
			aux_mao_bot = aux_mao_bot->right;			
		}
		if(valida_jogada(mesa, aux_mao_bot) != 0){
			aux_mao_bot = bot;
		}
		
		while(valida_jogada(mesa, aux_mao_bot) == 0 && aux_mao_bot->right != NULL){
			aux_mao_bot = aux_mao_bot->right;				
		}
		if(valida_jogada(mesa, aux_mao_bot) != 0){				
			mesa = insere_mesa(mesa, aux_mao_bot, 0);
			bot = remove_peca_jogada(bot, aux_mao_bot);			
		}
		if(bot == NULL){
			break;
		}
		flag_jogador = 1;
	}while(jogo_ativo); // fecha while flag_jogo
	quem_ganhou(jogador, bot, monte);	
	return 0;
}


