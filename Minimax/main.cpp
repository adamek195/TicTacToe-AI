#include <stdlib.h>
#include <algorithm>
#include <iostream>

//wartosci poczatkowe alfa i beta
const int MAX = 1000;
const int MIN = -1000;

//implementacja funkcji minimax
//dla aktualnego gracza ( poczatkowo wywolywany jest korzen i maximizer)

int minimax(int depth, int nodeIndex, bool maximizingPlayer, int values[], int alpha, int beta)
{
    //stan koncowy to znaczy
    //ze ukonczono wezel koncowy
    if(depth == 3)
        return values[nodeIndex];
    if(maximizingPlayer)
    {
        int best = MIN;
        //powracanie dla lewych
        //i prawych dzieci
        for(int i = 0; i < 2; i++)
        {
            int val = minimax(depth+1, nodeIndex*2+i, false,values,alpha, beta);
            best = std::max(best,val);
            alpha = std::max(alpha,best);

            //przycinanie alfa beta
            if(beta <= alpha)
                break;
        }
        return best;
    }
    else
    {
        int best = MAX;
        //powracanie dla lewych i prawych dzieci
        for(int i = 0; i < 2; i++)
        {
            int val = minimax(depth+1, nodeIndex*2+i,true,values,alpha,beta);
            best = std::min(best,val);
            beta = std::min(beta,best);

            //przycinanie alfa-beta
            if(beta <= alpha)
                break;
        }
        return best;
    }
}

int main()
{
    int values[9] = {1,3,2,-1,1,2,4,2,-1};
    std::cout << "the optimal value is :" << minimax(0,0,false,values,MIN,MAX) << std::endl;
    return 0;
}