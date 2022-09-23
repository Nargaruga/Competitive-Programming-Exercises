#include <iostream>

using namespace std;

int main()
{
    int n = 0;
    while(n < 1)
    {
        cout << "Please input the number of elements in your array." << endl;
        cin >> n;
    }

    int elems[n];
    cout << "Please input the elements." << endl;
    for(int i = 0; i < n; i++)
    {
        cin >> elems[i];
    }

    int LIS[n] = {0};
    LIS[0] = 1;
    for(int i = 1; i < n; i++)
    {
        int maxInd = 0;
        bool found = false;
        //Look at the prefix to find the LIS that ends with an element
        //  smaller than the current (ith) one, so that we may extend it with
        //  elems[i].
        for(int j = 0; j < i; j++)
        {
            if(LIS[j] >= LIS[maxInd] && elems[i] > elems[j])
            {
                maxInd = j;
                found = true;
            }
        }

        if(found)
            LIS[i] = LIS[maxInd] + 1;
        else
            //No suitable LIS found, so the current element marks
            // the start of a new one
            LIS[i] = 1;
    }

    int ans = 0;
    for(int i = 0; i < n; i++)
    {
        if(LIS[i] > ans)
            ans = LIS[i];
    }

    printf("The LIS is %d element(s) long.\n", ans);
    
    return 0;
}