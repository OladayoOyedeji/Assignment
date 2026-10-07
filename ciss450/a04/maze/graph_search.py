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
                 ):

    #==========================================================================
    # TODO: The code here creates a *random* solution starting at state (0,0).
    # Replace with the correct late version of graph search algorithm.
    #==========================================================================
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
            #     q.append(d)
        # (r, c) = (0, 0)
        # maze = problem.maze
        # for action in solution:
        #     (r, c) = maze.get_adj_tuple((r, c), action)
        # dirs = maze.get_directions((r, c))
        # if dirs != []:
        #     action = random.choice(dirs)
        #     solution.append(action)
        #     print("actions:", dirs, ",", end='')
        #     print("choose:", action, ",", end='')
        #     print("resulting pos:", maze.get_adj_tuple((r, c), action))
        #     print("solution:", solution)
        #     print()
            
        # if random.randrange(0, 200) == 0:
        #     return solution
        
        
        
        #======================================================================
        # TODO: The following randomly colors the maze cells with red and blue.
        # Replace with the following:
        # - Iterate through the fringe and color the states of the search
        #   nodes with blue
        # - Iterate through the closed list and color the states with red
	# - Color the initial state green
        #======================================================================
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
