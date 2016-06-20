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
	vector<pair<string, string>> go;
	umap<string, int> edge;
	
	int m;
	cin >> m;
	string x, y;
	for (int i = 0; i < m; i++) {
		cin >> x >> y;
		go.push_back(make_pair(x, y));
		edge[x]++;
	}

	double tstart = gettime();

	umap<string, double> rank_prev;
	for (int i = 0; i < n; i++) rank_prev[member[i]] = 100;
	int finish = 1024;
	for (int i = 0; i < finish; i++) {
		cout << i << endl;
		umap<string, double> rank;
		for (int j = 0; j < n; j++) if (!edge[member[j]]) rank[member[j]] = rank_prev[member[j]];
		for (int j = 0; j < (int)go.size(); j++) {
			rank[go[j].second] += rank_prev[go[j].first] / (double)edge[go[j].first];
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
		

