#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>

using namespace std;

int main() {
    cout.tie(nullptr);
    ios::sync_with_stdio(false);

    int B, L, D;
    cin >> B >> L >> D;
    vector<int> S(B);
    vector<int> N(L), T(L), M(L);
    vector<vector<int>> books(L), librairies(B);
    for(int i = 0; i < B; i++) cin >> S[i];
    for(int i = 0; i < L; i++) {
        cin >> N[i] >> T[i] >> M[i];
        int b;
        for(int j = 0; j < N[i]; j++) {
            cin >> b;
            librairies[b].push_back(i);
            books[i].push_back(b);
        }
    }

    vector<int> score_each_lib(L, 0);

    for(int i = 0; i < L; i++) {
        vector<int> score;
        for(int book : books[i]) {
            score.push_back(S[book]);
        }
        sort(score.begin(), score.end());
        for(int day = 0; day < D - T[i]; day++) {
            for(int curr_book = M[i]-1; curr_book >= 0; curr_book--) {
                score_each_lib[i] += score[day*M[i] + curr_book];
            }
        }
    }

    vector<pair<int,int>> lib_orders;
    for(int i = 0; i < L; i++) {
        lib_orders.push_back(make_pair(score_each_lib[i],i));
    }

    sort(lib_orders.begin(), lib_orders.end());

    // register everyone...
    cout << L << endl;

    for(int i = L-1; i >= 0; i--) {
        int current_lib = lib_orders[i].second;
        cout << current_lib << " " << N[current_lib] << endl;
        //sort books

        vector<pair<int,int> > book_order;
        for(int book = 0; book < N[current_lib]; book++) {
            book_order.push_back(make_pair(S[books[current_lib][book]], books[current_lib][book]));
        }

        sort(book_order.begin(), book_order.end());

        for(int book = N[current_lib]-1; book >=0; book--) {
            if(book != N[current_lib]-1) cout << " ";
            cout << book_order[book].second;
        }
        cout << endl;
    }


    return 0;
}
