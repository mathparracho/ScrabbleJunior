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


////// ENGLISH VERSION //////

The Program is based on 5 files:
-Three Headers, nominated as POOL, PLAYER and BOARD;
-Two programs named BoardBuilder and ScrabbleJunior;

The function of each file is very specific, and is described as follows:
-POOL.h: Stores the 3 vectors responsible for performing most of the tasks, they being the "letters" vector that stores all the letters arranged on the board,
the "words" vector that stores all the words on the board, and the "monster" vector, a three-dimensional vector that stores a tuple containing each letter and its coordinates,
inside a vector that contains the word, inside a vector that contains all the words;
-PLAYER.h: Stores the player's score and name, as well as updating new values;
-BOARD.h: Stores the dimension of the board and a vector containing the board itself;
-BoardBuilder.cpp: Responsible for generating a new board, naming it, defining its size and the words that belonged to it;
-ScrabbleJunior.cpp: Responsible for opening a board and performing all the activities of the game;

The game works as follows:
-When the user chooses a board, the program will check for its existence, if not confirmed, a standard board saved in the file folder will be used;
-With the selected board, it will be defined the number of players and their respective names, in order to differentiate them;
-A pair of values ​​of the type 'char' is generated randomly with the function "randomize ()", extracted from the vector "POOL.letters", so as not to generate letters that do not exist on the board
or letters that have already been used;
-In the "makemove ()" function, the player will decide which letter will be played first and its coordinate, which will have its value converted to integer by the "BOARD.tr ()" function,
and using these values ​​to look in the "POOL.monstro" vector and check if the letter of the specified coordinate is the same as the one chosen by the player, and if it is the letter it will be marked by red color;
-When all letters of a word have been chosen, the player will receive one more point;
-The game ends when one of the players finishes more than half of the words on the board, verified in the function "end_game ()";
-Every game takes place within a "while" cycle, so that it is possible to restart the game at the end;

It was considered the possibility of being able to play with the machine, using standard algorithms for solving puzzles as a way to emulate an Artificial Intelligence and allow
the game worked with only one Player. This possibility has been ruled out as the changes needed to implement this functionality would hinder the functioning of the current game,
in addition to the need to restructure all classes and functions in order to include this new functionality. We concluded that all the inconvenience that would be generated when trying to implement
such functionality would divert our attention from the initial theme of the project, and therefore, we kept the features originally described.

We had a certain difficulty regarding the handling of errors, since it is considerably complex all the possibilities of entries that the user can try, so the errors treated were those
that we think users could commit to, focusing mainly on those most expected.

Regarding the general context of the work, it was interesting to see how Object Oriented Programming facilitates development, keeping the code more readable and separating the features,
in addition to facilitating the explanation of the development stages, a crucial factor for projects developed as a team.
