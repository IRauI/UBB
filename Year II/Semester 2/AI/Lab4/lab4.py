import random
import numpy as np
from graph import Graph

def read_graph(filename):
  f=open(filename,"r");
  mat=[]

  n=int(f.readline())
  graph=Graph(n)
  for i in range(n):
      mat.append([])
      line=f.readline()
      elems=line.split(",")
      for j in range(n):
          graph.addEdge(i,int(elems[j]))
  s=int(f.readline())
  d=int(f.readline())
  return graph,s,d

def crossOver(chromosome_x,chromosome_y):
    common=[]
    for node_x in chromosome_x[0:len(chromosome_x)]:
        if node_x in chromosome_y:
            common.append(node_x)

    if len(common)>0:
        point=np.random.choice(common)
    else :
        return chromosome_x,chromosome_y
    
    poz_x=chromosome_x.index(point)
    poz_y=chromosome_y.index(point)
    first_x=chromosome_x[:poz_x]
    first_y=chromosome_y[:poz_y]
    last_x=chromosome_x[poz_x:]
    last_y=chromosome_y[poz_y:]

    return first_x+last_y,first_y+last_x

def calculate_distance(graph,chromosome):
    source=chromosome[0]
    sum=0
    for node in chromosome[1:]:

        if graph.graph[source][node]==0:
            sum+=1000000
        else:
            sum+=graph.graph[source][node]
        source=node
    return sum


def initialize(graph,source,destination, nr_of_chroms):
    chromosomes = []
    for j in range(nr_of_chroms):
        chromosome=[source]
        i=0
        lungime=np.random.randint(graph.V)
        while i < lungime:
            new=random.randint(0,graph.V-1)
            if new!=chromosome[i]:
                chromosome.append(new)
                i+=1

        chromosome.append(destination)
        chromosomes.append(chromosome)
    return chromosomes
def create_tuple(chromosomes,matrix):
    tuples=[]
    for chromosme in chromosomes:
        tuples.append((calculate_distance(matrix,chromosme),chromosme))
    return tuples

def mutation(chromosomes,graph):
    positio_1=random.randint(0,len(chromosomes)-1)
    new = random.randint(0,int((graph.V - 1)))
    position=random.randint(0,len(chromosomes[positio_1][1])-1)
    chromosomes[positio_1][1][position] = new

def shortest_path(matrix,source,destination,nr_of_generations):
    nr_of_chroms=40
    chromosomes=initialize(matrix,source,destination,nr_of_chroms)
    chromosomes=create_tuple(chromosomes,matrix)
    chromosomes.sort(key=lambda c:c[0])

    for j in range(nr_of_generations):
        for i in range(int(nr_of_chroms/3)):
            ch_x=chromosomes[np.random.randint(int(nr_of_chroms/3))]
            ch_y = chromosomes[np.random.randint(int(nr_of_chroms/3))]
            child_1,child_2=crossOver(ch_x[1],ch_y[1])
            chromosomes.append((calculate_distance(matrix,child_1),child_1))
            chromosomes.append((calculate_distance(matrix, child_2), child_2))
            mutation(chromosomes,matrix)
        chromosomes=chromosomes[:int(nr_of_chroms/3)]

    chromosomes.sort( key=lambda c: c[0])
    return chromosomes[0]

grp,s,d=read_graph('Lab4/medium1.txt')

print(shortest_path(grp,s-1,d-1,30))