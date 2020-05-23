#include "Board.h"
#include "Game.h"
#include <SFML/Graphics.hpp>


int main()
{
    int size; //zmienna bedzie pobieraz rozmiar planszy do gry
    int choice; //zmienna wyboru tablice
    std::cout << "Podaj rozmiar planszy do gry w kolko i krzyzk, " << std::endl;
    std::cout << "Dostepne rozmiary planszy to: " << std::endl;
    std::cout << "1. plansza 3x3: " << std::endl;
    std::cout << "2. plansza 4x4: " << std::endl;
    std::cout << "3. plansza 5x5: " << std::endl;
    std::cout << "Twoj wybor to: ";
    std::cin >> choice;
    std::cin.ignore(100000, '\n');
    //menu planszy
    switch (choice)
    {
        case 1:
        {
            size = 3;
            Board board(size);
            game(board, size);
            break;

        }
        case 2:
        {
            size = 4;
            Board board(size);
            game(board, size);
            break;
        }
        case 3:
        {
            size = 5;
            Board board(size);
            game(board, size);
            break;
        }
        defaul:
        {
            std::cout << "Nie ma takiej opcji w menu!!!" << std::endl;
        }
    }
    
    return 0;
}