#include <iostream>
#include <cmath>
#include <unordered_map>

using namespace std;

void addSpell(int type, int dmg)
{

}

void removeSpell(int type, int dmg)
{

}

int main()
{
    int changes = 0;

    while (changes < 1 || changes > 2 * pow(10, 5))
    {
        cout << "Please insert the number of changes to the spell set. The range is [1, 2*10^5]." << endl;
        cin >> changes;
    }

    bool inputOver = false;
    unordered_map<int, int> spells; //<power, type>

    cout << "Please input " << changes << " pairs of integers, one pair at a time: \"type\" "
        "in range [0, 1] to decide if you wish to learn/forget a fire (0) or lightning (1) spell, "
        "and \"dmg\" in range [-10^9, 10^9], which defines the strength of the spell to remove (negative dmg), "
        "add (positive dmg). Unchecked constraints: you can only remove previously added spells, and there "
        "can't be two spells with the same power."
         << endl;

    int type, dmg;
    for(int i = 0; i < changes; i++)
    {
        cin >> type;
        cin >> dmg;

        if(type < 0 || type > 1 || dmg < -pow(10, 9) || dmg > pow(10, 9))
        {
            i--;
            cout << "A value outside the range was inserted." << endl;
        }
        else
        {
            if(dmg >= 0) spells.insert(make_pair(dmg, type));
            else spells.erase(-dmg);
        }
    }

    unordered_map<int, int>::iterator it;
    for(it = spells.begin(); it != spells.end(); it++)
    {
        cout << it->first << ":" << it->second << endl;
    }

    return 0;
}