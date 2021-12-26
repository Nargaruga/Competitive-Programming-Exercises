#include <iostream>
#include <cmath>
#include <cstdio>

using namespace std;

int buildTree(int tree[], int input[], int l, int r, int i);
void inc(int tree[], int nl, int nr, int sl, int sr, int v, int i);
int rmq(int tree[], int nl, int nr, int sl, int sr, int i);

int main()
{
    int n = 0, ops = 0;

    //Get the number of elements
    while (n < 1)
    {
        cout << "Please input the number of elements. The number must be greater than zero." << endl;
        cin >> n;
    }

    int arraySize = 2*n;
    int input[arraySize] = {0}; //We store the elements twice to allow for circularity (ABC becomes ABCABC)
    int tHeight = (int)(ceil(log2(arraySize))); //Smallest power of 2 that is >= 2*n
    int treeSize = 2*(int)pow(2, tHeight)-1;
    int tree[treeSize] = {0}; 

    //Get the elements
    cout << "Please input the array's elements." << endl;
    for(int i = 0; i < n; i++)
    {
        int v;
        cin >> v;
        input[i] = v;
        input[i+n] = v;
    }

    buildTree(tree, input, 0, arraySize-1, 0);

    //Get the number of operations
    while(ops < 1)
    {
        cout << "Please input the number of operations. The number must be greater than zero." << endl;
        cin >> ops;
    }

    //Get the operations
    for(int i = 0; i < ops; i++)
    {
        cout << "For RMQ insert the l and r bounds, followed by -1." << endl;
        cout << "For INC insert the l and r bounds, followed by v." << endl;

        int l, r, v;
        cin >> l;
        cin >> r;
        cin >> v;

        if (l < 0 || r < 0 || l > n-1 || r > n-1)
        {
            cout << "Invalid input. Please keep l and r in the [0, n-1] range." << endl;
            i++;
            continue;
        }

        int shiftedR = r;
        if(l > r)
        {
            //Exploit the circular nature of the array to allow queries where l > r
            shiftedR += n;
        }

        if(v == -1)
        {
            //RMQ
            cout << "The minimum value in range " << l << " " << r << " is "
                << rmq(tree, 0, arraySize-1, l, shiftedR, 0) << endl;
        } 
        else
        {
            //INC
            inc(tree, 0, arraySize-1, l, shiftedR, v, 0);
        }
    }

    return 0;
}

//Builds `tree` to be a segment tree based on the `input` array.
//  `l` and `r` are the left and right boundaries, respectively,
//  while `i` is the index of the current node.
//  These last parameters are needed for recursion.
int buildTree(int tree[], int input[], int l, int r, int i)
{
    if(l == r)
    {
        //The current node is a leaf
        tree[i] = input[l];
        return tree[i];
    }

    //Split the array and continue with the recursion
    int m = floor((l+r)/2);
    tree[i] = min(buildTree(tree, input, l, m, 2*i+1),
        buildTree(tree, input, m+1, r, 2*i+2));

    return tree[i];
}

//Increment the values in range [`sl`, `sr`] of the tree by `v`.
//  `nl` and `nr` are the bounds of the segment defined by the
//  current node, which has index `i`.
//  These last parameters are needed for recursion.
void inc(int tree[], int nl, int nr, int sl, int sr, int v, int i)
{
    if(nl >= sl && nr <= sr)
    {
        //The segment of the current node is contained in the given range
        tree[i] += v;
        return;
    }

    //No overlap
    if(sr < nl || sl > nr) return;

    //Otherwise, part of the node's segment is contained in the range
    int m = floor((nl+nr)/2); //Split the array
    inc(tree, nl, m, sl, sr, v, 2*i+1); //Left subtree
    inc(tree, m+1, nr, sl, sr, v, 2*i+2); //Right subtree
}

//Returns the minimum value in range [`sl`, `sr`] of `tree`.
//  `nl`, `nr` are the left and right boundaries of the node indexed `i`.
//  These last parameters are needed for recursion.
int rmq(int tree[], int nl, int nr, int sl, int sr, int i)
{
    fprintf(stdout, "nl: %d, nr: %d, sl: %d, sr: %d tree[i]: %d\n", nl, nr, sl, sr, tree[i]);
    //No overlap
    if(sr < nl || sl > nr) return INT32_MAX;

    //If the node's segment corresponds to the leaf or if the current node
    //  is a leaf, we return the current node's value.
    if((nl == sl && nr == sr) || nl == nr) return tree[i];

    int m = floor((nl+nr)/2); //Split the array
    int left = rmq(tree, nl, m, sl, sr, 2*i+1); //Left subtree
    int right = rmq(tree, m+1, nr, sl, sr, 2*i+2); //Right subtree

    return min(left, right);
}