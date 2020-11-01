#ifndef POOLH
#define POOLH

#include <iostream>
#include <string>
#include <vector>
#include <Windows.h>
#include <tuple>

using namespace std;

class Pool {
private:
    vector<char> letters;
    vector<string> words;
    vector<vector<tuple<char, int, int>>> monstro;
public:
    void new_word(string word);
    vector<string> get_words();
    void new_letter(char letter);
    void new_letters(vector<char>lista);
    vector<char> get_letters();
    void new_monster(vector<vector<tuple<char, int, int>>> lista);
    vector<vector<tuple<char, int, int>>> get_monster();
    int e_monster(int y, int x);   void monst_remove(int i, int j);
    void empty_remove(int c);
};
//adicionar uma palavra ao vetor de palavras

void Pool::new_word(string word) {
    this->words.push_back(word);
}

//retornar a lista de palavras
vector<string> Pool::get_words() {
    return this->words;
}

//adicionar uma letra ao vetor de palavras
void Pool::new_letter(char letter) {
    this->letters.push_back(letter);
}

//atualizar vetor de letras
void Pool::new_letters(vector <char> lista) {
    this->letters = lista;
}

//retornar a lista de letras
vector<char> Pool::get_letters() {
    return this->letters;
}

//atualizar monstro
void Pool::new_monster(vector<vector<tuple<char, int, int>>> lista) {
    this->monstro = lista;
}

//retornar monstro
vector<vector<tuple<char, int, int>>> Pool::get_monster() {
    return this->monstro;
}

//apagar valor do monstro
int Pool::e_monster(int y, int x) {
    vector<vector<tuple<char, int, int>>> lista = this->monstro;

    for (int i = 0; i < lista.size(); i++) {
        for (int j = 0; j < lista[i].size(); j++) {
            if (get<1>(lista[i][j]) == y && get<2>(lista[i][j]) == x) {
                monst_remove(i, j);
                
            }
        }
    }    
    lista = this->monstro;
    vector<vector<tuple<char, int, int>>> auxlista = lista;
    //cout << "elemento " << get<0>(this->monstro[0][0]) << endl;
    
    int c = 0;
    while(c < this->monstro.size()) {
        //cout << "vazia " << this->monstro[c].empty() << endl;
        if (this->monstro[c].empty()) {
            empty_remove(c);
            c--;
        }
        c++;
    }
    //cout << "size" << this->monstro.size() << endl;
    return lista.size() - this->monstro.size();
}

//função complementar do e_monster - apagar o tuple da letra
void Pool::monst_remove(int i, int j) {
    vector<vector<tuple<char, int, int>>> lista = this->monstro;
    vector<vector<tuple<char, int, int>>> newlist(lista.size(), vector<tuple<char, int, int>>());
    for (int c1 = 0; c1 < i; c1++) {
        for (int c2 = 0; c2 < lista[c1].size(); c2++) {
            newlist[c1].push_back(lista[c1][c2]);
        }
    }

    for (int c1 = 0; c1 < j; c1++) newlist[i].push_back(lista[i][c1]);
    for (int c2 = j+1; c2 < lista[i].size(); c2++) newlist[i].push_back(lista[i][c2]);

    for (int c1 = i+1; c1 < lista.size(); c1++) {
        for (int c2 = 0; c2 < lista[c1].size(); c2++) {
            newlist[c1].push_back(lista[c1][c2]);
        }
    }
    this->monstro = newlist;
}

//função complementar do e_monster - apagar a lista vazia
void Pool::empty_remove(int c) {
    vector<vector<tuple<char, int, int>>> lista = this->monstro;
    vector<vector<tuple<char, int, int>>> newlist(lista.size()-1, vector<tuple<char, int, int>>());
    for (int i = 0; i < c; i++) {
        for(int count = 0; count < lista[i].size(); count++) 
            newlist[i].push_back(lista[i][count]);        
    }
    for (int j = c+1; j < lista.size(); j++) {
        for (int count = 0; count < lista[j].size(); count++) {
            newlist[j-1].push_back(lista[j][count]);
        }
    }
    this->monstro = newlist;
}

#endif