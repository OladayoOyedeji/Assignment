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
                 closed_list=None,
                 view0=None,
                 cost=None,
                 iddfs=None
                 ):
    if cost == None:
        if iddfs == None:
            return early_graph_search(problem=problem,
                                      Node=Node,
                                      fringe=fringe,
                                      closed_list=closed_list,
                                      view0=view0)
        else:
            return IDDFS_graph_search(problem=problem,
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
        node, sol = fringe.get()
        # node.printl()
        sol = list(sol)
        closed_list.put(node)
        
        for d in node.get_directions():
            solution = sol.copy()
            solution.append(d)
            # print(sol, d)
            n0 = node.copy()
            n0.move(d)
        
            if problem.goal_test(n0):
                return solution
            
            if not (n0 in closed_list.values()):
                fringe.put((n0, solution))
        
    return None # None is used to indicate no solution

def late_graph_search(problem=None,
                      Node=None,
                      fringe=None,
                      closed_list=None,
                      view0=None,
                      cost=None
                      ):
    print(cost)
    def calc_cost(dire):
        print(cost)
        if dire == 'N':
            return cost[0]
        if dire == 'S':
            return cost[1]
        if dire == 'E':
            return cost[2]
        if dire == 'W':
            return cost[3]
        raise ValueError('invalid direction %s' % str(direction))
    initial_state = problem.get_initial_state()
    fringe.put((0,(initial_state, [])))
    
    while len(fringe) != 0:
        # print("QUEUE CONTENTS:", fringe)
        x = fringe.get()
        # _, (node, sol) = x
        y, r = x
        # print(y, r)
        node, sol = r
        sol = list(sol)
        if problem.goal_test(node): return sol
        closed_list.put(node)
    
        for d in  node.get_directions():
            solution = sol.copy()
            solution.append(d)
            # print(sol, d)
            n0 = node.copy()
            n0.move(d)
        
            if not (n0 in closed_list.values()):
                c = calc_cost(d)
                # print("JUST PUSHED:", (c, (n0, solution)))
                fringe.put((c, (n0, solution)))
                # print("JUST PUSHED:", (c, (n0, solution)))
                # print("QUEUE CONTENTS:", fringe.queue)
        
    return None

def DLS_graph_search(problem=None,
                 Node=None,
                 fringe=None,
                 closed_list=None,
                 view0=None,
                 ):
    
    while len(fringe) != 0:
        x, sol = fringe.get()
        sol = list(sol)
        node, depth = x
        closed_list.put(node)
        
        for d in node.get_DLSdirections(depth):
            solution = sol.copy()
            solution.append(d)
            n0 = node.copy()
            n0.move(d)
            
            if problem.goal_test(n0):
                return solution
            
            if not (n0 in closed_list.values()):
                fringe.put(((n0, depth+1), solution))
                
def IDDFS_graph_search(problem=None,
                      Node=None,
                      fringe=None,
                      closed_list=None,
                      view0=None,
                      ):
    initial_state = problem.get_initial_state()
    if problem.goal_test(initial_state): return []
    fringe.put(((initial_state, 0), []))
    
    for depth in range(1, 100):
        problem.board.max_depth = depth
        
        print("depth", depth, problem.board.max_depth)
        print(fringe)
        solutions = DLS_graph_search(problem, Node, fringe, closed_list)
        
        if solutions not in [None, []]:
            print("solution?", solutions)
            return solutions
        else:
            fringe.put(((initial_state, 0), []))
            closed_list.__init__()

    return None
