#include "Board.h"
#include "Game.h"
#include <SFML/Graphics.hpp>


int main()
{
    int size; //zmienna bedzie pobieraz rozmiar planszy do gry
    std::cout << "Podaj rozmiar planszy do gry w kolko i krzyzk: ";
    std::cin >> size;
    std::cin.ignore(100000, '\n');
    
    //tworzymy tablice do gry:
    Board board(size);
    game(board, size);
    return 0;
}