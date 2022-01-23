#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> computeLIS(vector<int> elems, int n);
vector<int> computeLDS(vector<int> elems, int n);

int main()
{
    int n = 0;
    while(n < 1)
    {
        cout << "Please input the number of elements in your array." << endl;
        cin >> n;
    }

    vector<int> elems;
    cout << "Please input the elements." << endl;
    for(int i = 0; i < n; i++)
    {
        int v;
        cin >> v;
        elems.push_back(v);
    }

    vector<int> LBS = vector<int>(n, 0);
    vector<int> LIS = computeLIS(elems, n);
    vector<int> LDS = computeLDS(elems, n);
    for(int i = 0; i < n; i++)
    {
        LBS[i] = LIS[i] + LDS[i] - 1;
        printf("El: %d, LIS: %d, LDS: %d, LBS: %d\n", elems[i], LIS[i], LDS[i], LBS[i]);
    }

    int ans = 0;
    for(int i = 0; i < n; i++)
    {
        if(LBS[i] > ans) 
            ans = LBS[i];
    }

    printf("The longest bitonic subsequence is %d elements long.\n", ans);
}

vector<int> computeLIS(vector<int> elems, int n)
{
    vector<int> LIS = vector<int>(n, 0);
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

    return LIS;
}

vector<int> computeLDS(vector<int> elems, int n)
{
    vector<int> LDS = vector<int>(n, 0);
    LDS[n-1] = 1;
    for(int i = n-2; i >= 0; i--)
    {
        int maxInd = n-1;
        bool found = false;
        //Look at the suffix to find the LDS that ends with an element
        //  greater than the current (ith) one, so that we may extend it with
        //  elems[i].
        for(int j = n-1; j > i; j--)
        {
            if(LDS[j] >= LDS[maxInd] && elems[i] > elems[j])
            {
                maxInd = j;
                found = true;
            }
        }
        
        if(found)
            LDS[i] = LDS[maxInd] + 1;
        else
            //No suitable LDS found, so the current element marks
            // the start of a new one
            LDS[i] = 1;
    }

    return LDS;
}