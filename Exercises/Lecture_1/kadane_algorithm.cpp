#include <iostream>

using namespace std;

int main()
{
    int currentSum = 0;
    int maxSum = 0;
    int n = 0;

    while(n <= 0)
    {
        cout << "Please insert the number of elements in your array. " << 
                "The number must be greater than 0" << endl;
        cin >> n;
    }
    int input[n];

    cout << "Please input " << n << " element(s) one at a time." << endl;
    for(int i = 0; i < n; i++)
    {
        cin >> input[i];
    }
    int max = input[0];

    for (int i = 0; i < n; i++)
    {
        //If the current element is < 0 we skip it, for it cannot be the prefix to the maximum
        // subarray. We still keep track of the maximum, so that the algorithm still works with an array
        // of only negative numbers.
        if (currentSum == 0 && input[i] < 0)
        {
            if (input[i] > max)
            {
                max = input[i];
            }
            continue;
        }

        //If the current element would bring the current sum < 0 we reset currentSum and start forming
        // a new subarray. Otherwise we keep on updating currentSum.
        // maxSum is updated as needed.
        if (currentSum + input[i] < 0)
        {
            if (currentSum > maxSum)
            {
                maxSum = currentSum;
            }
            currentSum = 0;
        }
        else
        {
            currentSum += input[i];
            if (currentSum > maxSum)
            {
                maxSum = currentSum;
            }
        }
    }

    //We return max when maxSum == 0 in order to cover the case of arrays containing only negative numbers
    int result = maxSum > 0 ? maxSum : max;
    cout << "The maximum sum of the elements in any subarray of the input is: " << result << endl;

    return 0;
}