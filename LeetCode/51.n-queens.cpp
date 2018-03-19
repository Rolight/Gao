/*
 * [51] N-Queens
 *
 * https://leetcode.com/problems/n-queens/description/
 *
 * algorithms
 * Hard (32.96%)
 * Total Accepted:    96.6K
 * Total Submissions: 291.9K
 * Testcase Example:  '4'
 *
 * The n-queens puzzle is the problem of placing n queens on an n×n chessboard
 * such that no two queens attack each other.
 *
 *
 *
 * Given an integer n, return all distinct solutions to the n-queens puzzle.
 *
 * Each solution contains a distinct board configuration of the n-queens'
 * placement, where 'Q' and '.' both indicate a queen and an empty space
 * respectively.
 *
 * For example,
 * There exist two distinct solutions to the 4-queens puzzle:
 *
 * [
 * ⁠[".Q..",  // Solution 1
 * ⁠ "...Q",
 * ⁠ "Q...",
 * ⁠ "..Q."],
 *
 * ⁠["..Q.",  // Solution 2
 * ⁠ "Q...",
 * ⁠ "...Q",
 * ⁠ ".Q.."]
 * ]
 *
 */

#include <iostream>
#include <map>
#include <string>
#include <vector>

using std::make_pair;
using std::pair;
using std::string;
using std::vector;

class DLXNode {
   public:
    DLXNode *left, *right, *up, *down;
    DLXNode *colHead, *rowHead;
    int row_id, col_id;
    void setLRUD(DLXNode *left, DLXNode *right, DLXNode *up, DLXNode *down) {
        this->left = left;
        this->right = right;
        this->up = up;
        this->down = down;
    }
    void setHead(int rid, int cid, DLXNode *rowHead, DLXNode *colHead) {
        this->row_id = rid;
        this->col_id = cid;
        this->rowHead = rowHead;
        this->colHead = colHead;
    }
};

class DLX {
   public:
    typedef vector<int> VI;
    vector<DLXNode *> cols, rows;
    int maxDep;
    DLX(int colNum, int maxDep) {
        int cm = colNum + 1;
        this->maxDep = maxDep;
        for (int i = 0; i <= colNum; i++) {
            cols.push_back(new DLXNode());
        }
        for (int i = 0; i <= colNum; i++) {
            cols[i]->setLRUD(cols[(i - 1 + cm) % cm], cols[(i + 1) % cm],
                             cols[i], cols[i]);
            cols[i]->col_id = i;
        }
    }

    void addRow(vector<int> &pos) {
        DLXNode *rowHead = new DLXNode();
        rowHead->setLRUD(rowHead, rowHead, rowHead, rowHead);
        int rid = rows.size();
        rows.push_back(rowHead);
        for (vector<int>::iterator iter = pos.begin(); iter != pos.end();
             ++iter) {
            DLXNode *newNode = new DLXNode();
            newNode->setLRUD(rowHead->left, rowHead, cols[*iter]->up,
                             cols[*iter]);
            newNode->setHead(rid, *iter, rows[rid], cols[*iter]);
            rowHead->left->right = newNode;
            rowHead->left = newNode;
            cols[*iter]->up->down = newNode;
            cols[*iter]->up = newNode;
        }
    }

    void deleteRow(DLXNode *rowHead) {
        for (DLXNode *cur = rowHead->right; cur != rowHead; cur = cur->right) {
            cur->up->down = cur->down;
            cur->down->up = cur->up;
        }
    }

    void deleteCol(DLXNode *colHead) {
        colHead->right->left = colHead->left;
        colHead->left->right = colHead->right;
        for (DLXNode *cur = colHead->down; cur != colHead; cur = cur->down) {
            cur->left->right = cur->right;
            cur->right->left = cur->left;
            deleteRow(cur->rowHead);
        }
    }

    void deleteState(DLXNode *rowHead) {
        deleteRow(rowHead);
        for (DLXNode *cur = rowHead->right; cur != rowHead; cur = cur->right) {
            deleteCol(cur->colHead);
        }
    }

    void recoverRow(DLXNode *rowHead) {
        for (DLXNode *cur = rowHead->right; cur != rowHead; cur = cur->right) {
            cur->up->down = cur->down->up = cur;
        }
    }

    void recoverCol(DLXNode *colHead) {
        for (DLXNode *cur = colHead->down; cur != colHead; cur = cur->down) {
            recoverRow(cur->rowHead);
            cur->right->left = cur->left->right = cur;
        }
        colHead->right->left = colHead->left->right = colHead;
    }

    void recoverState(DLXNode *rowHead) {
        for (DLXNode *cur = rowHead->right; cur != rowHead; cur = cur->right) {
            recoverCol(cur->colHead);
        }
        recoverRow(rowHead);
    }

    // find all solutions, return
    void solveStep(VI &solu, vector<VI> &solus) {
        if (solu.size() >= maxDep) {
            // find a solution
            solus.push_back(solu);
            return;
        }
        DLXNode *curCol = cols[0]->right;
        for (DLXNode *cur = curCol->down; cur != curCol; cur = cur->down) {
            solu.push_back(cur->row_id);
            deleteState(cur->rowHead);
            solveStep(solu, solus);
            recoverState(cur->rowHead);
            solu.pop_back();
        }
    }
};

class Solution {
   public:
    int colSpaceSize;
    int boardSize;
    vector<pair<int, int> > stateDecoder;

    vector<int> encodeCol(int row, int col) {
        vector<int> ret;
        ret.push_back(row);
        ret.push_back(col + boardSize);
        ret.push_back(row - col + boardSize + 2 * boardSize);
        ret.push_back(row + col - 1 + boardSize * 2 + boardSize * 2 - 1);
        return ret;
    }

    DLX *initDLX() {
        DLX *dlx = new DLX(colSpaceSize, boardSize);
        stateDecoder.clear();
        for (int r = 1; r <= boardSize; r++) {
            for (int c = 1; c <= boardSize; c++) {
                vector<int> state = encodeCol(r, c);
                dlx->addRow(state);
                stateDecoder.push_back(make_pair(r, c));
            }
        }
        return dlx;
    }

    vector<string> decodeSolu(vector<int> &solu) {
        vector<string> ret;
        string cur_str = "";
        for (int i = 1; i <= boardSize; i++) cur_str += ".";
        for (int r = 1; r <= boardSize; r++) {
            ret.push_back(cur_str);
        }
        for (vector<int>::iterator iter = solu.begin(); iter != solu.end();
             ++iter) {
            ret[stateDecoder[*iter].first - 1][stateDecoder[*iter].second - 1] =
                'Q';
        }
        return ret;
    }

    vector<vector<string> > solveNQueens(int n) {
        vector<vector<string> > ans;
        vector<int> tmp;
        vector<vector<int> > solus;
        // col space row, col, two diagonals
        colSpaceSize = n + n + n * 2 - 1 + n * 2 - 1;
        boardSize = n;
        DLX *dlx = initDLX();
        dlx->solveStep(tmp, solus);
        for (vector<vector<int> >::iterator iter = solus.begin();
             iter != solus.end(); ++iter) {
            ans.push_back(decodeSolu(*iter));
        }
        std::cout << "total find " << ans.size() << " solutions" << std::endl;
        return ans;
    }
};

int main() {
    int n;
    std::cin >> n;
    Solution s = Solution();
    auto res = s.solveNQueens(n);
    return 0;
    for (int i = 0; i < res.size(); i++) {
        for (int j = 0; j < res[i].size(); j++) {
            std::cout << res[i][j] << std::endl;
        }
        std::cout << "---------------" << std::endl;
    }
}