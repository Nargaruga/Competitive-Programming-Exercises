#include <iostream>
#include <algorithm>

using namespace std;

int main()
{
    string s1, s2;
    cout << "Please input two strings." << endl;
    cin >> s1;
    cin >> s2;

    int len1 = s1.length();
    int len2 = s2.length();
    int M[len1+1][len2+1];
    
    for(int i = 0; i <= len1; i++)
    {
        M[i][0] = i;
    }
    
    for(int j = 0; j <= len2; j++)
    {
        M[0][j] = j;
    }
    
    for(int i = 1; i <= len1; i++)
    {
        for(int j = 1; j <= len2; j++)
        {
            if(s1[i-1] == s2[j-1])
                M[i][j] = M[i-1][j-1];
            else
                M[i][j] = 1+ min({M[i-1][j], //deletion
                                  M[i][j-1], //insertion
                                  M[i-1][j-1]}); //substitution
        }
    }
    
    printf("The edit distance is %d.\n", M[len1][len2]);
}