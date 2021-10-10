#include <iostream>
#include <unordered_map>

using namespace std;

int main()
{
    int n = -1, k = -1;

    while (n < 0 && k < 0)
    {
        cout << "Please input the number of elements in the array and the value k. "
                "Both values must be greater than 0."
             << endl;

        cin >> n;
        cin >> k;
    }
    int input[n];

    cout << "Please insert the " << n << " elements of your array." << endl;
    for (int i = 0; i < n; i++)
    {
        cin >> input[i];
    }

    unordered_map<int, int> occurrences; //<value, occurrences of value in the segment>
    int i = 0, j = 0; //The current segment is [i,j]
    int segmentLength = 1; //Length of the segment
    int distinctCount = 0; //Number of distinct elements in the segment
    int maxLength = -1, maxStart = 0, maxEnd = 0;
    while (j < n)
    {
        //Check if the current element already appeared in the segment.
        if (occurrences.find(input[j]) == occurrences.end())
        {
            //It did not, so it's a new unique element.
            occurrences.insert(make_pair(input[j], 1));
            distinctCount++;
        }
        else
        {
            //It did.
            occurrences[input[j]]++;
        }

        //Check if the segment is k-good.
        if (distinctCount > k)
        {
            //It isn't anymore, so we check if the segment we just analyzed is the longest.
            if (segmentLength - 1 > maxLength)
            {
                maxLength = segmentLength - 1;
                maxStart = i;
                maxEnd = j - 1;
            }

            //Pass to the next segment, removing one element from the tail and updating the
            // number of occurrences and of distinct elements, if necessary.
            occurrences[input[i]]--;
            if(occurrences[input[i]] == 0)
            {
                distinctCount--;
            }
            i++;
            segmentLength--;
        }
        else
        {
            //The segment is still k-good, so we add another element at its end.
            segmentLength++;
            j++;
        }
    }

    //This is the case in which we explored the whole array, but never got the chance to update
    // the maxStart and maxEnd values, because the k-good property was always satisfied. In this
    // case, the longest k-good segment is the whole array.
    if(maxLength == -1)
    {
        maxStart = 0;
        maxEnd = n - 1;
    }

    cout << "The longest k-good segment is [" << maxStart << ", " << maxEnd << "]" << endl;
}