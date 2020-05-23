#include "Board.h"

//funkcja zwraca ruchy jesli na tablicy zostaly ruchy
// zwraca falsz jesli nie ma juz zadnych ruchow
bool Board::isMovesLeft()
{
    for (int i = 0; i < this->board.size(); i++)
    {
        for (int j = 0; j < this->board[i].size(); j++)
        {
            if (this->board[i][j] == 'n')
            {
                return true;
            }
        }
    }
    return false;
}

//funkcja wypisujaca stan planszy
void Board::printfBoard()
{
    for (int i = 0; i < this->board.size(); i++)
    {
        for (int j = 0; j < this->board[i].size(); j++)
        {
            std::cout << this->board[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

//funkcja sprawdzajaca czy gra juz sie skonczyla
int Board::check()
{
    //zmienne potrzeban do obslugi
    int playerWin = 0;
    int aiWin = 0;
    int nextIndex = 0;
    int previousIndex = 0;
    //sprawdzenie wierszow czy wygral gracz czy ai
    for (int row = 0; row < this->board.size(); row++)
    {
        //sprawdzamy czy w konketnym wierszu wygral gracz
        for (int j = 0; j < this->board[row].size(); j++)
        {
            nextIndex = j + 1;
            previousIndex = j - 1;
            //sprawdzamy warunki koncowe
            if (previousIndex == -1)
            {
                if (this->board[row][j] == 'x' && this->board[row][nextIndex] == 'x' && this->board[row][nextIndex+1] == 'x')
                    playerWin++;
            }
            else if (nextIndex == board.size())
            {
                if(this->board[row][j] == 'x' && this->board[row][previousIndex] == 'x' && this->board[row][previousIndex-1] == 'x')
                    playerWin++;
            }
            else if (this->board[row][j] == 'x' && (this->board[row][nextIndex] == 'x' || this->board[row][previousIndex] == 'x'))
                playerWin++; // zlczamy pola rowne x
       
        }
        //jesli jest tyle samo pol x co mozliwych wtedy wygral gracz
        if (playerWin >= this->sign)
            return 10;
        //zerujemy dane dla konkretnego wiersza
        playerWin = 0;
        nextIndex = 0;
        previousIndex = 0;
        //sprawdzamy czy wygrala ai
        for (int j = 0; j < this->board[row].size(); j++)
        {
            nextIndex = j + 1;
            previousIndex = j - 1;
            if (previousIndex == -1)
            {
                if(this->board[row][j] == 'o' && this->board[row][nextIndex] == 'o' && this->board[row][nextIndex+1] == 'o')
                    aiWin++;
            }
            else if (nextIndex == board.size())
            {
                if(this->board[row][j] == 'o' && this->board[row][previousIndex] == 'o' && this->board[row][previousIndex-1] == 'o')
                    aiWin++;
            }
            else if (this->board[row][j] == 'o' && (this->board[row][nextIndex] == 'o' || this->board[row][previousIndex] == 'o'))
                 aiWin++;
        }
        //jesli jest tyle samo pol o co mozliwych wtedy wygrala ai
        if (aiWin >= this->sign)
            return -10;
        //zerujemy dane dla konkretnego wiersza dla ai    
        aiWin = 0;
        nextIndex = 0;
        previousIndex = 0;
    }

    //sprawdzamy kolumny czy wygral gracz czy ai
    for (int col = 0; col < this->board.size(); col++)
    {
        //sprawdzamy czy wygral gracz
        for (int j = 0; j < this->board[col].size(); j++)
        {
            nextIndex = j + 1;
            previousIndex = j - 1;
            //sprawdzamy warunek koncowy zeby nie wyjsc poza zakres 
            if (previousIndex == -1)
            {
                if (this->board[j][col] == 'x' && this->board[nextIndex][col] == 'x' && this->board[nextIndex+1][col] == 'x')
                    playerWin++;
            }
            else if (nextIndex == board.size())
            {
                if (this->board[j][col] == 'x' && this->board[previousIndex][col] == 'x' && this->board[previousIndex-1][col] == 'x')
                    playerWin++;
            }
            else if (this->board[j][col] == 'x' && (this->board[nextIndex][col] == 'x' || this->board[previousIndex][col] == 'x'))
               playerWin++;
        }
        //jesli jest tyle samo mozliwych pol wtedy wygrala ai
        if (playerWin >= this->sign)
            return 10;
        //zerujemy dane dla konkretnej kolumny dla gracza    
        playerWin = 0;
        nextIndex = 0;
        previousIndex = 0;

        //sprawdzamy czy wygrala ai
        for (int j = 0; j < this->board[col].size(); j++)
        { 
            nextIndex = j + 1;
            previousIndex = j - 1;
            //sprawdzamy warunek koncowy zeby nie wyjsc poza zakres 
            if (previousIndex == -1)
            {
                if (this->board[j][col] == 'o' && this->board[nextIndex][col] == 'o' && this->board[nextIndex+1][col] == 'o')
                    aiWin++;
            }
            else if (nextIndex == board.size())
            {
                if (this->board[j][col] == 'o' && this->board[previousIndex][col] == 'o' && this->board[previousIndex-1][col] == 'o')
                    aiWin++;
            }
            else if (this->board[j][col] == 'o' && (this->board[nextIndex][col] == 'o' || this->board[previousIndex][col] == 'o'))
                    aiWin++;
        }
        if (aiWin >= this->sign)
            return -10;
        //zerujemy dane dla konkretnej kolumny dla ai   
        aiWin = 0;
    }

    //sprawdzamy w macierzy rzedy diagonalne czy wygral gracz czy ai
    for (int i = 0; i < this->board.size(); i++)
    {
        //sprawdzamy warunek koncowy zeby nie wyjsc poza zakres 
        nextIndex = i + 1;
        previousIndex = i - 1;
        //sprawdamy warunek poczatkowy zeby nie wyjsc poza zakres tablicy
        if (previousIndex == -1)
        {
            if(this->board[i][i] == 'x' && this->board[nextIndex][nextIndex] == 'x' && this->board[nextIndex+1][nextIndex+1] == 'x')
                playerWin++;
            if(this->board[i][i] == 'o' && this->board[nextIndex][nextIndex] == 'o' && this->board[nextIndex+1][nextIndex+1] == 'o')
                aiWin++;
        }
        else if (nextIndex == board.size())
        {
            if (this->board[i][i] == 'x' && this->board[previousIndex][previousIndex] == 'x' && this->board[previousIndex-1][previousIndex-1] == 'x')
                playerWin++;
            if (this->board[i][i] == 'o' && this->board[previousIndex][previousIndex] == 'o' && this->board[previousIndex-1][previousIndex-1] == 'o')
                aiWin++;
        }
        else if (this->board[i][i] == 'x' && (this->board[nextIndex][nextIndex] == 'x' || this->board[previousIndex][previousIndex] == 'x'))
            playerWin++;
        else if (this->board[i][i] == 'o' && (this->board[nextIndex][nextIndex] == 'o' || this->board[previousIndex][previousIndex] == 'o'))
            aiWin++;
    }
    //sprawdzamy czy wygral gracz
    if (playerWin >= this->sign)
        return 10;
    //zerujemy dane dla konkretnej kolumny dla gracza    
    playerWin = 0;
    nextIndex = 0;
    previousIndex = 0;

    //sprawdzamy czy wygral ai    
    if (aiWin == this->sign)
        return -10;
    //zerujemy dane dla konkretnej kolumny dla ai   
    aiWin = 0;

    //zmienne potrzebne do oblugi tego warunku
    int t = 1;
    int w = 1;
    //sprawdzamy w macierzy rzedy diagonalne czy wygral gracz czy ai
    for (int i = 0; i < this->board.size(); i++)
    {
        nextIndex = i + 1;
        previousIndex = i - 1;
        if (previousIndex == -1)
        {
            if(this->board[i][board.size() - (t)] == 'x' && this->board[nextIndex][board.size() - (t + 1)] == 'x' && this->board[nextIndex+1][board.size() - (t + 2)] == 'x')
                playerWin++;
            if(this->board[i][board.size() - (w)] == 'o' && this->board[nextIndex][board.size() - (w + 1)] == 'o' && this->board[nextIndex+1][board.size() - (w + 2)] == 'o')
                aiWin++;
        }
        else if (nextIndex == board.size())
        {
            if (this->board[i][board.size() - (t)] == 'x' && this->board[previousIndex][board.size() - (t - 1)] == 'x' && this->board[previousIndex][board.size() - (t - 2)] == 'x')
                playerWin++;
            if (this->board[i][board.size() - (w)] == 'o' && this->board[previousIndex][board.size() - (w - 1)] == 'o' && this->board[previousIndex][board.size() - (w - 2)] == 'o')
                aiWin++;
        }
        else if (this->board[i][board.size() - (t)] == 'x' && (this->board[nextIndex][board.size() - (t + 1)] == 'x' || this->board[previousIndex][board.size() - (t - 1)] == 'x'))
            playerWin++;
        else if (this->board[i][board.size() - (w)] == 'o' && (this->board[nextIndex][board.size() - (w + 1)] == 'o' || this->board[previousIndex][board.size() - (w - 1)] == 'o'))
            aiWin++;
        w++;
        t++;
    }
    //sprawdzamy czy wygral gracz
    if (playerWin >= this->sign)
        return 10;
    //zerujemy dane dla konkretnej kolumny dla gracza    
    playerWin = 0;
    nextIndex = 0;
    previousIndex = 0;

    //sprawdzamy czy wygral ai    
    if (aiWin >= this->sign)
        return -10;
    //zerujemy dane dla konkretnej kolumny dla ai   
    aiWin = 0;

    //jesli nikt nie wygral i jest remis zwroc 0
    return 0;
}

//funkcja zwracajaca rozmiar planszy
int Board::getSizeOfBoard()
{
    return this->board.size();
}

//funkcja zwracajaca rozmiar poszczegolnego wiersza na planszy
int Board::getSizeOfBoardRow(int row)
{
    return this->board[row].size();
}

//funkcja zwraca konkretny element na planszy
char Board::getElement(int i, int j)
{
    return this->board[i][j];
}

void Board::setElement(int i, int j, char element)
{
    this->board[i][j] = element;
}

//implementacja funkcji minimax, bierze pod uwage
//wszystkie mozliwe sposoby, w jakie moze przebiegac gra i zwraca wartosc planszy
int Board::minimax(int depth, bool isMax, int alpha, int beta)
{
    //zeby skrocic czas obliczen komputera
    if (depth == 7)
        return 0;

    int score = check();
    //jesli gracz wygral gre,zwroc jego oczekiwany wynik
    if (score == 10)
        return score;

    //jesli ai wygralo gre zwroc jej oczekiwany wynik    
    if (score == -10)
        return score;

    //jesli nie ma zwyciezcy i nie ma ruchow jest remis
    if (isMovesLeft() == false)
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
                    best = std::max(best, minimax(depth + 1, !isMax, alpha, beta));

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
                    best = std::min(best, minimax(depth + 1, !isMax, alpha, beta));

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
Move Board::findBestMove()
{
    int bestVal = MAX;
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
                int moveVal = minimax(0, true, MIN, MAX);
                //cofnij ruch
                board[i][j] = 'n';
                //jesli obecna wartosc jest lepsza niz najlepsza to zaaktualizuj
                if (moveVal < bestVal)
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
void Board::playerMove(int row,int col)
{
    if (row <= board.size() - 1 && row >= 0 && col <= board.size() - 1 && col >= 0)
    {
        //przypisanie do tablicy znaku gracza
        if (board[row][col] == 'n')
            board[row][col] = 'x';
        else
        {
            std::cout << " te pole jest juz zajete!!!" << std::endl;
        }
    }
    else
    {
        std::cout << "Wyszedles poza zakres!!!" << std::endl;
    }

}


//funkcja pozwalajaca wykonac ruch na planszy sztucznej inteligencji
Move Board::aiMove()
{
    Move bestMove = findBestMove();
    int row = bestMove.row;
    int col = bestMove.col;
    if (this->board[row][col] == 'n')
        this->board[row][col] = 'o';
    else
        std::cout << " te pole jest juz zajete!!!" << std::endl;
    return bestMove;
}
