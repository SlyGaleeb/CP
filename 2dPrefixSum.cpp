#include <bits/stdc++.h>
using namespace std;

int arr[1005][1005];
int sum[1005][1005];

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	
	int n,q,x1,y1,x2,y2,ans;
	char c;
	cin >> n >> q;
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= n; ++j) {
			cin >> c;
			if (c=='.')
				arr[i][j] = 0;
			else
				arr[i][j] = 1;
		}
	}
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= n; ++j) {
			sum[i][j] = sum[i][j-1] + sum[i-1][j] - sum[i-1][j-1] + arr[i][j];
		}
	}
	for (int i = 0; i < q; ++i) {
		cin >> x1 >> y1 >> x2 >> y2;
		ans = sum[x2][y2] - sum[x2][y1-1] - sum[x1-1][y2] + sum[x1-1][y1-1];
		cout << ans << "\n";
	}
	/*for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= n; ++j) {
			cout << arr[i][j];
		}
		cout << endl;
	}
	cout << endl;
		for (int i = 1; i <= n; ++i) {
			for (int j = 1; j <= n; ++j) {
				cout << sum	[i][j];
		}
		cout << endl;
	}*/
}