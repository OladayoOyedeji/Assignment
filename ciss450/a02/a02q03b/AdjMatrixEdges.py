import Edges

class AdjMatrixEdges(Edges.Edges):
    def __init__(self, E):
        Edges.Edges.__init__(self)
        self.E = set(E)
        
    def __contains__(self, u, v):
        return (u, v) in self.E

    def __iter__(self):
        for _ in self.E:
            yield _

if __name__ == '__main__':
    E = AdjMatrixEdges([[3, 1], [2, 1]], 4)
    print(E, type(E))
    print(str(E), type(E))
    for e in E:
        print(e, type(e))
