#include <algorithm>
#include <bitset>
#include <iostream>
#include <new>
#include <string>
#include <unordered_map>
#include <vector>
#include <map>
using namespace std;
#define ull unsigned long long
#define INF 100000

enum GamePiece { CIRCLE_PIECE = 1, FORK_PIECE = 2 };
enum GameTurn { CIRCLE_TURN = 0, FORK_TURN = 1 };

unordered_map<ull, int> umap;
unordered_map<string, int> value_table = {
    {"OOOOO", 5000},

    {"XOOOO", 5000},
    {"OXOOO", 5000},
    {"OOXOO", 5000},
    {"OOOXO", 5000},
    {"OOOOX", 5000},

    {".OOOO", 5000},
    {"OOOO.", 5000},
    {"O.OOO", 5000},
    {"OOO.O", 5000},
    {"OO.OO", 5000},

    {".OOO.", 80},
    {"..OOO", 80},
    {".O.OO", 80},
    {".OO.O", 80},
    {".OOO.", 80},
    {"O..OO", 80},
    {"O.O.O", 80},
    {"O.OO.", 80},
    {"OO..O", 80},
    {"OO.O.", 80},
    {"OOO..", 80},

    {"OOO.X", 40},
    {"OO.OX", 40},
    {"O.OOX", 40},
    {".OOOX", 40},

    {"X.OOO", 40},
    {"XO.OO", 40},
    {"XOO.O", 40},
    {"XOOO.", 40},

    {"OO...", 10},
    {".OO..", 10},
    {"..OO.", 10},
    {"...OO", 10},
    //
    {"XXXXX", -5000},

    {"XXXXO", -5000},
    {"XXXOX", -5000},
    {"XXOXX", -5000},
    {"XOXXX", -5000},
    {"OXXXX", -5000},

    {".XXXX", -5000},
    {"XXXX.", -5000},
    {"X.XXX", -5000},
    {"XXX.X", -5000},
    {"XX.XX", -5000},

    {".XXX.", -80},
    {"..XXX", -80},
    {".X.XX", -80},
    {".XX.X", -80},
    {".XXX.", -80},
    {"X..XX", -80},
    {"X.X.X", -80},
    {"X.XX.", -80},
    {"XX..X", -80},
    {"XX.X.", -80},
    {"XXX..", -80},

    {"XXX.O", -40},
    {"XX.XO", -40},
    {"X.XXO", -40},
    {".XXXO", -40},

    {"O.XXX", -40},
    {"OX.XX", -40},
    {"OXX.X", -40},
    {"OXXX.", -40},

    {"XX...", -10},
    {".XX..", -10},
    {"..XX.", -10},
    {"...XX", -10},
};

unordered_map<string, int> final_table = {
    {"OOOOO", 5300},  {"XOOOO", 5300},  {"OXOOO", 5300},  {"OOXOO", 5300},
    {"OOOXO", 5300},  {"OOOOX", 5300},  {"XXXXX", -5300}, {"XXXXO", -5300},
    {"XXXOX", -5300}, {"XXOXX", -5300}, {"XOXXX", -5300}, {"OXXXX", -5300},
};

void print_win(int val) {
  if (val < -4000) {
    cout << "X win" << endl;
  } else if (val > 4000) {
    cout << "O win" << endl;
  } else {
    cout << "Draw" << endl;
  }
}

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

int evaluate(ull *board, bool isFinal) {
  int value = 0;
  vector<string> lines;
  string line1;
  string line2;
  for (int row = 0; row < 5; row++) {
    line1 = "";
    line2 = "";
    for (int col = 0; col < 5; col++) {
      // for row
      ull tmp = 1;
      tmp <<= col * 2 + 10 * row;
      if (*board & tmp) {
        line1 += "O";
      } else if (*board & tmp << 1) {
        line1 += "X";
      } else {
        line1 += ".";
      }

      // for column
      tmp = 1;
      tmp <<= col * 10 + 2 * row;
      if (*board & tmp) {
        line2 += "O";
      } else if (*board & tmp << 1) {
        line2 += "X";
      } else {
        line2 += ".";
      }
    }
    lines.push_back(line1);
    lines.push_back(line2);
  }

  line1 = "";
  line2 = "";
  int diagonal_left[5] = {0, 6, 12, 18, 24};
  int diagonal_right[5] = {4, 8, 12, 16, 20};
  for (int i = 0; i < 5; i++) {
    ull tmp1 = 1;
    ull tmp2 = 1;
    tmp1 <<= diagonal_left[i] * 2;
    tmp2 <<= diagonal_right[i] * 2;
    if (*board & tmp1)
      line1 += "O";
    else if (*board & tmp1 << 1)
      line1 += "X";
    else
      line1 += ".";
    if (*board & tmp2)
      line2 += "O";
    else if (*board & tmp2 << 1)
      line2 += "X";
    else {
      line2 += ".";
    }
    lines.push_back(line1);
    lines.push_back(line2);
  }
  if (isFinal) {
    for (int i = 0; i < lines.size(); i++) {
      auto search = final_table.find(lines[i]);
      if (search != final_table.end()) {
        value += search->second;
      }
    }
  } else {
    for (int i = 0; i < lines.size(); i++) {
      auto search = value_table.find(lines[i]);
      if (search != value_table.end()) {
        value += search->second;
      }
    }
  }
  return value;
}

int who_win(int depth, ull board, GameTurn round, int alpha, int beta) {
  ull this_board = board;
  int result;
  vector<int> emptys = find_empty(&this_board);

  if (emptys.size() == 3) {
    for (int i = 0; i < emptys.size(); i++) {
      move_piece(&this_board, emptys[i], FORK_TURN);
    }
    return evaluate(&this_board, true);
  }

  // if (depth == 5) {
  //   return evaluate(&this_board, false);
  // }

  vector<vector<int>> next_sets = find_next_sets(emptys);
  if (round == CIRCLE_TURN) {
    int best_val = -INF;
    for (int i = 0; i < next_sets.size(); i++) {
      ull next_board = this_board;
      move_piece(&next_board, next_sets[i][0], CIRCLE_TURN);
      move_piece(&next_board, next_sets[i][1], CIRCLE_TURN);
      int next_result;
      // auto search = umap.find(next_board);
      // if (search != umap.end()) {        
      //   next_result = search->second;
      // } else {
      next_result = who_win(depth + 1, next_board, FORK_TURN, alpha, beta);
      //   umap.insert({next_board, next_result});
      // }
      best_val = max(best_val, next_result);
      alpha = max(alpha, best_val);
      if (beta <= alpha)
        break;
    }
    return best_val;
  } else if (round == FORK_TURN) {
    int best_val = INF;
    for (int i = 0; i < next_sets.size(); i++) {
      ull next_board = this_board;
      move_piece(&next_board, next_sets[i][0], FORK_TURN);
      move_piece(&next_board, next_sets[i][1], FORK_TURN);
      int next_result;
      // auto search = umap.find(next_board);
      // if (search != umap.end()) {
      //   next_result = search->second;
      // } else {
      next_result = who_win(depth + 1, next_board, CIRCLE_TURN, alpha, beta);
      //   umap.insert({next_board, next_result});
      // }
      best_val = min(best_val, next_result);
      beta = min(beta, best_val);
      if (beta <= alpha)
        break;
    }
    return best_val;
  }

  return 0;
}

int main(int argc, char *argv[]) {
  int games;
  cin >> games;
  for (int i = 0; i < games; i++) {
    ull board = input_game();
    GameTurn round = get_round(board);
    int result_val = who_win(0, board, round, -INF, +INF);
    print_win(result_val);
  }
}