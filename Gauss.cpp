#include <bits/stdc++.h>
#include <unistd.h>
using namespace std;
using ll = long long;
using ld = double;
const int mxn = 2e5+10;
const ld EPS = 1e-9;
const int inf = 1e9;
const unsigned int microsecond = 1000000;

int gauss(vector<vector<ld> >  a, vector<ld> &ans) {
	int n = a.size(), m = a[0].size()-1;

	vector<int> free(m, 0), where(m, 0);
	for(int row = 0, col = 0; row<n and col<m; col++) {
		int k = row; 
		for(int i=row+1; i<n; i++) 
			if(abs(a[i][col])>abs(a[k][col]))
				k = i;

		if(abs(a[k][col])<EPS) {
			free[col] = 1;
			continue;
		}

		swap(a[k], a[row]);

		for(int i=col+1; i<=m; i++) a[row][i]/=a[row][col];
		a[row][col] = 1;

		for(int i=0; i<n; i++) if(i!=row) {
			for(int j=m; j>=col; j--) {
				a[i][j] -= a[row][j]*a[i][col];
			}
		}

		where[col] = row;
		row++;
	}

	//Constructing answer
	ans.resize(m);
	for(int i=0; i<m; i++) {
		if(free[i]) ans[i] = 0;
		else ans[i] = a[where[i]][m];
	}

	//Retest

	for(int row = 0; row<n; row++) {
		ld b_test = 0;
		for(int j=0; j<m; j++) b_test+=a[row][j]*ans[j];
		if(abs(b_test-a[row][m])>EPS) return 0;
	}

	for(int i=0; i<m; i++) if(free[i]) return inf;

	return 1;
}

signed main() {
	//ios_base::sync_with_stdio(0); cin.tie(0);


	cout << "In the equation Ax = b, please enter the matrix size of A?\n";
	int n, m; cin>>n>>m;
	cout << "Please enter A itself.\n";
	vector<vector<ld> > a(n, vector<ld> (m+1, 0));

	for(int i=0; i<n; i++) for(int j=0; j<m; j++) cin>>a[i][j];

	cout << "Please enter the b column of size " << n << '\n';
	for(int row = 0; row<n; row++) {
		cin>>a[row][m];
	}

	cout << "Solving the equation Ax = b ...\n";


	vector<ld> ans;

	int sol = gauss(a, ans);

	for(int i=0; i<50; i++) {
		cout << ".";
		usleep(microsecond/10);
	}
	cout << '\n';

	if(sol==inf) {
		cout << "The equation has infinite solutions. Here is one of them: \n";
		for(int i=0; i<m; i++) cout << ans[i] << " "; cout << '\n';
	}
	else if(sol==0) {
		cout << "The equation has no solution.\n";
	}
	else {
		cout << "The solution has a unique solution:\n";
		for(int i=0; i<m; i++) cout << ans[i] << " "; cout << '\n';
	}

	cout << "Thanks for using our service.\n";


	return 0;
}
