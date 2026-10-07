'''
Variable:
    A string.

Value:
    A string or int or float.

Domain:
    A list of values.
    In a CSP object, self.dom is a dictionary.
    For instance self.dom['A'] is a set of values for variable 'A'.
    
Constraint:
    A constraint is a string, a Python boolean expr, example "A != B".
    In a CSP object, self.constraint is a dictionary.
    self.constraint[X] is a constraint where X is a frozenset. For instance
    self.constraint[frozenset(['A', 'B'])] = "A != B".

    It is assumed that for each collection of variables, there is only
    one constraint. This is not an issue since two constraint "A < B" and
    "B < 2 * A" can be combined into "A < B and B < 2 * A".
    
    We are "cheating here" since our constraints are easy enough that
    Python expressions as strings is sufficient since Python can evaluate
    Python string expressions. (For any other "usual" programming language,
    the constraints are any propositional formulas or predicates, and
    we would have to use a logic library that allows creation of
    propositional variables, compound propositions, substitutions,
    evaluations, etc.)

Assignment:
    List of (variable, value). For instance ("X", 1) represents the assignment
    X = 1.

The CSP backtrack search assumes that the constraints are all unary or
binary. (This is not a serious limitation - see lecture notes.)

Example: Graph coloring.

    A
   /|
  B-C-D
  |
  E

A,B,C,D,E = 'A','B','C','D','E'
r,g,b,y = 'r','g','b','y'

csp = CSP(vars = [A, B, C, D, E],
          dom = {A: [r,g,b,y],
                 B: [r,g,b,y],
                 C: [r,g,b,y],
                 D: [r,g,b,y],
                 E: [r,g,b,y],
                 },
          constraint = {frozenset([A]): 'A == "r"',
                        frozenset([B]): 'B != "r"',
                        frozenset([A,B]): 'A != B',
                        frozenset([A,C]): 'A != C',
                        frozenset([B,C]): 'B != C',
                        frozenset([B,E]): 'B != E',
                        frozenset([C,D]): 'C != D',
                        },
          )
'''
    
import copy
from csp_util import *    

class CSP:

    def __init__(self,
                 vars=None,
                 dom=None,
                 constraint=None):
        self.vars = vars
        self.dom = dom
        self.constraint = constraint
        self.neighbors = dict([(X, set([])) for X in self.vars])
        for key in self.constraint.keys():
            for X in key:
                self.neighbors[X] |= key - frozenset([X])
        
    def __repr__(self):
        d = '\n'.join(["    %s: %s" % (v, self.dom[v]) \
                       for v in self.vars])
        c = '\n'.join(["    %s: (%s)" % (str(sorted(list(k))).replace('[','{').replace(']','}'),
                                         v) \
                       for k, v in sorted(self.constraint.items())])
        return r'''<CSP
  vars: %s
  dom:
%s
  constraints:
%s
>''' % (self.vars, d, c)


if __name__ == '__main__':
    A,B,C,D,E = 'A','B','C','D','E'
    r,g,b,y = 'r','g','b','y'
    colors = [r,g,y,b]
    
    csp = CSP(vars = [A, B, C, D, E],
              dom = {A: [r,g,b,y],
                     B: [r,g,b,y],
                     C: [r,g,b,y],
                     D: [r,g,b,y],
                     E: [r,g,b,y],
              },
              constraint = {frozenset([A]): 'A == "r"',
                            frozenset([B]): 'B != "r"',
                            frozenset([A,B]): 'A != B',
                            frozenset([A,C]): 'A != C',
                            frozenset([B,C]): 'B != C',
                            frozenset([B,E]): 'B != E',
                            frozenset([C,D]): 'C != D',
              },
    )
    print(csp)

