#include <iostream>
#include <cmath>
#include <algorithm>
#include <unordered_map>
#include <cstring>

using namespace std;

int query(int tree[], int nl, int nr, int sl, int sr, int i);
void update(int tree[], int nl, int nr, int sl, int sr, int v, int i);

int main()
{
    int n = 0;

    while(n < 1)
    {
        cout << "Please input the number of elements. "
            << "The number must be greater than zero." << endl;
        cin >> n;
    }

    int elems[n];
    int sorted[n];
    unordered_map<int, int> ranks; //<value, position in ordering>
    int maxVal = INT32_MIN;

    cout << "Please input your elements." << endl;
    for(int i = 0; i < n; i++)
    {
        int v;
        cin >> v;
        elems[i] = v;
        sorted[i] = v;
        if(elems[i] > maxVal) maxVal = elems[i];
    }

    //Order the values and map them to their rank. This allows us to have
    //  values in range [0, n-1] so that we may avoid to create a very large
    //  segment tree in case the array contains values much larger than its
    //  own size.
    sort(sorted, sorted+n);
    for(int i = 0; i < n; i++)
    {
        ranks[sorted[i]] = i;
    }

    int treeSize = 2 * ((int) (pow(2, (int) ceil(log2(n))))) - 1;
    //The leaf of interval [ranks[elems[i]], ranks[elems[i]]] will hold the number
    //  of occurrences of the elems[i] element.
    //  The tree will be gradually built with update
    //  operations, so for now we just initialize it to 0.
    int segTree[treeSize] = {0}; 
                                 
    int rightGreaterCount[n] = {0}; //The ith element will be the # of j such that A[i] < A[j] and i < j
    int leftSmallerCount[n] = {0}; //The ith element will be the # of j such that A[i] > A[j] and i > j

    //Compute suffix counts. Notice we iterate backwards
    for(int i = n-1; i >= 0; i--)
    {
        //At this point, we only processed elements on the right of i, so
        //  we can query the segment tree to count how many of those fall
        //  at the right of elems[i] in the ordering (in other words, those
        //  elements which are greater than elems[i])
        rightGreaterCount[i] = query(segTree, 0, n-1, ranks[elems[i]]+1, ranks[maxVal], 0);
        update(segTree, 0, n-1, ranks[elems[i]], ranks[elems[i]], 1, 0);
    }

    //Reset the tree
    for(int i = 0; i < treeSize; i++)
    {
        segTree[i] = 0;
    }

    //Compute prefix counts
    for(int i = 0; i < n; i++)
    {
        //At this point, we only processed elements on the left of i, so
        //  we can query the segment tree to count how many of those fall
        //  at the left of elems[i] in the ordering (in other words, those
        //  elements which are less than elems[i])
        leftSmallerCount[i] = query(segTree, 0, n-1, 0, ranks[elems[i]]-1, 0);
        update(segTree, 0, n-1, ranks[elems[i]], ranks[elems[i]], 1, 0);
    }

    //Compute triplets (i, j, k) such that i < j < k and elems[i] < elems[j] < elems[k]
    int answer = 0;
    for(int i = 0; i < n-1; i++)
    {
        answer += leftSmallerCount[i] * rightGreaterCount[i];
    }

    cout << answer << " triplet(s) satisfy the conditions." << endl;
}

//Returns the sum of range [`sl`, `sr`] of `tree`.
//  `nl`, `nr` are the left and right boundaries of the node indexed `i`.
//  These last three parameters are needed for recursion.
int query(int tree[], int nl, int nr, int sl, int sr, int i)
{
    //No overlap
    if(sl > nr || sr < nl) return 0;

    //Leaf
    if(nl == nr) return tree[i];

    //Total overlap
    if(nl == sl && nr == sr) return tree[i]; 

    //Partial overlap
    int mid = floor((nl + nr) / 2);
    return query(tree, nl, mid, sl, sr, 2*i+1) +
        query(tree, mid+1, nr, sl, sr, 2*i+2);
}

//Increment the values in range [`sl`, `sr`] of the tree by `v`.
//  `nl` and `nr` are the bounds of the segment defined by the
//  current node, which has index `i`.
//  These last three parameters are needed for recursion.
void update(int tree[], int nl, int nr, int sl, int sr, int v, int i)
{
    if(nl >= sl && nr <= sr)
    {
        //The segment of the current node is contained in the given range
        tree[i] += v;
        return;
    }

    //No overlap
    if(sl > nr || sr < nl) return;

    //Some overlap
    tree[i] += v; 
    int mid = floor((nl+nr)/2);
    update(tree, nl, mid, sl, sr, v, 2*i+1);
    update(tree, mid+1, nr, sl, sr, v, 2*i+2);
}