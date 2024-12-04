#include <iostream>
#include <sstream>
using namespace std;

int get_xmas_count(string line)
{
    int N = line.length();
    int count = 0;
    for (int i = 0; i < N; i++)
    {
        string possible_xmas = line.substr(i, 4);
        if (possible_xmas == "XMAS")
        {
            count += 1;
        }
    }
    return count;
}

vector<string> transpose(vector<string> lines)
{
    int dim1 = lines.size();
    int dim2 = lines[0].length();
    vector<string> lines_transposed;
    for (int i = 0; i < dim2; i++)
    {
        string line(dim1, ' ');
        lines_transposed.push_back(line);
    }
    for (int i = 0; i < dim2; i++)
    {
        for (int j = 0; j < dim1; j++)
        {
            lines_transposed[i][j] = lines[j][i];
        }
    }
    return lines_transposed;
}

string get_diagonal(vector<string> lines, int offset)
{
    int dim1 = lines.size();
    int dim2 = lines[0].length();
    string line = "";
    for (int i = 0; i < dim1; i++)
    {
        for (int j = 0; j < dim2; j++)
        {
            if (i + offset == j)
            {
                line = line + lines[i][j];
            }
        }
    }
    return line;
}

int star1(vector<string> lines)
{
    int N = lines.size();
    int num_xmas = 0;

    // original matrix
    for (int i = 0; i < N; i++)
    {
        string current_line = lines[i];
        num_xmas += get_xmas_count(current_line);
        reverse(current_line.begin(), current_line.end());
        num_xmas += get_xmas_count(current_line);
    }
    // original matrix diagonals
    int offset = -lines.size() + 1;
    int max_offset = 2 * (lines.size() - 1) + 1;
    for (int i = offset; i < max_offset; i++)
    {
        string current_line = get_diagonal(lines, i);
        num_xmas += get_xmas_count(current_line);
        reverse(current_line.begin(), current_line.end());
        num_xmas += get_xmas_count(current_line);
    }
    // matrix transposed (and rotated)
    vector<string> lines_transposed = transpose(lines);
    vector<string> lines_rotated_90;
    for (int i = 0; i < lines_transposed.size(); i++)
    {
        string current_line = lines_transposed[i];
        num_xmas += get_xmas_count(current_line);
        reverse(current_line.begin(), current_line.end());
        lines_rotated_90.push_back(current_line);
        num_xmas += get_xmas_count(current_line);
    }
    // matrix rotated 90 diagonals
    for (int i = offset; i < max_offset; i++)
    {
        string current_line = get_diagonal(lines_rotated_90, i);
        num_xmas += get_xmas_count(current_line);
        reverse(current_line.begin(), current_line.end());
        num_xmas += get_xmas_count(current_line);
    }
    return num_xmas;
}

int star2()
{
    return 0;
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
    cout << "Star 2 solution " << star2() << endl;
    return 0;
}
