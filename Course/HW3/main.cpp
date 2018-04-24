/*
** Liu, An-chi @ Copyright
*/
#include <algorithm>
#include <bitset>
#include <functional>
#include <iostream>
#include <map>
#include <new>
#include <string>
#include <unordered_map>
#include <vector>
using namespace std;
#define ull unsigned long long
#define INF 1000000

enum GamePiece { NONE_PIECE = 0, CIRCLE_PIECE = 1, FORK_PIECE = 2 };
enum GameTurn { CIRCLE_TURN = 0, FORK_TURN = 1 };

// for rotate and flip
vector<vector<int>> boards_rf = {
    {4,  9,  14, 19, 24, 3,  8,  13, 18, 23, 2,  7, 12,
     17, 22, 1,  6,  11, 16, 21, 0,  5,  10, 15, 20},
    {24, 23, 22, 21, 20, 19, 18, 17, 16, 15, 14, 13, 12,
     11, 10, 9,  8,  7,  6,  5,  4,  3,  2,  1,  0},
    {20, 15, 10, 5,  0,  21, 16, 11, 6,  1,  22, 17, 12,
     7,  2,  23, 18, 13, 8,  3,  24, 19, 14, 9,  4},
    {4,  3,  2,  1,  0,  9,  8,  7,  6,  5,  14, 13, 12,
     11, 10, 19, 18, 17, 16, 15, 24, 23, 22, 21, 20},
    {24, 19, 14, 9,  4,  23, 18, 13, 8,  3,  22, 17, 12,
     7,  2,  21, 16, 11, 6,  1,  20, 15, 10, 5,  0},
    {20, 21, 22, 23, 24, 15, 16, 17, 18, 19, 10, 11, 12,
     13, 14, 5,  6,  7,  8,  9,  0,  1,  2,  3,  4},
    {0,  5,  10, 15, 20, 1,  6,  11, 16, 21, 2,  7, 12,
     17, 22, 3,  8,  13, 18, 23, 4,  9,  14, 19, 24}};

struct NodeInfo {
  NodeInfo(ull board, int alpha, int beta) {
    _board = board;
    _alpha = alpha;
    _beta = beta;
  };
  ull _board;
  int _alpha;
  int _beta;
  bool operator==(const NodeInfo &other) const {
    return (_board == other._board && _alpha == other._alpha &&
            _beta == other._beta);
  }
};

struct NodeInfoHasher {
  size_t operator()(const NodeInfo &k) const {
    return ((hash<ull>()(k._board) ^ (hash<int>()(k._alpha) << 1)) >> 1) ^
           (hash<int>()(k._beta) << 1);
  }
};

unordered_map<NodeInfo, int, NodeInfoHasher> umap;

unordered_map<string, int> final_table = {
    {"OOOOO", 5000},  {"XOOOO", 5000},  {"OXOOO", 5000},  {"OOXOO", 5000},
    {"OOOXO", 5000},  {"OOOOX", 5000},  {"XXXXX", -5000}, {"XXXXO", -5000},
    {"XXXOX", -5000}, {"XXOXX", -5000}, {"XOXXX", -5000}, {"OXXXX", -5000},
};

void print_board(ull board) {
  for (int row = 0; row < 5; row++) {
    for (int col = 0; col < 5; col++) {
      ull tmp = 1;
      tmp <<= col * 2 + 10 * row;
      if (board & tmp) {
        cout << "O";
      } else if (board & tmp << 1) {
        cout << "X";
      } else {
        cout << ".";
      }
    }
    cout << endl;
  }
}

inline void print_win(int val) {
  if (val <= -5000) {
    cout << "X win" << endl;
  } else if (val >= 5000) {
    cout << "O win" << endl;
  } else {
    cout << "Draw" << endl;
  }
}

inline void save_rotate_flip_boards(const NodeInfo *info, const int *value) {
  ull board = info->_board;
  NodeInfo newInfo = NodeInfo(board, info->_alpha, info->_beta);
  vector<GamePiece> this_board;
  for (int row = 0; row < 5; row++) {
    for (int col = 0; col < 5; col++) {
      ull tmp = 1;
      tmp <<= col * 2 + 10 * row;
      if (board & tmp) {
        this_board.push_back(CIRCLE_PIECE);
      } else if (board & tmp << 1) {
        this_board.push_back(FORK_PIECE);
      } else {
        this_board.push_back(NONE_PIECE);
      }
    }
  }
  // origin one
  umap.insert({newInfo, *value});
  for (int i = 0; i < boards_rf.size(); i++) {
    ull new_board = 0;
    for (int j = 0; j < 25; j++) {
      ull piece = NONE_PIECE;
      if (this_board[j] == CIRCLE_PIECE) {
        piece = CIRCLE_PIECE;
        piece <<= boards_rf[i][j];
        new_board ^= piece;
      } else if (this_board[j] == FORK_PIECE) {
        piece = FORK_PIECE;
        piece <<= boards_rf[i][j];
        new_board ^= piece;
      } else {
        piece <<= boards_rf[i][j];
        new_board ^= piece;
      }
    }
    newInfo._board = new_board;
    umap.insert({newInfo, *value});
  }
}

// Note: 如果讓第一個元素在最左邊的話，bit元素運算會更快，因為只要一直往左邊推就好。
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

inline void get_round(ull board, GameTurn *turn, int *round) {
  int counter = 0;
  for (int i = 0; i < 50; i++) {
    ull tmp = 1;
    tmp <<= i;
    if (board & tmp)
      counter++;
  }
  if ((counter / 2) % 2 == 0) {
    *turn = CIRCLE_TURN;
  } else {
    *turn = FORK_TURN;
  }
  *round = (counter / 2);
}

inline vector<int> find_empty(ull *board) {
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

inline void move_piece(ull *board, int position, GameTurn turn) {
  ull piece;
  if (turn == CIRCLE_TURN) {
    piece = CIRCLE_PIECE;
  } else {
    piece = FORK_PIECE;
  }
  piece <<= (2 * position);
  *board ^= piece;
}

inline vector<vector<int>> find_next_sets(vector<int> &v) {
  vector<vector<int>> tmp;
  for (int i = 0; i < v.size(); i++) {
    for (int j = i + 1; j < v.size(); j++) {
      vector<int> t = {v[i], v[j]};
      tmp.push_back(t);
    }
  }
  return tmp;
}

inline int evaluate(ull *board) {
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

  for (int i = 0; i < lines.size(); i++) {
    auto search = final_table.find(lines[i]);
    if (search != final_table.end()) {
      value += search->second;
    }
  }
  if (value > 0) {
    value = 5000;
  } else if (value < 0) {
    value = -5000;
  }

  return value;
}

int who_win(int depth, ull board, GameTurn turn, int alpha, int beta,
            int round) {
  ull this_board = board;
  int result;
  vector<int> emptys = find_empty(&this_board);

  if (emptys.size() == 3) {
    for (int i = 0; i < emptys.size(); i++) {
      move_piece(&this_board, emptys[i], FORK_TURN);
    }
    return evaluate(&this_board);
  }

  vector<vector<int>> next_sets = find_next_sets(emptys);
  if (turn == CIRCLE_TURN) {
    int best_val = -INF;
    multimap<int, ull> boards;
    for (int i = 0; i < next_sets.size(); i++) {
      ull next_board = this_board;
      move_piece(&next_board, next_sets[i][0], CIRCLE_TURN);
      move_piece(&next_board, next_sets[i][1], CIRCLE_TURN);
      if (round <= 5) {
        boards.insert({evaluate(&next_board), next_board});
      } else {
        boards.insert({0, next_board});
      }
    }
    for (auto i = boards.rbegin(); i != boards.rend(); i++) {
      ull next_board = i->second;
      int next_result;
      NodeInfo nodeinfo = NodeInfo(next_board, alpha, beta);
      auto search = umap.find(nodeinfo);
      if (search != umap.end()) {
        next_result = search->second;
      } else {
        next_result =
            who_win(depth + 1, next_board, FORK_TURN, alpha, beta, round + 1);
        if (round < 6 || depth < 2) {
          save_rotate_flip_boards(&nodeinfo, &next_result);
        } else {
          umap.insert({nodeinfo, next_result});
        }
      }
      best_val = max(best_val, next_result);
      alpha = max(alpha, best_val);
      if (beta <= alpha)
        break;
    }
    return best_val;
  }

  else if (turn == FORK_TURN) {
    int best_val = INF;
    multimap<int, ull> boards;
    for (int i = 0; i < next_sets.size(); i++) {
      ull next_board = this_board;
      move_piece(&next_board, next_sets[i][0], FORK_TURN);
      move_piece(&next_board, next_sets[i][1], FORK_TURN);
      if (round <= 5) {
        boards.insert({evaluate(&next_board), next_board});
      } else {
        boards.insert({0, next_board});
      }
    }
    for (auto it = boards.begin(); it != boards.end(); it++) {
      ull next_board = it->second;
      int next_result;
      NodeInfo nodeinfo = NodeInfo(next_board, alpha, beta);
      auto search = umap.find(nodeinfo);
      if (search != umap.end()) {
        next_result = search->second;
      } else {
        next_result =
            who_win(depth + 1, next_board, CIRCLE_TURN, alpha, beta, round + 1);
        if (round < 6 || depth < 2) {
          save_rotate_flip_boards(&nodeinfo, &next_result);
        } else {
          umap.insert({nodeinfo, next_result});
        }
      }
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
  GameTurn turn;
  int round;
  ull board;
  cin >> games;
  for (int i = 0; i < games; i++) {
    board = input_game();
    get_round(board, &turn, &round);
    int result_val = who_win(0, board, turn, -INF, +INF, round);
    print_win(result_val);
  }
}