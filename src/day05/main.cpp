#include <iostream>
#include <fstream>
#include <sstream>
#include <set>
using namespace std;

int star1(vector<vector<int>> rules, vector<vector<int>> updates)
{
    vector<bool> is_correct_order;
    for (int j = 0; j < updates.size(); j++)
    {
        unordered_map<int, int> updates_idx_map;
        for (int i = 0; i < updates[j].size(); i++)
        {
            updates_idx_map[updates[j][i]] = i;
        }

        bool correct_order = true;
        for (int i = 0; i < rules.size(); i++)
        {
            int a, b;
            a = rules[i][0];
            b = rules[i][1];
            if (updates_idx_map[a] > updates_idx_map[b] && updates_idx_map[b] != 0)
            {
                correct_order = false;
            }
        }
        is_correct_order.push_back(correct_order);
    }

    int running_total = 0;
    for (int i = 0; i < is_correct_order.size(); i++)
    {
        if (is_correct_order[i])
        {
            int N = updates[i].size();
            N = (N + 1) / 2;
            running_total += updates[i][N];
        }
    }
    return running_total;
}

int star2(vector<vector<int>> rules, vector<vector<int>> updates)
{
    set<int> incorrect_order_idxs;
    for (int j = 0; j < updates.size(); j++)
    {
        unordered_map<int, int> updates_idx_map;
        for (int i = 0; i < updates[j].size(); i++)
        {
            updates_idx_map[updates[j][i]] = i;
        }

        for (int i = 0; i < rules.size(); i++)
        {
            int a, b;
            a = rules[i][0];
            b = rules[i][1];
            if (updates_idx_map[a] > updates_idx_map[b] &&
                updates_idx_map[a] != 0 && updates_idx_map[b] != 0)
            {
                incorrect_order_idxs.insert(j);
                int tmp;
                tmp = updates[j][updates_idx_map[a]];
                updates[j][updates_idx_map[a]] = updates[j][updates_idx_map[b]];
                updates[j][updates_idx_map[b]] = tmp;

                j -= 1;
                break;
            }
        }
    }

    int running_total = 0;
    for (const int &element : incorrect_order_idxs)
    {
        int N = updates[element].size() / 2;
        running_total += updates[element][N];
    }
    return running_total;
}

int main()
{

    ifstream file("rules.txt");
    vector<vector<int>> rules;
    string rule;
    while (getline(file, rule))
    {
        stringstream ss(rule);
        int a = -1, b = -1;
        char seperator = '|';
        ss >> a >> seperator >> b;
        vector<int> rule_vector;
        rule_vector.push_back(a);
        rule_vector.push_back(b);
        rules.push_back(rule_vector);
    }

    ifstream updates_file("updates.txt");
    vector<vector<int>> updates;
    string update;
    while (getline(updates_file, update))
    {
        stringstream ss(update);
        vector<int> pages;
        string tmp_str;
        pages.push_back(-1);
        while (getline(ss, tmp_str, ','))
        {
            pages.push_back(stoi(tmp_str));
        }
        updates.push_back(pages);
    }

    cout << "Star 1 solution " << star1(rules, updates) << endl;
    cout << "Star 2 solution " << star2(rules, updates) << endl;
    return 0;
}

/*
Handy reading IO
auto read_file(const std::string &filename)
{
    auto file = std::ifstream{filename};

    auto rules = Rules{};
    auto updates = Updates{};

    for (std::string line; std::getline(file, line) && !line.empty();)
    {
        replace(line, '|', ' ');
        size_t page1, page2;
        std::istringstream{line} >> page1 >> page2;
        rules[page1].insert(page2);
    }

    for (std::string line; std::getline(file, line);)
    {
        replace(line, ',', ' ');
        auto iss = std::istringstream{line};
        copy(istream_iterator<size_t>{iss}, istream_iterator<size_t>{}, back_inserter(updates.emplace_back()));
    }

    return std::make_pair(std::move(rules), std::move(updates));
}
*/