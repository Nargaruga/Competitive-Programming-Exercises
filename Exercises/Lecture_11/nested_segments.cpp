#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

int main() 
{
    int n = 0;
    vector<pair<int, int>> segments;

    //Get the number of segments
    while (n < 1)
    {
        cout << "Please input the number of segments." << endl;
        cin >> n;
    }

    cout << "Please input the start and end points of each segment, in the form l r, "
         << "where l is the lower bound and r is the upper bound."
         << "l must be greater than 0 and r must be greater than or equal to l." << endl;

    int l = -1, r = -1, max = 0, min = 0;
    for (int i = 0; i < n; i++)
    {
        //Get the start and end of each segment
        cin >> l >> r;
        if (l < 1 || r < l)
        {
            cout << "An illegal value was inserted." << endl;
            i--;
        }
        else
        {   
            segments.push_back(make_pair(l, r));
        }
    }

    return 0;
}

void buildTree(int tree[], int array[], int l, int r, int i)
{
    if(r < l <= 0) return;
    if(l == r) tree[i] = array[l];

    int mid = floor((l + r) / 2);

    buildTree(tree, array, l, mid, 2*i);
    buildTree(tree, array, mid+1, r, 2*i+1);

    tree[i] = tree[2*i] + tree[2*i+1];
}