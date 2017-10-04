import random
import numpy as np
import matplotlib.pyplot as plt

from collections import defaultdict


def load_data(filename):
    with open(filename, 'r') as f:
        raw_data = [l.split() for l in f.readlines()]
    return np.array(raw_data, dtype=float)

def plot_2d_points_data(data):
    x = defaultdict(list)
    y = defaultdict(list)
    color = lambda x: 'ro' if x == -1 else 'go'
    for d in data:
        x[color(d[-1])].append(d[0])
        y[color(d[-1])].append(d[1])
    for c in ['ro', 'go']:
        plt.plot(x[c], y[c], c)
    plt.show(block=False)


def preprocess_data(raw_data):
    X = raw_data[:, :-1].T
    Y = raw_data[:, -1:]
    return X, Y


# ============== Simple SMO Alogorithm ================

# SMO by random choice a2

def initKernel(kernel_function, X):
    m = X.shape[1]
    K = np.zeros((m, m))

    for i in range(m):
        for j in range(m):
            K[i, j] = kernel_function(X[:, i], X[:, j])

    return K



def SMO(X, Y, C, eps, maxIter, kernel_function=lambda x, y: np.sum(x * y)):
    # number of train data
    m = X.shape[1]
    # number of axis
    n = X.shape[0]

    alpha = np.zeros((m, 1))
    g = np.zeros((m, 1))
    b = 0
    K = initKernel(kernel_function, X)

    for _ in range(maxIter):

        for i in range(m):
            g[i, 0] = np.sum(alpha * Y * K[:, i:i+1]) + b
            yg = Y[i, 0] * g[i, 0]
            cur_alpha = alpha[i, 0]

            # not satisfy KKT
            if not (cur_alpha == 0 and yg + eps >= 1 or \
                    0 < cur_alpha < C and abs(yg - 1) < eps or \
                    cur_alpha == C and yg - eps <= 1):

                # choose a2 for random
                j = random.randint(0, m - 1)
                while j == i:
                    j = random.randint(0, m - 1)

                g[j, 0] = np.sum(alpha * Y * K[:, j:j+1]) + b

                a1_old, a2_old = alpha[i, 0], alpha[j, 0]
                y1, y2 = Y[i, 0], Y[j, 0]
                b_old = b

                E1 = g[i, 0] - y1
                E2 = g[j, 0] - y2

                eta = (E1 - E2) / (K[i, i] + K[j, j] - 2 * K[i, j])
                a2_new_unc = a2_old + \
                    y2 * (E1 - E2) / (K[i, i] + K[j, j] - 2 * K[i, j])

                if y1 != y2:
                    L = max(0, a2_old - a1_old)
                    H = min(C, C + a2_old - a1_old)
                else:
                    L = max(0, a2_old + a1_old - C)
                    H = min(C, a2_old + a1_old)

                a2_new = max(L, min(a2_new_unc, H))
                # print('g1', g[i, 0], 'g2', g[j, 0])
                # print('y1', y1, 'y2', y2)
                # print('a2_new_unc', a2_new_unc, '\nL', L, 'H', H, 'a2_new', a2_new)
                # print('--------------')
                a1_new = a1_old + y1 * y2 * (a2_old - a2_new)

                b1_new = -E1 - y1 * K[i, i] * (a1_new - a1_old) - y2 * \
                    K[j, i] * (a2_new - a2_old) + b_old
                b2_new = -E2 - y1 * K[i, j] * (a1_new - a1_old) - y2 * \
                    K[j, j] * (a2_new - a2_old) + b_old

                b_new = (b1_new + b2_new) / 2

                # update arguement
                alpha[i, 0] = a1_new
                alpha[j, 0] = a2_new
                b = b_new

    w = np.sum((alpha * Y).reshape(m) * X, axis=1, keepdims=True)
    return {
        'm': m,
        'X': X,
        'Y': Y,
        'alpha': alpha,
        'kernel_function': kernel_function,
        'b': b,
    }


def gaussKernel(x, z, ag = 1):
    dis = -np.sum((x - z) ** 2)
    return np.exp(dis / 2 / ag / ag)


def predict(x, model):
    n = x.shape[1]
    K = np.zeros((model['m'], n))
    for i in range(model['m']):
        for j in range(n):
            K[i, j] = model['kernel_function'](model['X'][:, i], x[:, j])
    # shape(m, 1), K.shape = (m, n)
    g = np.matmul(K.T, model['alpha'] * model['Y']) + model['b']
    return np.sign(g)
