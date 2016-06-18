#include <iostream>
#include <vector>
#include <map>
#include <iomanip>
#include <string>

using namespace std;

int main(void)
{
	int n;
	cin >> n;
	vector<string> member(n);
	for (int i = 0; i < n; i++) cin >> member[i];
	map<string, vector<string>> go;
	
	int m;
	cin >> m;
	for (int i = 0; i < m; i++) {
		string x, y;
		cin >> x >> y;
		go[x].push_back(y);
		// go[y].push_back(x); //無向グラフなら
	}
	map<string, double> rank_prev;
	for (int i = 0; i < n; i++) rank_prev[member[i]] = 100;
	int finish = 100;
	for (int i = 0; i < finish; i++) {
		map<string, double> rank;
		for (int j = 0; j < n; j++) {
			for (int k = 0; k < (int)go[member[j]].size(); k++) {
				rank[go[member[j]][k]] += rank_prev[member[j]] / (double)go[member[j]].size();
				// cout << rank_prev[member[j]] << " " << go[member[j]].size() << " " << rank_prev[member[j]] / (double)go[member[j]].size() << " " << rank[go[member[j]][k]] << endl;
			}
		}
		cout << setw(4) << i + 1 << " ";
		for (int j = 0; j < n; j++) cout << setw(5) << rank[member[j]] << " ";
		cout << endl;
		rank_prev = rank;
	}
	return 0;
}
		

