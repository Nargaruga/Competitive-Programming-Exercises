#include <iostream>
#include <cmath>

using namespace std;

int main()
{
    int c = 0, n = 0;
    
    while( c < 1 || n < 1)
    {
        cout << "Please input the capacity and the number of elements." << endl
            << "Both number must be greater than zero." << endl;

        cin >> c;
        cin >> n;
    }

    int weights[n+1] = {0};
    int values[n+1] = {0};
    cout << "Please input weight and value for each item." << endl;
    for(int i = 1; i <= n; i++)
    {
        cin >> weights[i];
        cin >> values[i];
    }

    //Cell K[i][j] contains the answer for the subproblem with items up
    //  to the ith and capacity j
    int K[n+1][c+1];
    for(int i = 0; i <= n; i++)
    {
        for(int j = 0; j <= c; j++)
        {
            K[i][j] = 0;
        }
    }

    int spaceLeft = c;
    for(int i = 1; i <= n; i++)
    {
        for(int j = 1; j <= c; j++)
        {
            //If the current element i fits, we consider whether to leave it
            //  or pick it, based of whether the current best value we found for
            //  the current capacity, identified by K[i-1][j], is better than
            //  value[i] summed to the best profit we can get from capacity j-weight[i]
            if(weights[i] <= spaceLeft)
                K[i][j] = max(K[i-1][j], //Don't pick the ith item
                              K[i-1][j-weights[i]] + values[i]); //Pick the ith item
            else
                K[i][j] = K[i-1][j];
        }
    }

    printf("The maximum revenue is: %d.\n", K[n][c]);

    return 0;
}