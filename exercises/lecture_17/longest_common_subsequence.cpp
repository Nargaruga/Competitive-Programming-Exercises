#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

int main()
{
    string s1, s2;

    cout << "Input two strings." << endl;
    cin >> s1;
    cin >> s2;

    int l1 = s1.length();
    int l2 = s2.length();
    int lcs[l1+1][l2+1]; //lcs[i][j] = longest common subsequence up to s1[i] and s2[j]

    //Init 2D array to 0
    for(int i = 0; i <= l1; i++)
    {
        for(int j = 0; j <= l2; j++)
        {
            lcs[i][j] = 0;
        }
    }
    
    //We iterate over each element of the matrix
    for(int i = 1; i <= l1; i++)
    {
        for(int j = 1; j <= l2; j++)
        {
            //Compute the current element based on previous cells
            if(s1[i-1] == s2[j-1])
                lcs[i][j] = lcs[i-1][j-1] + 1;
            else
                lcs[i][j] = max({lcs[i-1][j],
                                lcs[i][j-1]});
            
        }
    }

    printf("The longest common subsequence is %d character(s) long.\n", lcs[l1][l2]);
}