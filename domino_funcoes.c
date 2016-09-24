TppecaDomino *inicializa(){
	return NULL;
}

Asciiart *inicializaasc(){
	return NULL;
}

int contar_elementos(TppecaDomino *l){
	TppecaDomino *aux = l;
	int elementos = 0;
	while(aux != NULL){
		elementos++;
		aux = aux->right;		
	}
	return elementos;
}

int contar_elementosasc(Asciiart *l){
	Asciiart *aux = l;
	int elementos = 0;
	while(aux != NULL){
		elementos++;
		aux = aux->prox;		
	}
	return elementos;
}

TppecaDomino *cria_pecas(){
	int i, j;
	TppecaDomino *novo = (TppecaDomino *)malloc(sizeof(TppecaDomino));
	novo->left = NULL;
	TppecaDomino *aux = novo, *anterior = novo;
	novo->numberRight = 0;
	novo->numberLeft  = 0;

	for(i=1; i<=6; i++){
		for(j=0; j<=i; j++){
			aux = (TppecaDomino *)malloc(sizeof(TppecaDomino));
			aux->numberRight = j;
			aux->numberLeft = i;
			aux->left = anterior;
			anterior->right = aux;
			anterior = aux;
		}
	}

	aux->right = NULL;
	return novo;
}

TppecaDomino *insere_inicio(TppecaDomino *l, int num1, int num2){
	TppecaDomino *aux = l, *novo = (TppecaDomino *)malloc(sizeof(TppecaDomino));
	if(aux == NULL){
		novo->numberLeft = num1;
		novo->numberRight = num2;
		novo->left = NULL;
		novo->right = NULL;
		return novo;
	}
	while(aux != NULL){
		aux = aux->right;
	}
	novo->numberLeft = num1;
	novo->numberRight = num2;
	novo->right = l;
	novo->left = NULL;
	l->left = novo;
	return novo;
}

TppecaDomino *insere_fim(TppecaDomino *l, int m, int n){
	TppecaDomino *novo = (TppecaDomino *)malloc(sizeof(TppecaDomino));
	if(l == NULL){
		novo->right = NULL;
		novo->left = NULL;
		novo->numberLeft = m;
		novo->numberRight = n;
		return novo;
	}
	TppecaDomino *aux = l;
	novo->right = NULL;
	novo->numberLeft = m;
	novo->numberRight = n;
	while(aux->right!= NULL){
		aux = aux->right;
	}
	novo->left = aux;
	aux->right = novo;
	return l;
}

TppecaDomino *excluir(TppecaDomino *l, int num1, int num2){
	TppecaDomino *aux = l, *prox = NULL, *anterior;
	if(num1 == aux->numberLeft && num2 == aux->numberRight && aux->left == NULL){
		int tamanho = contar_elementos(aux);
		if(tamanho>1){
			aux = l->right;
			aux->left = NULL;
			free(l);
			return aux;
		}else{
			free(l);
			return NULL;
		}
	}
	while(num1 != aux->numberLeft || num2 != aux->numberRight){
		anterior = aux;
		aux = aux->right;
		prox = aux->right;		
	}
	if(aux->right == NULL){
		anterior = aux->left;
		anterior->right = NULL;
		free(aux);
		return l;
	}
	anterior->right = prox;
	prox->left = anterior;
	free(aux);
	return l;
}

TppecaDomino *copiar(TppecaDomino *l, int num){
	TppecaDomino *aux = l;
	int i;
	for(i = 0; i<num; i++){
		aux = aux->right;
	}
	return aux;
}

/*---------------------------------------------------	
	Return 0 = Jogada inválida
	Return 1 = Jogada válida em um dos lados.
	Return 2 = Jogada válida em ambos os lados.	
---------------------------------------------------*/
int valida_jogada(TppecaDomino *mesa, TppecaDomino *jogada){
  TppecaDomino *aux = jogada, *aux_mesa = mesa;
  int inicio = 0, final = 0;
	if(aux_mesa == NULL){
		return 0;
	}
	if(jogada->numberLeft == 0 && jogada->numberRight == 0){ // retorna 2, indicando que a peça pode ser posta nos dois lados da mesa
		return 2; //Valida a jogada em ambos os lados pois 0:0 = Coringa.
	}
	if(aux->numberLeft == aux_mesa->numberLeft) inicio++;
	else if(aux->numberRight == aux_mesa->numberLeft) inicio++;
	
	while(aux_mesa->right != NULL){ //Encontra o último elemento da lista.
		aux_mesa = aux_mesa->right;
	}
	if(aux->numberLeft == aux_mesa->numberRight) final++;
	else if(aux->numberRight == aux_mesa->numberRight) final++;
	if(inicio > 0 && final > 0){
		return 2;
	}else if(inicio > 0 || final > 0){
		return 1;
	} 
  return 0;
}

/*---------------------------------------------------
	lado == 0 quando só se pode inserir de um lado
	lado == 1 para inserir do lado esquerdo
	lado == 2 para inserir do lado direito
---------------------------------------------------*/

TppecaDomino *insere_mesa(TppecaDomino *mesa, TppecaDomino *jogada, int lado){
   TppecaDomino *aux = mesa;
	if(lado == 1 || lado == 0){ //LADO DIREITO DA MESA SE POSSÍVEL
		if(jogada->numberLeft == 0 && jogada->numberRight == 0){ // verifica se é o coringa que o jogador tem na mao
			aux = insere_inicio(aux, 0, 0); // se sim, insere no lado esquerdo da mesa a peça |0||0|
			return aux;
		}else if(jogada->numberRight == aux->numberLeft){
			aux = insere_inicio(aux, jogada->numberLeft, jogada->numberRight);
			return aux;
		}else if(jogada->numberLeft == aux->numberLeft){
			aux = insere_inicio(aux, jogada->numberRight, jogada->numberLeft);
			return aux;
		}
	}
	if(lado == 2 || lado == 0){ //LADO ESQUERDO DA MESA SE POSSÍVEL
		while(aux->right != NULL){ // vai até o final da mesa;
			aux = aux->right;
		}
		if(jogada->numberLeft == 0 && jogada->numberRight == 0){ // verifica se é o coringa que será jogado
			aux = insere_fim(aux, 0, 0); // insere o coringa no final da mesa
			return mesa;
		}else if(jogada->numberLeft == aux->numberRight){
			aux = insere_fim(aux, jogada->numberLeft, jogada->numberRight);
			return mesa;
		}else if(jogada->numberRight == aux->numberRight){
			aux = insere_fim(aux, jogada->numberRight, jogada->numberLeft);
		}	return mesa;
	}
	return mesa;
}

TppecaDomino *remove_peca_jogada(TppecaDomino *mao, TppecaDomino *jogada){
	TppecaDomino *ant, *prox, *aux = mao;
	if(aux->left == NULL && aux->right == NULL){
		free(mao);
		mao = inicializa();
		return mao;
	}
	while(aux != jogada){
		aux = aux->right;
	}
	if(aux->right == NULL){
		ant = aux->left;
		ant->right = NULL;
		free(aux);
		return mao;
	}
	if(aux->left == NULL){
		prox = aux->right;
		prox->left = NULL;
		mao = prox;
		free(aux);
		return mao;
	}
	ant = aux->left;
	prox = aux->right;
	ant->right = prox;
	prox->left = ant;
	free(aux);
	return mao;
}


int testa_pecas(TppecaDomino *l, TppecaDomino *mesa){ //Função que passa a vez caso o jogador não tenha peças compatíveis com a mesa.
	TppecaDomino *aux = l;
	while(aux != NULL){
		if(valida_jogada(mesa, aux) == 0){
			aux = aux->right;
		}else{
			return 1;
		}
	}
	return 0;
}

void imprime(TppecaDomino *l){
	TppecaDomino *p = l;
	int aux = 0;
	while(p != NULL){
		printf("|%d|%d| ", p->numberLeft, p->numberRight);
		aux++;
		if(aux == 6) printf("\n");
		if(aux == 6) aux = 0;
		p = p->right;
	}
	printf("\n");
}

void imprime_info(TppecaDomino *mesa, TppecaDomino *mao_jogador, TppecaDomino *mao_bot, TppecaDomino *monte){
	system("clear");
	printf("Peças no monte: %d", contar_elementos(monte));
	printf("\tPeças na sua mão: %d\tPeças na mão do bot: %d\n\n", contar_elementos(mao_jogador), contar_elementos(mao_bot));
	printf("\tMESA:\n");
	imprime(mesa);
	printf("\n\tMÃO DO JOGADOR:\n");
	imprime(mao_jogador);
	printf("\n");
}

void quem_ganhou(TppecaDomino *jogador, TppecaDomino *bot, TppecaDomino *monte){
	int pontos_jogador = 0, pontos_bot = 0;
	while(jogador != NULL){
		pontos_jogador = jogador->numberLeft + jogador->numberRight;
		if(jogador->right == NULL){
			break;
		}
		jogador = jogador->right;
	}
	while(bot != NULL){
		pontos_bot = bot->numberLeft + bot->numberRight;
		if(bot->right == NULL){
			break;
		}
		bot = bot->right;
	}
	printf("MÃO DO BOT:\n");
	imprime(bot);
	printf("PEÇAS QUE RESTARAM NO MONTE:\n");
	imprime(monte);
	printf("\n\n\n\n");
	if(pontos_jogador < pontos_bot || contar_elementos(jogador) == 0){
		printf("PARABÉNS! VOCÊ GANHOU!\n");
		printf("Seus pontos: %d\nPontos do bot: %d\n", pontos_jogador, pontos_bot);
	}else if(pontos_bot < pontos_jogador || contar_elementos(bot) == 0){
		printf("VOCÊ PERDEU!\n");
		printf("Seus pontos: %d\nPontos do bot: %d\n", pontos_jogador, pontos_bot);
	}else{
		printf("EMPATE!\n");
		printf("Seus pontos: %d\nPontos do bot: %d\n", pontos_jogador, pontos_bot);
	}
	printf("\nOBS: Jogador com menos pontos vence.\n\n");
}

void desenhar(Asciiart *peca, int valor, int x, int fazer){
	int i;
	if(fazer == 1){
		for(i=0;i<22;i++){
			peca->desenho[0][i] = '-';
			peca->desenho[4][i] = '-';
			if(i == 0 || i == 10 || i == 11 || i == 21){
				peca->desenho[1][i] = '|';
				peca->desenho[2][i] = '|';
				peca->desenho[3][i] = '|';
			}else{
				peca->desenho[1][i] = ' ';
				peca->desenho[2][i] = ' ';
				peca->desenho[3][i] = ' ';
			}
		}
	}
	switch(valor){
		case 1:
			peca->desenho[2][5+x] = 'o';
			break;
		case 2:
			peca->desenho[1][2+x] = 'o';
			peca->desenho[3][8+x] = 'o';
			break;
		case 3:
			peca->desenho[1][2+x] = 'o';
			peca->desenho[2][5+x] = 'o';
			peca->desenho[3][8+x] = 'o';
			break;
		case 4:
			peca->desenho[1][2+x] = 'o';
			peca->desenho[1][8+x] = 'o';
			peca->desenho[3][2+x] = 'o';
			peca->desenho[3][8+x] = 'o';
			break;
		case 5:
			peca->desenho[1][2+x] = 'o';
			peca->desenho[1][8+x] = 'o';
			peca->desenho[2][5+x] = 'o';
			peca->desenho[3][2+x] = 'o';
			peca->desenho[3][8+x] = 'o';
			break;
		case 6:
			peca->desenho[1][2+x] = 'o';
			peca->desenho[1][5+x] = 'o';
			peca->desenho[1][8+x] = 'o';
			peca->desenho[3][2+x] = 'o';
			peca->desenho[3][5+x] = 'o';
			peca->desenho[3][8+x] = 'o';
	}
}

Asciiart *alocardesenho(Asciiart *peca){
	Asciiart *novo = (Asciiart *)malloc(sizeof(Asciiart));
	if(peca == NULL){
		novo->prox = NULL;
		return novo;
	}
	Asciiart *aux_peca = peca;
	novo->prox = NULL;
	while(aux_peca->prox != NULL){
		aux_peca = aux_peca->prox;
	}
	aux_peca->prox = novo;
	return peca;
}

Asciiart *chamardesenho(TppecaDomino *l){
	TppecaDomino *aux_l= l;
	Asciiart *desenho = (Asciiart *)malloc(sizeof(Asciiart)), *aux_desenho;
	int x, fazer;
	while(aux_l!= NULL){
		desenho = alocardesenho(desenho);
		aux_l = aux_l->right;
	}
	aux_l = l, aux_desenho = desenho;
	while(aux_l!=NULL){
		x = 0, fazer = 1;
		desenhar(aux_desenho, aux_l->numberLeft, x, fazer);
		x+= 11,	fazer = 0;
		desenhar(aux_desenho, aux_l->numberRight, x, fazer);
		aux_l = aux_l->right;
		aux_desenho = aux_desenho->prox;
	}
	return desenho;
}

void printar(Asciiart *peca){
	Asciiart *aux_peca = peca;
	int i, j;
	for(i=0;i<5;i++){
		printf("\n");
		while(aux_peca != NULL){
			for(j=0;j<22;j++){
				printf("%c", aux_peca->desenho[i][j]);
			}
			aux_peca = aux_peca->prox;
		}
	aux_peca = peca;
	}
	printf("\n");
}

void logo_uffs(){                                                                                
	printf("UUUUUUUU     UUUUUUUUFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF   SSSSSSSSSSSSSSS\n");
	printf("U::::::U     U::::::UF::::::::::::::::::::FF::::::::::::::::::::F SS:::::::::::::::S\n");
	printf("U::::::U     U::::::UF::::::::::::::::::::FF::::::::::::::::::::FS:::::SSSSSS::::::S\n");
	printf("UU:::::U     U:::::UUFF::::::FFFFFFFFF::::FFF::::::FFFFFFFFF::::FS:::::S     SSSSSSS\n");
	printf("U:::::U     U:::::U   F:::::F       FFFFFF  F:::::F       FFFFFFS:::::S            \n");
	printf("U:::::D     D:::::U   F:::::F               F:::::F             S:::::S            \n");
	printf(" U:::::D     D:::::U   F::::::FFFFFFFFFF     F::::::FFFFFFFFFF    S::::SSSS         \n");
	printf(" U:::::D     D:::::U   F:::::::::::::::F     F:::::::::::::::F     SS::::::SSSSS    \n");
	printf(" U:::::D     D:::::U   F:::::::::::::::F     F:::::::::::::::F       SSS::::::::SS  \n");
	printf(" U:::::D     D:::::U   F::::::FFFFFFFFFF     F::::::FFFFFFFFFF          SSSSSS::::S \n");
	printf(" U:::::D     D:::::U   F:::::F               F:::::F                         S:::::S\n");
	printf(" U::::::U   U::::::U   F:::::F               F:::::F                         S:::::S\n");
	printf(" U:::::::UUU:::::::U FF:::::::FF           FF:::::::FF           SSSSSSS     S:::::S\n");
	printf("  UU:::::::::::::UU  F::::::::FF           F::::::::FF           S::::::SSSSSS:::::S\n");
	printf("    UU:::::::::UU    F::::::::FF           F::::::::FF           S:::::::::::::::SS \n");
	printf("      UUUUUUUUU      FFFFFFFFFFF           FFFFFFFFFFF            SSSSSSSSSSSSSSS   \n");

	printf(" \t       _____   ____  __  __ _____ _   _  ____ \n");
	printf(" \t      |  __   / __  |   /  |_   _|   | |/ __   \n");
	printf(" \t      | |  | | |  | |    / | | | |   | | |  | |\n");
	printf(" \t      | |  | | |  | | |  | | | | | . ` | |  | |\n");
	printf(" \t      | |__| | |__| | |  | |_| |_| |   | |__| |\n");
	printf(" \t      |_____/  ____/|_|  |_|_____|_|  _| ____/ \n");

printf("\n\n ▄▄▄      ██▀███ ▄▄▄█████▓█    ██ ██▀███     ▓█████     ██ ▄█▄▄▄     ▓█████▄ █    ██ \n");
printf("▒████▄   ▓██ ▒ ██▓  ██▒ ▓▒██  ▓██▓██ ▒ ██▒   ▓█   ▀     ██▄█▒████▄   ▒██▀ ██▌██  ▓██▒\n");
printf("▒██  ▀█▄ ▓██ ░▄█ ▒ ▓██░ ▒▓██  ▒██▓██ ░▄█ ▒   ▒███      ▓███▄▒██  ▀█▄ ░██   █▓██  ▒██░\n");
printf("░██▄▄▄▄██▒██▀▀█▄ ░ ▓██▓ ░▓▓█  ░██▒██▀▀█▄     ▒▓█  ▄    ▓██ █░██▄▄▄▄██░▓█▄   ▓▓█  ░██░\n");
printf(" ▓█   ▓██░██▓ ▒██▒ ▒██▒ ░▒▒█████▓░██▓ ▒██▒   ░▒████▒   ▒██▒ █▓█   ▓██░▒████▓▒▒█████▓ \n");
printf(" ▒▒   ▓▒█░ ▒▓ ░▒▓░ ▒ ░░  ░▒▓▒ ▒ ▒░ ▒▓ ░▒▓░   ░░ ▒░ ░   ▒ ▒▒ ▓▒▒   ▓▒█░▒▒▓  ▒░▒▓▒ ▒ ▒ \n");
printf("  ▒   ▒▒ ░ ░▒ ░ ▒░   ░   ░░▒░ ░ ░  ░▒ ░ ▒░    ░ ░  ░   ░ ░▒ ▒░▒   ▒▒ ░░ ▒  ▒░░▒░ ░ ░ \n");
printf("  ░   ▒    ░░   ░  ░      ░░░ ░ ░  ░░   ░       ░      ░ ░░ ░ ░   ▒   ░ ░  ░ ░░░ ░ ░ \n");
printf("  ░  ░  ░               ░       ░           ░  ░   ░  ░       ░  ░  ░      ░     \n");
printf("\n\n\tPRESSIONE QUALQUER TELCA PARA JOGAR...\n");
}                   
