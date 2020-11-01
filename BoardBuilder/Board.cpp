#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <stdlib.h> 
#include "BOARD.h"
#include <Windows.h>

using namespace std;

//append das linhas no arquivo texto
void add_arq(string pos,char ori,string word,string nameboard) {

	ofstream arqv(nameboard + ".txt", ios::app);
	char a = toupper(pos[0]); char b = tolower(pos[1]); char c = toupper(ori); char d;
	arqv << a << b;
	arqv << " ";
	arqv << c;
	arqv << " ";
	int i = 0;
	while (word[i]) {
		d = toupper(word[i]);
		arqv << d;
		i++;
	}
	arqv << '\n';
	arqv.close();

}

//tratamento de erro da dimensão
unsigned int get_dimension() {
	unsigned int dim;
	cout << "Type the dimension of the board you want (max 20): ";
	cin >> dim;
	//Error Check
	while (!cin.good() || dim > 20) {
		cout << "You wrote something wrong! Please try again: ";

		//Cleaning system
		cin.clear();
		cin.ignore(INT_MAX, '\n');

		//Getting input again
		cin >> dim;
	}
	return dim;
}

//processo de validação da tentativa do usuário
vector<vector<int>> check_valid (string word, string pos, char ori, vector<vector<int>> board,int dim, Board &brd) {
	vector<vector<int>> oldboard = board;
	int len = word.size();
	int lin = brd.tr(pos[0]);
	int col = brd.tr(pos[1]);
	bool error = false;
	for (int i = 0; i < len; i++) {
		if (ori == 'h') {
			if (col + i > dim - 1) { error = true; break; }
			if (board[lin][col + i] != 0 && board[lin][col + i] != word[i]) { error = true; break; }
			board[lin][col + i] = word[i];

		}
		else{
			if (lin + i > dim - 1) { error = true; break; }
			if (board[lin + i][col] != 0 && board[lin + i][col] != word[i]) { error = true; break; }
			board[lin + i][col] = word[i];

		}
	}
	if (error) { cerr << "An error occurred, please try again" << endl; return oldboard; }
	return board;
}

//processo de montagem do board
void create_board(vector<vector<int>> board,int dim, Board &brd, string nameboard) {


	//verificação de abertura de arquivo WORDS.txt e sua transformação em vector
	vector <string> vwords;
	ifstream arq;
	string linha;
	arq.open("WORDS.txt");
	if (arq.is_open()) {
		while (getline(arq, linha)) {
			vwords.push_back(linha);
		}
		arq.close();
	}
	//fim da transformação

	vector<vector<int>> oldboard;
	bool check = true;
	string word,pos;
	char add, ori;
	while (check) {
		cout << "Do you want to add a new word? (y/n): ";
		cin >> add;
		while (add != 'y' && add != 'n') {
			cerr << "Please type 'y' for 'yes' or 'n' for 'no': ";
			cin.clear();
			cin.ignore(256, '\n');
			cin >> add;
		}
		if (add == 'n') break;

		while (check) {
			cout << "Type the word you want to add: ";
			cin >> word;

			//convert the word to uppercase
			char let;
			string upword = "";
			for (int j = 0; j < word.size(); j++) {
				let = toupper(word[j]);
				upword += let;
			}
			//

			if (find(vwords.begin(), vwords.end(), word) != vwords.end()) {
				cout << "Type the position of the first letter you want to add: ";
				cin >> pos;
				if (brd.tr(pos[0]) > dim - 1 || brd.tr(pos[1]) > dim - 1) {
					cerr << "Dimensions are not valid!" << endl;
					break;
				}
				cout << "Type the orientation for the word you want to add (v/h): ";
				cin >> ori;
				
				oldboard = board;
				board = check_valid(upword, pos, ori, board, dim, brd);

				brd.new_board(board);
				brd.print_board();
				if (oldboard != board) add_arq(pos, ori, upword, nameboard);

				break;

			}else{
				cout << "The word you gave does not exist! Please try again" << endl;
			}
		}
	}
}


//append do board no final do arquivo texto
void append_board(vector<vector<int>> board, int dim, string nameboard) {
	ofstream arq(nameboard +".txt",ios::app);
	arq << " \n\n";
	char c, d;
	string alpha = "abcdefghijklmnopqrstuvwxyz";
	arq << "   ";
	for (int k = 0; k < dim; k++) {
		arq << alpha[k] << "  ";
	}
	arq << '\n';
	for (int i = 0; i < dim; i++) {
		c = toupper(alpha[i]);
		arq << c << "  ";
		for (int j = 0; j < dim; j++) {
			d = toupper(board[i][j]);
			if (board[i][j] == 0) arq << '-' << "  ";
			else { arq << d << "  "; }
		}
		arq << '\n';
	}
	arq.close();
}

//main
int main() {
	Board brd;
	unsigned int dim;

	string nameboard;
	cout << "Name of the board you want to create: ";
	cin >> nameboard;

	dim = get_dimension();
	brd.set_dim(dim);
	vector< vector<int> > board(dim, vector<int>(dim));
	board = brd.fillboard(board,dim);
	brd.new_board(board);
	brd.print_board();

	ofstream arquivo(nameboard + ".txt");

	arquivo << dim << " " << 'X' << " " << dim << endl;
	arquivo.close();

	create_board(board,dim,brd,nameboard);

	append_board(brd.get_board(), dim, nameboard);

	cout << "All done!";
	
	return 0;
}