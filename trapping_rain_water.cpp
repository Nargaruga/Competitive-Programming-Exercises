#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
    int n = 0;

    while (n <= 0)
    {
        cout << "Please insert the number of elements in your array. "
             << "The number must be greater than 0" << endl;
        cin >> n;
    }

    int elevationMap[n];
    cout << "Please input " << n << " element(s) one at a time." << endl;
    //Initialize the elevation map
    for(int i = 0; i < n; i++)
    {
        cin >> elevationMap[i];
    }

    vector<int> leftWalls; //leftWalls[i] is the maximum height of walls 0 to i
    vector<int> rightWalls;//rightWalls[i] is the maximum height of walls n-1 to i
    int maxWall = 0;
    int waterLevel = 0;
    int totalWater = 0;

    //Initialize leftWalls
    for (int i = 0; i < n; i++)
    {
        if (elevationMap[i] > maxWall)
        {
            maxWall = elevationMap[i];
        }

        leftWalls.push_back(maxWall);
    }

    maxWall = 0;

    //Initialize rightWalls
    for (int i = n - 1; i >= 0; i--)
    {
        if (elevationMap[i] > maxWall)
        {
            maxWall = elevationMap[i];
        }

        rightWalls.push_back(maxWall);
    }
    //Reverse rightWalls because we constructed iterating backwards on the elevation map and
    // using push_back(), which inserts at the end of the vector
    std::reverse(rightWalls.begin(), rightWalls.end());

    //Compute the amount of water at each index of the elevation map, adding it to the total
    for (int i = 0; i < n; i++)
    {
        //The water level depends on the height of the shortest of the two walls that delimit the water pool
        waterLevel = min(leftWalls[i], rightWalls[i]);
        //We prevent the water level at cell i to be computed as negative by setting it to 0
        // if the wall at said cell is higher than waterLevel
        totalWater += elevationMap[i] < waterLevel ? waterLevel - elevationMap[i] : 0;
    }

    cout << "The amount of trapped water is: " << totalWater << " units." << endl;

    return 0;
}

//Returns the minimum between a and b
int min(int a, int b)
{
    return a < b ? a : b;
}