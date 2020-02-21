#include <iostream>
#include <vector>
#include <queue>
#include <cmath>

using namespace std;

#define ADD 90
#define POW 1.0

int main() {
	cout.tie(nullptr);
	ios::sync_with_stdio(false);

	int B, L, D;
	cin >> B >> L >> D;
	vector<int> S(B);
	vector<int> N(L), T(L), M(L);
	vector<vector<int>> books(L), librairies(B);
	priority_queue<pair<double, int>> q;
	vector<double> score_lib(L, 0);
	double mean_score = 0;
	for(int i = 0; i < B; i++) {
		cin >> S[i];
		mean_score += S[i];
	}
	mean_score /= B;
	for(int i = 0; i < L; i++) {
		cin >> N[i] >> T[i] >> M[i];
		int b;
		int score = 0;
		for(int j = 0; j < N[i]; j++) {
			cin >> b;
			librairies[b].push_back(i);
			books[i].push_back(b);
			score_lib[i] += S[b];
		}
		score_lib[i] -= (0.09*mean_score)*double(T[i]);
		score_lib[i] /= (ADD + pow(double(T[i]), POW));
		q.push({score_lib[i], i});
	}
	
	int t = 0;
	int SCORE = 0;
	vector<int> Y;
	vector<bool> seen(B, false);
	vector<bool> seenL(L, false);
	vector<vector<int>> k;
	while(t < D) {
		pair<double, int> a;
		int lib;
		while(!q.empty()) {
			a = q.top();
			lib = a.second;
			if(t+T[lib]+1 < D && !seenL[lib] && abs(a.first - score_lib[a.second]) < 1e-5) break;
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
					score_lib[l] -= double(S[b]) / (ADD + pow(double(T[l]), POW));
					if(!seenL[l]) q.push({score_lib[l], l});
				}
				k.back().push_back(b);
				SCORE += S[b];
			}
		}
		t += T[lib];
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