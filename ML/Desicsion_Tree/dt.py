import numpy as np
import random
import copy

from collections import defaultdict
from time import time

import graphviz


iris_data_path = './iris.txt'
lense_data_path = './lenses.txt'

class TreeNode:

    def __init__(self):
        self.children = []
        self.data = {}

    @property
    def uid(self):
        return str(id(self))

    @property
    def info(self):
        return '\n'.join([
            '%s, %s' % (key, value)
            for key, value in self.data.items()
        ])

    # view graph of the Tree
    # this node is root
    def graph(self):
        graph = graphviz.Digraph()
        self._draw(graph, self)
        return graph

    def _draw(self, graph, treeNode):
        gnode = graph.node(name=treeNode.uid, label=treeNode.info)
        for child_info in treeNode.children:
            child = child_info['child']
            edge_label = str(treeNode.data['basis']) + child_info['basis_str']
            chgnode = self._draw(graph, child)
            graph.edge(treeNode.uid, child.uid, label=edge_label)
        return gnode


def load_data(filename, dtype=None):
    data = []
    classify = {}
    with open(filename, 'r') as f:
        for line in f.readlines():
            line = line.strip().split(',')
            cur_classify = line[-1]
            if cur_classify not in classify:
                classify[cur_classify] = len(classify)
            line[-1] = classify[cur_classify]
            data.append(line)
    return {
        'data': np.array(data, dtype=dtype),
        'classify': classify
    }


def entropy(vec):
    value, count = np.unique(vec, return_counts=True)
    total = np.sum(count)
    p = count / total
    return -np.sum(p * np.log(p))


def split_data(D, A):
    ret = defaultdict(list)
    DA = D[:, A:A+1]
    D = np.append(D[:, 0:A], D[:, A+1:], axis=1)
    for idx in range(DA.shape[0]):
        ret[DA[idx, 0]].append(list(D[idx, :]))
    for key in ret.keys():
        ret[key] = np.array(ret[key])
    return ret


# input Dataset and Attribute output g
# A is a integer mean index of arrtibute column
# g(D, A) = H(D) - H(D|A)
def information_gain(D, A):
    # the last col is classify
    HD = entropy(D[:, -1])
    HDA = 0
    splited_data = split_data(D, A)
    for AValue, AData in splited_data.items():
        p = AData.shape[0] / D.shape[0]
        curH = entropy(AData[:, -1])
        HDA += p * curH
    return HD - HDA


def information_gain_ratio(D, A):
    g = information_gain(D, A)
    Ha = entropy(D[:, A])
    return g / Ha


def majorty_vote(D):
    vec = D[:, -1]
    value, count = np.unique(vec, return_counts=True)
    return max(zip(value, count), key=lambda x: x[1])[0]


# ID3 algorithm

def ID3_build(curData):
    dt = TreeNode()

    # leaf child
    if curData.shape[1] <= 2 or curData.shape[0] == 1:
        dt.data['classify'] = majorty_vote(curData)
        return dt

    max_A, max_information_gain = -1, -1
    for Aid in range(curData.shape[1] - 1):
        g = information_gain(curData, Aid)
        if g > max_information_gain:
            max_A = Aid
            max_information_gain = g
    splited_data = split_data(curData, max_A)
    for AValue in splited_data:
        ch = ID3_build(splited_data[AValue])
        dt.data['basis'] = max_A
        dt.children.append({
            'child': ch,
            'basis_func': lambda x, n=AValue: x == n,
            'basis_str': ' = %s' % str(AValue),
        })
    return dt


def ID3(raw_data):
    data = raw_data['data']
    classify = raw_data['classify']
    tree = ID3_build(data)
    return {
        'classify': classify,
        'tree': tree
    }

# C4.5 algorithm
def C45_build(curData):
    dt = TreeNode()

    # leaf child
    if curData.shape[1] <= 2 or curData.shape[0] == 1:
        dt.data['classify'] = majorty_vote(curData)
        return dt

    max_A, max_information_gain_ratio = -1, -1
    for Aid in range(curData.shape[1] - 1):
        g = information_gain_ratio(curData, Aid)
        if g > max_information_gain_ratio:
            max_A = Aid
            max_information_gain_ratio = g
    splited_data = split_data(curData, max_A)
    for AValue in splited_data:
        ch = ID3_build(splited_data[AValue])
        dt.data['basis'] = max_A
        dt.children.append({
            'child': ch,
            'basis_func': lambda x, n=AValue: x == n,
            'basis_str': ' = %s' % str(AValue),
        })
    return dt


def C45(raw_data):
    data = raw_data['data']
    classify = raw_data['classify']
    tree = C45_build(data)
    return {
        'classify': classify,
        'tree': tree
    }

# TODO:CART


def DTreePredict(model, vec):
    curNode = model['tree']
    while 'classify' not in curNode.data:
        basis = curNode.data['basis']
        nextNode = None
        for child_info in curNode.children:
            if child_info['basis_func'](vec[basis]):
                nextNode = child_info['child']
                break
        # find error
        if nextNode is None:
            return None
        vec = np.append(vec[:basis], vec[basis + 1:])
        curNode = nextNode
    return curNode.data['classify']

# raw_data format should b
# { 'data': xxx, 'classify': xxx}
# this function will random choose 20% data as test data
def washData(raw_data):
    divided_data = defaultdict(list)
    data = raw_data['data']
    test_data = []
    train_data = []
    for row in list(data):
        divided_data[row[-1]].append(row)
    for _, data in divided_data.items():
        test_size = len(data) // 5
        random.shuffle(data)
        test_data += data[:test_size]
        train_data += data[test_size:]
    test_data = np.array(test_data)
    train_data = np.array(train_data)
    raw_data['data'] = train_data
    raw_data['test_data'] = test_data[:, :-1]
    raw_data['test_classify'] = test_data[:, -1:]


def testModel(train_data_path, train_func, case=100, dtype=None):
    now = time()
    correct, total = 0, 0
    for _ in range(case):
        data = load_data(train_data_path, dtype=dtype)
        washData(data)
        model = train_func(data)
        results = []
        for idx in range(data['test_data'].shape[0]):
            test_case = data['test_data'][idx]
            result = DTreePredict(model, test_case)
            results.append([result])
        results = np.array(results)
        correct += np.sum(results == data['test_classify'])
        total += data['test_data'].shape[0]
    timespan = time() - now
    print('test finished in %.4f, accuracy is %.4f' % (
        timespan, correct / total))
