#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

struct Input
{
    string disk_map;
};

Input read_input(string filename)
{
    ifstream file("input.txt");
    string disk_map;
    getline(file, disk_map);
    return Input{disk_map};
}

vector<string> expand(string disk_view)
{
    int isFile = 1;
    int num_blocks;
    int id = 0;
    vector<string> disk_view_expanded;
    for (char ch : disk_view)
    {
        num_blocks = ch - '0'; // Interesting...
        if (isFile)
        {
            for (int i = 0; i < num_blocks; i++)
            {
                disk_view_expanded.push_back(to_string(id));
            }
            id++;
            isFile = 0;
        }
        else
        {
            for (int i = 0; i < num_blocks; i++)
            {
                disk_view_expanded.push_back(".");
            }
            isFile = 1;
        }
    }
    return disk_view_expanded;
}

long long checksum(vector<string> disk_map_fragmented)
{
    long long total = 0;
    int i = 0;
    for (string block : disk_map_fragmented)
    {
        if (block != "." && block != "\0")
        {
            total += stoi(disk_map_fragmented[i]) * i;
        }
        i++;
    }
    return total;
}

long long star1(vector<string> disk_map_fragmented)
{
    int left = 0, right = disk_map_fragmented.size();
    for (string block : disk_map_fragmented)
    {
        if (block == ".")
        {
            while (disk_map_fragmented[right] == "." ||
                   disk_map_fragmented[right] == "\0")
            {
                right--;
            }
            disk_map_fragmented[left] = disk_map_fragmented[right];
            disk_map_fragmented[right] = ".";
            right--;
        }
        left++;
        if (left == right)
        {
            break;
        }
    }
    return checksum(disk_map_fragmented);
}

long long star2(vector<string> disk_map_fragmented)
{
    int left = 0;
    string block;
    for (int right = disk_map_fragmented.size(); right > 0; right--)
    {
        block = disk_map_fragmented[right];
        if (block != "." && block != "\0")
        {
            int fileSize = 0;
            string fileId = block;
            while (disk_map_fragmented[right] == fileId)
            {
                fileSize++;
                right--;
            }
            int voidSize = 0;
            int isVoid = 0;
            for (int left = 0;
                 left <= right + 1;
                 left++)
            {
                if (disk_map_fragmented[left] == ".")
                {
                    voidSize++;
                }
                else
                {
                    if (voidSize == 0)
                    {
                        continue;
                    }
                    if (fileSize <= voidSize)
                    {
                        for (int j = 0; j < fileSize; j++)
                        {
                            disk_map_fragmented[left - voidSize + j] = fileId;
                            disk_map_fragmented[right + j + 1] = ".";
                        }
                        right++;
                        break;
                    }
                    voidSize = 0;
                }
            }
            right++;
        }
    }
    return checksum(disk_map_fragmented);
}

int main()
{
    string filename = "input.txt";
    Input input = read_input(filename);
    vector<string> disk_map_fragmented = expand(input.disk_map);

    cout << "Star 1 solution " << star1(disk_map_fragmented) << endl;
    cout << "Star 2 solution " << star2(disk_map_fragmented) << endl;
    return 0;
}