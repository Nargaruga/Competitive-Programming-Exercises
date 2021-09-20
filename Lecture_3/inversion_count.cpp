#include <iostream>

using namespace std;

int main()
{
    int n;

    while(n <= 0)
    {
        cout << "Please insert the number of elements in your array. " << 
                "The number must be greater than 0" << endl;
        cin >> n;
    }
    int input[n];

    cout << "Please input " << n << " element(s) one at a time." << endl;
    for(int i = 0; i < n; i++)
    {
        cin >> input[i];
    }
    


    return 0;
}