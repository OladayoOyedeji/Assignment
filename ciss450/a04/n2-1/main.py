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
    
search = input("bfs or dfs: ")

problem = N2_1Problem(board=board,
                      initial_state=board,
                      goal_states=board.goal_states())

if search == 'bfs':
    fringe = Queue()
elif search == 'dfs':
    fringe = Stack()
else:
    raise Exception('invalid search')

closed_list = SetClosedList()
solution, n = graph_search(problem=problem,
                        fringe=fringe,
                        closed_list=closed_list# ,
                        # view0=view0
                        )
print(solution, n)


import animation
print("test")
animation.draw(board.board, solution, prompt=False)
