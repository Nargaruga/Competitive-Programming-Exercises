#include <iostream>
#include <cmath>
#include <unordered_map>

using namespace std;

int query(unordered_map<int, int> tree[], int nl, int nr, int sl, int sr, int x, int i);
unordered_map<int, int> buildTree(int elems[], int n, unordered_map<int, int> tree[], int nl, int nr, int i);

int main()
{
    int n = 0, m = 0;

    while(n < 1 || m < 1)
    {
        cout << "Please input the number of elements in your array "
            << "and the number of queries you wish to perform. "
            << "Both numbers must be greater than zero." << endl;
        cin >> n;
        cin >> m;
    }

    int elems[n];
    cout << "Please input your elements." << endl;
    for(int i = 0; i < n; i++)
    {
        cin >> elems[i];
    }

    int treeSize = 2*((int)pow(2, (int)ceil(log2(n))))-1;
    unordered_map<int, int> tree[treeSize];
    buildTree(elems, n, tree, 0, n-1, 0);

    cout << "Please insert your queries." << endl
         << "A query is made of three parameters i, j, x "
         << "and reports the number of values in A[i, j] "
         << "which are >= x. `A` is the input array." << endl;
    for(int iter = 0; iter < m; iter++)
    {
        int i, j, x;

        cin >> i;
        cin >> j;
        cin >> x;

        int res = query(tree, 0, n-1, i, j, x, 0);
        printf("Result for %d, %d, %d: %d\n", i, j, x, res);

    }

    return 0;
}

int query(unordered_map<int, int> tree[], int nl, int nr, int sl, int sr, int x, int i)
{
    //No overlap
    if(sl > nr || sr < nl) return 0;

    printf("[%d, %d]: %d\n", nl, nr, tree[i][x]);

    //Total overlap || leaf
    if((sl == nl && sr == nr) || (nl == nr)) return tree[i][x];

    int mid = floor((nl+nr)/2);
    return query(tree, nl, mid, sl, sr, x, 2*i+1) +
        query(tree, mid+1, nr, sl, sr, x, 2*i+2);
}

unordered_map<int, int> buildTree(int elems[], int n, unordered_map<int, int> tree[], int nl, int nr, int i)
{
    //Leaf
    if(nl == nr)
    {
        tree[i] = unordered_map<int, int>();
        
        //Save in the map a couple <element, occs> where occs in the # of values indexed
        //  in range [nl, nr] such that they are <= element 
        for(int j = 0; j < n; j++)
        {
            //Recall that all the elements in the array have values in range [0, n-1]
            if(elems[nl] <= j) tree[i][j] = 1;
            else tree[i][j] = 0;
        }

        return tree[i];
    }

    int mid = floor((nl+nr)/2);
    unordered_map<int, int> left = buildTree(elems, n, tree, nl, mid, 2*i+1);
    unordered_map<int, int> right = buildTree(elems, n, tree, mid+1, nr, 2*i+2);

    //Merge the two maps and return the result
    for(auto it = left.begin(); it != left.end(); it++)
    {
        int key = it->first;
        int val = it->second;

        //Right[key] is guaranteed to exist due to how we built the tree
        right[key] += val;
    }

    tree[i] = right;

    return right;
}