typedef struct _pecaDomino{
	int numberRight;
	int numberLeft;
	struct _pecaDomino *right;
	struct _pecaDomino *left;
}TppecaDomino;

TppecaDomino *inicializa(){
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
	int inicio = 0, final = 0, coringa = 0;
	if(aux_mesa->numberLeft == 0 && aux_mesa->numberRight == 0){
		coringa++;
	}else if(jogada->numberLeft == 0 && jogada->numberRight == 0){
		return 2; //Valida a jogada em ambos os lados pois 0:0 = Coringa.
	}
	if(aux->numberLeft == aux_mesa->numberLeft){
		inicio++;	
	} 
	else if(aux->numberRight == aux_mesa->numberLeft){
		inicio++;
	}
	while(aux_mesa->right != NULL){ //Encontra o último elemento da lista.
		aux_mesa = aux_mesa->right;
	}
	if(aux_mesa->numberLeft == 0 && aux_mesa->numberRight == 0){
		coringa++;
	}
	if(aux->numberLeft == aux_mesa->numberRight){
		final++;
	}
	else if(aux->numberRight == aux_mesa->numberRight){
		final++;
	}
	if(inicio > 0 && final > 0){
		return 2;
	}else if((inicio > 0 || final > 0) && coringa > 0){
		return 2;
	}else if(coringa > 0){
		return 1;
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
	if(lado == 1){
		if(aux->numberLeft == 0 && aux->numberRight == 0){
			aux = insere_inicio(aux, jogada->numberLeft, jogada->numberRight);
			return aux;
		}
		if(aux->left == NULL && (jogada->numberLeft == 0 && jogada->numberRight == 0)){
			aux = insere_inicio(aux, jogada->numberLeft, jogada->numberRight);
			return aux;
		}else if(aux->left == NULL && jogada->numberRight == aux->numberLeft){
			aux = insere_inicio(aux, jogada->numberLeft, jogada->numberRight);
			return aux;
		}else if(aux->left == NULL && jogada->numberLeft == aux->numberLeft){
			aux = insere_inicio(aux, jogada->numberRight, jogada->numberLeft);
			return aux;
		}
	}else if(lado == 2){
		while(aux->right != NULL){
			aux = aux->right;
		}
		if(aux->numberLeft == 0 && aux->numberRight == 0){
			aux = insere_fim(aux, jogada->numberLeft, jogada->numberRight);
			return aux;
		}
		if(jogada->numberLeft == 0 && jogada->numberRight == 0){
			aux = insere_fim(aux, jogada->numberLeft, jogada->numberRight);
			return mesa;
		}else if(jogada->numberLeft == aux->numberRight){
			aux = insere_fim(aux, jogada->numberLeft, jogada->numberRight);
			return mesa;
		}else{
			aux = insere_fim(aux, jogada->numberRight, jogada->numberLeft);
		}		
		return mesa;
	}else if(lado == 0){		
		if(aux->numberLeft == 0 && aux->numberRight == 0){
			aux = insere_inicio(aux, jogada->numberLeft, jogada->numberRight);
			return aux;
		}
		if(aux->left == NULL && (jogada->numberLeft == 0 && jogada->numberRight == 0)){
			aux = insere_inicio(aux, jogada->numberLeft, jogada->numberRight);
			return aux;
		}else if(aux->left == NULL && jogada->numberRight == aux->numberLeft){
			aux = insere_inicio(aux, jogada->numberLeft, jogada->numberRight);
			return aux;
		}else if(aux->left == NULL && jogada->numberLeft == aux->numberLeft){
			aux = insere_inicio(aux, jogada->numberRight, jogada->numberLeft);
			return aux;
		}
		while(aux->right != NULL){
			aux = aux->right;
		}
		if(aux->numberLeft == 0 && aux->numberRight == 0){
			aux = insere_fim(aux, jogada->numberLeft, jogada->numberRight);
			return aux;
		}
		if(jogada->numberLeft == 0 && jogada->numberRight == 0){
			aux = insere_fim(aux, jogada->numberLeft, jogada->numberRight);
			return mesa;
		}else if(jogada->numberLeft == aux->numberRight){
			aux = insere_fim(aux, jogada->numberLeft, jogada->numberRight);
			return mesa;
		}else{
			aux = insere_fim(aux, jogada->numberRight, jogada->numberLeft);
		}		
		return mesa;
	}
	return mesa;
}

TppecaDomino *remove_peca_jogada(TppecaDomino *mao, TppecaDomino *jogada){
	TppecaDomino *ant, *prox, *aux = mao;
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

/*TppecaDomino *bot_joga(TppecaDomino *mesa){
	TppecaDomino *aux_mesa = mesa;
	if(valida_jogada(mesa, jogada) == 0)	
}*/

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