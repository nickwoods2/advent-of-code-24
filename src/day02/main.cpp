#include <iostream>
#include <sstream>
using namespace std;

const int N = 1000;

bool is_all_increasing(string line)
{
    stringstream ss(line);
    int a = 0, b = 0, i = 0;
    bool is_safe = true;
    while (ss >> a)
    {
        if ((a <= b | abs(a - b) > 3) && i >= 1)
        {
            is_safe = false;
        }
        b = a;
        i++;
    }
    return is_safe;
}

bool is_all_decreasing(string line)
{
    stringstream ss(line);
    int a = 0, b = 0, i = 0;
    bool is_safe = true;
    while (ss >> a)
    {
        if ((a >= b | abs(a - b) > 3) && i >= 1)
        {
            is_safe = false;
        }
        b = a;
        i++;
    }
    return is_safe;
}

bool fault_tolerant_is_safe(string line)
{
    stringstream ss(line);
    int a;
    int num_levels = 0;
    while (ss >> a)
    {
        num_levels++;
    }

    bool is_safe = false;
    for (int i = 0; i < num_levels; i++)
    {
        int j = 0;
        string line_tmp = "";
        string a;
        stringstream ss(line);
        while (ss >> a)
        {
            if (i != j)
            {
                line_tmp = line_tmp + a + " ";
            }
            j++;
        }
        if (is_all_increasing(line_tmp) | is_all_decreasing(line_tmp))
        {
            is_safe = true;
        }
    }
    return is_safe;
}

int star1(vector<string> lines)
{
    int num_safe = 0;
    for (int i = 0; i < N; i++)
    {
        string line = lines[i];
        bool is_safe = is_all_increasing(line) | is_all_decreasing(line);
        if (is_safe)
        {
            num_safe++;
        }
    }
    return num_safe;
}

int star2(vector<string> lines)
{
    int num_safe = 0;
    for (int i = 0; i < N; i++)
    {
        string line = lines[i];
        bool is_safe = fault_tolerant_is_safe(line);
        if (is_safe)
        {
            num_safe++;
        }
    }
    return num_safe;
}

int main()
{
    vector<string> lines;
    string line;
    while (getline(cin, line))
    {
        lines.push_back(line);
    }
    cout << "Star 1 solution " << star1(lines) << endl;
    cout << "Star 2 solution " << star2(lines) << endl;
    return 0;
}
