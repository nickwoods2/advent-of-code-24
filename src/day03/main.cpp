#include <iostream>
#include <sstream>
using namespace std;

string extract_number(char a, char b, char c)
{
    string current_number = "";
    if (isdigit(a))
    {
        current_number = current_number + a;
        if (isdigit(b))
        {
            current_number = current_number + b;
            if (isdigit(c))
            {
                current_number = current_number + c;
            }
        }
    }
    return current_number;
}

bool update_system_state(bool current_state, string switch_instruction)
{
    if (switch_instruction == "don't()")
    {
        return false;
    }
    else
    {
        switch_instruction = switch_instruction.substr(0, 4);
        if (switch_instruction == "do()")
        {
            return true;
        }
    }
    return current_state;
}

int star1(string file)
{
    int N = file.length();
    int running_total = 0;
    for (int i = 0; i < N; i++)
    {
        string start = file.substr(i, 4);
        if (start == "mul(")
        {
            string a = "";
            a = extract_number(file[i + 4], file[i + 5], file[i + 6]);
            int ptr1 = i + 4 + a.length();
            string b = "";
            b = extract_number(file[ptr1 + 1], file[ptr1 + 2], file[ptr1 + 3]);
            int ptr2 = ptr1 + 1 + b.length();
            if (file[ptr1] == ',' && file[ptr2] == ')' && a.length() > 0 && b.length() > 0)
            {
                int a_int = stoi(a);
                int b_int = stoi(b);
                running_total += a_int * b_int;
            }
        }
    }
    return running_total;
}

int star2(string file)
{
    bool do_mul = true;
    int N = file.length();
    int running_total = 0;
    for (int i = 0; i < N; i++)
    {
        do_mul = update_system_state(do_mul, file.substr(i, 7));
        string start = file.substr(i, 4);
        if (start == "mul(")
        {
            string a = "";
            a = extract_number(file[i + 4], file[i + 5], file[i + 6]);
            int ptr1 = i + 4 + a.length();
            string b = "";
            b = extract_number(file[ptr1 + 1], file[ptr1 + 2], file[ptr1 + 3]);
            int ptr2 = ptr1 + 1 + b.length();
            if (file[ptr1] == ',' && file[ptr2] == ')' && a.length() > 0 && b.length() > 0 && do_mul)
            {
                int a_int = stoi(a);
                int b_int = stoi(b);
                running_total += a_int * b_int;
            }
        }
    }
    return running_total;
}

int main()
{
    string chunk;
    string file = "";
    while (cin >> chunk)
        file = file + chunk;

    cout << "Star 1 solution " << star1(file) << endl;
    cout << "Star 2 solution " << star2(file) << endl;
    return 0;
}
