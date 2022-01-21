#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void add(vector<int>& tree, int i, int val, int size);
int getSum(const vector<int>& tree, int i);
bool comparePairs(pair<int, int> a, pair<int, int> b);

int main()
{
    int n = 0;
    vector<int> BITree; //Binary Indexed Tree
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
            //Keep track of the minimum start point and the maximum end point
            if(r > max)
                max = r;
            if(l < min)
                min = l;

            segments.push_back(make_pair(l, r));
        }
    }

    //Determine the needed size for the BIT
    int size = max - min + 1;
    BITree = vector<int>(size);

    //Sort the array of segments in decreasing order of starting points
    //  (basically, segments which start later will be processed first)
    sort(segments.begin(), segments.end(), comparePairs);

    //Process the segments
    for(int i = 0; i < n; i++)
    {
        //At this point, all segments which start after the ith have been processed, so
        //  we check how many of those end before the ith. This is done by getting the
        //  prefix sum in the BIT at the index corresponding to the right bound of the ith segment.
        cout << "Segment [" << segments[i].first << ", " << segments[i].second << "] contains " 
             << getSum(BITree, segments[i].second - min) << " other segment(s)." << endl; 

        //Now that the ith segment is processed, we can add one to the BIT at the index 
        //  corresponding to its right bound, so that the following segments can count 
        //  the number of segments that end before them.
        add(BITree, segments[i].second - min + 1, 1, size);
    }
}

//Returns true if the first element of a is greater than the first element of b,
//  otherwise returns false
bool comparePairs(pair<int, int> a, pair<int, int> b)
{
    if(a.first > b.first)
        return true;
    else
        return false;
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