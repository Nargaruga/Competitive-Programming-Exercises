#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;

void add(int BITree[], int i, int val, int size);
int getSum(int BITree[], int i);

int main()
{
    int n = 0;
    unordered_map<int, int> occurrences; //<v, occurrences of v>

    //Get the number of elements
    while (n < 1)
    {
        cout << "Please input the number of elements in your array. "
             << "This number must be greater than zero." << endl;
        cin >> n;
    }

    int input[n] = {0};
    int BITree[n] = {0}; 
    int prefixCounts[n] = {0}; //prefixCounts[i] = # of occurrences of input[i] in [0, i]

    cout << "Please input the elements you wish to insert." << endl;
    for (int i = 0; i < n; i++)
    {
        cin >> input[i];

        //Populate the prefixCounts array
        occurrences[input[i]]++;
        prefixCounts[i] = occurrences[input[i]];
    }

    occurrences.clear();
    
    int indexCount = 0; //Number of couples <i, j> such that f(0, i, input[i]) > f(j, n, input[j])
    //At each iteration, the BIT will hold in position i the number of elements that occured i times
    //  up to now. Since we are iterating backwards, those element are all after i, so they satisfy the
    //  condition j > i.
    for(int i = n - 1; i >= 0; i--) 
    {
        //Get the # of elements in [i, n] that appear less times than the # of times input[i] appears in [0, i]
        indexCount += getSum(BITree, prefixCounts[i] - 1);
        //Increment the # of occurrences of the current element
        occurrences[input[i]]++;
        //The element input[i] occurs k = occurrences[input[i]] times, so we increment the number of
        //  elements that occur k times by 1.
        add(BITree, occurrences[input[i]], 1, n);
    }

    cout << "The number of couples <i,j> that satisfy the condition is " << indexCount << endl;
}


//Add the value v to the element BITree[i], updating the other elements accordingly
void add(int BITree[], int i, int v, int size)
{
    while(i <= size)
    {
        BITree[i] += v;
        i += i & (-i);
    }
}

//Get the prefix sum at index i
int getSum(int BITree[], int i) {
    int sum = 0;

    while(i > 0)
    {
        sum += BITree[i];
        i -= i & (-i);
    }

    return sum;
}