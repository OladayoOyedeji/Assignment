"""
Backtracking search.with tree pruning and heuristic
- Uses backtracking tree search (i.e., no closed list).
- A state is a partial and consistent assignment.
- An action is adding an assignment of for form X = x to assignment. This
  involves:
  - Choosing a variable X
  - Choosing a value x in the domain of X

Pruning:
  - FC = Forward checking
  - NC = Node consistency checking
  - AC = Arc consistency checking 
NC and AC is used as processing before the BT search.
During the BT search, once a (X, x) is added to the assignment,
  - FC is executed
  - NC is executed
  - AC using MAC (specifically AC3) is executed

Heuristic:
  - For choosing a variable:
      - MRV = minimum remaining value heuristic
      - MD = maximum degree heuristic
    MRV is used first and MD is used as tie-breaker.
    If there are ties after MRV-MD is used, then the ties are sorted and
    the first is selected.
  - For choosing a value (for a variable):
      - LCV = least constraining value
    The domain of variable is sorted by LCV (and then by the value).

USAGE
-----
bt2_helper(csp, assignment, view=None, option=None)
bt2(csp, assignment, view=None, option=None)

- csp: CSP object
- view; For visualization during search
- option is a dictionary for turning on/off pruning and heuristics
  - option['FC_option'] = True/False
  - option['AC_option'] = True/False
  - option['var_selection_option'] = 'MRV-MD' or None
  - option['val_selection_option'] = 'LCV' or None
"""

import copy
from SudokuCSP import SudokuCSP

def bt2_helper(csp, assignment, view=None, option=None):

    if csp.goal_test(assignment):
        return True
    
    #==========================================================================
    # Select variable X from csp.
    #==========================================================================
    X = None
    
    for x in csp.ordered_dom(X, option):
        
        #======================================================================
        # Select value x and add (X, x) to assignment to get new_assignment.
        #======================================================================
        assignment.append((X, x))
        
        #======================================================================
        # Display new assignment
        #======================================================================
        if view: view.run(csp, assignment)
        
        #======================================================================
        # Forward checking
        # Form new_csp with X removed from csp.
        #======================================================================
        new_csp = SudokuCSP(vars=None, 
                            dom=None,
                            constraint=None)
        #======================================================================
        # NC on Y for Y affected by X.
        # If NC fails, remove (X, x) from assignment and continue to the next
        # iteration of the for loop.
        #======================================================================

        #======================================================================
        # AC on Y for Y affected by X.
        # If AC fails, remove (X, x) from assignment and continue to the next
        # iteration of the for loop.
        #======================================================================

        #======================================================================
        # Make recursive call bt2_helper with new_csp.
        # If return is True, return True.
        # Otherwise, remove (X, x) from assignment and continue to the next
        # iteration of the for loop.
        #======================================================================
        
    return False


def bt2(csp, assignment, view=None, option=None):
    #======================================================================
    # NC
    #======================================================================
    if option!=None and option['NC']:
        flag = csp.node_consistency_check()
        if flag == False:
            return False
    #======================================================================
    # AC
    #======================================================================    
    if option!=None and option['AC']:
        flag = csp.ac3()
        if flag == False:
            return False

    flag = bt2_helper(csp, assignment, view=view, option=option)
    return flag
