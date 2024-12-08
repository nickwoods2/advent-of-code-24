#include <iostream>
#include <fstream>
#include <sstream>
#include <set>
using namespace std;

struct Input
{
    vector<long long> totals;
    vector<vector<long long>> components;
};

Input read_input()
{
    vector<string> calibation_equations;
    ifstream file("input.txt");
    for (string line; getline(file, line) && !line.empty();)
    {
        for (long long i = 0; i < line.size(); i++)
        {
            if (line[i] == ':')
            {
                line[i] = ' ';
            }
        }
        calibation_equations.push_back(line);
    }

    vector<long long> totals;
    vector<vector<long long>> components;
    long long num;
    for (const auto &equation : calibation_equations)
    {
        stringstream ss(equation);
        vector<long long> components_given_expression;
        bool isFirst = true;
        while (ss >> num)
        {
            if (isFirst)
            {
                totals.push_back(num);
                isFirst = false;
            }
            else
            {
                components_given_expression.push_back(num);
            }
        }
        components.push_back(components_given_expression);
    }
    return Input{totals, components};
}

set<string> get_permutations(vector<char> possible_operations, int num_operations)
{
    set<string> permutations;
    string permutation = "";
    for (int i = 0; i < num_operations; i++)
    {
        permutation += possible_operations[0];
    }
    permutations.insert(permutation);

    for (int k = 1; k < possible_operations.size(); k++)
    {
        char swap_operator = possible_operations[k];
        for (int j = 0; j < num_operations; j++)
        {
            for (const string permutation : permutations)
            {
                for (long long i = 0; i < num_operations; i++)
                {
                    string tmp = permutation;
                    tmp[i] = swap_operator;
                    permutations.insert(tmp);
                }
            }
        }
    }
    return permutations;
}

long long get_result(Input calibration_equations, vector<char> possible_operations)
{
    set<int> expression_sizes;
    for (int j = 0; j < calibration_equations.totals.size(); j++)
    {
        expression_sizes.insert(calibration_equations.components[j].size() - 1);
    }

    unordered_map<int, set<string>> permutations_cached;
    set<string> permutations;
    for (int size : expression_sizes)
    {
        permutations = get_permutations(possible_operations, size);
        permutations_cached[size] = permutations;
    }

    long long result = 0;
    for (int j = 0; j < calibration_equations.totals.size(); j++)
    {
        vector<long long> components = calibration_equations.components[j];
        long long correct_total = calibration_equations.totals[j];
        int num_operations = calibration_equations.components[j].size() - 1;

        permutations = permutations_cached[num_operations];
        long long running_total = 0;
        for (const string &permutation : permutations)
        {
            running_total = components[0];
            for (int i = 0; i < num_operations; i++)
            {
                if (permutation[i] == '+')
                {
                    running_total += components[i + 1];
                }
                else if (permutation[i] == '*')
                {
                    running_total *= components[i + 1];
                }
                else if (permutation[i] == '|')
                {
                    string left = to_string(running_total);
                    string right = to_string(components[i + 1]);
                    string concat = left + right;
                    running_total = stoll(concat);
                }
            }
            if (running_total == correct_total)
            {
                result += running_total;
                break;
            }
        }
    }
    return result;
}

long long star1(Input calibration_equations)
{
    vector<char> possible_operations = {'+', '*'};
    return get_result(calibration_equations, possible_operations);
}
long long star2(Input calibration_equations)
{
    vector<char> possible_operations = {'+', '*', '|'};
    return get_result(calibration_equations, possible_operations);
}

int main()
{
    Input calibation_equations = read_input();
    cout << "Star 1 solution " << star1(calibation_equations) << endl;
    cout << "Star 2 solution " << star2(calibation_equations) << endl;
    return 0;
}