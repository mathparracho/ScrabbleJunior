#ifndef BOARD_H_
#define BOARD_H_

#include <iostream>
#include <string>
#include <vector>
#include <Windows.h>
using namespace std;

class Board {
private:
	vector<vector<int>> board;
	unsigned int dim;
public:
	~Board();
	void print_board();
	void new_board(vector<vector<int>>);
	void set_dim(int);
	vector<vector<int>> get_board();
	vector<vector<int>> fillboard(vector<vector<int>> board, int dim);
	int tr(char c);
};

//printar board no console
void Board::print_board() {

	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	vector<vector<int>> board = this->board;
	unsigned int dim = this->dim;

	char c, d, e;
	string alpha = "abcdefghijklmnopqrstuvwxyz";
	SetConsoleTextAttribute(h, BACKGROUND_BLUE | BACKGROUND_INTENSITY);
	cout << "   ";
	for (int k = 0; k < dim; k++) {
		cout << alpha[k] << "  ";
	}
	SetConsoleTextAttribute(h, FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_INTENSITY);
	cout << '\n';
	for (int i = 0; i < dim; i++) {
		SetConsoleTextAttribute(h, BACKGROUND_BLUE | BACKGROUND_INTENSITY);
		c = toupper(alpha[i]);
		cout << c << "  ";
		SetConsoleTextAttribute(h, FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_INTENSITY);
		for (int j = 0; j < dim; j++) {
			d = board[i][j];
			if (d != toupper(d)) {
				SetConsoleTextAttribute(h, FOREGROUND_RED | FOREGROUND_INTENSITY);
				e = toupper(d);
				cout << e << "  ";
				SetConsoleTextAttribute(h, FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_INTENSITY);
			}
			else if (board[i][j] == 0) cout << '-' << "  ";
			else { cout << d << "  "; }
		}
		cout << '\n';
	}
}

//atualizar board na classe
void Board::new_board(vector<vector<int>> board) {
	this->board = board;
}

//setar a dimensão
void Board::set_dim(int dim) {
	this->dim = dim;
}

//retornar o board da classe
vector<vector<int>> Board::get_board() {
	return this->board;
}

//preencher o board inicial com 0's
vector<vector<int>> Board::fillboard(vector<vector<int>> board, int dim) {

	for (int i = 0; i < dim; i++) {
		for (int j = 0; j < dim; j++) {
			board[i][j] = 0;
		}
	}
	return board;
}

//transformar coordenadas de letras para numeros
int Board::tr(char c) {
	c = tolower(c);
	string alpha = "abcdefghijklmnopqrstuvwxyz";
	for (int i = 0; i <= 26; i++) {
		if (alpha[i] == c) return i;
	}
}

Board::~Board() {}
#endif