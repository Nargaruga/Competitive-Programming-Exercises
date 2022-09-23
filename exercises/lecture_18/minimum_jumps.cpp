#include <iostream>
#include <climits>

using namespace std;

int computeJumps(int elems[], int n);

int main()
{
    int n = 0;

    while(n < 1)
    {
        cout << "Please input the number of elements in your array." << endl;
        cin >> n;
    }

    int elems[n];

    cout << "Please input the array's elements." << endl;
    for(int i = 0; i < n; i++)
    {
        cin >> elems[i];
    }

    int ans = computeJumps(elems, n);
    printf("The minimum number of jumps is %d\n", ans);
}

//Computes the minimum number of jumps needed to reach
//  the end of `elems`, which has length n, from the first
//  element. The maximum length of the jump from cell i
//  is elems[i].
//  Returns -1 if the end cannot be reached.
int computeJumps(int elems[], int n)
{
    if(n < 1) return 0;

    int results[n];
    fill(results, results+n, -1);
    results[0] = 0;

    //For each cell...
    for(int i = 0; i < n; i++)
    {
        int el = elems[i];
        //...consider all of the potential destinations...
        for(int j = 1; j <= el && i+j < n; j++)
        {
            //...and see if the current cell is the best way to reach it (for now)
            if((results[i] > -1 && results[i+j] == -1) || results[i+j] > results[i] + 1)
                results[i+j] = results[i] + 1;
        }
    }

    return results[n-1];
}