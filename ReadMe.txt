O Programa é baseado em 5 arquivos:
-Três Headers, nomeados como POOL, PLAYER e BOARD;
-Dois programas nomeados como BoardBuilder e o ScrabbleJunior;

A função de cada arquivo é bastante específica, e descrita da seguinta forma:
-POOL.h: Armazena os 3 vetores responsáveis por realizar grande parte das tarefas, sendo eles o vetor "letters" que armazena todas as letras dispostas no tabuleiro, 
o vetor "words" que armazena todas as palavras no tabuleiro, e o vetor "monstro", um vetor tridimensional que armazena um tuple contendo cada letra e suas coordenadas, 
dentro de um vetor que contem a palavra, dentro de um vetor que contém todas as palavras;
-PLAYER.h: Armazena a pontuação e o nome do jogador, assim como atualizar novos valores;
-BOARD.h:Armazena a dimensão do tabuleiro e um vetor contendo o próprio tabuleiro;
-BoardBuilder.cpp: Responsável por gerar um tabuleiro novo, nomeá-lo, definir sua dimensão e as palavras que pertenceram à ele;
-ScrabbleJunior.cpp: Responável por abrir um tabuleiro e realizar todas as atividades do jogo;

O jogo funciona da seguinte forma:
-Quando o usuário escolhe um tabuleiro, o programa irá verificar sua existência, caso não se confirme irá ser usado um tabuleiro padrão salvo na pasta do arquivo;
-Com o tabuleiro selecionado, será definido à quantidade de jogadores e seus respectivos nomes, de forma à diferencia-los;
-É gerado aleatóriamente com a função "randomize()" um par de valores do tipo 'char', extraidos do vetor "POOL.letters", de forma à não gerar letras que não existam no tabuleiro
ou letras que já foram usadas;
-Dentro da função "makemove()" o jogador irá decidir qual letra será jogada primeiro e sua coordenada, que terá seu valor convertido para inteiro pela função "BOARD.tr()",
e usando esses valores para procurar no vetor"POOL.monstro" e verificar se a letra da coordenada específicada é igual à escolhida pelo jogador, e caso seja a letra será marcada pela cor vermelha;
-Quando todas as letras de uma palavra foram escolhidas, o jogador receberá mais um ponto;
-O jogo termina quando algum dos jogadores concluir mais da metade das palavras no tabuleiro, verificado na função "end_game()";
-Todo jogo ocorre dentro de um ciclo "while", de forma à ser possível reiniciar o jogo ao final;

Foi considerado à possibilidade de se poder jogar com a máquina, utilizando algoritmos padrões para resolução de "puzzles" como forma de emular uma Inteligência Artificial e permitir que 
o jogo funcionasse com apenas um Player. Essa possibilidade foi descartada pois as alterações necessárias para implementar essa funcionalidade iriam prejudicar o funcionamento do jogo atual,
além de se tornar necessário reestruturar todas as classes e funções de forma à comportar essa nova funcionalidade. Chegamos à conclusão que todo o transtorno que seria gerado ao tentar implementar
tal funcionalidade iria desviar nossa atenção do tema inicial do projeto, e portanto, mantivemos as funcionalidades originalmente descritas.

Tivemos uma certa dificuldade no que tange ao tratamento de erros, visto que é consideravelmente complexo todas as possibilidades de entradas que o usuário pode tentar, por isso os erros tratados foram aqueles
que consideramos que os usuários poderiam cometer, focando principalmente naqueles mais esperados.

No que toca ao contexto geral do trabalho, foi interessante perceber como Programação Orientada à Objetos facilita o desenvolvimento, mantendo o código mais legível e separando as funcionalidades,
além de facilitar à explicação das etapas de desenvolvimento, fator crucial para projetos desenvolvidos em equipa.  
