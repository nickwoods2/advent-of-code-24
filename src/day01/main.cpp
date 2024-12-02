#include <iostream>

using namespace std;

const int N = 1000;

int star1(vector<int> left, vector<int> right)
{
  sort(left.begin(), left.end());
  sort(right.begin(), right.end());

  int total = 0;
  for (int i = 0; i < N; i++)
  {
    total += abs(left[i] - right[i]);
  }
  return total;
}

int star2(vector<int> left, vector<int> right)
{
  unordered_map<int, int> hash_map;
  for (int i = 0; i < N; i++)
  {
    hash_map[left[i]] += 1;
  }
  int total = 0;
  for (int i = 0; i < N; i++)
  {
    total += hash_map[right[i]] * right[i];
  }
  return total;
}

int main()
{
  vector<int> left, right;
  for (int i = 0; i < N; i++)
  {
    int a, b;
    cin >> a >> b;
    left.push_back(a);
    right.push_back(b);
  }
  cout << "Star 1 solution " << star1(left, right) << endl;
  cout << "Star 2 solution " << star2(left, right) << endl;
  return 0;
}
