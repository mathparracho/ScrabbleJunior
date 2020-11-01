#ifndef PLAYERH
#define PLAYERH


#include <iostream>
#include <string>
#include <vector>
#include <Windows.h>
using namespace std;

class Player {
private:
    int id;
    string nome;
    int score;
    char flet;
    char slet;

public:
    void update_score(int num);
    void name(string word);
    void identity(int num);
    string disp();
    int pontuation();
};

void Player::update_score(int num) {
    this->score += num;
}

void Player::identity(int num) {
    this->id = num;
}
void Player::name(string word) {
    this->nome = word;
}
string Player::disp() {
    return this->nome;
}
int Player::pontuation() {
    return this->score;
}
#endif