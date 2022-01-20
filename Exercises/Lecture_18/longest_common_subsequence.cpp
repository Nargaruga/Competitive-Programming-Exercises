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
    int lcs[l1][l2] = {0}; //lcs[i][j] = longest common subsequence up to s1[i] and s2[j]
    
    //We iterate over each element of the matrix
    for(int i = 0; i < l1; i++)
    {
        for(int j = 0; j < l2; j++)
        {
            //Compute the current element based on previous cells
            if(i == 0 && j > 0)
                lcs[i][j] = lcs[i][j-1];
            else if(i > 0 && j == 0)
                lcs[i][j] = lcs[i-1][j];
            else if(i > 0 && j > 0)
                lcs[i][j] = max({lcs[i-1][j],
                                lcs[i][j-1],
                                lcs[i-1][j-1]});
        
            //A match! The length of the subsequence increases
            if(s1[i] == s2[j])
                lcs[i][j]++;
        }
    }

    printf("The longest common subsequence is %d character(s) long.\n", lcs[l1-1][l2-1]);
}