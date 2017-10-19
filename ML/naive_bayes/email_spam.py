#  Machine Learning in action p60 example
#  Using Naive Bayes and word-bag model

import os
import re
import math
import codecs
import random
import numpy as np

from collections import defaultdict
from pprint import pprint
from time import time

data_path = './email/'
test_size = 5

def load_data():
    data = defaultdict(list)
    for folder in ['spam', 'ham']:
        path = os.path.join(data_path, folder)
        for file_name in os.listdir(path):
            file_path = os.path.join(path, file_name)
            # print('load file from path ', file_path)
            with codecs.open(
                    file_path, 'r', encoding='utf-8', errors='ignore') as f:
                data[folder].append(f.read())
        random.shuffle(data[folder])
        data[folder + '_test'] = data[folder][:test_size]
        data[folder] = data[folder][test_size:]
    return data


def wash_data(data):
    model = defaultdict(list)
    worddict = {}
    for key, raw_str_list in data.items():
        for raw_str in raw_str_list:
            raw_str = raw_str.lower()
            words = re.findall('\w+', raw_str)
            for word in words:
                if word not in worddict:
                    worddict[word] = len(worddict)
            model[key].append(words)
    model['worddict'] = worddict
    model['raw_data'] = data
    return model


def word2vec(wordslist, worddict):
    vec = [0] * len(worddict)
    for word in wordslist:
        vec[worddict[word]] += 1
    return vec


def buildTrainData(model):
    trainMatrix = []
    classMatrix = []
    for cid, category in enumerate(['spam', 'ham']):
        for wordslist in model[category]:
            vec = word2vec(wordslist, model['worddict'])
            trainMatrix.append(vec)
            classMatrix.append([cid])
    model['trainMatrix'] = np.array(trainMatrix)
    model['classMatrix'] = np.array(classMatrix)
    return model


def naiveBayesTrain(model):
    # Laplace smoothing
    _lamda = 1

    X, Y = model['trainMatrix'], model['classMatrix']
    YValue, NK = np.unique(Y, return_counts=True)

    PY = (NK + _lamda) / (np.sum(NK) + _lamda * len(YValue))
    PXY = {}
    SumJ = {}
    for yid, y in enumerate(YValue):
        nowX = X * (Y == y)
        PXY[y] = {}
        for wid in range(X.shape[1]):
            curX = nowX[:, wid]
            value, counts = np.unique(curX, return_counts=True)
            counts[0] = NK[yid] - sum(counts[1:])
            SumJ[wid] = len(value)
            default_value = _lamda / (NK[yid] + SumJ[wid] * _lamda)
            PXY[y][wid] = defaultdict(lambda: default_value)
            # PXY[y][wid] = {}
            for i, v in enumerate(value):
                # N(X(j)=l|y=ck) = counts[i]
                if counts[i] > NK[yid]:
                    import pdb; pdb.set_trace()
                PXY[y][wid][v] = (counts[i] + _lamda) / (
                    NK[yid] + SumJ[wid] * _lamda)
    model['PXY'] = PXY
    model['PY'] = PY
    model['YValue'] = YValue
    return model


def BayesPredict(model, vec):
    YValue = model['YValue']
    worddict = model['worddict']
    PXY = model['PXY']
    PY = model['PY']
    ret = {}
    maxy = -1
    for yid, y in enumerate(YValue):
        pxy = math.log(PY[yid])
        for wid in range(len(worddict)):
            pxy += math.log(PXY[y][wid][vec[wid]])
        ret[y] = pxy
        if maxy == -1 or ret[y] > ret[maxy]:
            maxy = y
    return ret, maxy


def runTest(model, g='_test'):
    worddict = model['worddict']
    categories = ['spam', 'ham']
    total, correct = 0, 0
    for cid, category in enumerate(['spam' + g, 'ham' + g]):
        for wordslist in model[category]:
            vec = word2vec(wordslist, worddict)
            detail, result = BayesPredict(model, vec)
            # print('this is a %s, result is %s' % (
            #     category, categories[result]))
            # pprint(detail)
            total += 1
            if cid == result:
                correct += 1
    # print('accuracy is %d/%d' % (correct, total))
    return correct, total


def run(test_round=1000):
    now = time()
    correct, total = 0, 0
    for _ in range(test_round):
        data = load_data()
        model = wash_data(data)
        model = buildTrainData(model)
        model = naiveBayesTrain(model)
        c, t = runTest(model)
        correct += c
        total += t
    print('finished in %.3f, accuracy is %.2f' % (
        time() - now, correct / total))


if __name__ == '__main__':
    run()
