"""
Brute force backtracking search.
- Uses backtracking tree search (i.e., no closed list).
- A "state" is a partial and consistent assignment.
- An "action" is adding an assignment of the form X = x to assignment. This
  involves:
  - Choosing a variable X
  - Choosing a value x in the domain of X

Note that this backtrack search does not use optimization or heuristic.
"""

from csp_util import *    

def bt0(csp, assignment, view=None, option=None):
    #==========================================================================
    # CSP BT search without any heuristic
    #==========================================================================
    if csp.goal_test(assignment):
        return True

    #==========================================================================
    # Choose variable that is unassignment
    #==========================================================================
    assigned_vars = [var for (var,val) in assignment]
    X = None
    for X in csp.vars:
        if X not in assigned_vars:
            break
    if X == None:
        raise ValueError("Cannot find unassigned variable")

    #==========================================================================
    # Iterate over all x in domain of X and see if (X, x) (i.e., X = x) can
    # be added to assignment to form consistent assignment.
    #==========================================================================
    for x in csp.dom[X]:

        #======================================================================
        # Check if any constraint is violated for the assignment + [(X, x)]
        # 1. If no constraint is violated, modify state (the assignment) by
        #    adding (X, x) (i.e., X = x) to the assignment. Make recursive bt0
        #    call for next assignment.
        # 2. If some constraint is violated, then the current (X, x) that was
        #    added to assignment must be removed and a new x is used.
        #======================================================================
        if is_consistent(csp, assignment + [(X, x)]):

            assignment.append((X, x))
            if view: view.run(csp, assignment)

            flag = bt0(csp, assignment, view=view, option=option)
            if flag == True:
                return True
            else:
                #==============================================================
                # The assignment became inconsistent in a future bt0 call.
                # Remove (X, x) from assignment and try a new x.
                #==============================================================
                assignment.pop() 
        else:
            #==================================================================
            # assignment + [(X,x)] is inconsistent.
            # Try a new x from domain of X in the next iteration of the for-
            # loop.
            #==================================================================
            pass
        
    return False
