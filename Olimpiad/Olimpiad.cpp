#include <iostream>
#include <cmath>

using namespace std;

int main() {
    int M, N;
    cin >> M >> N;

    int white_row, white_col, black_row, black_col;
    cin >> white_row >> white_col >> black_row >> black_col;

    int row_diff = abs(white_row - black_row);
    int col_diff = abs(white_col - black_col);

    if ((row_diff % 2 == 0 && col_diff % 2 == 0) || (row_diff % 2 != 0 && col_diff % 2 != 0)) {
        cout << "0 0 0" << endl;
    }
    else {
        int moves = max(row_diff, col_diff);
        int meet_row = (black_row > white_row) ? black_row - row_diff / 2 : white_row - row_diff / 2;
        int meet_col = (black_col > white_col) ? black_col - col_diff / 2 : white_col - col_diff / 2;
        cout << moves << " " << meet_row << " " << meet_col << endl;
    }

    return 0;
}