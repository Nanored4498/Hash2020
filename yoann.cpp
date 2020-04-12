#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <set>
#include <cmath>

using namespace std;

// compile with DIVIDE for the problem E
#ifdef DIVIDE
#define TIME_MUL 0.028
#define D_POW 1.55
#define DC 0.26
#else
#define TIME_MUL 3
#endif

int main() {
	cout.tie(nullptr);
	ios::sync_with_stdio(false);

	int B, L, D;
	cin >> B >> L >> D;
	vector<int> S(B);
	vector<int> N(L), T(L), M(L);
	vector<vector<int>> books(L), librairies(B);
	vector<vector<int>> inLib(B);
	#ifdef DIVIDE
	priority_queue<pair<double, int>> q;
	vector<double> score_lib(L, 0);
	#else
	priority_queue<pair<long long, int>> q;
	vector<long long> score_lib(L, 0);
	#endif
	double sm = 0, smt = 0;
	vector<int> last_book(L);
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
		sm += M[i];
		smt += M[i] * T[i];
		sort(books[i].begin(), books[i].end(), [&S](int b0, int b1) {return S[b0] > S[b1];});
		int n = min(N[i], M[i] * (D-T[i]));
		last_book[i] = n;
		for(int j = 0; j < n; j++) score_lib[i] += S[books[i][j]];
		for(int j = 0; j < N[i]; j++) inLib[books[i][j]].push_back(j);
		mean_score += score_lib[i];
		mean_time += T[i];
	}
	int ratio = TIME_MUL*double(mean_score / mean_time);
	mean_time /= L;
	for(int i = 0; i < L; i++) {
		#ifdef DIVIDE
		score_lib[i] = double(score_lib[i] - ratio*T[i]) / (DC*double(mean_time) + pow(double(T[i]), D_POW));
		#else
		score_lib[i] = (score_lib[i] - ratio*T[i]);
		#endif
		q.push({score_lib[i], i});
	}
	
	int t = 0;
	int SCORE = 0;
	vector<int> Y;
	vector<bool> seen(B, false);
	vector<bool> seenL(L, false);
	vector<vector<int>> k;
	bool recomp = false;
	while(t < D) {
		#ifdef DIVIDE
		pair<double, int> a;
		#else
		pair<int, int> a;
		#endif
		int lib;
		while(!q.empty()) {
			a = q.top();
			lib = a.second;
			if(t+T[lib] < D && !seenL[lib] && abs(a.first - score_lib[lib]) < 1e-5) {
				int n = M[lib] * (D-t-T[lib]);
				if(!recomp && N[lib] <= n) break;
				recomp = true;
				score_lib[lib] = -ratio*T[lib];
				double m = 0, m2 = 0, nm = 0;
				for(int i = 0; i < N[lib]; i++) {
					if(i >= n) break;
					int b = books[lib][i];
					if(seen[b]) n ++;
					else {
						m += S[b];
						m2 += S[b]*S[b];
						nm ++;
					}
				}
				score_lib[lib] += m;
				m2 /= nm;
				m /= nm;
				double fac = min(70.0, max(1.0, (sm * (D-t) - 0.75*smt) / L));
				fac = 65;
				score_lib[lib] -= fac*sqrt(m2 - m*m);
				last_book[lib] = n;
				#ifdef DIVIDE
				score_lib[lib] /= (DC*double(mean_time) + pow(double(T[lib]), D_POW));
				#endif
				if(abs(a.first - score_lib[lib]) < 1e-5) break;
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
				for(int j = 0; j < librairies[b].size(); j++) {
					int l = librairies[b][j];
					if(seenL[l] || inLib[b][j] >= last_book[l]) continue;
					#ifdef DIVIDE
					score_lib[l] -= double(S[b]) / (DC*double(mean_time) + pow(double(T[l]), D_POW));
					#else
					score_lib[l] -= S[b];
					#endif
					q.push({score_lib[l], l});
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