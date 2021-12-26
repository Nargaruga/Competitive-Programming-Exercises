#include <iostream>

using namespace std;

struct team {
    int member1;
    int member2;
    int strength;
};
//[TODO]
int main()
{
    int n = 0;

    while(n <= 0)
    {
        cout << "Please insert the number of teams. " << 
                "The number must be greater than 0" << endl;
        cin >> n;
    }
    int strength[n][n] = {0};

    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < i; j++)
        {
            cout << "Please insert the stregth of team " << i << ", " << j << "." << endl;
            cin >> strength[i][j];
        }
    }

    for(int i = 0; i < n; i++)
    {
        for(int j = i + 1; j < n; j++)
        {
            strength[i][j] = strength[j][i];
        }
    }

    

    return 0;
}