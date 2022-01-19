#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <cmath>

using namespace std;

bool compFirst(pair<int, int> p1, pair<int, int> p2);
bool compSecond(pair<int, int> p1, pair<int, int> p2);
void add(int v, int k, int& ans, vector<int> colors, int occs[], unordered_map<int, vector<int>> edges);
void remove(int v, int k, int& ans, vector<int> colors, int occs[], unordered_map<int, vector<int>> edges);

int main()
{
    int n = 0, m = 0;

    while(n < 1 || m < 1)
    {
        cout << "Please input the number of elements in your tree "
            << "and the number of queries you wish to perform. "
            << "Both numbers must be greater than zero." << endl;
        cin >> n;
        cin >> m;
    }

    vector<int> colors;
    colors.push_back(0);
    cout << "Please input your elements." << endl;
    for(int i = 1; i <= n; i++)
    {
        int v;
        cin >> v;
        colors.push_back(v);
    }

    unordered_map<int, vector<int>> edges;
    cout << "Please input your edges." << endl;
    for(int i = 0; i < n-1; i++)
    {
        int start, end;

        cin >> start;
        cin >> end;

        if(start < 1 || end > n || start == end)
        {
            cout << "Invalid edge." << endl;
            i--;
        }
        else
        {
            if(edges.find(start) == edges.end())
                edges.insert(make_pair(start, vector<int>()));
            else
                edges[start].push_back(end);
        } 
    }

    vector<pair<int, int>> queries;
    cout << "Please input your queries." << endl;
    for(int i = 0; i < m; i++)
    {
        int v, k;

        cin >> v;
        cin >> k;

        if(v < 1 || v > n)
        {
            cout << "The following must hold: 1<=v<=n" << endl;
            i--;
        } else
        {
            queries.push_back(make_pair(v, k));
        }
    }

    //Sort queries by increasing order of v
    sort(queries.begin(), queries.end(), compFirst);

    //Divide the array in sqrt(n) groups of sqrt(n)
    //  elements and sort the queries in each group
    //  by increasing order of k.
    int groupSize = ceil(sqrt(n));
    for(int i = 0; i < groupSize; i++)
    {
        int curGroupStart = i * groupSize + 1;
        int curGroupEnd = (i < groupSize - 1)
            ? curGroupStart + groupSize - 1
            : n - 1;

        sort(queries.begin() + curGroupStart,
            queries.begin() + curGroupEnd,
            compSecond);
    }

    int occs[n+1] = {0};

    //Answer the queries
    int prev_v = 0, prev_k = 0;
    int ans = 0;
    for(int i = 0; i < m; i++)
    {
        int v = queries[i].first;
        int k = queries[i].second;

        if(v < prev_v)
        {
            prev_v--;
            add(prev_v, k, ans, colors, occs, edges);
        }

        if(v > prev_v)
        {
            remove(prev_v, k, ans, colors, occs, edges);
            prev_v++;
        }

        printf("Answer for (%d, %d): %d\n",
            v,
            k,
            ans);
    }
}

//Returns true if p1's first member is smaller than
//  p2's first member, returns false otherwise
bool compFirst(pair<int, int> p1, pair<int, int> p2)
{
    return p1.first < p2.first;
}

//Returns true if p1's second member is smaller than
//  p2's second member, returns false otherwise
bool compSecond(pair<int, int> p1, pair<int, int> p2)
{
    return p1.second < p2.second;
}

void add(int v, int k, int& ans, vector<int> colors, int occs[], unordered_map<int, vector<int>> edges)
{
    int occurrences = occs[colors[v]] + 1;
    if(occurrences >= k) ans++;

    for(int child : edges[v])
    {
        printf("Child: %d\n", child);
        add(child, k, ans, colors, occs, edges);
    }
}

void remove(int v, int k, int& ans, vector<int> colors, int occs[], unordered_map<int, vector<int>> edges)
{
    int occurrences = occs[colors[v]] - 1;
    if(occurrences < k) ans--;

    for(int child : edges[v])
    {
        remove(child, k, ans, colors, occs, edges);
    }
}