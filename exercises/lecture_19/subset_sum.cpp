#include <iostream>

using namespace std;

int main()
{
    int n = 0;

    while(n < 1)
    {
        cout << "Please input the number of elements in the array." << endl;
        cin >> n;
    }

    int arr[n+1] = {0};
    cout << "Please input the elements of the array." << endl;
    for(int i = 1; i <= n; i++)
    {
        cin >> arr[i];
    }

    int sum = 0;
    for(int i = 1; i <= n; i++)
    {
        sum += arr[i];
    }
    //The array can only be equally partitioned in two parts
    //  if the sum of all its elements is divisible by two.
    if(sum % 2 != 0)
    {
        cout << "The array cannot be equally partitioned." << endl;
        return 0;
    }
        
    int halfSum = sum/2;
    int P[n+1][halfSum+1]; //P[i, j]: max sum < j for elements up to the ith
    for(int i = 0; i <= n; i++)
    {
        for(int j = 0; j <= halfSum; j++)
        {
            P[i][j] = 0;
        }
    }
    
    //The goal is to see if we can reach exactly half of the total sum
    //  by picking some of the array's elements.
    for(int i = 1; i <= n; i++)
    {
        for(int j = 1; j <= halfSum; j++)
        {
            //The ith element can only be picked if doing so doesn't go over
            //  the current capacity j.
            if(j - arr[i] >= 0)
                P[i][j] = max(P[i-1][j], //Do not pick the ith element
                              P[i-1][j-arr[i]] + arr[i]); //Pick the ith element
            else
                P[i][j] = P[i-1][j];
        }
    }
    
    if(P[n][halfSum] == halfSum)
        cout << "The array can be equally partitioned." << endl;
    else
        cout << "The array cannot be equally partitioned." << endl;
}