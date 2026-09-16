import Graph
import VertexSet
import SetEdges

class SetGraph(Graph.Graph):
    '''
    If G is a graph object, then
    G.E -- set of edges where each edge is a frozenset of two nodes
    '''
    def __init__(self, V, E):
        Graph.Graph.__init__(self)
        self.__V = VertexSet.VertexSet(V)
        self.__E = SetEdges.SetEdges(E)
        
    def get_V(self):
        return self.__V
    V = property(get_V, None)
    
    def get_E(self):
        return self.__E
    E = property(get_E, None)
    
    def is_node(self, i):
        return i in self.__V
    
    def is_edge(self, i, j):
        return frozenset([i,j]) in self.__E
    
    def is_adj(self, i, j):
        return self.is_edge(i, j)
    
    def __str__(self):
        return '<SetGraph V=%s, E=%s>' % (str(self.__V),
                                          str(self.__E))
