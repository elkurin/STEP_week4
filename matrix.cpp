/***************************************************

これは行列計算である
行列のべき乗である
ゆえにO(logSTEP)で計算できる
ただし収束判定がつらい？
あとノードやSTEP数に対して辺がかなり少ないグラフの場合、大量のゼロ倍を計算することになり無駄
並列で計算すればO(logN)で終わるかな？(それぞれの要素についてO(1)でおわる計算のものをN要素足すのでlogNで終わりそう)(そんなにうまくいくのか分からない)

圧倒的に要素の中に0が多いことが分かっているなら、0じゃない要素のみ持つ配列を保存しておいて計算すると、0じゃない数をMとしてO(M)で一回の計算が出きそう

***************************************************/

#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <iomanip>

using namespace std;

void printmat(vector<vector<double>> matrix)
{
	for (int i = 0; i < (int)matrix.size(); i++) {
		for (int j = 0; j < (int)matrix.size(); j++) cout << setw(4) << fixed << setprecision(4) << matrix[i][j] << " ";
		cout << endl;
	}
	// {{{ sum check
	// for (int i = 0; i < matrix.size(); i++) {
	// 	double sum = 0;
	// 	for (int j = 0; j < matrix.size(); j++) sum += matrix[j][i];
	// 	if (sum != 1.0) cout << "WRONG " << i << endl;
	// }
	// }}}
}

// {{{ 普通の行列積計算
/*
vector<vector<double>> mult(vector<vector<double>> a, vector<vector<double>> b)
{
	vector<vector<double>> c(a.size(), vector<double>(a.size(), 0));
	for (int i = 0; i < (int)a.size(); i++) {
		for (int j = 0; j < (int)a.size(); j++) {
			for (int k = 0; k < (int)a.size(); k++) {
				c[i][j] += a[i][k] * b[k][j];
			}
		}
	}
	return c;
}
*/
// }}}

// ノードに対して辺の数がかなり少ないと分かっているとき用の行列積計算
// 0にならない要素の数をMとするとO(M+N*N)で計算できる
vector<vector<double>> mult(vector<vector<double>> a, vector<vector<double>> b)
{
	vector<vector<double>> c(a.size(), vector<double>(a.size(), 0));
	vector<vector<double>> b_clean(a.size(), vector<double>());
	vector<vector<int>> index(a.size());
	for (int i = 0; i < (int)b.size(); i++) {
		for (int j = 0; j < (int)b.size(); j++) {
			if (b[i][j]) {
				b_clean[i].push_back(b[i][j]);
				index[i].push_back(j);
			}
			// b_clean[i].push_back(b[i][j]);
		}
	}
	for (int i = 0; i < (int)a.size(); i++) {
		for (int j = 0; j < (int)a.size(); j++) {
			if (!a[i][j]) continue;
			for (int k = 0; k < (int)b_clean[j].size(); k++) {
				c[i][index[j][k]] += a[i][j] * b_clean[j][k];
			}
		}
	}
	return c;
}

vector<double> mult(vector<vector<double>> a, vector<double> b)
{
	vector<double> c(a.size(), 0);
	for (int i = 0; i < (int)a.size(); i++) {
		for (int j = 0; j < (int)a.size(); j++) {
			c[i] += a[i][j] * b[j];
		}
	}
	return c;
}

/// {{{ 普通のべき乗計算, step=nのやつ, 下の奴はstep=2**n
/*
vector<vector<double>> matpow(vector<vector<double>> matrix, int n)
{
	vector<vector<double>> ret(matrix.size(), vector<double>(matrix.size(), 0));
	if (n == 0) {
		for (int i = 0; i < (int)matrix.size(); i++) ret[i][i] = 1;
		return ret;
	} else if (n % 2) {
		return mult(matrix, matpow(matrix, n - 1));
	} else {
		ret = mult(matrix, n / 2);
		return mult(ret, ret);
	}
}
*/
// }}}


vector<vector<double>> matpow(vector<vector<double>> matrix, int n)
{
	vector<vector<double>> ret(matrix.size(), vector<double>(matrix.size(), 0));
	for(int i = 0; i < n; i++) {
		cout << i << endl;
		ret = mult(matrix, matrix);
		matrix = ret;
		// printmat(matrix);
	}
	return ret;
}


int main(void)
{
	int n;
	cin >> n;
	vector<string> member(n);
	unordered_map<string, int> index;
	for (int i = 0; i < n; i++) {
		cin >> member[i];
		index[member[i]] = i;
	}

	unordered_map<string, vector<string>> go;
	int m;
	cin >> m;
	string x, y;
	for (int i = 0; i < m; i++) {
		cin >> x >> y;
		go[x].push_back(y);
	}

	vector<vector<double>> matrix(n, vector<double>(n, 0));
	for (int i = 0; i < n; i++) {
		if (!go[member[i]].size()) {
			matrix[i][i] = 1;
			continue;
		}
		double c = 1.0 / (double)go[member[i]].size();
		for (int j = 0; j < (int)go[member[i]].size(); j++) {
			matrix[index[go[member[i]][j]]][i] += c;
		}
	}
	// printmat(matrix);

	int step = 10;
	matrix = matpow(matrix, step);

	vector<double> rank(n, 100);
	rank = mult(matrix, rank);

	double sum = 0;
	for (int i = 0; i < n; i++) {
		cout << rank[i] << " ";
		sum += rank[i];
	}
	cout << endl;

	cout << sum << " " << 100 * n << endl;

	return 0;
}

