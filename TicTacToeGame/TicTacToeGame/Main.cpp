#include "Board.h"
#include "Game.h"
#include <SFML/Graphics.hpp>


int main()
{
    int size; //zmienna bedzie pobieraz rozmiar planszy do gry
    int sign; //zmiena ktora bedzie wczytywac ile znakow daje zwyciestwo
    std::cout << "Podaj rozmiar planszy do gry w kolko i krzyzk, " << std::endl;
    std::cout << "Twoj wybor to: ";
    std::cin >> size;
    std::cin.ignore(100000, '\n');
    std::cout << "Podaj ilosc symboli ktora daje zwyciestwo w rzedzie: ";
    std::cin >> sign;
    std::cin.ignore(100000, '\n');
    Board board(size, sign);
    game(board, size);
    return 0;
}