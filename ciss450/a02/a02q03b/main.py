import AdjMatrixGraph

def is_coloring(G, c):
    # check each edge if
    for edge in G.E:
        e = list(edge)
        if c[e[0]] == c[e[1]]:
            return False
    return True
    
    
# if __name__ == '__main__':
#     V = []
#     E = [(0, 1), (0, 3), (2, 1), (3, 1)]
    
#     G = SetGraph.SetGraph(V, E)
    
#     c = {0: 'RED', 1:' GREEN', 2 :'BLUE', 3:'BLUE'}

#     print(is_coloring(G, c))

if __name__ == '__main__':
    n = int(input("number of nodes: "))
    V = list(range(n))
    E = []
    while 1:
        i = int(input())
        if i == -1: # stop entering edges if input is -1
            break
        j = int(input())
        E.append((i, j))
    G = SetGraph.SetGraph(V, E)
    
    c = []
    for i in V:
        color = input('color for %s: ' % i)
        c.append((i, color))
        
    print(is_coloring(G, c))
            
