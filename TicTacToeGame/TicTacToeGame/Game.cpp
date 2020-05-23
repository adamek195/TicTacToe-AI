#include "Game.h"

//funkcja imitujaca gre w kolko i krzyzk
void game(Board& board,int size)
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
    sf::Texture *texturePlayer = new sf::Texture[count]; //zmienne beda wczytywac krzyzk gracza
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
                //dla pierwszego wiersza
                int border = 1;
                for (int i = 0; i < size; i++)
                {
                    //jesli kliknelismy myszka w przwidzianym zakresie
                    if (xMouse > i*100 && xMouse < border*100 && yMouse > 0 && yMouse < 100)
                    {
                        //jesli sa wolne miejsca na planszy gracz moze wykonac ruch
                        if (board.isMovesLeft())
                        {
                            board.playerMove(0, i);
                            board.printfBoard();
                            std::cout << "----------" << std::endl;
                            std::cout << "Ruch sztucznej inteligencji: " << std::endl;
                            texturePlayer[i].loadFromFile("images/krzyzyk.png");
                            std::cout << "Wcisnij enter aby sztuczna inteligencja wykonala ruch: " << std::endl;
                            spritePlayer[i].setTexture(texturePlayer[i]);
                            spritePlayer[i].setPosition(i*100, 0);
                        }
                        victory = board.check();
                        if (victory == 10)
                        {
                            std::cout << "Brawo wygrales !!!" << std::endl;
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
                                    windowVictory.draw(spriteWinner);
                                }
                                for (int i = 0; i < count; i++)
                                    window.draw(spritePlayer[i]);
                                window.display();
                                windowVictory.draw(spriteWinner);
                                windowVictory.display();
                            }
                        }
                    }
                    border++; // zwiekszamy granice
                }
                border = 1; // ustawiamy granice znowu na 1
                //sprawdzamy wiersz drugi
                for (int i = 0; i < size; i++)
                {
                    if (xMouse > i * 100 && xMouse < border * 100 && yMouse > 100 && yMouse < 200)
                    {
                        //jesli sa wolne miejsca na planszy gracz moze wykonac ruch
                        if (board.isMovesLeft())
                        {
                            board.playerMove(1, i);
                            board.printfBoard();
                            std::cout << "----------" << std::endl;
                            std::cout << "Ruch sztucznej inteligencji: " << std::endl;
                            std::cout << "Wcisnij enter aby sztuczna inteligencja wykonala ruch: " << std::endl;
                            texturePlayer[i + size].loadFromFile("images/krzyzyk.png");
                            spritePlayer[i + size].setTexture(texturePlayer[i + size]);
                            spritePlayer[i + size].setPosition(i * 100, 100);
                        }
                        victory = board.check();
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
                    border++; // zwiekszamy granice
                }
                border = 1; // ustawiamy znowu granice
                //sprawdzamy trzeci wiersz
                for (int i = 0; i < size; i++)
                {
                    if (xMouse > i*100 && xMouse < border*100 && yMouse > 200 && yMouse < 300)
                    {
                        //jesli sa wolne miejsca na planszy gracz moze wykonac ruch
                        if (board.isMovesLeft())
                        {
                            board.playerMove(2, i);
                            board.printfBoard();
                            std::cout << "----------" << std::endl;
                            std::cout << "Ruch sztucznej inteligencji: " << std::endl;
                            texturePlayer[i+size*2].loadFromFile("images/krzyzyk.png");
                            spritePlayer[i + size * 2].setTexture(texturePlayer[i + size * 2]);
                            spritePlayer[i + size * 2].setPosition(i*100, 200);
                        }
                        victory = board.check();
                        if (victory == 10)
                        {
                            std::cout << "Brawo wygrales !!!" << std::endl;
                            std::cout << "TU sie wswitli obrazek ze wygrales smieciu" << std::endl;
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
                    border++;
                }
                border = 1; // ustawiamy wiersz na 
                //jesli mamy plansze 4 x 4
                //ustawiamy 4 wiersz
                for (int i = 0; i < size; i++)
                {
                    if (xMouse > i * 100 && xMouse < border * 100 && yMouse > 300 && yMouse < 400)
                    {
                        //jesli sa wolne miejsca na planszy gracz moze wykonac ruch
                        if (board.isMovesLeft())
                        {
                            board.playerMove(3, i);
                            board.printfBoard();
                            std::cout << "----------" << std::endl;
                            std::cout << "Ruch sztucznej inteligencji: " << std::endl;
                            std::cout << "Wcisnij enter aby sztuczna inteligencja wykona³a ruch: " << std::endl;
                            texturePlayer[i + size * 3].loadFromFile("images/krzyzyk.png");
                            spritePlayer[i + size * 3].setTexture(texturePlayer[i + size * 3]);
                            spritePlayer[i + size * 3].setPosition(i * 100, 300);
                        }
                        victory = board.check();
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
                    border++;
                }
                border = 1; // ustawiamy wiersz na 
                //jesli mamy plansze 5 x 5
                //ustawiamy 5 wiersz
                for (int i = 0; i < size; i++)
                {
                    if (xMouse > i * 100 && xMouse < border * 100 && yMouse > 400 && yMouse < 500)
                    {
                        //jesli sa wolne miejsca na planszy gracz moze wykonac ruch
                        if (board.isMovesLeft())
                        {
                            board.playerMove(4, i);
                            board.printfBoard();
                            std::cout << "----------" << std::endl;
                            std::cout << "Ruch sztucznej inteligencji: " << std::endl;
                            std::cout << "Wcisnij enter aby sztuczna inteligencja wykona³a ruch: " << std::endl;
                            texturePlayer[i + size * 4].loadFromFile("images/krzyzyk.png");
                            spritePlayer[i + size * 4].setTexture(texturePlayer[i + size * 4]);
                            spritePlayer[i + size * 4].setPosition(i * 100, 400);
                        }
                        victory = board.check();
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
                    border++;  
                }
                victory = board.check();
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
                    aiMove = board.aiMove();
                    board.printfBoard();
                    //sprawdzamy pierwszy wiersz
                    for (int i = 0; i < size; i++)
                    {
                        if (aiMove.row == i && aiMove.col == 0)
                        {
                            textureAi[i].loadFromFile("images/kolo.png");
                            spriteAi[i].setTexture(textureAi[i]);
                            spriteAi[i].setPosition(0, i*100);
                            std::cout << "----------" << std::endl;
                            std::cout << "Twoj ruch: " << std::endl;
                            //jesli wygrala ai zakoncz rozgrywje
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
                    //sprawdzamy drugi wiersz
                    for (int i = 0; i < size; i++)
                    {
                        if (aiMove.row == i && aiMove.col == 1)
                        {
                            textureAi[i+size].loadFromFile("images/kolo.png");
                            spriteAi[i+size].setTexture(textureAi[i+size]);
                            spriteAi[i+size].setPosition(100, i*100);
                            std::cout << "----------" << std::endl;
                            std::cout << "Twoj ruch: " << std::endl;
                            //jesli wygrala ai zakoncz rozgrywje
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
                    //sprawdzamy trzeci wiersz
                    for (int i = 0; i < size; i++)
                    {
                        if (aiMove.row == i && aiMove.col == 2)
                        {
                            textureAi[i+size*2].loadFromFile("images/kolo.png");
                            spriteAi[i + size * 2].setTexture(textureAi[i + size * 2]);
                            spriteAi[i + size * 2].setPosition(200, i*100);
                            std::cout << "----------" << std::endl;
                            std::cout << "Twoj ruch: " << std::endl;
                            //jesli wygrala ai zakoncz rozgrywje
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
                    //sprawdzamy 4 wiersz dla ai
                    for (int i = 0; i < size; i++)
                    {
                        if (aiMove.row == i && aiMove.col == 3)
                        {
                            textureAi[i + size * 3].loadFromFile("images/kolo.png");
                            spriteAi[i + size * 3].setTexture(textureAi[i + size * 3]);
                            spriteAi[i + size * 3].setPosition(300, i * 100);
                            std::cout << "----------" << std::endl;
                            std::cout << "Twoj ruch: " << std::endl;
                            //jesli wygrala ai zakoncz rozgrywje
                            victory = board.check();
                            if (victory == -10)
                            {
                                std::cout << "Przykro mi przegrales ze sztuczna inteligencja !!!" << std::endl;
                                windowVictory.create(sf::VideoMode(280, 135, 32), "Winner"); //okna ma wymiary 290 na 150
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
                    //sprawdzamy 5 wiersz dla ai
                    for (int i = 0; i < size; i++)
                    {
                        if (aiMove.row == i && aiMove.col == 4)
                        {
                            textureAi[i + size * 4].loadFromFile("images/kolo.png");
                            spriteAi[i + size * 4].setTexture(textureAi[i + size * 4]);
                            spriteAi[i + size * 4].setPosition(400, i * 100);
                            std::cout << "----------" << std::endl;
                            std::cout << "Twoj ruch: " << std::endl;
                            //jesli wygrala ai zakoncz rozgrywje
                            victory = board.check();
                            if (victory == -10)
                            {
                                std::cout << "Przykro mi przegrales ze sztuczna inteligencja !!!" << std::endl;
                                windowVictory.create(sf::VideoMode(280, 135, 32), "Winner"); //okna ma wymiary 290 na 150
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