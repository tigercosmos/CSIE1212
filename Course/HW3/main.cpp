#include <algorithm>
#include <bitset>
#include <iostream>
#include <new>
#include <string>
#include <unordered_map>
#include <vector>
using namespace std;
#define ull unsigned long long

enum GamePiece { CIRCLE_PIECE = 1, FORK_PIECE = 2 };
enum GameResult { DRAW = 0, CIRCLE_WIN = 1, FORK_WIN = 2 };
enum GameTurn { CIRCLE_TURN = 0, FORK_TURN = 1 };

unordered_map<ull, GameResult> umap;

// void printVector(vector<int> v) {
//   for (int i = 0; i < v.size(); i++) {
//     cout << v[i] << " ";
//   }
//   cout << endl;
// }

// void printVectorVector(vector<vector<int>> v) {
//   for (int i = 0; i < v.size(); i++) {
//     cout << "[" << v[i][0] << ", " << v[i][1] << "] ";
//   }
//   cout << endl;
// }

inline static ull input_game() {
  ull board = 0;
  for (int row = 0; row < 5; row++) {
    char tmp[5];
    cin >> tmp;
    for (int col = 0; col < 5; col++) {
      ull piece = 0;
      if (tmp[col] == 'O') {
        piece = CIRCLE_PIECE;
        piece <<= (2 * col + row * 10);
        board ^= piece;
      } else if (tmp[col] == 'X') {
        piece = FORK_PIECE;
        piece <<= (2 * col + row * 10);
        board ^= piece;
      }
    }
  }
  return board;
}

// round count from 0
inline GameTurn get_round(ull board) {
  int counter = 0;
  for (int i = 0; i < 50; i++) {
    ull tmp = 1;
    tmp <<= i;
    if (board & tmp)
      counter++;
  }
  if ((counter / 2) % 2 == 0) {
    return CIRCLE_TURN;
  }
  return FORK_TURN;
}

// when the board is filled with pieces, and then evaluate the result.
GameResult evaluate(ull board) {
  int result_counter = 0;
  for (int row = 0; row < 5; row++) {
    char line_row_count = 0;
    char line_col_count = 0;

    for (int col = 0; col < 5; col++) {
      // for row
      ull tmp = 1;
      tmp <<= col * 2 + 10 * row;
      if (board & tmp) {
        line_row_count += 1;
      } else {
        line_row_count -= 1;
      }

      // for column
      tmp = 1;
      tmp <<= col * 10 + 2 * row;
      if (board & tmp)
        line_col_count += 1;
      else
        line_col_count -= 1;
    }
    if (line_col_count >= 3) {
      result_counter += 1;
    } else if (line_col_count <= -3) {
      result_counter -= 1;
    }
    if (line_row_count >= 3) {
      result_counter += 1;

    } else if (line_row_count <= -3) {
      result_counter -= 1;
    }
  }

  // for diagonal
  char line_diagonal_left_count = 0;
  char line_diagonal_right_count = 0;
  int diagonal_left[5] = {0, 6, 12, 18, 24};
  int diagonal_right[5] = {4, 8, 12, 16, 20};
  for (int i = 0; i < 5; i++) {
    ull tmp1 = 1;
    ull tmp2 = 1;
    tmp1 <<= diagonal_left[i] * 2;
    tmp2 <<= diagonal_right[i] * 2;
    if (board & tmp1)
      line_diagonal_left_count += 1;
    else
      line_diagonal_left_count -= 1;
    if (board & tmp2)
      line_diagonal_right_count += 1;
    else
      line_diagonal_right_count -= 1;
  }
  if (line_diagonal_left_count >= 3) {
    result_counter += 1;
  } else if (line_diagonal_left_count <= -3) {
    result_counter -= 1;
  }
  if (line_diagonal_right_count >= 3) {
    result_counter += 1;
  } else if (line_diagonal_right_count <= -3) {
    result_counter -= 1;
  }
  if (result_counter > 0)
    return CIRCLE_WIN;
  if (result_counter < 0)
    return FORK_WIN;
  return DRAW;
}

vector<int> find_empty(ull *board) {
  vector<int> v;
  ull tmp = 1;
  tmp = (tmp << 50) - 1;
  ull inverted_board = *board ^ tmp;

  for (int i = 0; i < 25; i++) {
    int flag = 0;
    ull tmp = 1;
    tmp <<= i * 2;
    if (inverted_board & tmp) {
      flag += 1;
    }
    tmp <<= 1;
    if (inverted_board & tmp) {
      flag += 1;
    }
    if (flag == 2) {
      v.push_back(i);
    }
  }
  return v;
}

void move_piece(ull *board, int position, GameTurn turn) {
  ull piece;
  if (turn == CIRCLE_TURN) {
    piece = CIRCLE_PIECE;
  } else {
    piece = FORK_PIECE;
  }
  piece <<= (2 * position);
  *board ^= piece;
}

vector<vector<int>> find_next_sets(vector<int> &v) {
  vector<vector<int>> tmp;
  for (int i = 0; i < v.size(); i++) {
    for (int j = i + 1; j < v.size(); j++) {
      vector<int> t = {v[i], v[j]};
      tmp.push_back(t);
    }
  }
  return tmp;
}

GameResult who_win(ull board, GameTurn round) {
  ull this_board = board;
  GameResult result;
  vector<int> emptys = find_empty(&this_board);
  if (emptys.size() == 3) {
    for (int i = 0; i < emptys.size(); i++) {
      move_piece(&this_board, emptys[i], FORK_TURN);
    }
    result = evaluate(board);
  } else {
    auto search = umap.find(this_board);
    if (search != umap.end()) {
      return search->second;
    }

    vector<vector<int>> next_sets = find_next_sets(emptys);
    if (round == CIRCLE_TURN) {
      result = FORK_WIN;
      for (int i = 0; i < next_sets.size(); i++) {
        ull next_board = this_board;
        move_piece(&next_board, next_sets[i][0], CIRCLE_TURN);
        move_piece(&next_board, next_sets[i][1], CIRCLE_TURN);
        GameResult nextresult = who_win(next_board, FORK_TURN);

        if (nextresult == CIRCLE_WIN) {
          result = CIRCLE_WIN;
          break;
        } else if (nextresult == DRAW && result == FORK_WIN) {
          result = DRAW;
        }
      }
      return result;
    } else if (round == FORK_TURN) {
      result = CIRCLE_WIN;
      for (int i = 0; i < next_sets.size(); i++) {
        ull next_board = this_board;
        move_piece(&next_board, next_sets[i][0], FORK_TURN);
        move_piece(&next_board, next_sets[i][1], FORK_TURN);
        GameResult nextresult = who_win(next_board, CIRCLE_TURN);

        if (nextresult == FORK_WIN) {
          result = FORK_WIN;
          break;
        } else if (nextresult == DRAW && result == CIRCLE_WIN) {
          result = DRAW;
        }
      }
      return result;
    }
  }

  auto search = umap.find(this_board);
  if (search == umap.end()) {
    umap.insert({this_board, result});
  }
  return result;
}

int main(int argc, char *argv[]) {
  int games;
  cin >> games;
  for (int i = 0; i < games; i++) {
    ull board = input_game();
    GameTurn round = get_round(board);
    GameResult result = who_win(board, round);
    if (result == DRAW) {
      cout << "Draw" << endl;
    } else if (result == CIRCLE_WIN) {
      cout << "O win" << endl;
    } else {
      cout << "X win" << endl;
    }
  }
}