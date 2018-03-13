#include <vector>
#include <string>
#include <iostream>
#include <algorithm>

using namespace std;

int price[1000][1000] = { 0 };
int income[1000][1000];
pair<int,char> cut_location[1000][1000];
int cutPrice, N, M;

void fill() {
    for (int i = 1; i <= N; ++i) {
        for (int j = 1; j <= M; j++) {
            income[i][j] = price[i][j];// do not cut.
            cut_location[i][j] = make_pair(0, 'n');
            for (int k = 1; k <= i / 2; ++k) { // Cut location
                if (income[i][j] < income[k][j] + income[i - k][j] - cutPrice) {
                    income[i][j] = income[k][j] + income[i - k][j] - cutPrice;
                    cut_location[i][j] = make_pair(k, 'h');
                }
            }
            for (int k = 1; k <= j / 2; ++k) { // Cut location
                if (income[i][j] < income[i][k] + income[i][j - k] - cutPrice) {
                    income[i][j] = income[i][k] + income[i][j - k] - cutPrice;
                    cut_location[i][j] = make_pair(k, 'v');
                }
            }
        }
    }
}

void print(int height, int width) {
    int cut_position = cut_location[height][width].first;
    char cut_direction = cut_location[height][width].second;
    if (cut_position == 0) {
        cout << height << "x" << width << endl;
        return;
    }

    if (cut_direction == 'h') {
        print(cut_position, width);
        print(height - cut_position, width);
    } else if (cut_direction == 'v') {
        print(height, cut_position);
        print(height, width - cut_position);
    }
}

int main() {
    cin >> N >> M >> cutPrice;
    for (int i = 1; i <= N; ++i) {
        for (int j = 1; j <= M; j++) {
            cin >> price[i][j];
        }
    }
    fill();
    cout << "Maximal income = " << income[N][M] << endl;
    print(N, M);
    return 0;
}

/* Test input values given here
5 6 1
1 1 1 1 1 1
1 1 4 1 1 1
1 1 1 1 1 1
1 1 1 1 1 1
1 1 1 1 1 5
*/
