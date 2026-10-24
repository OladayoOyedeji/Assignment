import sys
import random;

# import config
from Board import *
from Problem import *
from Fringe import *
from ClosedList import *
from graph_search import graph_search

seed = int(input("enter random seed: "))
random.seed(seed)

size = int(input("size: "))
random = input("random or not: ")
board = RandomBoard(size)
if random not in "yY":
    board = input("initial: ")
    board = Board(n=size, s=board, seperator=',')
    
search = input("bfs or dfs or ucs or iddfs: ")


cost = None
iddfs = None
if search == 'bfs':
    fringe = Queue()
elif search == 'dfs':
    fringe = Stack()
elif search == 'ucs':
    fringe = FPQueue()
    cost = list(map(int, input().split()))
    if len(cost) < 4:
        cost.extend([0] * (4 - len(cost)))
    print(cost)
elif search == 'iddfs':
    fringe = Stack()
    board = DLSBoard(board)
    iddfs = True
else:
    raise Exception('invalid search')

problem = N2_1Problem(board=board,
                      initial_state=board,
                      goal_states=board.goal_states())

closed_list = SetClosedList()
solution = graph_search(problem=problem,
                        fringe=fringe,
                        closed_list=closed_list,
                        cost=cost,
                        iddfs=iddfs
                        )
print(type(solution))
print(len(solution))
input()


import animation
print("test")
print(board.board)
animation.draw(board.board, solution, prompt=False)
