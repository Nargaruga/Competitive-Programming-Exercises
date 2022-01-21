#include <iostream>
#include <vector>

using namespace std;

void add(vector<int>& tree, int i, int val, int size);
int getSum(const vector<int>& tree, int i);

int main()
{
    int n = 0, u = 0;
    vector<int> BITree; //Binary Indexed Tree

    //Get the number of elements in the array and the number of updates to perform
    while (n < 1 || u < 1)
    {
        cout << "Please input the number of elements in your array and "
             << "the number of updates you wish to perform" << endl
             << "Both values must be greater than 0." << endl;
        cin >> n >> u;
    }

    BITree = vector<int>(n+1);

    cout << "Please input your updates in the form l r val where l is the lower bound, "
         << "r is the upper bound and val is the value you wish to add to all the elements in the interval." << endl
         << "l must be greater than or equal to 1 and r must be in range [l, n]." << endl;
    int l = -1, r = -1, val = 0;
    for (int i = 0; i < u; i++)
    {
        //Get the range to update and the value to add
        cin >> l >> r >> val;
        if (l < 1 || r < l || r > n)
        {
            cout << "A value outside the permitted range was inserted." << endl;
            i--;
        }
        else
        {
            //Update the array
            for(int i = l; i <= r; i++)
            {
                add(BITree, i, val, n);
            }
        }
    }

    //Get the number of queries to perform
    int q = -1;
    while (q < 0)
    {
        cout << "Please input the number of queries you wish to perform." << endl
             << "The value must be greater than 0." << endl;
        cin >> q;
    }

    int index;
    for(int i = 0; i < q; i++)
    {
        cout << "Please input the index you wish to query." << endl;
        cin >> index;

        if(index <= 0 || index > n)
        {
            cout << "The index must be included in [1, n], where n is the size of the array." << endl;
            i--;
        } else {
            //Query the BIT and get the value that would be at index "index" if we kept the array of actual values
            cout << "Value: " << getSum(BITree, index) - getSum(BITree, index-1) << endl;
        }
    }
}

//Add the value v to the element BITree[i], updating the other elements accordingly
void add(vector<int>& BITree, int i, int v, int size)
{
    while(i <= size)
    {
        BITree[i] += v;
        i += i & (-i);
    }
}

//Get the prefix sum at index i
int getSum(const vector<int>& BITree, int i) {
    int sum = 0;

    while(i > 0)
    {
        sum += BITree[i];
        i -= i & (-i);
    }

    return sum;
}