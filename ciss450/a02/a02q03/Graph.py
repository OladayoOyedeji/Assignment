# File: Graph.py

class Graph:
    def __init__(self):
        pass
    
    def is_node(self, i):
        raise NotImplementedError
    
    def is_edge(self, i, j):
        raise NotImplementedError
    
    def is_adj(self, i, j):
        raise NotImplementedError
    
    def __str__(self):
        raise NotImplementedError
