
#include <iostream>
#include <string>
#include <thread>
#include <chrono>
#include <vector>
using namespace std;

void f(char c) {
	for (int q = 5; q--; cout << q << c << this_thread::get_id() << endl)
		this_thread::sleep_for(chrono::milliseconds(777));
}

int sm(int a, int b) { return a + b; }
void fsm(int a, int b, int &c) { c = sm(a, b); }

int fi(int& t) {    return ++t; }

void obertka(vector<int> &pv, function<int(int&)> pf) {
	for (auto &t : pv)
		pf(t);
}


int main()
{
	int a, b, c, z; a = 2, b = 5;
	thread t3(fsm, a, b, std::ref(c));
	t3.join();
	a = 7;
	z = [&c](int a, int b)->int { return c = sm(a, b); }(a, b);
	a = 9;

	auto fL = [&c](int a, int b)->int { return ( c = sm(a, b)); };

	cout << z << "\nc=" << c;
	
	function<int(int&)> pf = fi;
	function<int(int &)> pfL = [&a](int &p) {return ++p+ ++a; };
	cout << endl << pfL(b);

	vector<int> v {11, 7, 19, 3};
	obertka(v, [](int& t)->int { return ++t; });
	return 111;
}