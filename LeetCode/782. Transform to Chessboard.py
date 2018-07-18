class Solution:

    def calc_row(self, board, i):
        count = 0
        ct = 0
        for idx, val in enumerate(self.n_mask_1):
            if board[i][idx] == val:
                continue
            count += 1
            if board[i][idx] < val:
                ct -= 1
            else:
                ct += 1
        if ct != 0:
            count = -1
        else:
            count //= 2

        count_1 = 0
        ct = 0

        for idx, val in enumerate(self.n_mask_2):
            if board[i][idx] == val:
                continue
            count_1 += 1
            if board[i][idx] < val:
                ct -= 1
            else:
                ct += 1
        if ct != 0:
            count_1 = -1
        else:
            count_1 //= 2

        if count < 0 and count_1 < 0:
            return -1000
        elif count >= 0 and count_1 >= 0:
            return min(count, count_1)
        else:
            return max(count, count_1)

    def calc_col(self, board, i):
        count = 0
        ct = 0
        for idx, val in enumerate(self.m_mask_1):
            if board[idx][i] == val:
                continue
            count += 1
            if board[idx][i] < val:
                ct -= 1
            else:
                ct += 1
        if ct != 0:
            count = -1
        else:
            count //= 2

        count_1 = 0
        ct = 0

        for idx, val in enumerate(self.m_mask_2):
            if board[idx][i] == val:
                continue
            count_1 += 1
            if board[idx][i] < val:
                ct -= 1
            else:
                ct += 1
        if ct != 0:
            count_1 = -1
        else:
            count_1 //= 2

        if count < 0 and count_1 < 0:
            return -1000
        elif count >= 0 and count_1 >= 0:
            return min(count, count_1)
        else:
            return max(count, count_1)

    def check_row(self, board):
        v0 = board[0]
        v1 = [x ^ 1 for x in v0]

        for g in board:
            if g != v0 and g != v1:
                return False
        return True

    def check_col(self, board):
        vboard = []

        for c in range(len(board[0])):
            vboard.append([])
            for r in range(len(board)):
                vboard[c].append(board[r][c])

        v0 = vboard[0]
        v1 = [x ^ 1 for x in v0]

        for g in vboard:
            if g != v0 and g != v1:
                return False

        return True

    def movesToChessboard(self, board):
        """
        :type board: List[List[int]]
        :rtype: int
        """
        if not self.check_col(board) or not self.check_row(board):
            return -1
        n = len(board)
        m = len(board[0])

        self.n_mask_1 = [i % 2 for i in range(n)]
        self.n_mask_2 = [i ^ 1 for i in self.n_mask_1]

        self.m_mask_1 = [i % 2 for i in range(m)]
        self.m_mask_2 = [i ^ 1 for i in self.m_mask_1]

        n_min_val = min([self.calc_row(board, i) for i in range(n)])
        m_min_val = min([self.calc_col(board, i) for i in range(m)])

        return max(-1, n_min_val + m_min_val)
