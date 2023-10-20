#include <iostream>
#include <conio.h>
#include <ctime>
#include <windows.h>
#include <string>

using namespace std;
int tamanho = 4;
int corpo[121][2];
int temp[2][2];
int fruta[2];  
int contagemf;

string sprites[4] = { "[ ]", "(*)", "(O)", "{%}" };
string matriz[11][11] = {
    "[ ]", "[ ]", "[ ]", "[ ]", "[ ]", "[ ]", "[ ]", "[ ]", "[ ]", "[ ]", "[ ]",
    "[ ]", "[ ]", "[ ]", "[ ]", "[ ]", "[ ]", "[ ]", "[ ]", "[ ]", "[ ]", "[ ]",
    "[ ]", "[ ]", "[ ]", "[ ]", "[ ]", "[ ]", "[ ]", "[ ]", "[ ]", "[ ]", "[ ]",
    "[ ]", "[ ]", "[ ]", "[ ]", "[ ]", "[ ]", "[ ]", "[ ]", "[ ]", "[ ]", "[ ]",
    "[ ]", "[ ]", "[ ]", "[ ]", "[ ]", "[ ]", "[ ]", "[ ]", "[ ]", "[ ]", "[ ]",
    "[ ]", "[ ]", "[ ]", "(*)", "(*)", "(O)", "[ ]", "[ ]", "[ ]", "[ ]", "[ ]",
    "[ ]", "[ ]", "[ ]", "[ ]", "[ ]", "[ ]", "[ ]", "[ ]", "[ ]", "[ ]", "[ ]",
    "[ ]", "[ ]", "[ ]", "[ ]", "[ ]", "[ ]", "[ ]", "[ ]", "[ ]", "[ ]", "[ ]",
    "[ ]", "[ ]", "[ ]", "[ ]", "[ ]", "[ ]", "[ ]", "[ ]", "[ ]", "[ ]", "[ ]",
    "[ ]", "[ ]", "[ ]", "[ ]", "[ ]", "[ ]", "[ ]", "[ ]", "[ ]", "[ ]", "[ ]",
    "[ ]", "[ ]", "[ ]", "[ ]", "[ ]", "[ ]", "[ ]", "[ ]", "[ ]", "[ ]", "[ ]",
};

bool sair = false;

void gameover() {
    system("cls");
    for (int i = 0; i < 10; i++) {
        cout << "Game Over\n";
        Sleep(200);
    }

    cout << "Frutas comidas: " << contagemf << endl;
    Sleep(400);
    exit(0);
}

int colisao(int x, int y) {
    if (matriz[x][y] == "[ ]") {
        return 0;  // Vazio
    }
    if (matriz[x][y] == "(*)") {
        return 1;  // Corpo
    }
    if (matriz[x][y] == "(O)") {
        return 2;  // Cabeça
    }
    if (matriz[x][y] == "{%}") {
        return 3;  // Fruta
    }
}

void setas() {
    cout << "Use as setas para mover ";
    char k;
    k = _getch();

    if (k == 27) {
        sair = true;
        return;
    }

    temp[0][0] = corpo[tamanho - 1][0];
    temp[0][1] = corpo[tamanho - 1][1];

    for (int i = tamanho; i > 0; i--) {
        corpo[i][0] = corpo[i - 1][0];
        corpo[i][1] = corpo[i - 1][1];
    }

    switch (k) {
    case 72:  // Seta para cima
        corpo[0][1] -= 1;
        if (corpo[0][1] < 0) {
            corpo[0][1] = 10;
        }
        break;
    case 80:  // Seta para baixo
        corpo[0][1] += 1;
        if (corpo[0][1] > 10) {
            corpo[0][1] = 0;
        }
        break;
    case 77:  // Seta para direita
        corpo[0][0] += 1;
        if (corpo[0][0] > 10) {
            corpo[0][0] = 0;
        }
        break;
    case 75:  // Seta para esquerda
        corpo[0][0] -= 1;
        if (corpo[0][0] < 0) {
            corpo[0][0] = 10;
        }
        break;
    default:
        cout << "Not An Arrow Key\n";
    }

    if (colisao(corpo[0][1], corpo[0][0]) == 1) {
        gameover();
    }

    matriz[temp[0][1]][temp[0][0]] = sprites[0];
    matriz[fruta[1]][fruta[0]] = sprites[3];  // Alterado para usar as coordenadas da fruta
    matriz[corpo[0][1]][corpo[0][0]] = sprites[2];

    for (int i = 1; i < tamanho; i++) {
        matriz[corpo[i][1]][corpo[i][0]] = sprites[1];
    }
}

void fmatriz() {
    for (int l = 0; l < 11; l++) {
        for (int c = 0; c < 11; c++) {
            cout << matriz[l][c];
        }
        cout << endl;
    }
}

void frutas() {
    srand(time(0));
    do {
        fruta[0] = rand() % 11;
        fruta[1] = rand() % 11;
    } while (colisao(fruta[1], fruta[0]) != 0);  // Continue gerando até encontrar uma posição vazia
}

int main() {
    corpo[0][0] = 5;
    corpo[0][1] = 5;
    corpo[1][0] = 4;
    corpo[1][1] = 5;
    corpo[2][0] = 3;
    corpo[2][1] = 5;
    frutas();
    while (!sair) {
        system("cls");
        cout << "Snake Game - Gabriel Trein" << endl;
        cout << "linha " << corpo[0][1] + 1 << endl;
        cout << "coluna " << corpo[0][0] + 1 << endl;
        cout << "Frutas comidas " << contagemf << endl;
        fmatriz();
        setas();
        if (corpo[0][1] == fruta[1] && corpo[0][0] == fruta[0]) {
            contagemf++;
            tamanho = tamanho + 2;
            frutas();
        }
    }
    return 0;
}
