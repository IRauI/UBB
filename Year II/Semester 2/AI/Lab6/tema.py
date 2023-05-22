import csv
import os
import matplotlib.pyplot as plt
import numpy as np  
from sklearn import linear_model

def completeData(inputs):
    input0_notCorrupted = [inputs[0][i] for i in range(len(inputs[0])) if inputs[0][i] != -1 and inputs[1][i] != -1]
    input1_notCorrupted = [inputs[1][i] for i in range(len(inputs[1])) if inputs[0][i] != -1 and inputs[1][i] != -1]


    w0, w1 = train_uni(input1_notCorrupted, input0_notCorrupted)

    for index, elem in enumerate(inputs[0]):
        if elem == -1 or elem == 0:
            inputs[0][index] = w0 + w1 * inputs[1][index]

    w0, w1 = train_uni(input0_notCorrupted, input1_notCorrupted)

    for index, elem in enumerate(inputs[1]):
        if elem == -1 or elem == 0:
            inputs[1][index] = w0 + w1 * inputs[0][index]

    return [inputs[0], inputs[1]]
    
    
def loadData(fileName, inputName, inputName2, outputName):
    data = []
    dataNames = []
    with open(fileName) as csv_file:
        csv_reader = csv.reader(csv_file, delimiter=',')
        line_count = 0
        for row in csv_reader:
            if line_count == 0:
                dataNames = row
            else:
                data.append(row)
            line_count += 1

    for index in range(len(data)):
        for j in range(len(data[index])):
            if data[index][j] == '':
                data[index][j] = '-1'

    selectedVariable = dataNames.index(inputName)
    inputs = [float(data[i][selectedVariable]) for i in range(len(data))]
    selectedVariable2 = dataNames.index(inputName2)
    inputs2 = [float(data[i][selectedVariable2]) for i in range(len(data))]
    selectedOutput = dataNames.index(outputName)
    outputs = [float(data[i][selectedOutput]) for i in range(len(data))]

    for index, elem in enumerate(inputs):
        if (inputs[index] == 0 and inputs2[index] == 0) or (inputs[index] == -1 and inputs2[index] == -1):
            inputs.pop(index)
            inputs2.pop(index)
            outputs.pop(index)

    return [inputs, inputs2], outputs





def split_data(inputs, outputs):
    # split data into training data (80%) and testing data (20%)

    np.random.seed(5)
    indexes = [i for i in range(len(outputs))]
    trainSample = np.random.choice(indexes, int(0.8 * len(outputs)), replace = False)
    validationSample = [i for i in indexes  if not i in trainSample]

    trainIn = []
    valIns = []

    for feature in inputs:
        trainIn.append([feature[i] for i in trainSample])
        valIns.append([feature[i] for i in validationSample]) 
    
    trainOut = [outputs[i] for i in trainSample]
    valOut = [outputs[i] for i in validationSample]

    return trainIn, trainOut, valIns, valOut


def train_uni(trainIn, trainOut):
    aux = [[el] for el in trainIn]

    regressor = linear_model.LinearRegression()
    regressor.fit(aux, trainOut)
    w0, w1 = regressor.intercept_, regressor.coef_[0]
    return w0, w1

def train_bi(trainIn, trainOut):
    aux = [[el1, el2] for el1, el2 in zip(trainIn[0], trainIn[1])]

    regressor = linear_model.LinearRegression()
    regressor.fit(aux,trainOut)
    w0, w1, w2 = regressor.intercept_, regressor.coef_[0], regressor.coef_[1]
    return w0, w1, w2

def plotPredictedModel(inputs, outputs, inputName, inputName2, outputName):
    trainIn, trainOut, valIns, valOut = split_data(inputs, outputs)
    w0, w1, w2 = train_bi(trainIn, trainOut)
    predictedOutputs = [w0 + w1 * el1 + w2 * el2 for el1,el2 in zip(valIns[0],valIns[1])]
    fig = plt.figure()
    ax = fig.add_subplot(projection='3d')
    ax.scatter(valIns[0], valIns[1], valOut, c='r', marker='^', label='Validation data')
    ax.scatter(valIns[0], valIns[1], predictedOutputs, c='b', marker='o', label='Predicted data')
    ax.set_title('Validation data and the predicted data')
    ax.set_xlabel(inputName)
    ax.set_ylabel(inputName2)
    ax.set_zlabel(outputName)
    plt.legend(loc='upper right')
    plt.show()
    
def plotDataHistogram(inputs, outputs, inputName, inputName2, outputName):
    plt.style.use('classic')
    plt.subplot(1, 3, 1)
    plt.hist(inputs[0], bins=10, color='red', alpha=0.5, label=inputName)
    plt.title(inputName)
    plt.subplot(1, 3, 2)
    plt.hist(inputs[1], bins=10, color='blue', alpha=0.5, label=inputName2)
    plt.title(inputName2)
    plt.subplot(1, 3, 3)
    plt.hist(outputs, bins=10, color='yellow', alpha=0.5, label=outputName)
    plt.title(outputName)
    plt.show()


def plotData3D(inputs, outputs, inputName, inputName2, outputName):
    plt.style.use('default')
    fig = plt.figure()
    ax = fig.add_subplot(projection='3d')
    trainIn, trainOut, valIns, valOut = split_data(inputs, outputs)
    ax.scatter(trainIn[0], trainIn[1], trainOut, c='r', marker='o', label='Traing data')
    ax.scatter(valIns[0], valIns[1], valOut, c='b', marker='^', label='Validation data')
    ax.set_xlabel(inputName)
    ax.set_ylabel(inputName2)
    ax.set_zlabel(outputName)
    plt.legend(loc='upper right')
    plt.show()
    
def plotTrainDataLearnedModel(inputs, outputs, inputName, inputName2, outputName):
    trainIn, trainOut, valIn, valOut = split_data(inputs, outputs)
    w0, w1, w2 = train_bi(trainIn, trainOut)
    noOfPoints = 1000
    x1ref = []
    val = min(trainIn[0])
    step = (max(trainIn[0]) - min(trainIn[0])) / noOfPoints
    for i in range(noOfPoints):
        x1ref.append(val)
        val += step
    x2ref = []
    val = min(trainIn[1])
    step = (max(trainIn[1]) - min(trainIn[1])) / noOfPoints
    for i in range(noOfPoints):
        x2ref.append(val)
        val += step
    yref = []
    for i in range(noOfPoints):
        yref.append(w0 + w1 * x1ref[i] + w2 * x2ref[i])

    fig = plt.figure()
    ax = fig.add_subplot( projection='3d')
    trainIn, trainOut, valIns, valOut = split_data(inputs, outputs)
    ax.scatter(trainIn[0], trainIn[1], trainOut, c='r', marker='o', label='Train data')
    ax.scatter(x1ref, x2ref, yref, c='b', marker='.', label='Learned model')
    ax.set_title('Train data and the learned model')
    ax.set_xlabel(inputName)
    ax.set_ylabel(inputName2)
    ax.set_zlabel(outputName)
    plt.legend(loc='upper right')
    plt.show()

def main():
    crtDir = os.getcwd()
    filePath = os.path.join(crtDir, 'Lab6', 'data', 'v1.csv')

    inputs, outputs = loadData(filePath, 'Economy..GDP.per.Capita.', 'Freedom', 'Happiness.Score')
    inputs = completeData(inputs)

    plotDataHistogram(inputs, outputs, 'GDP', 'Freedom', 'Happiness')
    plotData3D(inputs, outputs, 'GDP', 'Freedom', 'Happiness')
    plotTrainDataLearnedModel(inputs, outputs, 'GDP', 'Freedom', 'Happiness')
    plotPredictedModel(inputs, outputs, 'GDP', 'Freedom', 'Happiness')

main()
