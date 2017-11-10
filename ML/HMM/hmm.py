# using hmm model for chinese words segmentation
# train data from https://github.com/ldanduo/HMM/blob/master/RenMinData.txt_utf8

from collections import defaultdict

data_path = './train_data.txt'

STAT = ['B', 'M', 'E', 'S']
STAT_MAPPING = {
    'B': 0, 'M': 1, 'E': 2, 'S': 3
}
NUM_STAT = len(STAT)

s = lambda x: STAT_MAPPING[x]

def load_data():
    with open(data_path, 'r') as f:
        return f.readlines()


# label the state of each single word
def label_line(line):
    line = line.split(' ')
    ch_seq = []
    label_seq = []
    for word in line:
        word = word.strip()
        if len(word) == 0:
            continue
        if len(word) == 1:
            label_seq.append(s('S'))
            ch_seq.append(word)
        else:
            for idx, ch in enumerate(word):
                if idx == 0:
                    label_seq.append(s('B'))
                elif idx == len(word) - 1:
                    label_seq.append(s('E'))
                else:
                    label_seq.append(s('M'))
                ch_seq.append(ch)
    return ch_seq, label_seq


# HMM train with labeled train data
def HMM_train():
    data = load_data()
    alpha = [[0 for i in range(NUM_STAT)] for i in range(NUM_STAT)]
    beta = [defaultdict(int) for i in range(NUM_STAT)]
    beta_sum = [0 for i in range(NUM_STAT)]
    pi = [0 for i in range(NUM_STAT)]
    for line in data:
        line = line.strip()
        if len(line) == 0:
            continue
        ch_seq, label_seq = label_line(line)
        assert len(ch_seq) == len(label_seq)
        # mantain the alpha and beta
        pi[label_seq[0]] += 1
        beta[label_seq[0]][ch_seq[0]] += 1
        beta_sum[label_seq[0]] += 1
        for i in range(1, len(ch_seq)):
            prev_stat, cur_stat = label_seq[i - 1], label_seq[i]
            cur_ob = ch_seq[i]
            # update alpha
            alpha[prev_stat][cur_stat] += 1
            # update beta
            beta[cur_stat][cur_ob] += 1
            beta_sum[cur_stat] += 1
    pi_sum = sum(pi)
    print(pi)
    print(beta_sum)
    for i in range(NUM_STAT):
        cur_sum = sum(alpha[i])
        for j in range(NUM_STAT):
            alpha[i][j] /= cur_sum
        for key in beta[j]:
            beta[j][key] /= beta_sum[i]
        pi[i] /= pi_sum
    return {
        'alpha': alpha,
        'beta': beta,
        'pi': pi
    }

# handle log(0) -> -oo
def log(x):
    from math import log
    inf = 1e90
    if x == 0:
        return -inf
    return log(x)


def rs(label_seq):
    rev = {
        0: 'B', 1: 'M', 2: 'E', 3: 'S'
    }
    return [rev[x] for x in label_seq]


# HMM predict using viterbi algorithm
def HMM_predict(val, model):
    m = len(val)
    alpha = model['alpha']
    beta = model['beta']
    pi = model['pi']
    # f[i][j] means p when in time i, stat is j
    f = [[0 for __ in range(NUM_STAT)] for _ in range(m)]
    for i in range(NUM_STAT):
        f[0][i] = log(pi[i]) + log(beta[i][val[0]])
    for i in range(1, m):
        for cur_stat in range(NUM_STAT):
            for pre_stat in range(NUM_STAT):
                f[i][cur_stat] = max(
                    f[i][cur_stat],
                    f[i - 1][pre_stat] + log(alpha[pre_stat][cur_stat]) +
                    log(beta[cur_stat][val[i]])
                )
    # get path
    label_seq = []
    cur_stat = s('E') if f[m - 1][s('E')] > f[m - 1][s('S')] else s('S')
    label_seq.append(cur_stat)
    for i in range(m - 2, -1, -1):
        prev_stat = 0
        min_dis = 1
        for j in range(0, NUM_STAT):
            cur_dis = abs(f[i + 1][cur_stat] -
                          f[i][j] - log(alpha[j][cur_stat]) -
                          log(beta[cur_stat][val[i + 1]]))
            if cur_dis < min_dis:
                min_dis = cur_dis
                prev_stat = j
        cur_stat = prev_stat
        label_seq.append(cur_stat)
    label_seq.reverse()
    # output result
    result = ''
    for ch, label in zip(val, label_seq):
        result += ch
        if label in [s('S'), s('E')]:
            result += '|'
    return result
