#include "Timer.h"
#include <Matrix4x4.h>
#include <iostream>
#include <vector>
#include <type_traits>
#include "ComponentStorage.h"
#include "ComponentWorld.h"
#include <typeindex>
#include <memory>
using namespace std;
template <typename T>
bool IsTrue(T t)
{
	return t > 0;
}
template<typename First>
bool CheckStatus(First first)
{
	return IsTrue(first);
}
template<typename First, typename ... T>
bool CheckStatus(First first, T... t)
{
	return IsTrue(first) && CheckStatus(t...);
}
static int counter = 0;
template<typename T>
struct Test
{
	const int size = (++counter);
};
int main()
{
	Test<int> ints;
	Test<string> strings;

	cout << ints.size << endl;
	cout << strings.size << endl;
}