#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
    vector<int> input;
    vector<int> largeElements;
    vector<int> result;

    int n = 0;

    while(n <= 0)
    {
        cout << "Please insert the number of elements in your array. " << 
                "The number must be greater than 0" << endl;
        cin >> n;
    }

    cout << "Please input " << n << " element(s) one at a time." << endl;
    for(int i = 0; i < n; i++)
    {
        int el;
        cin >> el;
        input.push_back(el);
    }

    //Iterate backwards over the "input" vector. At each iteration i, "largestElements" contains
    // elements at the right of i which are potentially larger than input[i]
    for (int i = n-1; i >= 0; i--)
    {
        if (largeElements.empty())
        {
            //The next larger element of the last element is -1
            result.push_back(-1);
            largeElements.push_back(input[i]);
        }
        else if (largeElements.back() > input[i])
        {
            //We found the next larger element for input[i]
            result.push_back(largeElements.back());
            largeElements.push_back(input[i]);
        }
        else
        {
            //The last element of "largerElements" is smaller than input[i],
            //  so we keep popping until we find the next larger element for input[i]
            while (!largeElements.empty() && largeElements.back() <= input[i])
            {
                largeElements.pop_back();
            }
            if (largeElements.empty())
            {
                //No larger element than input[i] on the right of i, so we put -1
                result.push_back(-1);
            }
            else
            {
                //We did find the next larger element of input[i]
                result.push_back(largeElements.back());
            }
            largeElements.push_back(input[i]);
        }
    }

    cout << "The resulting array is:" << endl;
    for(int i = n-1; i >= 0; i--)
    {
        cout << result[i] << " ";
    }
    cout << endl;

    return 0;
}