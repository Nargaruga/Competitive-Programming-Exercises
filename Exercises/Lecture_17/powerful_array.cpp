#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <cmath>

using namespace std;

bool compStart(pair<int, int> p1, pair<int, int> p2);
bool compEnd(pair<int, int> p1, pair<int, int> p2);
void add(int elem, int& ans, unordered_map<int, int> ranks, int occs[], int n);
void remove(int elem, int& ans, unordered_map<int, int> ranks, int occs[], int n);

int main()
{
    int n = 0, t = 0;

    while(n < 1 || t < 1)
    {
        cout << "Please input the number of elements in your array "
            << "and the number of queries you wish to perform. "
            << "Both numbers must be greater than zero." << endl;
        cin >> n;
        cin >> t;
    }

    vector<int> elems;
    elems.push_back(0);
    cout << "Please input your elements." << endl;
    for(int i = 1; i <= n; i++)
    {
        int v;
        cin >> v;
        elems.push_back(v);
    }

    vector<pair<int, int>> queries;
    cout << "Please input your queries." << endl;
    for(int i = 0; i < t; i++)
    {
        int l, r;

        cin >> l;
        cin >> r;

        if(l < 1 || r > n || l > r)
        {
            cout << "The following must hold: 1<=l<=r<=n" << endl;
            i--;
        } else
        {
            queries.push_back(make_pair(l, r));
        }
    }

    //Sort queries by increasing order of l
    sort(queries.begin(), queries.end(), compStart);

    //Sort each subsection of size at most intSqrt
    //  by increasing order of r
    int intSqrt = ceil(sqrt(t));
    for(int i = 0; i < intSqrt; i++)
    {
        int curGroupStart = i * intSqrt;
        int curGroupEnd = (i < intSqrt - 1)
            ? curGroupStart + intSqrt
            : intSqrt;

        sort(queries.begin() + curGroupStart,
            queries.begin() + curGroupEnd,
            compEnd);
    }

    //Sort the elements in a new array and map their values
    //  to their position in the sorted array
    unordered_map<int, int> ranks;
    vector<int> sorted(elems.begin(), elems.end());
    for(int i = 1; i <= n; i++)
    {
        ranks.insert(make_pair(sorted[i], i));
    }

    //occs[i] = #occurrences of i
    int occs[n+1] = {0};

    //Answer the queries
    int prevStart = 0, prevEnd = 0; //Bounds of the previous query
    int ans = 0;
    for(int i = 0; i < t; i++)
    {
        //Get the bounds for the current query
        int currStart = queries[i].first;
        int currEnd = queries[i].second;

        if(currEnd < currStart) continue;

        while(prevStart > currStart)
        {
            prevStart--;
            add(elems[prevStart], ans, ranks, occs, n);
        }

        while(prevStart < currStart)
        {
            remove(elems[prevStart], ans, ranks, occs, n);
            prevStart++;
        }

        while(prevEnd > currEnd)
        {
            remove(elems[prevEnd], ans, ranks, occs, n);
            prevEnd--;
        }

        while(prevEnd < currEnd)
        {
            prevEnd++;
            add(elems[prevEnd], ans, ranks, occs, n);
        }

        printf("Answer for (%d, %d): %d\n",
            currStart,
            currEnd,
            ans);
    }
}

//Returns true if p1's first member is smaller than
//  p2's first member, returns false otherwise
bool compStart(pair<int, int> p1, pair<int, int> p2)
{
    return p1.first < p2.first;
}

//Returns true if p1's first member is smaller than
//  p2's first member, returns false otherwise
bool compEnd(pair<int, int> p1, pair<int, int> p2)
{
    return p1.second < p2.second;
}

//Adds a new occurrence of elem and computes the new ans
void add(int elem, int& ans, unordered_map<int, int> ranks, int occs[], int n)
{
    auto iter = ranks.find(elem);

    if(iter != ranks.end())
    {
        int rank = iter->second;
        ans -= occs[rank] * occs[rank] * elem;
        occs[rank]++;
        ans += occs[rank] * occs[rank] * elem;
    }
}

//Removes an occurrence of elem and computes the new ans
void remove(int elem, int& ans, unordered_map<int, int> ranks, int occs[], int n)
{
    auto iter = ranks.find(elem);

    if(iter != ranks.end())
    {
        int rank = iter->second;
        ans -= occs[rank] * occs[rank] * elem;
        occs[rank]--;
        ans += occs[rank] * occs[rank] * elem;
    }
}


