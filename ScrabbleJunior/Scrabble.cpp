#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <stdlib.h> 
#include <Windows.h>
#include <sstream>
#include <time.h>
#include <random>
#include "BOARD.h"
#include "POOL.h"
#include <utility> 
#include "PLAYER.h"
#include <tuple>

using namespace std;

//faz a leitura do board no txt
void read_board(Board& brd, Pool& pl) {
	vector <string> list;
	ifstream arq;
	string linha;
	stringstream ss;
	int count = 0;
	int dim;
	string aword;
	char cword;

	string name_board;
	cout << "Type the name of the board you want to play : ";
	cin >> name_board;

	arq.open(name_board + ".txt");

	while (!arq.is_open()) {
		cout << "This board does not exist" << endl;
		cout << "Please type another one: ";

		cin.clear();
		cin >> name_board;
		arq.open(name_board + ".txt");
	}

	if (arq.is_open()) {
		while (getline(arq, linha)) {
			if (linha[0] == ' ') { arq.close(); break; }
			if (linha == "") { arq.close(); break; }
			if (count == 0) {
				ss << linha;
				ss >> dim;
				ss.clear();
				count++;
			}
			else {
				list.push_back(linha);
			}
		}
		arq.close();
	}

	vector< vector<int> > board(dim, vector<int>(dim));
	brd.set_dim(dim);
	board = brd.fillboard(board, dim);
	brd.new_board(board);
	vector<vector<tuple<char, int, int>>> monstro(list.size(), vector<tuple<char, int, int>>());
	for (int i = 0; i < list.size(); i++) {
		string line = list[i];
		int x, y;
		y = brd.tr(line[0]);
		x = brd.tr(line[1]);
		char ori = line[3];
		int add = 0;

		aword = line.substr(5, line.length() - 5);
		pl.new_word(aword);

		for (int k = 5; k < line.length(); k++) {
			pl.new_letter(line[k]);
		}

		for (int count = 5; count < line.length(); count++) {
			if (ori == 'V') {
				board[y + add][x] = line[count];
				monstro[i].push_back(make_tuple(line[count], y + add, x));
			}
			else {
				board[y][x + add] = line[count];
				monstro[i].push_back(make_tuple(line[count], y, x + add));
			}
			add++;
		}
	}
	pl.new_monster(monstro);
	brd.new_board(board);
}

//atualiza o vetor das letras
void at_vector(vector <char>& letters, int i) {
	vector <char> lista = letters;
	vector <char> nlista;
	for (int j = 0; j <= i - 1; j++) {
		nlista.push_back(lista[j]);
	}
	for (int v = i + 1; v < lista.size(); v++) {
		nlista.push_back(lista[v]);
	}
	letters = nlista;
}

//retorna letras de maneira randomica para o turno do jogador
pair<char, char> randomize(Pool& pl) {
	srand(time(NULL));
	pair <char, char> valores;
	vector <char> letters = pl.get_letters();
	int size = letters.size();
	if (letters.size() < 2) {
		int i = rand() % size;
		valores.first = letters[i];
		at_vector(letters, i);
		pl.new_letters(letters);
		valores.second = '*';
		return valores;
	}
	else {
		int i = rand() % size;
		valores.first = letters[i];
		at_vector(letters, i);
		size--;

		i = rand() % size;
		valores.second = letters[i];
		at_vector(letters, i);
		pl.new_letters(letters);
		return valores;
	}
}

//Verifica se o jogo foi vencido por alguem (metade)
bool end_game(Pool& pl, int nump, Player& player) {
	vector <string> word_list = pl.get_words();
	int size = word_list.size();
	int points = player.pontuation();
	if (points > (ceil(size / 2))) {
		return false;
	}
	return true;

}

//Faz a jogada
bool make_move(int n, int nump, char flet, char slet, Board& brd, Pool& pl, Player& player1, Player& player2, Player& player3, Player& player4) {
	if (n > nump) {
		n = 1;
	}
	char moveX, moveY, letter, comp;
	cout << "\tTurn of Player " << n << endl;
	cout << "\tChoose the letter you want to place first: " << endl;
	cin >> letter;
	letter = toupper(letter);

	while (letter != flet && letter != slet) {
		cout << "----The letter you've choosen does not match the letters you have, choose another one " << endl;
		cin.clear();
		cin.ignore(INT_MAX, '\n');
		cin >> letter;
		letter = toupper(letter);
	}

	cout << "\tChoose the position where you want to place your letter: " << endl;
	//

	bool error = true;
	cin >> moveX >> moveY;
	int cordX, cordY;
	vector <vector<int>> lista;
	lista = brd.get_board();

	while (error) {

		cordX = brd.tr(moveX);
		cordY = brd.tr(moveY);
		comp = lista[cordX][cordY];

		if (comp != letter) {
			cout << "----Invalid Position,choose another one" << endl;
			error = true;
			cin.clear();
			cin.ignore(INT_MAX, '\n');
			cin >> moveX >> moveY;
		}
		else error = false;
	}

	//
	int ponto1 = pl.e_monster(cordX, cordY);
	cout << '\n' << endl;
	cout << "Your Score:  " << ponto1 << endl;
	lista[cordX][cordY] = tolower(lista[cordX][cordY]);
	brd.new_board(lista);

	//

	int ponto2 = 0;
	if (slet != '*') {
		cout << "\tChoose the position to the other letter" << endl;

		error = true;
		cin >> moveX >> moveY;
		lista = brd.get_board();

		if (letter == flet) {

			while (error) {

				cordX = brd.tr(moveX);
				cordY = brd.tr(moveY);
				comp = lista[cordX][cordY];
				if (comp != slet) {
					cout << "----Invalid Position,choose another one" << endl;
					error = true;
					cin.clear();
					cin.ignore(INT_MAX, '\n');
					cin >> moveX >> moveY;
				}
				else error = false;
			}

		}
		else if (letter == slet) {
			while (error) {

				cordX = brd.tr(moveX);
				cordY = brd.tr(moveY);
				comp = lista[cordX][cordY];
				if (comp != flet) {
					cout << "----Invalid Position,choose another one" << endl;
					error = true;
					cin.clear();
					cin.ignore(INT_MAX, '\n');
					cin >> moveX >> moveY;
				}
				else error = false;
			}

		}
		ponto2 = pl.e_monster(cordX, cordY);
		lista[cordX][cordY] = tolower(lista[cordX][cordY]);
		brd.new_board(lista);
	}


	

	int pontos = ponto1 + ponto2;
	bool won;
	if (n == 1) {
		player1.update_score(pontos);
		cout << "Score of " << player1.disp() << ": " << pontos << endl;
		cout << '\n';
		won = end_game(pl, nump, player1);
	}
	else if (n == 2) {
		player2.update_score(pontos);
		cout << "Score of " << player2.disp() << ": " << pontos << endl;
		won = end_game(pl, nump, player2);
	}
	else if (n == 3) {
		player3.update_score(pontos);
		cout << "Score of " << player3.disp() << ": " << pontos << endl;
		won = end_game(pl, nump, player3);
	}
	else if (n == 4) {
		player4.update_score(pontos);
		cout << "Score of " << player4.disp() << ": " << pontos << endl;
		won = end_game(pl, nump, player4);
	}


	return won;
}



int main() {
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	char rematch = 'y';
	while (rematch == 'y') {

		Board brd;	Pool pl;
		Player player1;	Player player2;	Player player3;	Player player4;
		read_board(brd, pl);
		brd.print_board();

		int nump;
		cout << "How many players are expected? :     (2-4)" << endl;
		cin >> nump;
		while (nump < 2 || nump > 4 || !cin.good()) {
			cout << "\nInvalid player amount, it needs to be between 2 and 4, try again: \n" << endl;
			cin.clear();
			cin.ignore(INT_MAX, '\n');
			cin >> nump;
		}
		string word;
		if (nump >= 2) {
			player1.identity(1);
			cout << "What is the name of player 1?  " << endl;
			cin >> word;
			player1.name(word);
			player2.identity(2);
			cout << "What is the name of player 2?  " << endl;
			cin >> word;
			player2.name(word);
		}
		if (nump >= 3) {
			player1.identity(3);
			cout << "What is the name of player 3?  " << endl;
			cin >> word;
			player3.name(word);
		}
		if (nump == 4) {
			player1.identity(4);
			cout << "What is the name of player 4?  " << endl;
			cin >> word;
			player4.name(word);
		}
		vector <char> letters = pl.get_letters();
		int size = letters.size();
		int n = 1;
		bool working = true;
		while (working) {

			if (pl.get_letters().size() == 0) break;

			cout << "\n";
			brd.print_board();
			pair <char, char> valores;
			valores = randomize(pl);
			char flet = valores.first;
			char slet = valores.second;

			if (slet == '*') { cout << "\nYour letter is " << flet << endl; }
			else { cout << "\nYour letters are " << flet << " and " << slet << endl; }

			working = make_move(n, nump, flet, slet, brd, pl, player1, player2, player3, player4);
			n++;
		}


		string winner;
		int n_winners = 0;
		int win_score = max(max(max(player1.pontuation(), player2.pontuation()), player3.pontuation()), player4.pontuation());
		vector <int> scores = { player1.pontuation(), player2.pontuation(), player3.pontuation(), player4.pontuation() };
		vector <string> names = { player1.disp(), player2.disp(), player3.disp(), player4.disp() };
		vector <int> ind_winners;

		for (int k = 0; k < 4; k++) {
			if (scores[k] == win_score) {
				n_winners++;
				ind_winners.push_back(k);
			}
		}


		if (n_winners == 1) {

			cout << "\n\t";
			SetConsoleTextAttribute(h, BACKGROUND_BLUE | BACKGROUND_INTENSITY);
			cout << " Congratulations " << names[ind_winners[0]] << ", You Won ";
			SetConsoleTextAttribute(h, FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_INTENSITY);
			cout << "\n";
		}

		else {

			cout << "\n";
			cout << "There is a tie!" << endl;


			if (n_winners == 2) {
				cout << "\n\t";
				SetConsoleTextAttribute(h, BACKGROUND_BLUE | BACKGROUND_INTENSITY);
				cout << " Congratulations " << names[ind_winners[0]] << " and " << names[ind_winners[1]] << ", You tied! ";
				SetConsoleTextAttribute(h, FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_INTENSITY);
				cout << "\n";
			}
			if (n_winners == 3) {
				cout << "\n\t";
				SetConsoleTextAttribute(h, BACKGROUND_BLUE | BACKGROUND_INTENSITY);
				cout << " Congratulations " << names[ind_winners[0]] << "," << names[ind_winners[1]] << " and " << names[ind_winners[2]] << ", You tied! ";
				SetConsoleTextAttribute(h, FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_INTENSITY);
				cout << "\n";
			}
			if (n_winners == 4) {
				cout << "\n\t";
				SetConsoleTextAttribute(h, BACKGROUND_BLUE | BACKGROUND_INTENSITY);
				cout << " Congratulations " << names[ind_winners[0]] << "," << names[ind_winners[1]] << "," << names[ind_winners[2]] << " and " << names[ind_winners[3]] << ", You tied! ";
				SetConsoleTextAttribute(h, FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_INTENSITY);
				cout << "\n";
			}

			SetConsoleTextAttribute(h, FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_INTENSITY);
		}




		cout << "\n";
		cout << "Do you want to play again? y/n" << endl;
		cin >> rematch;
		if (rematch != 'n' && rematch != 'y') {
			cout << "Invalid answer, try to use 'y' or 'n': " << endl;
			cin >> rematch;
		}
	}
	return 0;
}