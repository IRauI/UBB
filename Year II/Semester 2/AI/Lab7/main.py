import csv
import os
import matplotlib.pyplot as plt
import numpy as np
import pandas as pd
from sklearn import linear_model

from BGD import BGDRegression


def loadData(filename, inputVariables, outputVariable):
    file = pd.read_csv(filename)
    inputs = []

    for feature in inputVariables:
        inputs.append([float(value) if not pd.isna(value) and value != 0 else -1 for value in file[feature]])
    output = [float(value) for value in file[outputVariable]]
    return inputs, output

def splitData(inputs, outputs, percentage, normalize=False):
    np.random.seed(5)
    indexes = [i for i in range(len(outputs))]
    trainSample = np.random.choice(indexes, int(percentage * len(outputs)), replace=False)
    testSample = [i for i in range(len(outputs)) if i not in trainSample]
    trainInputs = []
    testInputs = []
    for feature in inputs:
        trainInputs.append([feature[i] for i in trainSample])
        testInputs.append([feature[i] for i in testSample])
    trainOutput = [outputs[i] for i in trainSample]
    testOutput = [outputs[i] for i in testSample]

    return trainInputs, trainOutput, testInputs, testOutput


def removeBlanks(inputs):
    input0_not_corrupted = [inputs[0][i] for i in range(len(inputs[0])) if inputs[0][i] != -1 and inputs[1][i] != -1]
    input1_not_corrupted = [inputs[1][i] for i in range(len(inputs[1])) if inputs[0][i] != -1 and inputs[1][i] != -1]

    w0, w1 = learnModelUnivariate(input1_not_corrupted, input0_not_corrupted)
    for index, elem in enumerate(inputs[0]):
        if elem == -1 or elem == 0:
            inputs[0][index] = w0 + w1 * inputs[1][index]

    w0, w1 = learnModelUnivariate(input0_not_corrupted, input1_not_corrupted)

    for index, elem in enumerate(inputs[1]):
        if elem == -1 or elem == 0:
            inputs[1][index] = w0 + w1 * inputs[0][index]

    return [inputs[0], inputs[1]]

def normalize(features, mean=None, standard=None):
    if mean is None:
        mean = sum(features) / len(features)
    if standard is None:
        standard = (1 / len(features) * sum([(feat - mean) ** 2 for feat in features])) ** 0.5
    normalised_features = [(feat - mean) / standard for feat in features]
    return normalised_features, mean, standard


def normalizeData(inputs, outputs):
    normalized_inputs = []
    for feature in inputs:
        normalized_features, mean_value, std_dev = normalize(feature)
        normalized_inputs.append(normalized_features)
    normalized_outputs, mean_value, std_dev = normalize(outputs)
    return normalized_inputs, normalized_outputs

def plotDataHistogram(inputs, outputs, inputVariableName, inputVariableName2, outputVariableName):
    plt.style.use('classic')
    plt.subplot(2, 2, 1)
    plt.hist(inputs[0], bins=10, color='red', alpha=0.5, label=inputVariableName)
    plt.legend(loc='upper right')
    plt.title('Histogram of ' + inputVariableName)
    plt.subplot(2, 2, 2)
    plt.hist(inputs[1], bins=10, color='green', alpha=0.5, label=inputVariableName2)
    plt.legend(loc='upper right')
    plt.title('Histogram of ' + inputVariableName2)
    plt.subplot(2, 2, 3)
    plt.hist(outputs, bins=10, color='blue', alpha=0.5, label=outputVariableName)
    plt.legend(loc='upper right')
    plt.title('Histogram of ' + outputVariableName)
    plt.show()


def plotData3D(inputs, outputs, inputVariableName, inputVariableName2, outputVariableName):
    plt.style.use('default')
    fig = plt.figure()
    ax = fig.add_subplot(111, projection='3d')
    trainInputs, trainOutputs, validationInputs, validationOutputs = splitData(inputs, outputs, 0.8)
    ax.scatter(trainInputs[0], trainInputs[1], trainOutputs, c='r', marker='o', label='Train data')
    ax.scatter(validationInputs[0], validationInputs[1], validationOutputs, c='g', marker='^', label='Validation data')
    ax.set_xlabel(inputVariableName)
    ax.set_ylabel(inputVariableName2)
    ax.set_zlabel(outputVariableName)
    plt.legend(loc='upper right')
    plt.show()


def learnModelUnivariate(trainInputs, trainOutputs):
    xx = [[el] for el in trainInputs]
    regressor = BGDRegression()
    regressor.fit(xx, trainOutputs)
    w0, w1 = regressor.intercept_, regressor.coef_[0]
    return w0, w1

def learnModel(trainInputs, trainOutputs):
    xx = [[el1, el2] for el1, el2 in zip(trainInputs[0], trainInputs[1])]

    regressor = BGDRegression()
    regressor.fit(xx, trainOutputs)
    w0, w1, w2 = regressor.intercept_, regressor.coef_[0], regressor.coef_[1]
    return w0, w1, w2


def plotTrainDataLearnedModel(inputs, outputs, inputVariableName, inputVariableName2, outputVariableName):
    trainInputs, trainOutputs, validationInput, validationOutput = splitData(inputs, outputs, 0.8)
    w0, w1, w2 = learnModel(trainInputs, trainOutputs)
    noOfPoints = 1000
    x1ref = []
    val = min(trainInputs[0])
    step = (max(trainInputs[0]) - min(trainInputs[0])) / noOfPoints
    for i in range(noOfPoints):
        x1ref.append(val)
        val += step
    x2ref = []
    val = min(trainInputs[1])
    step = (max(trainInputs[1]) - min(trainInputs[1])) / noOfPoints
    for i in range(noOfPoints):
        x2ref.append(val)
        val += step
    yref = []
    for i in range(noOfPoints):
        yref.append(w0 + w1 * x1ref[i] + w2 * x2ref[i])

    fig = plt.figure()
    ax = fig.add_subplot(111, projection='3d')
    trainInputs, trainOutputs, validationInputs, validationOutputs = splitData(inputs, outputs, 0.8)
    ax.scatter(trainInputs[0], trainInputs[1], trainOutputs, c='r', marker='o', label='Train data')
    ax.scatter(x1ref, x2ref, yref, c='b', marker='.', label='Learned model')
    ax.set_title('Train data and the learned model')
    ax.set_xlabel(inputVariableName)
    ax.set_ylabel(inputVariableName2)
    ax.set_zlabel(outputVariableName)
    plt.legend(loc='upper right')
    plt.show()


def predictModel(inputs, w0, w1, w2=None):
    if w2 is None:
        predictedOutputs = [w0 + w1 * el for el in inputs]
    else:
        predictedOutputs = [w0 + w1 * el1 + w2 * el2 for el1, el2 in zip(inputs[0], inputs[1])]
    return predictedOutputs


def plotPredictedModel(inputs, outputs, inputVariableName, inputVariableName2, outputVariableName):
    trainInputs, trainOutputs, validationInputs, validationOutputs = splitData(inputs, outputs, 0.8)
    w0, w1, w2 = learnModel(trainInputs, trainOutputs)
    predictedOutputs = predictModel(validationInputs, w0, w1, w2)
    fig = plt.figure()
    ax = fig.add_subplot(111, projection='3d')
    ax.scatter(validationInputs[0], validationInputs[1], validationOutputs, c='g', marker='^', label='Validation data')
    ax.scatter(validationInputs[0], validationInputs[1], predictedOutputs, c='y', marker='o', label='Predicted data')
    ax.set_title('Validation data and the predicted data')
    ax.set_xlabel(inputVariableName)
    ax.set_ylabel(inputVariableName2)
    ax.set_zlabel(outputVariableName)
    plt.legend(loc='upper right')
    plt.show()


crtDir = os.getcwd()
filePath = os.path.join(crtDir, 'data', 'v3.csv')

inputs, outputs = loadData(filePath, ['Economy..GDP.per.Capita.', 'Freedom'], 'Happiness.Score')
inputs = removeBlanks(inputs)
inputs, outputs = normalizeData(inputs, outputs)

plotDataHistogram(inputs, outputs, 'GDP per Capita', 'Freedom', 'Happiness Score')
plotData3D(inputs, outputs, 'GDP per Capita', 'Freedom', 'Happiness Score')
plotTrainDataLearnedModel(inputs, outputs, 'GDP per Capita', 'Freedom', 'Happiness Score')
plotPredictedModel(inputs, outputs, 'GDP per Capita', 'Freedom', 'Happiness Score')
