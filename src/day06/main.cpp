#include <iostream>
#include <fstream>
#include <sstream>
#include <set>
using namespace std;

int star1(vector<vector<char>> room, array<int, 2> position, char direction)
{
    char object_ahead = '.';
    int i = position[0], j = position[1];
    int i_ahead, j_ahead;
    set<array<int, 2>> visited;
    while (true)
    {
        array<int, 2> position = {i, j};
        visited.insert(position);
        if (direction == '^')
        {
            i_ahead = i - 1;
            j_ahead = j;
        }
        else if (direction == 'v')
        {
            i_ahead = i + 1;
            j_ahead = j;
        }
        else if (direction == '>')
        {
            i_ahead = i;
            j_ahead = j + 1;
        }
        else if (direction == '<')
        {
            i_ahead = i;
            j_ahead = j - 1;
        }
        object_ahead = room[i_ahead][j_ahead];
        if (object_ahead == 'Z')
        {
            break;
        }
        else if (object_ahead == '#')
        {
            if (direction == '^')
            {
                direction = '>';
            }
            else if (direction == 'v')
            {
                direction = '<';
            }
            else if (direction == '>')
            {
                direction = 'v';
            }
            else if (direction == '<')
            {
                direction = '^';
            }
        }
        else
        {
            i = i_ahead;
            j = j_ahead;
        }
    }
    return visited.size();
}

bool loop_exists(vector<vector<char>> room, array<int, 2> position, char direction)
{
    // Initial guard state
    array<int, 2> starting_position = position;
    char starting_direction = direction;

    // Return true if guard ever returns to a previously visited state
    char object_ahead = '.';
    int i = position[0], j = position[1];
    int i_ahead, j_ahead;
    set<array<int, 3>> visited;
    while (true)
    {
        int direction_int = direction;
        array<int, 3> position = {i, j, direction_int};
        visited.insert(position);
        if (direction == '^')
        {
            i_ahead = i - 1;
            j_ahead = j;
        }
        else if (direction == 'v')
        {
            i_ahead = i + 1;
            j_ahead = j;
        }
        else if (direction == '>')
        {
            i_ahead = i;
            j_ahead = j + 1;
        }
        else if (direction == '<')
        {
            i_ahead = i;
            j_ahead = j - 1;
        }
        object_ahead = room[i_ahead][j_ahead];
        if (object_ahead == 'Z')
        {
            return false;
        }
        else if (object_ahead == '#')
        {
            if (direction == '^')
            {
                direction = '>';
            }
            else if (direction == 'v')
            {
                direction = '<';
            }
            else if (direction == '>')
            {
                direction = 'v';
            }
            else if (direction == '<')
            {
                direction = '^';
            }
        }
        else
        {
            i = i_ahead;
            j = j_ahead;
        }
        direction_int = direction;
        array<int, 3> new_position = {i, j, direction_int};
        if (visited.find(new_position) != visited.end())
        {
            return true;
        }
    }
}

int star2(vector<vector<char>> room, array<int, 2> position, char direction)
{
    bool is_loop = false;
    int num_loops = 0;
    int total = room.size() * room[0].size();
    int counter = 0;
    for (int i = 1; i < room.size() - 1; i++)
    {
        for (int j = 1; j < room[i].size() - 1; j++)
        {
            if (i == position[0] && j == position[1])
            {
                continue;
            }
            char placeholder = room[i][j];
            room[i][j] = '#';
            is_loop = loop_exists(room, position, direction);
            room[i][j] = placeholder;
            counter += 1;
            if (is_loop)
            {
                num_loops += 1;
            }
        }
    }
    return num_loops;
}

int main()
{
    vector<vector<char>> room;
    ifstream file("input.txt");
    char pad_char = 'Z';
    array<int, 2> position = {0, 0};
    char direction = '^';
    int i = 1, j = 1;
    for (string line; getline(file, line) && !line.empty();)
    {
        vector<char> room_row;
        room_row.push_back(pad_char);
        j = 1;
        for (char ch : line)
        {
            if (ch == '^' || ch == 'v' || ch == '>' || ch == '<')
            {
                position = {i, j};
                direction = ch;
            }
            room_row.push_back(ch);
            j++;
        }
        room_row.push_back(pad_char);
        room.push_back(room_row);
        i++;
    }
    vector<char> pad_vector(room[0].size(), 'Z');
    room.insert(room.begin(), pad_vector);
    room.push_back(pad_vector);

    cout << "Star 1 solution " << star1(room, position, direction) << endl;
    cout << "Star 2 solution " << star2(room, position, direction) << endl;
    return 0;
}