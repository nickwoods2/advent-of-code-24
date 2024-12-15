#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <set>
using namespace std;

struct Input
{
    vector<vector<char>> farm;
    size_t numRows;
    size_t numCols;
};

Input readInput(string filename)
{
    ifstream file(filename);
    string line;
    vector<vector<char>> farm;
    while (getline(file, line))
    {
        vector<char> row;
        for (char ch : line)
        {
            row.push_back(ch);
        }
        farm.push_back(row);
    }
    return Input{farm, farm.size(), farm[0].size()};
}

bool inside(int numRows, int numCols, pair<int, int> position)
{
    return position.first >= 0 && position.first < numRows &&
           position.second >= 0 && position.second < numCols;
}

void traverseConnectedRegion(vector<vector<char>> &farm,
                             char &current,
                             set<pair<int, int>> &visited,
                             pair<int, int> position)
{
    if (!inside(farm.size(), farm[0].size(), position))
    {
        return;
    }
    if (farm[position.first][position.second] != current)
    {
        return;
    }
    visited.insert(position);
    vector<pair<int, int>> directions{{position.first - 1, position.second},
                                      {position.first, position.second + 1},
                                      {position.first + 1, position.second},
                                      {position.first, position.second - 1}};
    for (pair<int, int> direction : directions)
    {
        if (visited.find(direction) == visited.end())
        {
            traverseConnectedRegion(farm, current, visited, direction);
        }
    }
}

void updatePerimeter(vector<vector<int>> &farm,
                     int &current,
                     map<int, int> &perimeter,
                     int rowPtr, int colPtr, int numRows, int numCols)
{
    if (rowPtr < 0 || rowPtr >= numRows || colPtr < 0 || colPtr >= numCols)
    {
        perimeter[current] += 1;
    }
    else if (farm[rowPtr][colPtr] != current)
    {
        perimeter[current] += 1;
    }
}

int star1(vector<vector<int>> farm, size_t numRows, size_t numCols)
{
    map<int, int> perimeter{};
    map<int, int> area{};
    int rowPtr{}, colPtr{};
    int current{};
    vector<pair<int, int>> directions;
    for (int i = 0; i < numRows; i++)
    {
        for (int j = 0; j < numCols; j++)
        {
            current = farm[i][j];
            area[current] += 1;
            directions = {
                {i - 1, j},
                {i, j + 1},
                {i + 1, j},
                {i, j - 1}};
            for (const auto &d : directions)
            {
                updatePerimeter(farm, current, perimeter,
                                d.first, d.second, numRows, numCols);
            }
        }
    }

    long answer{};
    for (const auto &pair : perimeter)
    {
        answer += perimeter[pair.first] * area[pair.first];
    }
    return answer;
}

int star2(vector<vector<int>> &farm, size_t &numRows, size_t &numCols)
{
    return 0;
}

int main()
{
    Input input = readInput("input.txt");

    vector<vector<int>> integerFarm{};
    integerFarm.resize(input.numRows);
    for (int i = 0; i < input.numRows; ++i)
    {
        integerFarm[i].resize(input.numCols);
    }

    int tag = 0;
    pair<int, int> currentPosition{};
    char current{};
    set<pair<int, int>> connectedRegion{}, visited{};
    for (int i = 0; i < input.numRows; i++)
    {
        for (int j = 0; j < input.numCols; j++)
        {
            current = input.farm[i][j];
            currentPosition = {i, j};
            if (visited.find(currentPosition) == visited.end())
            {
                connectedRegion = {};
                traverseConnectedRegion(input.farm,
                                        current,
                                        connectedRegion,
                                        currentPosition);
                for (pair<int, int> position : connectedRegion)
                {
                    integerFarm[position.first][position.second] = tag;
                    visited.insert(position);
                }
                tag++;
            }
        }
    }
    cout << "Star 1 solution " << star1(integerFarm, input.numRows, input.numCols) << endl;
    // cout << "Star 2 solution " << star2(integerFarm, input.numRows, input.numCols) << endl;
    return 0;
}