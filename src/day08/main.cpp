#include <iostream>
#include <fstream>
#include <sstream>
#include <utility>
#include <set>
using namespace std;

struct Input
{
    unordered_map<char, vector<pair<int, int>>> antenna_positions;
    int num_rows;
    int num_cols;
};

Input read_input()
{
    unordered_map<char, vector<pair<int, int>>> antenna_positions;
    pair<int, int> position;
    ifstream file("input.txt");
    int row = 0, col = 0;
    for (string line; getline(file, line) && !line.empty();)
    {
        col = 0;
        for (char ch : line)
        {
            int a = ch;
            if (ch != '.')
            {
                pair<int, int> position = {row, col};
                antenna_positions[ch].push_back(position);
            }
            col++;
        }
        row++;
    }
    int num_rows = row;
    int num_cols = col;
    return Input{antenna_positions, num_rows, num_cols};
}

bool valid_position(pair<int, int> position,
                    int num_rows,
                    int num_cols)
{
    bool inside = position.first >= 0 && position.first < num_rows &&
                  position.second >= 0 && position.second < num_cols;
    return inside;
}

vector<pair<int, int>> get_antinodes(pair<int, int> first_antenna_pos,
                                     pair<int, int> second_antenna_pos,
                                     int num_rows,
                                     int num_cols,
                                     int star)
{
    vector<pair<int, int>> antinodes;
    pair<int, int> antinode;

    int delta_row = first_antenna_pos.first - second_antenna_pos.first;
    int delta_col = first_antenna_pos.second - second_antenna_pos.second;
    int updated_row, updated_col;

    // First direction
    updated_row = first_antenna_pos.first;
    updated_col = first_antenna_pos.second;
    if (star == 1)
    {
        updated_row += delta_row;
        updated_col += delta_col;
    }
    while (true)
    {
        antinode = {updated_row,
                    updated_col};
        if (valid_position(antinode, num_rows, num_cols))
        {
            antinodes.push_back(antinode);
            if (star == 1)
            {
                break;
            }
            updated_row += delta_row;
            updated_col += delta_col;
        }
        else
        {
            break;
        }
    }

    // Second direction
    updated_row = second_antenna_pos.first;
    updated_col = second_antenna_pos.second;
    if (star == 1)
    {
        updated_row -= delta_row;
        updated_col -= delta_col;
    }
    while (true)
    {
        antinode = {updated_row,
                    updated_col};
        if (valid_position(antinode, num_rows, num_cols))
        {
            antinodes.push_back(antinode);
            if (star == 1)
            {
                break;
            }
            updated_row -= delta_row;
            updated_col -= delta_col;
        }
        else
        {
            break;
        }
    }
    return antinodes;
}

int star1(Input input)
{
    set<pair<int, int>> antinodes;
    vector<pair<int, int>> antinodes_placeholder;
    int star = 1;
    for (const auto &kv_pairs : input.antenna_positions)
    {
        char key = kv_pairs.first;
        vector<pair<int, int>> val = kv_pairs.second;
        int num_antennas = kv_pairs.second.size();
        for (int i = 0; i < num_antennas; i++)
        {
            for (int j = i + 1; j < num_antennas; j++)
            {
                antinodes_placeholder = get_antinodes(val[i], val[j],
                                                      input.num_rows,
                                                      input.num_cols,
                                                      star);
                for (pair<int, int> antinode : antinodes_placeholder)
                {
                    antinodes.insert(antinode);
                }
            }
        }
    }
    return antinodes.size();
}

int star2(Input input)
{
    set<pair<int, int>> antinodes;
    vector<pair<int, int>> antinodes_placeholder;
    int star = 2;
    for (const auto &kv_pairs : input.antenna_positions)
    {
        char key = kv_pairs.first;
        vector<pair<int, int>> val = kv_pairs.second;
        int num_antennas = kv_pairs.second.size();
        for (int i = 0; i < num_antennas; i++)
        {
            for (int j = i + 1; j < num_antennas; j++)
            {
                antinodes_placeholder = get_antinodes(val[i], val[j],
                                                      input.num_rows,
                                                      input.num_cols,
                                                      star);
                for (pair<int, int> antinode : antinodes_placeholder)
                {
                    antinodes.insert(antinode);
                }
            }
        }
    }
    return antinodes.size();
}

int main()
{
    Input input = read_input();
    cout << "Star 1 solution " << star1(input) << endl;
    cout << "Star 2 solution " << star2(input) << endl;
    return 0;
}