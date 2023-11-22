
#include <iostream>
#include <rat/mod_a/header1.hpp>
#include <rat/mod_so/header2.hpp>

using namespace rat;
using namespace std;

int main()
{
	auto r1 = fun1(1, 1);
	auto r2 = fun1(2, 2);
	cout << r1 << ' ' << r2 << endl;
	return 0;
}
