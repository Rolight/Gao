# clustering algorithm using gmm
# using iris data

import numpy as np
import matplotlib.pyplot as plt
import random

from sklearn.decomposition import PCA

DIM = 2


def load_data():
    data, label = [], []
    with open('iris.txt', 'r') as f:
        for line in f.readlines():
            line = line.strip().split(',')
            data.append(line[:-1])
            label.append(line[-1])
    data = np.array(data, dtype=float)
    label = np.array(label)

    # for sake of visualization, using pca to reduce dimension to 2
    pca = PCA(n_components=DIM)
    data = pca.fit_transform(data)
    return data, label


def gauss(y, mu, sigma):
    mu = mu[0] + mu[1]
    sigma = sigma[0] + sigma[1]
    y = y[0] + y[1]
    ret = (
        1 / (np.sqrt(2 * np.pi) * sigma) *
        np.exp(
            (-(y - mu) ** 2) /
            (2 * sigma * sigma)
        )
    )
    return ret


def em(data):
    y = data
    M = y.shape[0]
    # in iris data, we have 3 categories
    K = 3
    # initialize theta as random matrix
    theta = np.zeros((M, K))
    # initialize sigma, mu and alpha
    mu = np.random.randn(K, DIM)
    sigma = np.abs(np.random.randn(K, DIM))
    alpha = np.array([1 / 3 for k in range(K)])


    # start iteration
    maxIter = 50
    while maxIter > 0:
        --maxIter
        newTheta = np.zeros((M, K))
        # E step, calculate the theta using old arg
        for j in range(M):
            for k in range(K):
                newTheta[j, k] = alpha[k] * gauss(y[j, :], mu[k, :], sigma[k, :])
            newTheta[j, :] /= np.sum(newTheta[j, :])
        dis = np.sum((np.sum(newTheta - theta) ** 2))
        theta = newTheta
        # M step, calculate the argmax and get new arg
        for k in range(K):
            alpha[k] = np.sum(theta[:, k]) / M
            sigma[k, :] = np.sum((y - mu[k, :]) ** 2, axis=0) / \
                np.sum(theta[:, k])
            mu[k, :] = np.sum(theta[:, k:k+1] * y, axis=0) / np.sum(theta[:, k])

        print('cur dis is %.4f' % dis)
        if dis < 1e-8:
            break
    return {
        'alpha': alpha,
        'mu': mu,
        'sigma': sigma,
        'theta': theta
    }


def main():
    data, label = load_data()
    plt.subplot(221)
    plt.scatter(data[:, 0], data[:, 1])

    plt.subplot(222)

    color = ['red', 'green', 'blue']
    model = em(data)
    theta = model['theta']
    glabel = []
    for i in range(data.shape[0]):
        glabel.append(color[theta[i].argmax()])
    plt.scatter(data[:, 0], data[:, 1], c=color)


    from sklearn.mixture import GaussianMixture

    plt.subplot(223)
    gmm = GaussianMixture(n_components=3, init_params='random')
    gmm.fit(data)
    c = list(map(color.__getitem__, gmm.predict(data)))
    plt.scatter(data[:, 0], data[:, 1], c=c)

    plt.subplot(224)
    gmm = GaussianMixture(n_components=3, init_params='kmeans')
    gmm.fit(data)
    c = list(map(color.__getitem__, gmm.predict(data)))
    plt.scatter(data[:, 0], data[:, 1], c=c)
    plt.show()
