/*
 * [212] Word Search II
 *
 * https://leetcode.com/problems/word-search-ii/description/
 *
 * algorithms
 * Hard (24.74%)
 * Total Accepted:    64.2K
 * Total Submissions: 258.6K
 * Testcase Example:
 * '[["o","a","a","n"],["e","t","a","e"],["i","h","k","r"],["i","f","l","v"]]\n["oath","pea","eat","rain"]'
 *
 *
 * Given a 2D board and a list of words from the dictionary, find all words in
 * the board.
 *
 *
 * Each word must be constructed from letters of sequentially adjacent cell,
 * where "adjacent" cells are those horizontally or vertically neighboring. The
 * same letter cell may not be used more than once in a word.
 *
 *
 *
 * For example,
 * Given words = ["oath","pea","eat","rain"] and board =
 *
 * [
 * ⁠ ['o','a','a','n'],
 * ⁠ ['e','t','a','e'],
 * ⁠ ['i','h','k','r'],
 * ⁠ ['i','f','l','v']
 * ]
 *
 *
 * Return ["eat","oath"].
 *
 *
 *
 * Note:
 * You may assume that all inputs are consist of lowercase letters a-z.
 *
 *
 * click to show hint.
 *
 * You would need to optimize your backtracking to pass the larger test. Could
 * you stop backtracking earlier?
 *
 * If the current candidate does not exist in all words' prefix, you could stop
 * backtracking immediately. What kind of data structure could answer such
 * query efficiently? Does a hash table work? Why or why not? How about a Trie?
 * If you would like to learn how to implement a basic trie, please work on
 * this problem: Implement Trie (Prefix Tree) first.
 *
 */
import java.util.*;

class Solution {
    class TrieNode {
        HashMap<Character, TrieNode> ch;
        boolean isWord;
        TrieNode() {
            ch = new HashMap<>();
            isWord = false;
        }
    }

    class QueueNode {
        TrieNode tree_node;
        String word;
        int x, y;

        QueueNode(TrieNode tree_node, String word, int x, int y) {
            this.x = x;
            this.y = y;
            this.tree_node = tree_node;
            this.word = word;
        }
    }

    int n;
    int m;
    int[] dx = {0, 0, 1, -1};
    int[] dy = {1, -1, 0, 0};

    public void insert(String word, TrieNode root) {
        TrieNode cur = root;
        for (int i = 0; i < word.length(); i++) {
            Character now = word.charAt(i);
            if (cur.ch.get(now) == null) {
                TrieNode newNode = new TrieNode();
                cur.ch.put(now, newNode);
            }
            cur = cur.ch.get(now);
        }
        cur.isWord = true;
    }

    public String list2string(List<Character> str) {
        String s = "";
        for (int i = 0; i < str.size(); i++) {
            s += str.get(i);
        }
        return s;
    }

    public void dfs(int now_x, int now_y, List<String> ans, TrieNode cur_node, char[][] board,
        List<Character> cur_str, boolean[][] vis) {
        if (cur_node.isWord) {
            ans.add(list2string(cur_str));
            cur_node.isWord = false;
        }
        for (int i = 0; i < 4; i++) {
            int nx = now_x + dx[i], ny = now_y + dy[i];
            if (nx < 0 || nx >= n || ny < 0 || ny >= m || vis[nx][ny]
                || cur_node.ch.get(board[nx][ny]) == null) {
                continue;
            }
            vis[nx][ny] = true;
            cur_str.add(board[nx][ny]);
            dfs(nx, ny, ans, cur_node.ch.get(board[nx][ny]), board, cur_str, vis);
            cur_str.remove(cur_str.size() - 1);
            vis[nx][ny] = false;
        }
    }

    public List<String> findWords(char[][] board, String[] words) {
        // build trie tree
        if (board.length == 0)
            new ArrayList<String>();
        this.n = board.length;
        this.m = board[0].length;
        boolean[][] vis = new boolean[n][m];
        List<Character> cur_str = new ArrayList<Character>();
        List<String> ans = new ArrayList<String>();
        TrieNode root = new TrieNode();
        for (int i = 0; i < words.length; i++) {
            insert(words[i], root);
        }
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (root.ch.get(board[i][j]) == null) {
                    continue;
                }
                vis[i][j] = true;
                cur_str.add(board[i][j]);
                dfs(i, j, ans, root.ch.get(board[i][j]), board, cur_str, vis);
                cur_str.remove(0);
                vis[i][j] = false;
            }
        }
        Collections.sort(ans);
        return ans;
    }
}
