#include <iostream>
#include <vector>
#include <queue>

using namespace std;

#define ADD 3

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
		N[i] *= 3;
	}
	for(int i = 0; i < B; i++) {
		if(librairies[i].size()==2) {
			for(int l : librairies[i]) N[l] += ADD;
		}
	}
	for(int i = 0; i < L; i++) q.push({N[i], i});
	
	int t = 0;
	vector<int> Y;
	vector<bool> seen(B, false);
	vector<bool> seenL(L, false);
	vector<vector<int>> k;
	int score = 0;
	while(t < D) {
		pair<int, int> a;
		while(true) {
			a = q.top();
			if(a.first == N[a.second]) break;
			q.pop();
		}
		q.pop();
		int lib = a.second;
		Y.push_back(lib);
		k.push_back({});
		seenL[lib] = true;
		for(int b : books[lib]) {
			if(!seen[b]) {
				seen[b] = true;
				for(int l : librairies[b]) {
					N[l] -= 3;
					if(librairies[b].size() == 2) N[l] -= ADD;
					if(!seenL[l]) q.push({N[l], l});
				}
				if(t+2+k.back().size() < D) {
					k.back().push_back(b);
					score ++;
				}
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
	for(int i = 0; i < A; i++) {
		cout << Y[i] << " " << k[i].size() << "\n";
		for(int b : k[i]) cout << b << " " ;
		cout << "\n";
	}
	cerr << score << endl;

	return 0;
}