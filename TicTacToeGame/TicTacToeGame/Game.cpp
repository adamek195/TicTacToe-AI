#include "Game.h"

//funkcja imitujaca gre w kolko i krzyzk
void game(Board& board,int size)
{
    //tworzymy glowne okno gdzie bedzie wyswietlana gra TicTacToe
    sf::RenderWindow window; // zmienna 2D renderuje nam klase typu Render Window
    window.create(sf::VideoMode(size*100, size*100, 32), "TicTacToe"); //okna ma wymiary 300 na 300
    window.setActive(true); // ustaw focus na okno
    window.setFramerateLimit(60);

    //zmienna wyswietli nam liczbe elemntow na planszy
    int count = (size*size);
    // tworzymy zdarzenie potrzebne do obslugi graficznej gry
    sf::Event event; // zmienna event ktora bedzie rejestrowac jakies wydarzenie myszki lub klawiatury
    sf::Texture texture[9]; //zmienne beda wczytywac kwadraty
    sf::Texture texturePlayer[9]; //zmienne beda wczytywac krzyzk gracza
    sf::Texture textureAi[9]; //zmienne beda wczytywac  gracza

    //tworzymy obiekty ktore beda sie wyswietlac na planszy
    sf::Sprite sprite[9]; // wyswietlanie kwadratow
    sf::Sprite spritePlayer[9]; // wyswietlanie krzykow gracza
    sf::Sprite spriteAi[9]; //wyswietlnie kolek gracza

    float xMouse; //zmienna pobierajaca wspolrzedna x od myszki
    float yMouse; // zmienne pobierajaca wspolrzedna y od myszki 
     //zmienne potrzebne do obslugi gry
    int row, col;
    //zmienna sprawdzajaca czy ktos wygral
    int victory;
    
    //wczytujemy kwadraty tworzace plansze
    for (int i = 0; i < count; i++)
        texture[i].loadFromFile("images/kwadrat.png");

    //umozliwiamy narysowanie kwadratu
    for(int i = 0; i < 9; i++)
        sprite[i].setTexture(texture[i]);

    //ustawiamy pozycje kwadratow
    sprite[0].setPosition(0, 0);
    sprite[1].setPosition(100, 0);
    sprite[2].setPosition(200, 0);
    sprite[3].setPosition(0, 100);
    sprite[4].setPosition(100, 100);
    sprite[5].setPosition(200, 100);
    sprite[6].setPosition(0, 200);
    sprite[7].setPosition(100, 200);
    sprite[8].setPosition(200, 200);

    //wykonuj dopoki zostaja wolne miejsca w grze
    while (window.isOpen())
    {
        //dopoki okno jest otwarte
        while (window.isOpen())
        {
            while (window.pollEvent(event))
            {
                //zakonczenie gry wcisnieciem escape lub zamknieciem okna
                if (event.type == sf::Event::Closed || (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)))
                    window.close();

                //klikamy myszka i wybieramy nasz ruch
                if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
                {
                    xMouse = sf::Mouse::getPosition(window).x;
                    yMouse = sf::Mouse::getPosition(window).y;
                    //sprawdzamy wszystkie mozliwosci wykonania naszego ruchu
                    if (xMouse > 0 && xMouse < 100 && yMouse > 0 && yMouse < 100)
                    {
                        //jesli sa wolne miejsca na planszy gracz moze wykonac ruch
                        if (board.isMovesLeft())
                        {
                            board.playerMove(0, 0);
                            board.printfBoard();
                            std::cout << "----------" << std::endl;
                            std::cout << "Ruch sztucznej inteligencji: " << std::endl;
                            texturePlayer[0].loadFromFile("images/krzyzyk.png");
                            spritePlayer[0].setTexture(texturePlayer[0]);
                            spritePlayer[0].setPosition(0, 0);
                        }
                        victory = board.check();
                        if (victory == 10)
                        {
                            std::cout << "Brawo wygrales !!!" << std::endl;
                            std::cout << "TU sie wswitli obrazek ze wygrales smieciu" << std::endl;
                        }
                    }
                    if (xMouse > 100 && xMouse < 200 && yMouse > 0 && yMouse < 100)
                    {
                        //jesli sa wolne miejsca na planszy gracz moze wykonac ruch
                        if (board.isMovesLeft())
                        {
                            board.playerMove(0, 1);
                            board.printfBoard();
                            std::cout << "----------" << std::endl;
                            std::cout << "Ruch sztucznej inteligencji: " << std::endl;
                            texturePlayer[1].loadFromFile("images/krzyzyk.png");
                            spritePlayer[1].setTexture(texturePlayer[1]);
                            spritePlayer[1].setPosition(100, 0);
                        }
                        victory = board.check();
                        if (victory == 10)
                        {
                            std::cout << "Brawo wygrales !!!" << std::endl;
                            std::cout << "TU sie wswitli obrazek ze wygrales smieciu" << std::endl;
                        }
                    }
                    if (xMouse > 200 && xMouse < 300 && yMouse > 0 && yMouse < 100)
                    {
                        //jesli sa wolne miejsca na planszy gracz moze wykonac ruch
                        if (board.isMovesLeft())
                        {
                            board.playerMove(0, 2);
                            board.printfBoard();
                            std::cout << "----------" << std::endl;
                            std::cout << "Ruch sztucznej inteligencji: " << std::endl;
                            texturePlayer[2].loadFromFile("images/krzyzyk.png");
                            spritePlayer[2].setTexture(texturePlayer[1]);
                            spritePlayer[2].setPosition(200, 0);
                        }
                        victory = board.check();
                        if (victory == 10)
                        {
                            std::cout << "Brawo wygrales !!!" << std::endl;
                            std::cout << "TU sie wswitli obrazek ze wygrales smieciu" << std::endl;
                        }
                    }
                    if (xMouse > 0 && xMouse < 100 && yMouse > 100 && yMouse < 200)
                    {
                        //jesli sa wolne miejsca na planszy gracz moze wykonac ruch
                        if (board.isMovesLeft())
                        {
                            board.playerMove(1, 0);
                            board.printfBoard();
                            std::cout << "----------" << std::endl;
                            std::cout << "Ruch sztucznej inteligencji: " << std::endl;
                            texturePlayer[3].loadFromFile("images/krzyzyk.png");
                            spritePlayer[3].setTexture(texturePlayer[3]);
                            spritePlayer[3].setPosition(0, 100);
                        }
                        victory = board.check();
                        if (victory == 10)
                        {
                            std::cout << "Brawo wygrales !!!" << std::endl;
                            std::cout << "TU sie wswitli obrazek ze wygrales smieciu" << std::endl;
                        }
                    }
                    if (xMouse > 100 && xMouse < 200 && yMouse > 100 && yMouse < 200)
                    {
                        //jesli sa wolne miejsca na planszy gracz moze wykonac ruch
                        if (board.isMovesLeft())
                        {
                            board.playerMove(1, 1);
                            board.printfBoard();
                            std::cout << "----------" << std::endl;
                            std::cout << "Ruch sztucznej inteligencji: " << std::endl;
                            texturePlayer[4].loadFromFile("images/krzyzyk.png");
                            spritePlayer[4].setTexture(texturePlayer[4]);
                            spritePlayer[4].setPosition(100, 100);
                        }
                        victory = board.check();
                        if (victory == 10)
                        {
                            std::cout << "Brawo wygrales !!!" << std::endl;
                            std::cout << "TU sie wswitli obrazek ze wygrales smieciu" << std::endl;
                        }
                    }
                    if (xMouse > 200 && xMouse < 300 && yMouse > 100 && yMouse < 200)
                    {
                        //jesli sa wolne miejsca na planszy gracz moze wykonac ruch
                        if (board.isMovesLeft())
                        {
                            board.playerMove(1, 2);
                            board.printfBoard();
                            std::cout << "----------" << std::endl;
                            std::cout << "Ruch sztucznej inteligencji: " << std::endl;
                            texturePlayer[5].loadFromFile("images/krzyzyk.png");
                            spritePlayer[5].setTexture(texturePlayer[5]);
                            spritePlayer[5].setPosition(200, 100);
                        }
                        victory = board.check();
                        if (victory == 10)
                        {
                            std::cout << "Brawo wygrales !!!" << std::endl;
                            std::cout << "TU sie wswitli obrazek ze wygrales smieciu" << std::endl;
                        }
                    }
                    if (xMouse > 0 && xMouse < 100 && yMouse > 200 && yMouse < 300)
                    {
                        //jesli sa wolne miejsca na planszy gracz moze wykonac ruch
                        if (board.isMovesLeft())
                        {
                            board.playerMove(2, 0);
                            board.printfBoard();
                            std::cout << "----------" << std::endl;
                            std::cout << "Ruch sztucznej inteligencji: " << std::endl;
                            texturePlayer[6].loadFromFile("images/krzyzyk.png");
                            spritePlayer[6].setTexture(texturePlayer[6]);
                            spritePlayer[6].setPosition(0, 200);
                        }
                        victory = board.check();
                        if (victory == 10)
                        {
                            std::cout << "Brawo wygrales !!!" << std::endl;
                            std::cout << "TU sie wswitli obrazek ze wygrales smieciu" << std::endl;
                        }
                    }
                    if (xMouse > 100 && xMouse < 200 && yMouse > 200 && yMouse < 300)
                    {
                        //jesli sa wolne miejsca na planszy gracz moze wykonac ruch
                        if (board.isMovesLeft())
                        {
                            board.playerMove(2, 1);
                            board.printfBoard();
                            std::cout << "----------" << std::endl;
                            std::cout << "Ruch sztucznej inteligencji: " << std::endl;
                            texturePlayer[7].loadFromFile("images/krzyzyk.png");
                            spritePlayer[7].setTexture(texturePlayer[7]);
                            spritePlayer[7].setPosition(100, 200);
                        }
                        victory = board.check();
                        if (victory == 10)
                        {
                            std::cout << "Brawo wygrales !!!" << std::endl;
                            std::cout << "TU sie wswitli obrazek ze wygrales smieciu" << std::endl;
                        }
                    }
                    if (xMouse > 200 && xMouse < 300 && yMouse > 200 && yMouse < 300)
                    {
                        //jesli sa wolne miejsca na planszy gracz moze wykonac ruch
                        if (board.isMovesLeft())
                        {
                            board.playerMove(2, 2);
                            board.printfBoard();
                            std::cout << "----------" << std::endl;
                            std::cout << "Ruch sztucznej inteligencji: " << std::endl;
                            texturePlayer[8].loadFromFile("images/krzyzyk.png");
                            spritePlayer[8].setTexture(texturePlayer[8]);
                            spritePlayer[8].setPosition(200, 200);
                        }
                        victory = board.check();
                        if (victory == 10)
                        {
                            std::cout << "Brawo wygrales !!!" << std::endl;
                            std::cout << "TU sie wswitli obrazek ze wygrales smieciu" << std::endl;
                        }
                    }
                }
                //jesli sa wolne miejsca na planszy to ai wykonuje ruch
                if (board.isMovesLeft());
                board.aiMove();

                std::cout << "----------" << std::endl;
                board.printfBoard();

                //jesli wygrala ai zakoncz rozgrywje
                victory = board.check();
                if (victory == -10)
                {
                    std::cout << "Przykro mi przegrales ze sztuczna inteligencja !!!" << std::endl;
                    break;
                }
            }
            //jesli mamy remis
            window.clear(sf::Color(0, 0, 0));
            for (int i = 0; i < 9; i++)
            {
                window.draw(sprite[i]);
                window.draw(spritePlayer[i]);
            }
            window.display();
        }
    }
}