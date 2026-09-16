import Graph
import AdjMatrixEdges

class AdjMatrixGraph(Graph.Graph):
    def __init__(self, E, n):
        Graph.Graph.__init__(self)
        self.__E = SetEdges.SetEdges(E, n)

    def get_E(self):
        return self.__E
    E = property(get_E, None)

    def is_node(self, i):
        return i in range(self.__E.n)

    def is_edge(self, i, j):
        return (i,j) in self.__E
