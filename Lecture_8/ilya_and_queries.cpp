#include <iostream>
#include<vector>
#include <utility>

using namespace std;

int main() {
    string input;
    int k = -1, n;
    vector<pair<int, int>> queries;

    //We assume that the input string will only contain '.' and '#' characters
    cout << "Please input your string." << endl;
    cin >> input;
    n = input.length();

    while(k < 0) 
    {
        cout << "Please input the number of queries. The number must be greater than 0." << endl;
        cin >> k;
    }

    int l, r;
    cout << "Please input your queries in the form l r with 1 <= l < r <= n." << endl;
    for(int i = 0; i < k; i++) 
    {
        cin >> l >> r;;

        if(l < 1 || l > r || r > n)
        {
            cout << "Please follow the constraints." << endl;
            i--;
        } else {
             queries.push_back(make_pair(l, r));
        }
    }

    int count;
    cout << "Here is the answer to your queries." << endl;
    for(pair<int, int> query : queries)
    {
        l = query.first;
        r = query.second;
        count = 0;

        //Iterate backwards over the subarray [l, r) and, for each element, check
        // if it's equal to the one to its right.
        for(int i = r-1; i > l-1; i--) 
        {
            if(input[i] == input[i-1])
                count++;
        }

        cout << "l: " << l << ", r: " << r << ", Count: " << count << endl; 
    }
}