#include <iostream>

using namespace std;

int main()
{
    int n = 0;

    while(n < 1)
    {
        cout << "Please input the number of elements in your array." << endl;
        cin >> n;
    }

    cout << "Please insert the array's elements." << endl;
    int elems[n];
    int sum = 0;
    for(int i = 0; i < n; i++)
    {
        int el;
        cin >> el;
        elems[i] = el;

        sum += el;
    }

    if(sum % 3 != 0) 
    {
        cout << "There is no way to partition this array in three equal-sum parts." << endl;
        return -1;
    }

    int partialSum = 0;
    //suffixCounts[i] = # of suffixes which start at or after i that have sum equal to a third to the total
    int suffixCounts[n] = {0};
    if(elems[n-1] == sum / 3)
        suffixCounts[n-1] = 1;

    for(int i = n-2; i >= 0; i--)
    {
        partialSum += elems[i];
        if(partialSum == sum / 3 || partialSum == 0)
        {
            //This element marks the y of a potential (x, y) couple which
            //  splits the array in three segments of equal sum.
            suffixCounts[i] = suffixCounts[i+1] + 1;
            partialSum = 0;
        }
        else
            suffixCounts[i] = suffixCounts[i+1];
    }

    int prefixSum = 0;
    int ans = 0;
    //Compute the prefix sum for prefixes that start at i.
    //  Each time the prefix sum matches sum/3, add to the
    //  final answer the number of valid suffixes that can
    //  match with this index. We do i+2 because there must
    //  be at least one item between the indexes for the array
    //  to be split in three parts.
    for(int i = 0; i < n-2; i++)
    {
        prefixSum += elems[i];
        if(prefixSum == sum / 3)
            ans += suffixCounts[i+2];
    }

    if(ans == 0)
        cout << "There is no way to partition this array in three equal-sum parts." << endl;
    else
        printf("There are %d ways to split the array in three equal-sum parts.\n", ans);
}