from latextool_basic import *
p = Plot()
p += Graph.node(x=0, y=0, name='a')
p += Graph.node(x=1, y=2, name='b')
p += Graph.node(x=2, y=0, name='c')
p += Graph.edge(names=['a', 'b'])
p += Graph.edge(names=['b', 'c'])
p += Graph.edge(names=['c', 'a'])
print(p)

