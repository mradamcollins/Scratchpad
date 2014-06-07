/** unique_ptr doesn't have a make_unique (only available in c++14)
therefor we use variadic templates and perfect forwarding to provide the 
same functionality **/
using namespace std;
#include <memory>
#include <iostream>
#include <string>
#include <type_traits>
#include <utility>

template <typename T, typename... Args> unique_ptr<T> make_unique_helper(false_type, Args&&... args)
{
	return unique_ptr<T>(new T(forward<Args>(args)...));
}

template <typename T, typename... Args> unique_ptr<T> make_unique_helper(true_type, Args&&... args)
{
	static_assert(extent<T>() == 0, "make_unique<T[n] is forbidden, use make_unique<T[]> instead");
	typedef typename remove_extent<T>::type U;
	return unique_ptr<T>(new U[sizeof...(Args)]{forward<Args>(args)...});
}

template <typename T, typename... Args> unique_ptr<T> make_unique(Args&&... args)
{
	return make_unique_helper<T>(is_array<T>(), forward<Args>(args)...);
}


int main(int argc, char const *argv[])
{
	auto i = make_unique<int>(1234);
	cout << *i << endl;
	auto s = make_unique<string>(5, 'x');
	cout << *s << endl;
	auto a = make_unique<int[]>(1,2,3);
	cout << a[2] << endl;
	//auto err = make_unique<int[5]>(1,2,3,4,5);
	return 0;
}