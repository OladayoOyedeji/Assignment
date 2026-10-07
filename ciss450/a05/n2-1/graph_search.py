import random
from collections import deque
# from SearchNode import SearchNode
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
                 closed_list=None# ,
                 # view0=None,
                 ):

    #==========================================================================
    # TODO: The code here creates a *random* solution starting at state (0,0).
    # Replace with the correct late version of graph search algorithm.
    #==========================================================================
    initial_state = problem.get_initial_state()

    if problem.goal_test(initial_state): return []

    fringe.put((initial_state, []))
    
    while len(fringe) != 0:
        node, sol = fringe.get()
        # node.printl()
        sol = list(sol)
        closed_list.put(node)
        # if problem.goal_test(x):
        #     return solution
        # print("direction", node.get_directions())
        
        for d in  node.get_directions():
            solution = sol.copy()
            solution.append(d)
            # print(sol, d)
            n0 = node.copy()
            n0.move(d)
        
            if problem.goal_test(n0):
                return solution, n0
            
            if not (n0 in closed_list.values()):
                fringe.put((n0, solution))
        
        #======================================================================
        # TODO: The following randomly colors the maze cells with red and blue.
        # Replace with the following:
        # - Iterate through the fringe and color the states of the search
        #   nodes with blue
        # - Iterate through the closed list and color the states with red
	# - Color the initial state green
        #======================================================================
       
        
    return None # None is used to indicate no solution
