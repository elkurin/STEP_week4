#include <iostream>
#include <vector>
#include <fstream>
#include <ostream>
#include <random>
#include <map>

using namespace std;

random_device rd;

#define rep(i, n) for (int i = 0; i < (int)n; i++)
#define vec vector

namespace {
	ofstream create("random_data.txt");
}

int main(void)
{
	int n;
	cin >> n;
	create << n << endl;
	vec<int> node(n);
	rep(i, n) {
		node[i] = i;
		create << i << endl;
	}

	int m;
	cin >> m;
	create << m << endl;
	rep(i, m) {
		int a = rd() % n;
		int b = a;
		while(a == b) b = rd() % n;
		create << a << " " << b << endl;
	}
	return 0;
}
