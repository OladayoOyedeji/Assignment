import Edges

class AdjMatrixEdges(Edges.Edges):
    def __init__(self, E, n):
        Edges.Edges.__init__(self)
        self.E = []
        self.n = n
        for  i in range(n):
                self.E.append([0] * n)
        for i, j in E:
            self.E[i][j] = 1
        
    def __contains__(self, u, v):
        return self.E[u][v] == 1

    def __iter__(self):
        for _ in self.E:
            yield _

    def __str__(self):
        s = ""
        n = self.n
        for i in range(n):
            delim = ''
            for j in range(n):
                s += delim + str(self.E[i][j])
                delim = ', '
            s += '\n'

        return s

if __name__ == '__main__':
    E = AdjMatrixEdges([[3, 1], [2, 1]], 4)
    print(E, type(E))
    print(str(E), type(E))
    for e in E:
        print(e, type(e))
