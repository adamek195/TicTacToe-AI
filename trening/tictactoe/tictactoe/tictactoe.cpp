#include <iostream>
#include <algorithm>
#include <vector>

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
        for (int j = 0; board[i].size(); j++)
            if (board[i][j] == 'n')
                return true;
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

    //sprawdzamy w macierzy rzedy diagonalne czy wygral gracz czy ai
    for (int i = 0; i < board.size(); i++)
    {
        if (board[i][board.size() - 1] == 'x')
            playerWin++;
        if (board[i][board.size() - 1] == 'o')
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
int minimax(std::vector<std::vector<char>>& board, int depth, bool isMax)
{
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
        int best = -1000;
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
                    best = std::max(best, minimax(board, depth + 1, !isMax));
                    //cofnij ruch
                    board[i][j] = 'n';
                }
            }
        }
        return best;
    }
    //jesli jest ruch ai
    else
    {
        int best = 1000;
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
                    best = std::min(best, minimax(board, depth + 1, isMax));
                    //cofnij ruch
                    board[i][j] = 'n';
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
                int moveVal = minimax(board, 0, false);
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
            std::cout << " te pole jest juz zajete!!!" << std::endl;
    }
    else
        std::cout << "Wyszedles poza zakres!!!" << std::endl;
}


int main()
{
    //tworzymy tablice do gry w kolko i krzyzyk
    std::vector<std::vector<char>> board;
    initalizeBoard(board, 3);
    printfBoard(board);

    playerMove(board);
    printfBoard(board);
    Move bestMove = findBestMove(board);
    std::cout << bestMove.row << " " << bestMove.col;

    return 0;
}