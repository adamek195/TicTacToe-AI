#include "Game.h"

//funkcja imitujaca gre w kolko i krzyzk
void game(Board& board, int size)
{
    //tworzymy glowne okno gdzie bedzie wyswietlana gra TicTacToe
    sf::RenderWindow window; // zmienna 2D renderuje nam klase typu Render Window
    sf::RenderWindow windowVictory; // okno ktore bedzie wyswietlac o koncu gry
    window.create(sf::VideoMode(size*100, size*100, 32), "TicTacToe"); //okna ma wymiary 300 na 300
    window.setActive(true); // ustaw focus na okno
    window.setFramerateLimit(60);

    //zmienna wyswietli nam liczbe elemntow na planszy
    int count = (size*size);

    // tworzymy zdarzenie potrzebne do obslugi graficznej gry
    sf::Event event; // zmienna event ktora bedzie rejestrowac jakies wydarzenie myszki lub klawiatury
    sf::Texture textureWinner; // zmienna bedzie pokazywac zwyciezce
    sf::Texture *texture = new  sf::Texture[count]; //zmienne beda wczytywac kwadraty
    sf::Texture *texturePlayer = new sf::Texture[count]; //zmienne beda wczytywac krzyzyk gracza
    sf::Texture *textureAi = new sf::Texture[count]; //zmienne beda wczytywac  gracza

    //tworzymy obiekty ktore beda sie wyswietlac na planszy
    sf::Sprite spriteWinner; // zmienna bedzie pokazywac kto wygral
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

    //ustawiamy pozycje kwadratow na planszy
    for (int j = 0; j < size; j++)
    {
        for (int i = 0; i < size; i++)
        {
            sprite[i+size*j].setPosition(100 * i, 100 * j);
        }
    }
  
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
                //pobieramy wspolrzedne od naszej myszy
                xMouse = sf::Mouse::getPosition(window).x;
                yMouse = sf::Mouse::getPosition(window).y;

                //zmienne ktore beda ograniczac zakres myszki odpowednio dla wspolrzednych x i y
                int borderx = 1;
                int bordery = 1;
                //sprawdzamy wszystkie mozliwosci wykonania naszego ruchu
                for (int j = 0; j < size; j++)
                {
                    for (int i = 0; i < size; i++)
                    {
                        //jesli kliknelismy myszka w przwidzianym zakresie ustaw nasz ruch
                        if (xMouse > i * 100 && xMouse < borderx * 100 && yMouse > j*100 && yMouse < bordery *100)
                        {
                            //jesli sa wolne miejsca na planszy gracz moze wykonac ruch
                            if (board.isMovesLeft())
                            {
                                board.playerMove(j, i); //ustaw nasz ruch na plnaszy
                                board.printfBoard(); //wyswietl w konsoli komunikat z zaznaczonym ruchem
                                std::cout << "----------" << std::endl;
                                std::cout << "Ruch sztucznej inteligencji: " << std::endl;
                                texturePlayer[i + size*j].loadFromFile("images/krzyzyk.png");
                                std::cout << "Wcisnij enter aby sztuczna inteligencja wykonala ruch: " << std::endl;
                                spritePlayer[i + j*size].setTexture(texturePlayer[i + j*size]);
                                spritePlayer[i + j*size].setPosition(i * 100, j*100);
                            }
                            victory = board.check();
                            //jest wykonany ruch jest zwyciezki wyswietl komunikat
                            if (victory == 10)
                            {
                                std::cout << "Brawo wygrales !!!" << std::endl;
                                windowVictory.create(sf::VideoMode(290, 135, 32), "Winner"); //okna ma wymiary 290 na 150
                                windowVictory.setActive(true); // ustaw focus na okno
                                windowVictory.setFramerateLimit(60);
                                textureWinner.loadFromFile("images/wygrana.png");
                                spriteWinner.setTexture(textureWinner);
                                spriteWinner.setPosition(0, 0);
                                //wyswietlamy komunikat w nowym oknie
                                while (windowVictory.isOpen())
                                {
                                    while (windowVictory.pollEvent(event))
                                    {
                                        //zakonczenie gry wcisnieciem escape lub zamknieciem okna
                                        if (event.type == sf::Event::Closed || (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)))
                                            windowVictory.close();
                                    }
                                    for (int i = 0; i < count; i++)
                                        window.draw(spritePlayer[i]);
                                    window.display();
                                    windowVictory.draw(spriteWinner);
                                    windowVictory.display();
                                }
                            }
                        }
                        borderx++; // zwiekszamy granice dla wspolrzednych x
                    }
                    borderx = 1; // ustawiamy granice znowu na 1
                    bordery++; // zwiekszamy granice dla wspolrzednych y
                }
                bordery = 1; 
                victory = board.check();
                //jesli mamy remis
                if (victory == 0 && board.isMovesLeft() == false)
                {
                    std::cout << "Remis!!!" << std::endl;
                    windowVictory.create(sf::VideoMode(290, 135, 32), "Winner"); //okna ma wymiary 290 na 150
                    windowVictory.setActive(true); // ustaw focus na okno
                    windowVictory.setFramerateLimit(60);
                    textureWinner.loadFromFile("images/remis.png");
                    spriteWinner.setTexture(textureWinner);
                    spriteWinner.setPosition(0, 0);
                    while (windowVictory.isOpen())
                    {
                        while (windowVictory.pollEvent(event))
                        {
                            //zakonczenie gry wcisnieciem escape lub zamknieciem okna
                            if (event.type == sf::Event::Closed || (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)))
                                windowVictory.close();
                        }
                        for (int i = 0; i < count; i++)
                            window.draw(spritePlayer[i]);
                        window.display();
                        windowVictory.draw(spriteWinner);
                        windowVictory.display();
                    }
                }
            }
            //jesli zostanie wycisniety klawisz enter to ruch wykonac ma ai
            if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Enter)
            {
                //jesli sa wolne miejsca na planszy to ai wykonuje ruch
                if (board.isMovesLeft())
                {
                    aiMove = board.aiMove(); // wybieramy najlepszy ruch na planszy dla Ai
                    board.printfBoard(); //deukujemy plansze po ruchu Ai
                    //zaznaczamy ruch na plnaszy Ai
                    for (int j = 0; j < size; j++)
                    {
                        for (int i = 0; i < size; i++)
                        {
                            if (aiMove.row == i && aiMove.col == j)
                            {
                                textureAi[i + j*size].loadFromFile("images/kolo.png");
                                spriteAi[i + j*size].setTexture(textureAi[i + j *size]);
                                spriteAi[i + j*size].setPosition(j * 100, i * 100);
                                std::cout << "----------" << std::endl;
                                std::cout << "Twoj ruch: " << std::endl;
                                //jesli wygrala ai zakoncz rozgrywke
                                victory = board.check();
                                if (victory == -10)
                                {
                                    std::cout << "Przykro mi przegrales ze sztuczna inteligencja !!!" << std::endl;
                                    windowVictory.create(sf::VideoMode(290, 135, 32), "Winner"); //okna ma wymiary 290 na 150
                                    windowVictory.setActive(true); // ustaw focus na okno
                                    windowVictory.setFramerateLimit(60);
                                    textureWinner.loadFromFile("images/przegrana.png");
                                    spriteWinner.setTexture(textureWinner);
                                    spriteWinner.setPosition(0, 0);
                                    while (windowVictory.isOpen())
                                    {
                                        while (windowVictory.pollEvent(event))
                                        {
                                            //zakonczenie gry wcisnieciem escape lub zamknieciem okna
                                            if (event.type == sf::Event::Closed || (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)))
                                                windowVictory.close();
                                        }
                                        for (int i = 0; i < count; i++)
                                            window.draw(spriteAi[i]);
                                        window.display();
                                        windowVictory.draw(spriteWinner);
                                        windowVictory.display();
                                    }
                                }
                            }
                        }
                    }
                    //jesli mamy remis 
                    victory = board.check();
                    if (victory == 0 && board.isMovesLeft() == false)
                    {
                        std::cout << "Remis!!!" << std::endl;
                        windowVictory.create(sf::VideoMode(280, 135, 32), "Winner"); //okna ma wymiary 290 na 150
                        windowVictory.setActive(true); // ustaw focus na okno
                        windowVictory.setFramerateLimit(60);
                        textureWinner.loadFromFile("images/remis.png");
                        spriteWinner.setTexture(textureWinner);
                        spriteWinner.setPosition(0, 0);
                        while (windowVictory.isOpen())
                        {
                            while (windowVictory.pollEvent(event))
                            {
                                //zakonczenie gry wcisnieciem escape lub zamknieciem okna
                                if (event.type == sf::Event::Closed || (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)))
                                    windowVictory.close();
                            }
                            for (int i = 0; i < count; i++)
                                window.draw(spriteAi[i]);
                            window.display();
                            windowVictory.draw(spriteWinner);
                            windowVictory.display();
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
    // usuwamy dynamicznie zaalokowane obiekty
    delete[] texture;
    delete[] textureAi;
    delete[] texturePlayer;
    delete[] sprite;
    delete[] spriteAi;
    delete[] spritePlayer;
}