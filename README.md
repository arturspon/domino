# domino
Universidade Federal da Fronteira Sul
Curso de Ciência da Computação
Disciplina: Estrutura de Dados I
Professor: Jacson Luiz Matte
Trabalho NP1
Grupo: 2 pessoas
Data de entrega: 19/09/2016
Formato de entrega: apresentação em sala do item (a) da avaliação e arquivo
(s) entregues no Moodle do item (b) da avaliação
Objetivo: Implementar o algoritmo de um jogo de dominó duplo-seis, no qual
joga contra a máquina.
Forma de entrega: O programa deve ser implementado em linguagem C,
padrão ANSI. Todos devem submeter um arquivo nomeado .Caso alguém
implementar com bibliotecas próprias, então deve submeter um arquivo
compactado em formato .zip, contendo todas as bibliotecas necessárias, sob o
nome .
Estrutura: Para cada peça do dominó deve ser utilizado a estrutura abaixo:
typedef struct _pecaDomino{
int numberRight;
int numberLeft;
struct _pecaDomino *right;
struct _pecaDomino *left;
}TppecaDomino;
Desenvolvimento: O jogo do dominó deve conter 28 peças, com mostrado na
Figura 1. Desta são embaralhadas e distribuídas 6 peças para o jogador e 6 para
a máquina. O restante das peças fica como reserva para serem usadas no
decorrer do jogo. Estas peças devem ser armazenadas em listas duplamente
encadeadas. Deve conter pelo menos as listas de peças para o jogador,
máquina, reserva e a mesa do jogo. O menu do programa fica a critério dos
desenvolvedores.
As peças devem ser exibidas em ascii art, como no exemplo abaixo:
Figura 1. Peças do jogo de dominó duplo-seis.
Avaliação: serão utilizados 2 instrumentos de avaliação neste trabalho:
a) apresentação das estratégias de implementação e funcionamento da
mesma para o turma correspondendo a 20% da nota, divididos em 10% para a
organização da apresentação e 10% para o funcionamento;
b) (80% da nota). O restante da nota será a avaliação do professor em
relação ao código, usabilidade, estruturação e funcionamento.
Observações: Para cada erro de indentação e warning será descontado 0.1 na
nota do trabalho e caso não compile, a nota é zero.
Será compilado em ambiente Linux com o comando: gcc arq.c -o arq -Wall
Bonificação: De todos os trabalhos, serão elencados os 3 melhores pelo
professor, após a escolha a turma irá qualificar cada trabalho. O mais qualificado
receberá 1.5 pontos a mais, o segundo 1 e o menos qualificado receberá ½. 
