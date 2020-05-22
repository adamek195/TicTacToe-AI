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
    sf::Texture *texture = new  sf::Texture[count]; //zmienne beda wczytywac kwadraty
    sf::Texture *texturePlayer = new sf::Texture[count]; //zmienne beda wczytywac krzyzk gracza
    sf::Texture *textureAi = new sf::Texture[count]; //zmienne beda wczytywac  gracza

    //tworzymy obiekty ktore beda sie wyswietlac na planszy
    sf::Sprite *sprite = new sf::Sprite[count]; // wyswietlanie kwadratow
    sf::Sprite *spritePlayer = new sf::Sprite[count]; // wyswietlanie krzykow gracza
    sf::Sprite *spriteAi = new sf::Sprite[count]; //wyswietlnie kolek gracza

    float xMouse; //zmienna pobierajaca wspolrzedna x od myszki
    float yMouse; // zmienne pobierajaca wspolrzedna y od myszki

     //zmienne potrzebne do obslugi gry
    Move aiMove;
    //zmienna sprawdzajaca czy ktos wygral
    int victory;
    
    //wczytujemy kwadraty tworzace plansze
    for (int i = 0; i < count; i++)
        texture[i].loadFromFile("images/kwadrat.png");

    //umozliwiamy narysowanie kwadratu
    for(int i = 0; i < count; i++)
        sprite[i].setTexture(texture[i]);

    int length = 0; //zmienna potrzebna do obslugi
    //ustawiamy pozycje kwadratow
    //ustawiamy pierwszy kwadrat
    for (int i = 0; i < size; i++)
    {
        sprite[i].setPosition(100 * length, 0);
        length++;
    }
    length = 0; //zerujemy length
    //ustawiamy drugi wiersz
    for (int i = 0; i < size; i++)
    {
        sprite[i+size].setPosition(100 * length, 100);
        length++;
    }
    length = 0;
    //ustawiamy trzeci wiersz
    for (int i = 0; i < size; i++)
    {
        sprite[i+size*2].setPosition(100 * length, 200);
        length++;
    }
    length = 0;
    //jesli mamy tablice 4 na 4
    //ustawiamy czwarty wiersz
    if (size == 4)
    {
        for (int i = 0; i < size; i++)
        {
            sprite[i + size * 3].setPosition(100 * length, 300);
            length++;
        }
    }

    //jesli mamy tablice 5 na 5
    //ustawiamy czwarty i piaty wiersz
    if (size == 5)
    {
        for (int i = 0; i < size; i++)
        {
            sprite[i + size * 3].setPosition(100 * length, 300);
            length++;
        }
        length = 0; //zerujemy length
        for (int i = 0; i < size; i++)
        {
            sprite[i + size * 4].setPosition(100 * length, 400);
            length++;
        }
    }

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
                            spritePlayer[2].setTexture(texturePlayer[2]);
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
                    victory = board.check();
                    if (victory == 0 && board.isMovesLeft() == false)
                    {
                        std::cout << "Remis !!!" << std::endl;
                    }
                }
                //jesli zostanie wycisniety klawisz enter to ruch wykonac ma ai
                if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Enter)
                {
                    //jesli sa wolne miejsca na planszy to ai wykonuje ruch
                    if (board.isMovesLeft())
                    {
                        aiMove = board.aiMove();
                        board.printfBoard();
                        if (aiMove.row == 0 && aiMove.col == 0)
                        {
                            textureAi[0].loadFromFile("images/kolo.png");
                            spriteAi[0].setTexture(textureAi[0]);
                            spriteAi[0].setPosition(0, 0);
                            std::cout << "----------" << std::endl;
                            std::cout << "Twoj ruch: " << std::endl;
                            //jesli wygrala ai zakoncz rozgrywje
                            victory = board.check();
                            if (victory == -10)
                            {
                                std::cout << "Przykro mi przegrales ze sztuczna inteligencja !!!" << std::endl;
                            }
                        }
                        if (aiMove.row == 1 && aiMove.col == 0)
                        {
                            textureAi[1].loadFromFile("images/kolo.png");
                            spriteAi[1].setTexture(textureAi[1]);
                            spriteAi[1].setPosition(0, 100);
                            std::cout << "----------" << std::endl;
                            std::cout << "Twoj ruch: " << std::endl;
                            //jesli wygrala ai zakoncz rozgrywje
                            victory = board.check();
                            if (victory == -10)
                            {
                                std::cout << "Przykro mi przegrales ze sztuczna inteligencja !!!" << std::endl;
                            }
                        }
                        if (aiMove.row == 2 && aiMove.col == 0)
                        {
                            textureAi[2].loadFromFile("images/kolo.png");
                            spriteAi[2].setTexture(textureAi[2]);
                            spriteAi[2].setPosition(0, 200);
                            std::cout << "----------" << std::endl;
                            std::cout << "Twoj ruch: " << std::endl;
                            //jesli wygrala ai zakoncz rozgrywje
                            victory = board.check();
                            if (victory == -10)
                            {
                                std::cout << "Przykro mi przegrales ze sztuczna inteligencja !!!" << std::endl;
                            }
                        }
                        if (aiMove.row == 0 && aiMove.col == 1)
                        {
                            textureAi[3].loadFromFile("images/kolo.png");
                            spriteAi[3].setTexture(textureAi[3]);
                            spriteAi[3].setPosition(100, 0);
                            std::cout << "----------" << std::endl;
                            std::cout << "Twoj ruch: " << std::endl;
                            //jesli wygrala ai zakoncz rozgrywje
                            victory = board.check();
                            if (victory == -10)
                            {
                                std::cout << "Przykro mi przegrales ze sztuczna inteligencja !!!" << std::endl;
                            }
                        }
                        if (aiMove.row == 1 && aiMove.col == 1)
                        {
                            textureAi[4].loadFromFile("images/kolo.png");
                            spriteAi[4].setTexture(textureAi[4]);
                            spriteAi[4].setPosition(100, 100);
                            std::cout << "----------" << std::endl;
                            std::cout << "Twoj ruch: " << std::endl;
                            //jesli wygrala ai zakoncz rozgrywje
                            victory = board.check();
                            if (victory == -10)
                            {
                                std::cout << "Przykro mi przegrales ze sztuczna inteligencja !!!" << std::endl;
                            }
                        }
                        if (aiMove.row == 2 && aiMove.col == 1)
                        {
                            textureAi[5].loadFromFile("images/kolo.png");
                            spriteAi[5].setTexture(textureAi[5]);
                            spriteAi[5].setPosition(100, 200);
                            std::cout << "----------" << std::endl;
                            std::cout << "Twoj ruch: " << std::endl;
                            //jesli wygrala ai zakoncz rozgrywje
                            victory = board.check();
                            if (victory == -10)
                            {
                                std::cout << "Przykro mi przegrales ze sztuczna inteligencja !!!" << std::endl;
                            }
                        }
                        if (aiMove.row == 0 && aiMove.col == 2)
                        {
                            textureAi[6].loadFromFile("images/kolo.png");
                            spriteAi[6].setTexture(textureAi[6]);
                            spriteAi[6].setPosition(200, 0);
                            std::cout << "----------" << std::endl;
                            std::cout << "Twoj ruch: " << std::endl;
                            //jesli wygrala ai zakoncz rozgrywje
                            victory = board.check();
                            if (victory == -10)
                            {
                                std::cout << "Przykro mi przegrales ze sztuczna inteligencja !!!" << std::endl;
                            }
                        }
                        if (aiMove.row == 1 && aiMove.col == 2)
                        {
                            textureAi[7].loadFromFile("images/kolo.png");
                            spriteAi[7].setTexture(textureAi[7]);
                            spriteAi[7].setPosition(200, 100);
                            std::cout << "----------" << std::endl;
                            std::cout << "Twoj ruch: " << std::endl;
                            //jesli wygrala ai zakoncz rozgrywje
                            victory = board.check();
                            if (victory == -10)
                            {
                                std::cout << "Przykro mi przegrales ze sztuczna inteligencja !!!" << std::endl;
                            }
                        }
                        if (aiMove.row == 2 && aiMove.col == 2)
                        {
                            textureAi[8].loadFromFile("images/kolo.png");
                            spriteAi[8].setTexture(textureAi[8]);
                            spriteAi[8].setPosition(200, 200);
                            std::cout << "----------" << std::endl;
                            std::cout << "Twoj ruch: " << std::endl;
                            //jesli wygrala ai zakoncz rozgrywje
                            victory = board.check();
                            if (victory == -10)
                            {
                                std::cout << "Przykro mi przegrales ze sztuczna inteligencja !!!" << std::endl;
                            }
                        }
                    }
                }
            }
            //rysowanie planszy 
            window.clear(sf::Color(0, 0, 0));
            for (int i = 0; i < count; i++)
                window.draw(sprite[i]);
            for (int i = 0; i < count; i++)
                window.draw(spritePlayer[i]);
            for (int i = 0; i < count; i++)
                window.draw(spriteAi[i]);

            window.display();
        }
    }
    // usuwamy dynamicznie zaalokowane obiekty
    delete[] texture;
    delete[] textureAi;
    delete[] texturePlayer;
    delete[] sprite;
    delete[] spriteAi;
    delete[] spritePlayer;
}