#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

int computeVC(unordered_map<int, vector<int>> edges, int VC[], int i, int n);

int main()
{
    int n = 0;
    while(n < 1)
    {
        cout << "Please insert the size of the tree." << endl;
        cin >> n;
    }

    unordered_map<int, vector<int>> edges;
    cout << "Please input the tree's edges." << endl;
    for(int i = 0; i < n-1; i++)
    {
        int start, end;
        cin >> start;
        cin >> end;

        if(edges.find(start) == edges.end())
            edges.insert(make_pair(start, vector<int>()));
        else
            edges[start].push_back(end);
    }

    int VC[n+1];
    fill(VC, VC + n+1, -1);
    int ans = computeVC(edges, VC, 1, n);

    printf("There are %d nodes in the smallest vertex cover.\n", ans);
}

//Compute the minimum vertex cover for the tree of size `n` and root `i`
//  whose edges are defined in `edges`. The `VC` array is used to store
//  results in order to avoid computing the same subproblem multiple times
int computeVC(unordered_map<int, vector<int>> edges, int VC[], int i, int n)
{
    if(i < 0 || i >= n)
        return 0;

    //Leaf
    if(edges.find(i) == edges.end())
        return 1;

    //Result already computed
    if(VC[i] != -1)
        return VC[i];

    vector<int> children = edges[i];
    int childVC = 0, grandchildVC = 0;
    int left = 2*i;
    int right = 2*i+1;

    //VC including children
    childVC += computeVC(edges, VC, left, n);
    childVC += computeVC(edges, VC, right, n);

    //VC including current node and grandchildren
    grandchildVC += computeVC(edges, VC, 2*left, n);
    grandchildVC += computeVC(edges, VC, 2*left+1, n);
    grandchildVC += computeVC(edges, VC, 2*right, n);
    grandchildVC += computeVC(edges, VC, 2*right+1, n);

    VC[i] = max(childVC, grandchildVC + 1);

    return VC[i];
}

