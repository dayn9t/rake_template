
#include <iostream>
#include <hen/net/header1.hpp>
#include <hen/mod_so/header2.hpp>

using namespace hen;
using namespace std;

int main()
{
	auto r1 = multiply(1, 1);
	auto r2 = multiply(2, 2);
	cout << r1 << ' ' << r2 << endl;
	return 0;
}
