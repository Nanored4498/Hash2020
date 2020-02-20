#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

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
	vector<int> score_lib(L, 0);
	long long mean_score = 0;
	long long mean_time = 0;
	for(int i = 0; i < B; i++) cin >> S[i];
	for(int i = 0; i < L; i++) {
		cin >> N[i] >> T[i] >> M[i];
		int b;
		for(int j = 0; j < N[i]; j++) {
			cin >> b;
			librairies[b].push_back(i);
			books[i].push_back(b);
		}
		sort(books[i].begin(), books[i].end(), [&S](int b0, int b1) {return S[b0] > S[b1];});
		int n = min(N[i], M[i] * (D-T[i]));
		for(int j = 0; j < n; j++) score_lib[i] += S[books[i][j]];
		mean_score += score_lib[i];
		mean_time += T[i];
	}
	int ratio = 2*double(mean_score / mean_time);
	for(int i = 0; i < L; i++) {
		score_lib[i] -= ratio*T[i];
		q.push({score_lib[i], i});
	}
	
	int t = 0;
	int SCORE = 0;
	vector<int> Y;
	vector<bool> seen(B, false);
	vector<bool> seenL(L, false);
	vector<vector<int>> k;
	while(t < D) {
		pair<int, int> a;
		int lib;
		while(!q.empty()) {
			a = q.top();
			lib = a.second;
			if(t+T[lib] < D && !seen[lib] && a.first == score_lib[lib]) {
				int n = M[lib] * (D-t+T[lib]);
				if(N[lib] <= n) break;
				score_lib[lib] = -ratio*T[lib];
				for(int i = 0; i < N[lib]; i++) {
					if(i >= n) break;
					int b = books[lib][i];
					if(seen[b]) n ++;
					else score_lib[lib] += S[b];
				}
				if(a.first == score_lib[lib]) break;
				q.push({score_lib[lib], lib});
			}
			q.pop();
		}
		if(q.empty()) break;
		q.pop();
		Y.push_back(lib);
		k.push_back({});
		seenL[lib] = true;
		for(int b : books[lib]) {
			if(!seen[b]) {
				seen[b] = true;
				for(int l : librairies[b]) {
					score_lib[l] -= S[b];
					if(!seenL[l]) q.push({score_lib[l], l});
				}
				if(t+T[lib]+k.back().size()/M[lib] < D) {
					k.back().push_back(b);
					SCORE += S[b];
				}
			}
		}
		if(k.back().empty()) {
			k.pop_back();
			Y.pop_back();
		} else t += T[lib];
	}

	int A = k.size();
	cout << A << "\n";
	for(int i = 0; i < A; i++) {
		cout << Y[i] << " " << k[i].size() << "\n";
		for(int b : k[i]) cout << b << " " ;
		cout << "\n";
	}
	cerr << SCORE << endl;

	return 0;
}