# adaboost using decision stump as base function

import numpy as np
import random

from collections import defaultdict

iris_path = './iris.txt'
test_rate = 0.2

class DecisionStump:
    def __init__(self, split_value, feature_id, classify):
        self.split_value = split_value
        self.feature_id = feature_id
        self.classify = classify


def load_iris():
    data = []
    with open(iris_path, 'r') as f:
        for line in f.readlines():
            line = line.strip().split(',')
            data.append(line)
    return data


def wash_data(raw_data):
    test_data = []
    train_data = []
    random.shuffle(raw_data)
    test_case = int(len(raw_data) * test_rate)
    test_data += raw_data[:test_case]
    train_data += raw_data[test_case:]
    return {
        'train_data': np.array(train_data),
        'test_data': np.array(test_data)
    }

# treat label == correct_label as i, either -1
def train_decision_stump(train_data, train_weight, correct_label):
    label = (train_data[:, -1] == correct_label)
    min_loss, min_loss_feature, min_loss_feature_value = -1, -1, -1
    min_loss_classify = None
    for feature_id in range(train_data.shape[1] - 1):
        all_features = train_data[:, feature_id].astype(float)
        features = np.unique(all_features)
        features = np.append(np.array([features[0] - 1]), features)
        features = np.append(features, np.array([features[-1] + 1]))
        for split_value in features:
            cur_lte_loss = np.sum(
                ((all_features <= split_value) != label) * train_weight)
            cur_gt_loss = np.sum(
                ((all_features > split_value) != label) * train_weight)
            if cur_lte_loss < cur_gt_loss:
                cur_classify = 'lte'
                cur_loss = cur_lte_loss
            else:
                cur_classify = 'gt'
                cur_loss = cur_gt_loss
            if min_loss_feature == -1 or cur_loss < min_loss:
                min_loss = cur_loss
                min_loss_feature = feature_id
                min_loss_feature_value = split_value
                min_loss_classify = cur_classify
    ds = DecisionStump(
        split_value=min_loss_feature_value,
        feature_id=min_loss_feature,
        classify=min_loss_classify,
    )
    return ds

def convertY(Y):
    for yid in range(Y.shape[0]):
        Y[yid] = -1 if Y[yid] == 0 else Y[yid]
    return Y

# the weak classifier G using Decision Stump
# x is a matrix, return a label vector
def weakG(x, decision_stump):
    # print(dir(decision_stump))
    features = x[:, decision_stump.feature_id].astype(float)
    if decision_stump.classify == 'lte':
        return convertY((features <= decision_stump.split_value).astype(int))
    else:
        return convertY((features > decision_stump.split_value).astype(int))


# x = input_data, G is weak classifier list, A is coefficient list of G
def adaboost_predict(x, G, A):
    ret = np.zeros(x.shape[0])
    for decision_stump, a in zip(G, A):
        ret += weakG(x, decision_stump) * a
    return np.sign(ret)


def adaboost(train_data, correct_label, max_iter=50):
    Y = convertY((train_data[:, -1] == correct_label).astype(int))
    # size of train_data
    N = train_data.shape[0]
    # initialize with 1/N
    train_weight = np.array([1 / N for i in range(N)])
    G, A = [], []
    for iter_step in range(max_iter):
        if len(train_weight) < 12:
            print('cur w is %s' % str(train_weight))
        cur_g = train_decision_stump(train_data, train_weight, correct_label)
        cur_g_result = weakG(train_data, cur_g)
        em = np.sum((Y != cur_g_result) * train_weight)
        if em != 0:
            cur_a = 0.5 * np.log((1 - em) / em)
        else:
            cur_a = 1
        Zm = np.sum(np.exp(-cur_a * Y * cur_g_result) * train_weight)
        for wid, wmi in enumerate(train_weight):
            train_weight[wid] = wmi / Zm * np.exp(
                -cur_a * Y[wid] * cur_g_result[wid])
        G.append(cur_g)
        A.append(cur_a)
        cur_result = adaboost_predict(train_data, G, A)
        missclassification_amount = np.sum(cur_result != Y)
        if len(train_weight) < 12:
            print('iter %d, missclassification point amount %d\n' % (
                iter_step, missclassification_amount))
        if missclassification_amount == 0:
            break
    return {
        'G': G,
        'A': A
    }


def test_iris():
    data = wash_data(load_iris())
    train_data = data['train_data']
    test_data = data['test_data']
    # train
    labels = ['Iris-setosa', 'Iris-virginica', 'Iris-versicolor']
    models = {
        label: adaboost(train_data, label)
        for label in labels
    }
    # test
    correct = np.zeros(test_data.shape[0])
    for label in labels:
        model = models[label]
        result = adaboost_predict(test_data, model['G'], model['A'])
        result = (result > 0) == (test_data[:, -1] == label)
        correct += result.astype(int)
    total = test_data.shape[0]
    correct = np.sum(correct == 3)
    return correct, total


if '__main__' == __name__:
    correct, total = 0, 0
    for i in range(100):
        c, t = test_iris()
        correct += c
        total += t
    print('iris average accuracy is %.4f' % (correct / total, ))
    print('book p141 work flow is:')
    with open('simple.txt', 'r') as f:
        data = []
        for line in f.readlines():
            data.append(line.strip().split(','))
        data = np.array(data, dtype=int)
        adaboost(data, 1)
