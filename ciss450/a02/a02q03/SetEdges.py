import Edges

class SetEdges(Edges.Edges):
    def __init__(self, E):
        Edges.Edges.__init__(self)
        self.E = set()
        for e in E:
            self.E.add(frozenset(e))
            
    def __contains__(self, u, v):
        return frozenset([u, v]) in self.E
    
    def __iter__(self):
        for _ in self.E:
            yield _
            
    def __str__(self):
        xs = [list(e) for e in self.E]
        xs.sort()
        return '{%s}' % (', '.join(['{%s, %s}' % tuple(e) for e in xs]))
    

if __name__ == '__main__':
    E = SetEdges([[3, 1], [2, 1]])
    print(E, type(E))
    print(str(E), type(E))
    for e in E:
        print(e, type(e))
