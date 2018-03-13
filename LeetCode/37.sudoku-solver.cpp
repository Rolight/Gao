/*
 * [37] Sudoku Solver
 *
 * https://leetcode.com/problems/sudoku-solver/description/
 *
 * algorithms
 * Hard (31.87%)
 * Total Accepted:    89.4K
 * Total Submissions: 280K
 * Testcase Example:
 * '[['.','.','9','7','4','8','.','.','.'],['7','.','.','.','.','.','.','.','.'],['.','2','.','1','.','9','.','.','.'],['.','.','7','.','.','.','2','4','.'],['.','6','4','.','1','.','5','9','.'],['.','9','8','.','.','.','3','.','.'],['.','.','.','8','.','3','.','2','.'],['.','.','.','.','.','.','.','.','6'],['.','.','.','2','7','5','9','.','.']]'
 *
 * Write a program to solve a Sudoku puzzle by filling the empty cells.
 *
 * Empty cells are indicated by the character '.'.
 *
 * You may assume that there will be only one unique solution.
 *
 *
 *
 * A sudoku puzzle...
 *
 *
 *
 *
 * ...and its solution numbers marked in red.
 *
 */

#include <cstdio>
#include <iostream>
#include <vector>

using std::vector;
typedef vector<char> VC;
const int maxn = 1024;

class DLXNode {
public:
  DLXNode *left, *right, *up, *down;
  int rid, cid;
  DLXNode() : rid(0), cid(0), left(this), right(this), up(this), down(this) {}
};

class DLX {
public:
  int columns, rows;
  DLXNode *row_head[maxn], *col_head[maxn];
  // initialize DLX
  DLX(int col) {
    // initialize columns
    col_head[0] = new DLXNode();
    for (int i = 1; i <= col; i++) {
      col_head[i] = new DLXNode();
      col_head[i - 1]->right = col_head[i];
      col_head[i]->left = col_head[i - 1];
      col_head[i]->up = col_head[i]->down = col_head[i];
      col_head[i]->cid = i;
    }
    col_head[col]->right = col_head[0];
    col_head[0]->left = col_head[col];
    rows = 0;
    columns = col;
  }

  void print_cols() {
    std::cout << "DLX have cols: ";
    int count = 0;
    for (DLXNode *x = col_head[0]->right; x != col_head[0]; x = x->right) {
      std::cout << x->cid << " ";
      ++count;
    }
    std::cout << std::endl << "count: " << count << std::endl;
  }

  // append row to dlx, pos is a int array indicate numbers pos
  void append_row(vector<int> &pos) {
    row_head[rows] = new DLXNode();
    row_head[rows]->left = row_head[rows]->right = row_head[rows];
    row_head[rows]->up = row_head[rows]->down = row_head[rows];

    DLXNode *leftNode = row_head[rows];
    for (int i = 0; i < (int)pos.size(); i++) {
      int cur_col = pos[i];
      DLXNode *newNode = new DLXNode();
      newNode->rid = rows;
      newNode->cid = cur_col;

      newNode->left = leftNode;
      leftNode->right = newNode;

      newNode->right = row_head[rows];
      row_head[rows]->left = newNode;

      newNode->up = col_head[cur_col]->up;
      col_head[cur_col]->up->down = newNode;

      newNode->down = col_head[cur_col];
      col_head[cur_col]->up = newNode;

      leftNode = newNode;
    }
    rows++;
  }

  // find optimal solution
  // this operation will destroy dlx structure, so it will be only run called
  // once
  vector<int> solve() {
    vector<int> answer;
    solve_step(answer);
    return answer;
  }

  bool solve_step(vector<int> &answer) {
    if (col_head[0]->right == col_head[0]) {
      return true;
    }
    DLXNode *cur_col_head = col_head[0]->right;
    // enumerate each possibale row
    for (DLXNode *cur = cur_col_head->down; cur != cur_col_head;
         cur = cur->down) {
      delete_state(cur->rid);
      answer.push_back(cur->rid);
      if (solve_step(answer)) {
        return true;
      }
      recover_state(cur->rid);
      answer.pop_back();
    }
    return false;
  }

  void delete_state(int rid) {
    delete_row(rid);
    for (DLXNode *x = row_head[rid]->right; x != row_head[rid]; x = x->right) {
      delete_col(x->cid);
    }
  }

  void delete_row(int rid) {
    for (DLXNode *x = row_head[rid]->right; x != row_head[rid]; x = x->right) {
      x->up->down = x->down;
      x->down->up = x->up;
    }
  }

  void delete_col(int cid) {
    // delete col
    col_head[cid]->left->right = col_head[cid]->right;
    col_head[cid]->right->left = col_head[cid]->left;
    for (DLXNode *x = col_head[cid]->down; x != col_head[cid]; x = x->down) {
      // printf("del col\n");
      x->left->right = x->right;
      x->right->left = x->left;
      delete_row(x->rid);
    }
  }

  void recover_state(int rid) {
    for (DLXNode *x = row_head[rid]->right; x != row_head[rid]; x = x->right) {
      recover_col(x->cid);
    }
    recover_row(rid);
  }

  void recover_row(int rid) {
    for (DLXNode *x = row_head[rid]->right; x != row_head[rid]; x = x->right) {
      x->up->down = x->down->up = x;
    }
  }

  void recover_col(int cid) {
    // add col
    col_head[cid]->left->right = col_head[cid]->right->left = col_head[cid];
    for (DLXNode *x = col_head[cid]->down; x != col_head[cid]; x = x->down) {
      recover_row(x->rid);
      x->left->right = x->right->left = x;
    }
  }
};

const int dlx_col_size =
    9 * 9 * 4; // (row, num) + (col, num) + (block, num) + (col, row)
const int dlx_row_size = 9 * 9 * 9; // (row, col, num)

class Tri {
public:
  int r, c, num;
  Tri(int r = 0, int c = 0, int num = 0) : r(r), c(c), num(num) {}
};

class Solution {
public:
  int dlx_encoder[10][10][10];
  Tri dlx_decoder[maxn];

  // t = 'R'(Row), 'C'(Col), 'B'(Block), 'P' (PlaceHolder)
  // if t == 'P', t_val is row, num is col
  int col_encoder(char t, int t_val, int num) {
    int ret;
    if (t == 'R')
      ret = t_val * 9 + num;
    if (t == 'C')
      ret = 81 + t_val * 9 + num;
    if (t == 'B')
      ret = 162 + t_val * 9 + num;
    if (t == 'P')
      ret = 243 + t_val * 9 + num;
    // avoid 0
    return ret + 1;
  }

  void init_dlx(DLX *dlx, vector<VC> &board) {
    int cur_val = 0;
    vector<int> pos;
    for (int row = 0; row < 9; row++) {
      for (int col = 0; col < 9; col++) {
        for (int num = 0; num < 9; num++) {
          int block_id = (row / 3) * 3 + (col / 3);
          dlx_encoder[row][col][num] = cur_val;
          dlx_decoder[cur_val] = Tri(row, col, num);
          cur_val++;

          pos.clear();
          pos.push_back(col_encoder('R', row, num));
          pos.push_back(col_encoder('C', col, num));
          pos.push_back(col_encoder('B', block_id, num));
          pos.push_back(col_encoder('P', row, col));
          dlx->append_row(pos);
        }
      }
    }
    for (int row = 0; row < 9; row++) {
      for (int col = 0; col < 9; col++) {
        char ch_val = board[row][col];
        if (ch_val != '.') {
          int int_val = ch_val - '0' - 1;
          int row_id = dlx_encoder[row][col][int_val];
          dlx->delete_state(row_id);
        }
      }
    }
  }

  void solveSudoku(vector<VC> &board) {
    DLX *dlx = new DLX(dlx_col_size);
    init_dlx(dlx, board);
    vector<int> answer = dlx->solve();
    for (int i = 0; i < (int)answer.size(); i++) {
      Tri ans = dlx_decoder[answer[i]];
      board[ans.r][ans.c] = ans.num + 1 + '0';
    }
  }
};

/*
void testDLX() {
  DLX *dlx = new DLX(7);
  int row1[3] = {3, 5, 6};
  int row2[3] = {1, 4, 7};
  int row3[3] = {2, 3, 6};
  int row4[2] = {1, 4};
  int row5[2] = {2, 7};
  int row6[3] = {4, 5, 7};
  vector<int> a;
  a = vector<int>(row1, row1 + 3);
  dlx->append_row(a);
  a = vector<int>(row2, row2 + 3);
  dlx->append_row(a);
  a = vector<int>(row3, row3 + 3);
  dlx->append_row(a);
  a = vector<int>(row4, row4 + 2);
  dlx->append_row(a);
  a = vector<int>(row5, row5 + 2);
  dlx->append_row(a);
  a = vector<int>(row6, row6 + 3);
  dlx->append_row(a);

  dlx->print_cols();

  dlx->delete_state(1);
  dlx->print_cols();
  dlx->recover_state(1);
  dlx->print_cols();

  dlx->solve();
}
*/

int main() {
  // testDLX();
  // return 0;
  char input[9][9] = {{'.', '.', '9', '7', '4', '8', '.', '.', '.'},
                      {'7', '.', '.', '.', '.', '.', '.', '.', '.'},
                      {'.', '2', '.', '1', '.', '9', '.', '.', '.'},
                      {'.', '.', '7', '.', '.', '.', '2', '4', '.'},
                      {'.', '6', '4', '.', '1', '.', '5', '9', '.'},
                      {'.', '9', '8', '.', '.', '.', '3', '.', '.'},
                      {'.', '.', '.', '8', '.', '3', '.', '2', '.'},
                      {'.', '.', '.', '.', '.', '.', '.', '.', '6'},
                      {'.', '.', '.', '2', '7', '5', '9', '.', '.'}};
  vector<VC> b;
  for (int i = 0; i < 9; i++) {
    b.push_back(vector<char>());
    for (int j = 0; j < 9; j++) {
      b[i].push_back(input[i][j]);
    }
  }
  Solution s;
  s.solveSudoku(b);
  for (int i = 0; i < 9; i++) {
    for (int j = 0; j < 9; j++) {
      printf("%c ", b[i][j]);
    }
    putchar('\n');
  }
  return 0;
}