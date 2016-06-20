#include <iostream>
#include <vector>
#include <map>
#include <iomanip>
#include <string>
#include <unordered_map>
#include <sys/time.h>

using namespace std;

#define umap unordered_map

double gettime(void)
{
	struct timeval t;
	gettimeofday(&t, NULL);
	return (double)t.tv_sec + (double)t.tv_usec * 1e-6;
}

int main(void)
{
	int n;
	cin >> n;
	vector<string> member(n);
	for (int i = 0; i < n; i++) cin >> member[i];
	umap<string, vector<string>> go;
	
	int m;
	cin >> m;
	string x, y;
	for (int i = 0; i < m; i++) {
		cin >> x >> y;
		go[x].push_back(y);
		// go[y].push_back(x); //無向グラフなら
	}

	double tstart = gettime();

	umap<string, double> rank_prev;
	for (int i = 0; i < n; i++) rank_prev[member[i]] = 100;
	int finish = 1024;
	for (int i = 0; i < finish; i++) {
		cout << i << endl;
		umap<string, double> rank;
		for (int j = 0; j < n; j++) {
			if (!go[member[j]].size()) rank[member[j]] += rank_prev[member[j]];
			double plus = rank_prev[member[j]] / (double)go[member[j]].size();
			for (int k = 0; k < (int)go[member[j]].size(); k++) {
				rank[go[member[j]][k]] += plus;
			}
		}
		// cout << setw(4) << i + 1 << " ";
		// for (int j = 0; j < n; j++) cout << setw(5) << rank[member[j]] << " ";
		// cout << endl;
		rank_prev = rank;
	}
	double tend = gettime();
	for (int j = 0; j < n; j++) cout << setw(5) << rank_prev[member[j]] << " ";
	cout << endl;
	cout << tend - tstart << endl;
	return 0;
}
		

