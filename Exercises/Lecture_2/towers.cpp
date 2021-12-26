#include <iostream>
#include <vector>

using namespace std;

int MAX_LENGTH = 1000; //Maximum length of a bar, as specified by the problem's description

int main()
{
    int n = 0;

    while(n <= 0)
    {
        cout << "Please insert the number of bars at your disposal. " << 
                "The number must be greater than 0" << endl;
        cin >> n;
    }
    int bars[n] = {0};
    int occurrences[MAX_LENGTH] = {0};

    cout << "Please input each bar's length one at a time." << endl;
    //Initialize input array and count occurrences for each bar length
    for(int i = 0; i < n; i++)
    {
        int el;
        cin >> el;
        bars[i] = el;
        occurrences[el]++;
    }

    //Find the tower with the most bars and count all towers
    int max = 0;
    int towers = 0;
    for(int i = 0; i < MAX_LENGTH; i++)
    {
        if(occurrences[i] != 0)
        {
            towers++;
        }
        if(occurrences[i] > max)
        {
            max = occurrences[i];
        }
    }

    cout << "The tower with the most bars is " << max
         << " bars high, and the total number of towers is " << towers << "." << endl;

    return 0;
}