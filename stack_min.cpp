#include <iostream>
#include <stack>

using namespace std;

int main(void)
{
	stack<int> box;
	stack<int> minimum;

	while(1) {
		int get;
		cin >> get;
		if (get == 0) break;
		box.push(get);
		if (minimum.empty() || minimum.top() >= get) minimum.push(get);
	}

	while(!box.empty()) {
		cout << minimum.top() << endl;
		int get = box.top();
		box.pop();
		if (get == minimum.top()) minimum.pop();
	}
	return 0;
}

