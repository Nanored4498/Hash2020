#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <random>
#include <algorithm>
#include <functional> // for bind

using namespace std;
typedef vector<int> joli;
typedef pair<int, int> pii;

typedef map<int, vector<string>> PHOTOS;
PHOTOS photos_h;
PHOTOS photos_v; // can use two at the same time

int main() {
	int B, L, D;
	cin >> B >> L >> D;
	cout << B << " " << L << " " << D << endl;
	joli book_score();
}
