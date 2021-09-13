#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
    vector<int> leaders;
    int max = -1;
    int n = 0;
    int nLeaders = 0;

    while (n <= 0)
    {
        cout << "Please insert the number of elements in your array "
             << "The number must be greater than 0." << endl;
        cin >> n;
    }
    int input[n];

    cout << "Please input " << n << " element(s) one at a time." << endl;
    //Initialize the array
    for (int i = 0; i < n; i++)
    {
        cin >> input[i];
    }

    //Iterate over the array backwards, comparing each member against the current max
    // and eventually updating max when a new maximum is found.
    for (int i = n - 1; i >= 0; i--)
    {
        if (input[i] >= max)
        {
            leaders.push_back(input[i]);
            max = input[i];
            nLeaders++;
        }
    }

    //Optional, just to have the leaders in the order they appear in the original array.
    reverse(leaders.begin(), leaders.end());

    cout << "The leaders are: ";
    for (int i = 0; i < nLeaders; i++)
    {
        cout << leaders[i] << " ";
    }
    cout << endl;

    return 0;
}