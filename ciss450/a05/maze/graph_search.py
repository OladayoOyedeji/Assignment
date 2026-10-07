import random
from collections import deque
from SearchNode import SearchNode
from Fringe import Queue
from ClosedList import SetClosedList

#==============================================================================
# GRAPH_SEARCH
#
# The fringe and closed list must be drawn while the thinking takes place.
# - Draw the closed list blue (255, 0, 0).
# - Draw the fringe in green (0, 255, 0).
#
# There must be NO console printing in this python file. Make sure you remove
# them or comment them out when you are done.
#==============================================================================
def graph_search(problem=None,
                 Node=None,
                 fringe=None,
                 closed_list=None,
                 view0=None,
                 cost=None
                 ):
    if cost == None:
        return early_graph_search(problem=problem,
                           Node=Node,
                           fringe=fringe,
                           closed_list=closed_list,
                           view0=view0)
    else:
        return late_graph_search(problem=problem,
                           Node=Node,
                           fringe=fringe,
                           closed_list=closed_list,
                           view0=view0,
                           cost=cost)
    
def early_graph_search(problem=None,
                 Node=None,
                 fringe=None,
                 closed_list=None,
                 view0=None,
                 ):

    initial_state = problem.get_initial_state()

    if problem.goal_test(initial_state): return []

    fringe.put((initial_state, []))
    
    while len(fringe) != 0:
        x, sol = fringe.get()
        sol = list(sol)
        closed_list.put(x)
        # if problem.goal_test(x):
        #     return solution
        
        maze = problem.maze

        print("direction", maze.get_directions(x))
        for d in maze.get_directions(x):
            solution = sol.copy()
            solution.append(d)
            print(sol, d)
            if maze[x, d] != 0:
                continue
            n0 = maze.get_adj_tuple(x, d)
        
            if problem.goal_test(n0):
                return solution
            print(closed_list.values(), n0)
            if not (n0 in closed_list.values()):
                print(True)
                print(solution)
                fringe.put((n0, solution))
                
        if view0:
            # Fringe = blue
            for node in fringe:
                (r, c), _ = node
                
                view0['maze'].background[(r, c)] = (0, 0, 255)
            # Closed list = red
            for state in closed_list.values():
                r, c = state
                view0['maze'].background[(r, c)] = (255, 0, 0)

            # Initial state = green
            r, c = problem.initial_state
            view0['maze'].background[(r, c)] = (0, 255, 0)

            goal_states = list(problem.goal_states)
            for state in goal_states:
                r, c = state
                view0['maze'].background[(r, c)] = (0, 255, 0)
            view0.run()
        
    return None # None is used to indicate no solution

def late_graph_search(problem=None,
                 Node=None,
                 fringe=None,
                 closed_list=None,
                 view0=None,
                 cost=None
                 ):

    
    def calc_cost(state):
        if state not in cost.keys():
            return 0
        else:
            return cost[state]
    initial_state = problem.get_initial_state()
    fringe.put((calc_cost(initial_state), (initial_state, [])))
    
    while len(fringe) != 0:
        _, (node,sol) = fringe.get()
        sol = list(sol)
        
        if problem.goal_test(node): return sol
        closed_list.put(node)
        
        maze = problem.maze

        print("direction", maze.get_directions(node))
        for d in maze.get_directions(node):
            solution = sol.copy()
            solution.append(d)
            print(sol, d)
            n0 = maze.get_adj_tuple(node, d)
        
            print(closed_list.values(), n0)
            if not (n0 in closed_list.values()):
                print(True)
                print(solution)
                print(n0, calc_cost(n0))
                fringe.put((calc_cost(n0), (n0, solution)))
           
        if view0:
            # Fringe = blue
            for node in fringe:
                _ , ((r, c), _) = node
                
                view0['maze'].background[(r, c)] = (0, 0, 255)
                
            for node in cost.keys():
                (r, c) = node
                
                view0['maze'].background[(r, c)] = (255, 255, 0)

            # Closed list = red
            for state in closed_list.values():
                r, c = state
                view0['maze'].background[(r, c)] = (255, 0, 0)

            # Initial state = green
            r, c = problem.initial_state
            view0['maze'].background[(r, c)] = (0, 255, 0)

            goal_states = list(problem.goal_states)
            for state in goal_states:
                r, c = state
                view0['maze'].background[(r, c)] = (0, 255, 0)
            view0.run()
        
    return None # None is used to indicate no solution
