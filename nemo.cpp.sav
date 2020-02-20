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

    vector<double> score_each_lib(L, 0.);

    cerr << "yo" << endl;
    for(int i = 0; i < L; i++) {
        vector<int> score;
        for(int b = 0; b < N[i]; b++) {
            score.push_back(S[books[i][b]]);
        }
        sort(score.begin(), score.end());
        for(int day = 0; day < D - T[i]; day++) {
            for(int curr_book = 0; curr_book < M[i]; curr_book++) {
                if(day*M[i]+curr_book > N[i]-1) break;

                score_each_lib[i] += score[N[i] - (day*M[i] + curr_book) - 1];
            }

            if(day*M[i] > N[i]-1) break;
        }
        score_each_lib[i] *= (double)(M[i]*M[i]*N[i])/((double)(T[i]*T[i]*T[i]*T[i]));
    }

    vector<pair<double,int>> lib_orders;
    for(int i = 0; i < L; i++) {
        lib_orders.push_back(make_pair(score_each_lib[i],i));
    }

    sort(lib_orders.begin(), lib_orders.end());

    int curr_day = 0;

    int nb = 0;

    for(int i = L-1; i >= 0; i--) {
        int current_lib = lib_orders[i].second;
        curr_day += T[current_lib];
        if(curr_day>= D) break;
        nb++;
    }
    // register everyone...
    cout << nb << endl;
    curr_day = 0;

    vector<bool> sent(B, false);

    for(int i = L-1; i >= 0; i--) {
        int current_lib = lib_orders[i].second;
        curr_day += T[current_lib];
        if(curr_day>= D) break;
        
        cout << current_lib << " " << N[current_lib] << endl;

        //sort books

        vector<pair<int,int> > book_order;
        for(int book = 0; book < N[current_lib]; book++) {
            book_order.push_back(make_pair(S[books[current_lib][book]], books[current_lib][book]));
        }

        sort(book_order.begin(), book_order.end());
        int count_new_sent = 0;
        vector<int> discarded;

        for(int book = N[current_lib]-1; book >=0; book--) {
            while(sent[book_order[book].second] && book>=0) {
                discarded.push_back(book_order[book].second);
                book--;
            }
            if(book < 0) break;
            sent[book_order[book].second] = true;
            count_new_sent++;
            if(book != N[current_lib]-1) cout << " ";
            cout << book_order[book].second;
        }
        for(int b : discarded) {
            cout << " " << b;
        }

        cout << endl;
    }


    return 0;
}
