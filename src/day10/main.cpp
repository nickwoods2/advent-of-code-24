#include <iostream>
#include <fstream>
#include <sstream>
#include <set>
#include <utility>
using namespace std;

struct Input
{
    vector<vector<int>> map;
    set<pair<int, int>> startingPositions;
};

Input readInput(string filename)
{
    ifstream file(filename);
    vector<vector<int>> map{};
    string line{};
    set<pair<int, int>> startingPositions{};
    int rowNum{}, colNum{};
    while (getline(file, line))
    {
        vector<int> row{};
        colNum = 0;
        for (char ch : line)
        {
            if (ch != '.')
            {
                if (ch - '0' == 0)
                {
                    startingPositions.insert(make_pair(rowNum, colNum));
                }
                row.push_back(ch - '0');
                colNum++;
            }
            else
            {
                row.push_back(-1);
            }
        }
        rowNum++;
        map.push_back(row);
    }
    return Input{map, startingPositions};
}

bool inside(pair<int, int> position, int numRows, int numCols)
{
    return position.first >= 0 && position.first < numRows &&
           position.second >= 0 && position.second < numCols;
}

vector<pair<int, int>> getAdjacentPositions(pair<int, int> currentPosition)
{
    int i = currentPosition.first, j = currentPosition.second;
    vector<pair<int, int>> adjacentPositions = {{i, j + 1},  // right
                                                {i + 1, j},  // down
                                                {i, j - 1},  // left
                                                {i - 1, j}}; // up
    return adjacentPositions;
}

vector<int> getAdjacentHeights(vector<vector<int>> map, pair<int, int> position)
{
    vector<int> adjacentHeights;
    int i = position.first, j = position.second;
    vector<pair<int, int>> adjacentPositions = getAdjacentPositions(position);
    for (pair<int, int> position : adjacentPositions)
    {
        if (inside(position, map.size(), map[0].size()))
        {
            adjacentHeights.push_back(map[position.first][position.second]);
        }
        else
        {
            adjacentHeights.push_back(-1);
        }
    }
    return adjacentHeights;
}

set<pair<int, int>> stepUp(vector<vector<int>> map, int currentHeight,
                           pair<int, int> currentPosition,
                           set<pair<int, int>> visited)
{
    if (currentHeight == 9)
    {
        visited.insert(currentPosition);
        return visited;
    }
    vector<pair<int, int>> adjacentPositions = getAdjacentPositions(currentPosition);
    vector<int> adjacentHeights = getAdjacentHeights(map, currentPosition);
    int newHeight = currentHeight + 1;
    int height{};
    pair<int, int> newPosition{};
    for (int i = 0; i < 4; i++)
    {
        height = adjacentHeights[i];
        newPosition = adjacentPositions[i];
        if (height == newHeight)
        {
            visited = stepUp(map, newHeight, newPosition, visited);
        }
    }
    return visited;
}

int stepUpPartTwo(vector<vector<int>> map, int currentHeight,
                  pair<int, int> currentPosition)
{
    if (currentHeight == 9)
    {
        return 1;
    }
    vector<pair<int, int>> adjacentPositions = getAdjacentPositions(currentPosition);
    vector<int> adjacentHeights = getAdjacentHeights(map, currentPosition);
    int newHeight = currentHeight + 1;
    int height{};
    int numTrails{};
    pair<int, int> newPosition{};
    for (int i = 0; i < 4; i++)
    {
        height = adjacentHeights[i];
        newPosition = adjacentPositions[i];
        if (height == newHeight)
        {
            numTrails += stepUpPartTwo(map, newHeight, newPosition);
        }
    }
    return numTrails;
}

int star1(Input input)
{
    int answer = 0;
    for (pair<int, int> startingPosition : input.startingPositions)
    {
        set<pair<int, int>> visited{};
        visited = stepUp(input.map, 0, startingPosition, visited);
        answer += visited.size();
    }
    return answer;
}

int star2(Input input)
{
    int answer = 0;
    for (pair<int, int> startingPosition : input.startingPositions)
    {
        answer += stepUpPartTwo(input.map, 0, startingPosition);
    }
    return answer;
}

int main()
{
    Input input = readInput("input.txt");
    cout << "Star 1 solution " << star1(input) << endl;
    cout << "Star 2 solution " << star2(input) << endl;
    return 0;
}