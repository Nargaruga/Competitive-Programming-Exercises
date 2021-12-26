#include <iostream>
#include <cmath>

using namespace std;

//Orders the elements of input by "merging" in the right order the elements of
// the subarrays [start, center] and [center + 1, end]
void merge(int input[], int start, int center, int end, int &inversions) 
{
    int tmp[end - start + 1]; //Will contain the sorted elements of the two subarray we merge
    int i = start, j = center + 1, z = 0;

    //Keep iterating until we reach the end of a subarray
    while(i <= center && j <= end)
    {
        //Add to tmp the smallest element between the current ones of the two subarrays
        if(input[i] <= input[j])
        {
            tmp[z] = input[i];
            i++;
        }
        else
        {
            tmp[z] = input[j];
            //If we get into this block it means there's an element in the left subarray
            //  which is larger than an element in the right subarray, so we count an inversion
            inversions++; 
            j++;
        }
        z++;
    }

    //Fill tmp with the remaining elements of the first subarray, which are already sorted
    while(i <= center)
    {
        tmp[z] = input[i];
        i++;
        z++;
    }

    //Fill tmp with the remaining elements of the second subarray, which are already sorted
    while(j <= end)
    {
        tmp[z] = input[j];
        j++;
        z++;
    }

    //Finally, replace the elements in the input subarray with their sorted counterparts
    for(int k = start; k <= end; k++)
    {
        input[k] = tmp[k - start];
    }
}

//Implementation of merge sort which also counts the number of inversions in the array
void mergeSort(int input[], int start, int end, int &inversions)
{
    if(start < end) 
    {
        int center = floor((start + end) / 2);
        //Recursive call on the left side
        mergeSort(input, start, center, inversions);
        //Recursive call on the right side
        mergeSort(input, center + 1, end, inversions);
        //Merge the left and right array, ordering the elements and counting the inversions
        merge(input, start, center, end, inversions);
    }
}

int main()
{
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
    
    int inversions = 0;

    mergeSort(input, 0, n - 1, inversions);

    cout << "There are " << inversions << " inversion(s) in the array." << endl;

    cout << "Sorted array: ";
    for(int i = 0; i < n; i++)
    {
        cout << input[i] << " ";
    }
    cout << endl;

    return 0;
}

