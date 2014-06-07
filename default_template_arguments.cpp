#include <iostream>
#include <algorithm>
#include <functional>
#include <vector>

using namespace std;

template <typename T, typename F = less<typename T::value_type>> void Sort(T& t, F f = F())
{
	sort(t.begin(), t.end(), f);
}

template <typename C> void Print(const C& c)
{
	for (auto &i : c)
	{
		cout << i << " ";
	}
	cout << endl;
}

int main(int argc, char const *argv[])
{
vector<int> v {19,3,5,7,9,12,13,51,12,21,3,24,42,42,24,25,36,74,47,4884,489,95,54,4,47,4,2};


	cout <<"Hello world" << endl;
	Print(v);
	Sort(v);
	Print(v);
	Sort(v, greater<int>());
	Print(v);
	return 0;
}