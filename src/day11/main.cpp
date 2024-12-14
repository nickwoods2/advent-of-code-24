#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
using namespace std;

template <typename T>
void print_vector(const std::vector<T> &x)
{
    for (const auto &element : x)
    {
        cout << element << " ";
    }
    cout << endl;
}

struct Input
{
    vector<long long> stones;
};

Input readInput(string filename)
{
    ifstream file(filename);
    string stones_str;
    getline(file, stones_str);
    stringstream ss(stones_str);
    long long stone;
    vector<long long> stones;
    while (ss >> stone)
    {
        stones.push_back(stone);
    }
    return Input{stones};
}

long long star2(vector<long long> stones, int numBlinks)
{
    // Create initial map of stone_val: stone_count
    map<long long, long long> stoneCounts;
    for (long long stone : stones)
    {
        stoneCounts[stone] += 1;
    }

    string stone{};
    string left{}, right{};
    int stoneSize{};
    for (int i = 0; i < numBlinks; i++)
    {
        map<long long, long long> stoneCountsCopy{};
        for (const auto &pair : stoneCounts)
        {
            stone = to_string(pair.first);
            stoneSize = stone.size();
            if (pair.first == 0)
            {
                stoneCountsCopy[1] += pair.second;
            }
            else if (stoneSize % 2 == 0)
            {
                left = "";
                right = "";
                for (int k = 0; k < (stoneSize / 2); k++)
                {
                    left += stone[k];
                    right += stone[stoneSize / 2 + k];
                }
                stoneCountsCopy[stoll(left)] += pair.second;
                stoneCountsCopy[stoll(right)] += pair.second;
            }
            else
            {
                stoneCountsCopy[2024 * pair.first] += pair.second;
            }
        }
        stoneCounts = stoneCountsCopy;
    }
    long long answer = 0;
    for (const auto &pair : stoneCounts)
    {
        answer += pair.second;
    }
    return answer;
}

int main()
{
    Input input = readInput("input.txt");
    cout << "Star 1 solution " << star2(input.stones, 25) << endl;
    cout << "Star 2 solution " << star2(input.stones, 75) << endl;
    return 0;
}
