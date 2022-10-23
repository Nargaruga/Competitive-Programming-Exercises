#include <iostream>
#include <unordered_map>

using namespace std;

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

    unordered_map<int, int> distances; //<distance, distance> TODO: find a better way? Maybe a different data structure
    int max = 0, k = 0, curr = 0;

    //Add all the distances of adjacent elements to the unordered_map and keep track of the maximum distance
    for(int i = 1; i < n; i++)
    {
        int distance = input[i] - input[i-1];
        distances.insert(make_pair(distance, distance));
        if(distance > max)
        {
            max = distance;
        }
    }

    //The minimum k cannot be lower than the minimum distance. Moreover, since each time that we
    //  traverse a distance of k we decrement k itself, we need to set k to max + count - 1, where count
    //  is the amount of times we must traverse the maximum distance. -1 is there because the first longest
    //  jump is "free", since we set k as the maximum distance itself. Following the first jump, k will be
    //  said distance - 1, so we must increment it by one for each jump of that distance.
    int count = distances.count(max);
    k = max + count - 1;

    //Now we set the current distance we are inspecting as max-1: if no jumps of this distance exist, then
    //  we have finished, else we increment k by the count of said jumps - 1, for the same reasons explained
    //  above. We decrement curr and continue until we run out of distances or the current inspected distance
    //  never appears.
    curr = max - 1;
    while(distances.find(curr) != distances.end())
    {
        count = distances.count(curr);
        k += count - 1;
        curr--;
    }

    cout << "The minimum value of k is " << k << "." << endl;

    return 0;
}