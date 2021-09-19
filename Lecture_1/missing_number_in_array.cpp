#include <iostream>

using namespace std;

int main()
{
    int n = 0;

    while (n <= 0)
    {
        cout << "Please insert the number of elements in your array. "
             << "The number must be greater than 0" << endl;
        cin >> n;
    }

    int targetSum = ((n + 1) * n) / 2; //Sum of the first n + 1 natural numbers starting from 0
    int actualSum = 0;
    int input[n];

    cout << "Please input " << n - 1 << " element(s) one at a time." << endl;
    //Initialize the array
    for (int i = 0; i < n - 1; i++)
    {
        cin >> input[i];
    }

    for (int i = 0; i < n - 1; i++)
    {
        actualSum += input[i];
    }

    cout << "Il numero mancante è: " << targetSum - actualSum << endl;

    return 0;
}