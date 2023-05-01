import numpy as np
import networkx as nx
import matplotlib.pyplot as plt
import warnings

#algoritm genetic care sa identifice comunitatile dintr-o retea

def readNet(fileName):
    f = open(fileName, "r")
    net = {}
    n = int(f.readline())
    net['noNodes'] = n
    mat = []
    for i in range(n):
        mat.append([])
        line = f.readline()
        elems = line.split(" ")
        for j in range(n):
            mat[-1].append(int(elems[j]))
    net["mat"] = mat
    degrees = []
    noEdges = 0
    for i in range(n):
        d = 0
        for j in range(n):
            if (mat[i][j] == 1):
                d += 1
            if (j > i):
                noEdges += mat[i][j]
        degrees.append(d)
    net["noEdges"] = noEdges
    net["degrees"] = degrees
    f.close()
    return net

def modularity(communities, param):
    noNodes = param['noNodes']
    mat = param['mat']
    degrees = param['degrees']
    noEdges = param['noEdges']
    M = 2 * noEdges
    Q = 0.0
    for i in range(0, noNodes):
        for j in range(0, noNodes):
            if (communities[i] == communities[j]):
               Q += (mat[i][j] - degrees[i] * degrees[j] / M)
    return Q * 1 / M

def modularityGML(G,communities):
    noNodes =nx.number_of_nodes(G)
    mat = nx.to_numpy_array(G)
    degrees =[val for (node, val) in nx.degree(G)]
    noEdges = nx.number_of_edges(G)
    M = 2 * noEdges
    Q = 0.0
    for i in range(0, noNodes):
        for j in range(0, noNodes):
            if (communities[i] == communities[j]):
               Q += (mat[i][j] - degrees[i] * degrees[j] / M)
    return Q * 1 / M

def initialize(nrOfNodes,nrOfChromosomes):
    """
    initializeaza cromozomii
    """
    chromosomes=np.random.randint(nrOfNodes,size=(nrOfChromosomes,nrOfNodes))
    return chromosomes

def cross_over(chromosome_x,chromosome_y):
    """
    incruciseaza cromozomii
    """
    community_to_excange=np.random.choice(chromosome_x)
    for poz,community in enumerate(chromosome_x):
        if community==community_to_excange:
            chromosome_y[poz]=community
    return chromosome_y

def mutation(chromosome):
    """
    plaseaza un nod intr-o comunitate aleatorie
    """
    community=np.random.choice(chromosome)
    node=np.random.choice(range(len(chromosome)))
    chromosome[node]=community
    return chromosome

def selction(chromosomes_lst):
    """
    alege cromozomii cu cea mai mare modularitate
    """
    chromosomes_lst.sort(reverse=True, key=lambda x:x[0])
    return chromosomes_lst[0],chromosomes_lst[1]

def create_tuple(chromosomes,G):
    chroms_with_value=[]
    for chromosome in chromosomes:
        chroms_with_value.append((modularityGML(G,chromosome),chromosome))
    return chroms_with_value

def ga_algorithm(path,nr_of_generations):
    '''
    alege cromozomii cu cea mai mare modularitate si face un copil prin intercalarea lor
    '''
    G = nx.read_gml(path, label='id', destringizer=int)
    chromos=initialize(G.number_of_nodes(),400)
    chromosomes=create_tuple(chromos,G)
    for _ in range(nr_of_generations):
        for _ in range(int(nr_of_generations/2)):
            ch_x,ch_y=selction(chromosomes)
            child=cross_over(ch_x[1],ch_y[1])
            p_of_mutation=np.random.random()
            if(p_of_mutation<0.5):
                mutation(child)
            chromosomes.append((modularityGML(G,child),child))
        chromosomes.sort(reverse=True,key=lambda x:x[0])
        chromosomes=chromosomes[:int(nr_of_generations/2)]
    return chromosomes[0]

def plotNetwork(network, communities):
    np.random.seed(123)  # to freeze the graph's view (networks uses a random view)
    #    A=np.matrix(network["mat"])
    G = nx.read_gml(network, label='id', destringizer=int)
    pos = nx.spring_layout(G)  # compute graph layout
    plt.figure(figsize=(4, 4))  # image is 8 x 8 inches
    nx.draw_networkx_nodes(G, pos, node_size=100, cmap=plt.cm.RdYlBu, node_color=communities)
    nx.draw_networkx_edges(G, pos, alpha=0.3)
    plt.show()

path='Lab3/data/real-networks/real/krebs/krebs.gml'
comms=ga_algorithm(path,200)
plotNetwork(path,comms[1])