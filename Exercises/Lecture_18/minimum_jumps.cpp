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

int computeJumps(int elems[], int n)
{
    if(n < 1) return 0;

    int results[n];
    fill(results, results+n, -1);
    results[0] = 0;

    for(int i = 0; i < n; i++)
    {
        int el = elems[i];
        for(int j = 1; j <= el && i+j < n; j++)
        {
            if((results[i] > -1 && results[i+j] == -1) || results[i+j] > results[i] + 1)
                results[i+j] = results[i] + 1;
        }
    }

    return results[n-1];
}