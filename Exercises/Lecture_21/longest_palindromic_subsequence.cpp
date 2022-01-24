#include <iostream>
#include <algorithm>

using namespace std;

int main()
{
    string s;
    cout << "Please input a string." << endl;
    cin >> s;

    int n = s.length();
    int LPS[n+1][n+1];
    for(int i = 0; i <= n; i++)
    {
        LPS[i][0] = 0;
        LPS[0][i] = 0;
    }
    
    for(int i = 1; i <= n; i++)
    {
        for(int j = 1; j <= n; j++)
        {
            //Compare the ith character to the character that
            //  occupies the same position in the reversed string
            if(s[i-1] == s[n-j])
                LPS[i][j] = LPS[i-1][j-1] + 1; //Extend the palindromic subsequence
            else
                LPS[i][j] = max({LPS[i-1][j-1],
                                    LPS[i-1][j],
                                    LPS[i][j-1]});
        }
    }
    
    printf("The longest palindromic subsequence is %d characters long.\n", LPS[n][n]);
}