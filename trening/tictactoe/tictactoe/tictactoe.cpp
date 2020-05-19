#include <iostream>
#include <algorithm>
#include <vector>

#define MAX 1000
#define MIN -1000

//struktura opisujaca ruch ai
struct Move
{
    int row, col;
};

//funkcja zwraca ruchy jesli na tablicy zostaly ruchy
// zwraca falsz jesli nie ma juz zadnych ruchow
bool isMovesLeft(std::vector<std::vector<char>>& board)
{
    for (int i = 0; i < board.size(); i++)
    {
        for (int j = 0; j < board[i].size(); j++)
        {
            if (board[i][j] == 'n')
            {
                return true;
            }
        }
    }
    return false;
}

//funkcja inicjalizujaca plansze
void initalizeBoard(std::vector<std::vector<char>>& board, int size)
{
    for (int i = 0; i < size; i++)
    {
        board.push_back(std::vector<char>());
        for (int j = 0; j < size; j++)
            board[i].push_back('n');
    }
}

//funkcja wypisujaca stan planszy
void printfBoard(std::vector<std::vector<char>>& board)
{
    for (int i = 0; i < board.size(); i++)
    {
        for (int j = 0; j < board[i].size(); j++)
        {
            std::cout << board[i][j] << " ";
        }
        std::cout << std::endl;
    }
}


//funkcja sprawdzajaca czy gra juz sie skonczyla
int check(std::vector<std::vector<char>>& board)
{
    //zmienne potrzeban do obslugi
    int playerWin = 0;
    int aiWin = 0;

    //sprawdzenie wierszow czy wygral gracz czy ai
    for (int row = 0; row < board.size(); row++)
    {
        //sprawdzamy czy w konketnym wierszu wygral gracz
        for (int j = 0; j < board[row].size(); j++)
        {
            if (board[row][j] == 'x')
                playerWin++; // zlczamy pola rowne x
        }
        //jesli jest tyle samo pol x co mozliwych wtedy wygral gracz
        if (playerWin == board[row].size())
            return 10;
        //zerujemy dane dla konkretnego wiersza
        playerWin = 0;

        //sprawdzamy czy wygrala ai
        for (int j = 0; j < board[row].size(); j++)
        {
            if (board[row][j] == 'o')
                aiWin++;
        }
        //jesli jest tyle samo pol o co mozliwych wtedy wygrala ai
        if (aiWin == board[row].size())
            return -10;
        //zerujemy dane dla konkretnego wiersza dla ai    
        aiWin = 0;
    }

    //sprawdzamy kolumny czy wygral gracz czy ai
    for (int col = 0; col < board.size(); col++)
    {
        //sprawdzamy czy wygral gracz
        for (int j = 0; j < board[col].size(); j++)
        {
            if (board[j][col] == 'x')
                playerWin++;
        }
        //jesli jest tyle samo mozliwych pol wtedy wygrala ai
        if (playerWin == board[col].size())
            return 10;
        //zerujemy dane dla konkretnej kolumny dla gracza    
        playerWin = 0;

        //sprawdzamy czy wygrala ai
        for (int j = 0; j < board[col].size(); j++)
        {
            if (board[j][col] == 'o')
                aiWin++;
        }
        if (aiWin == board[col].size())
            return -10;
        //zerujemy dane dla konkretnej kolumny dla ai   
        aiWin = 0;
    }

    //sprawdzamy w macierzy rzedy diagonalne czy wygral gracz czy ai
    for (int i = 0; i < board.size(); i++)
    {
        if (board[i][i] == 'x')
            playerWin++;
        if (board[i][i] == 'o')
            aiWin++;
    }
    //sprawdzamy czy wygral gracz
    if (playerWin == board.size())
        return 10;
    //zerujemy dane dla konkretnej kolumny dla gracza    
    playerWin = 0;

    //sprawdzamy czy wygral ai    
    if (aiWin == board.size())
        return -10;
    //zerujemy dane dla konkretnej kolumny dla ai   
    aiWin = 0;

    //zmienne potrzebne do oblugi tego warunku
    int t = 1;
    int w = 1;
    //sprawdzamy w macierzy rzedy diagonalne czy wygral gracz czy ai
    for (int i = 0; i < board.size(); i++)
    {
        if (board[i][board.size() - (t++)] == 'x')
            playerWin++;
        if (board[i][board.size() - (w++)] == 'o')
            aiWin++;
    }
    //sprawdzamy czy wygral gracz
    if (playerWin == board.size())
        return 10;
    //zerujemy dane dla konkretnej kolumny dla gracza    
    playerWin = 0;

    //sprawdzamy czy wygral ai    
    if (aiWin == board.size())
        return -10;
    //zerujemy dane dla konkretnej kolumny dla ai   
    aiWin = 0;

    //jesli nikt nie wygral i jest remis zwroc 0
    return 0;
}

//implementacja funkcji minimax, bierze pod uwage
//wszystkie mozliwe sposoby, w jakie moze przebiegac gra i zwraca wartosc planszy
int minimax(std::vector<std::vector<char>>& board, int nodeIndex, int depth, bool isMax, int alpha, int beta)
{
    if (nodeIndex == 3)
        return 0;

    int score = check(board);
    //jesli gracz wygral gre,zwroc jego oczekiwany wynik
    if (score == 10)
        return score;
    //jesli ai wygralo gre zwroc jej oczekiwany wynik    
    if (score == -10)
        return score;
    //jesli nie ma zwyciezcy i nie ma ruchow jest remis
    if (isMovesLeft(board) == false)
        return 0;

    //jesli jest ruch gracza
    if (isMax)
    {
        int best = MIN;
        //przejscie przez cala plansze
        for (int i = 0; i < board.size(); i++)
        {
            for (int j = 0; j < board[i].size(); j++)
            {
                if (board[i][j] == 'n')
                {
                    board[i][j] = 'x';
                    //wywoluj minimax rekurencyjnie i wybierz maksymalna wartosc
                    //wybierz najwieksza wartosc sprawdzajac co zrobi przeciwnik
                    best = std::max(best, minimax(board, nodeIndex * 2 + i, depth + 1, !isMax, alpha, beta));

                    //cofnij ruch
                    board[i][j] = 'n';

                    //ciecie alpha beta
                    alpha = std::max(alpha, best);
                    if (beta <= alpha)
                        break;
                }
            }
        }
        return best;
    }
    //jesli jest ruch ai
    else
    {
        int best = MAX;
        //przejscie przez cala plansze
        for (int i = 0; i < board.size(); i++)
        {
            for (int j = 0; j < board[i].size(); j++)
            {
                //sprawdz czy jest pusta
                if (board[i][j] == 'n')
                {
                    //zrob ruch
                    board[i][j] = 'o';
                    //wywoluj minimax rekursywnie i wybierz najmniejsza wartosc
                    //sprawdzamy co zrobi przeciwnik
                    best = std::min(best, minimax(board, nodeIndex * 2 + i, depth + 1, !isMax, alpha, beta));

                    //cofnij ruch
                    board[i][j] = 'n';

                    //ciecie alpha beta
                    beta = std::min(beta, best);
                    if (beta <= alpha)
                        break;
                }
            }
        }
        return best;
    }
}

//znajdowanie najlepszej drogi dla przez ai
Move findBestMove(std::vector<std::vector<char>>& board)
{
    int bestVal = -1000;
    Move bestMove;
    bestMove.row = -1;
    bestMove.col = -1;
    //przemierzamy wszsytkie puste pola i oceniamy funkcja minimax dla wszystkich
    //pustych komorek i zwroc komrke z optymalna wartoscia
    for (int i = 0; i < board.size(); i++)
    {
        for (int j = 0; j < board[i].size(); j++)
        {
            //sprawdz czy obecna komorka jest pusta
            if (board[i][j] == 'n')
            {
                board[i][j] = 'o';
                //liczy funkcje oceny dla tego ruchu
                int moveVal = minimax(board, 0, 0, true, MIN, MAX);
                //cofnij ruch
                board[i][j] = 'n';
                //jesli obecna wartosc jest lepsza niz najlepsza to zaaktualizuj
                if (moveVal > bestVal)
                {
                    bestMove.row = i;
                    bestMove.col = j;
                    bestVal = moveVal;
                }
            }
        }
    }
    return bestMove;
}


//funkcja pozwalajaca wykonac ruch na planszy graczowi
void playerMove(std::vector<std::vector<char>>& board)
{
    int col = 0;
    int row = 0;
    std::cout << "Podaj wiersz ktory chcesz wybrac: ";
    std::cin >> row;
    std::cout << "Podaj kolumne ktora chcesz wybrac: ";
    std::cin >> col;
    if (row <= board.size() - 1 && row >= 0 && col <= board.size() - 1 && col >= 0)
    {
        //przypisanie do tablicy znaku gracza
        if (board[row][col] == 'n')
            board[row][col] = 'x';
        else
        {
            std::cout << " te pole jest juz zajete!!!" << std::endl;
            playerMove(board);
        }
    }
    else
    {
        std::cout << "Wyszedles poza zakres!!!" << std::endl;
        playerMove(board);
    }

}

//funkcja pozwalajaca wykonac ruch na planszy sztucznej inteligencji
void aiMove(std::vector<std::vector<char>>& board)
{
    Move bestMove = findBestMove(board);
    int row = bestMove.row;
    int col = bestMove.col;
    if (board[row][col] == 'n')
        board[row][col] = 'o';
    else
        std::cout << " te pole jest juz zajete!!!" << std::endl;
}

//funkcja imitujaca gre w kolko i krzyzk
void game(std::vector<std::vector<char>>& board)
{
    //zmienna sprawdzajaca czy ktos wygral
    int victory;
    //wykonuj dopoki zostaja wolne miejsca w grze
    while (isMovesLeft(board))
    {
        std::cout << "----------" << std::endl;
        std::cout << "Twoj ruch: " << std::endl;

        //jesli sa wolne miejsca na planszy gracz moze wykonac ruch
        if (isMovesLeft(board))
            playerMove(board);

        //jesli gracz wygral zakoncz petle
        victory = check(board);
        if (victory == 10)
        {
            std::cout << "Brawo wygrales !!!" << std::endl;
            break;
        }

        printfBoard(board);
        std::cout << "----------" << std::endl;
        std::cout << "Ruch sztucznej inteligencji: " << std::endl;

        //jesli sa wolne miejsca na planszy to ai wykonuje ruch
        if (isMovesLeft(board));
        aiMove(board);

        std::cout << "----------" << std::endl;
        printfBoard(board);

        //jesli wygrala ai zakoncz rozgrywje
        victory = check(board);
        if (victory == -10)
        {
            std::cout << "Przykro mi przegrales ze sztuczna inteligencja !!!" << std::endl;
            break;
        }
    }
    //jesli mamy remis
    if (victory == 0)
    {
        std::cout << "Remis !!!" << std::endl;;
    }
}

//glowna funkcja
int main()
{
    //tworzymy tablice do gry w kolko i krzyzyk
    std::vector<std::vector<char>> board;
    initalizeBoard(board, 3);
    game(board);
    return 0;
}