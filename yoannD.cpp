#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int main() {
	cout.tie(nullptr);
	ios::sync_with_stdio(false);

	int B, L, D;
	cin >> B >> L >> D;
	vector<int> S(B);
	vector<int> N(L), T(L), M(L);
	vector<vector<int>> books(L), librairies(B);
	priority_queue<pair<int, int>> q;
	for(int i = 0; i < B; i++) cin >> S[i];
	for(int i = 0; i < L; i++) {
		cin >> N[i] >> T[i] >> M[i];
		int b;
		for(int j = 0; j < N[i]; j++) {
			cin >> b;
			librairies[b].push_back(i);
			books[i].push_back(b);
		}
		q.push({N[i], i});
	}
	
	int t = 0;
	vector<int> Y;
	vector<bool> seen(B, false);
	vector<bool> seenL(L, false);
	vector<vector<int>> k;
	while(t < D) {
		pair<int, int> a;
		while(true) {
			a = q.top();
			if(a.first == N[a.second]) break;
			q.pop();
		}
		q.pop();
		int lib = a.second;
		// cout << N[lib] << endl;
		// return 0;
		Y.push_back(lib);
		k.push_back({});
		seenL[lib] = true;
		for(int b : books[lib]) {
			if(!seen[b]) {
				seen[b] = true;
				for(int l : librairies[b]) {
					N[l] --;
					if(!seenL[l]) q.push({N[l], l});
				}
				if(t+2+k.back().size() < D) k.back().push_back(b);
			}
		}
		if(k.back().empty()) {
			k.pop_back();
			Y.pop_back();
		}
		t += 2;
	}

	int A = k.size();
	cout << A << "\n";
	// return 0;
	for(int i = 0; i < A; i++) {
		cout << Y[i] << " " << k[i].size() << "\n";
		for(int b : k[i]) cout << b << " " ;
		cout << "\n";
	}

	return 0;
}