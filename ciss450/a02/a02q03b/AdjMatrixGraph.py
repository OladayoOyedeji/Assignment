import Graph
import AdjMatrixEdges

class AdjMatrixGraph(Graph.Graph):
    def __init__(self, E, V):
        Graph.Graph.__init__(self)
        self.__E = []
        self.__V = V

        for  i in V:
            self.__E.append([0] * len(V))

        for i, j in E:
            self.__E[i][j] = 1
            
    def get_E(self):
        return self.__E
    E = property(get_E, None)

    def is_node(self, i):
        return i in self.__V

    def is_edge(self, i, j):
        return (self.__E[i][j] == 1)
