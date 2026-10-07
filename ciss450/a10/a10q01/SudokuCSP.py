from CSP import CSP

class SudokuCSP(CSP):
    def __init__(self,
                 vars=None, dom=None, constraint=None,
                 **arg):

        if vars != None and dom != None and constraint != None:
            CSP.__init__(self,
                     vars=vars,
                     dom=dom,
                     constraint=constraint)
        else:
            vars = []
            dom = {}
            for x in 'ABCDEFGHI':
                for y in '123456789':
                    var = '%s%s' % (x, y)
                    vars.append(var)
                    dom[var] = [1,2,3,4,5,6,7,8,9]
            constraint={}

            # Row constraints
            ALPHA = 'ABCDEFGHI'
            for x in ALPHA:
                for i in range(1, 10):
                    for j in range(i + 1, 10):
                        var1 = '%s%s' % (x, i)
                        var2 = '%s%s' % (x, j)
                        c = '%s != %s' % (var1, var2)
                        constraint[frozenset([var1, var2])] = c

            # Column constraints
            for x in range(1, 10):
                for i in range(0, 9):
                    for j in range(i + 1, 9):
                        var1 = '%s%s' % (ALPHA[i], x)
                        var2 = '%s%s' % (ALPHA[j], x)
                        c = '%s != %s' % (var1, var2)
                        constraint[frozenset([var1, var2])] = c

            # 3-by-3 cell constraints
            ROWS = 'ABCDEFGHI'
            COLS = '123456789'
            for row in range(0, 9, 3):
                for col in range(0, 9, 3):
                    vars_in_cell = []
                    for i in range(row, row+3):
                        for j in range(col, col+3):
                            var = '%s%s' % (ROWS[i], COLS[j])
                            vars_in_cell.append(var)
                    for i in range(len(vars_in_cell)):
                        for j in range(i + 1, len(vars_in_cell)):
                            var1 = vars_in_cell[i]
                            var2 = vars_in_cell[j]
                            c = '%s != %s' % (var1, var2)
                            constraint[frozenset([var1, var2])] = c

            # These constraints correspond to the cells which are
            # pre-filled.
            for k, v in arg.items():
                constraint[frozenset([k])] = '%s == %s' % (k, v)

            CSP.__init__(self,
                         vars=vars,
                         dom=dict([(k,[1,2,3,4,5,6,7,8,9]) for k in vars]),
                         constraint=constraint)
        self.n = 81 # NOTE: This is used by goal_test and it not really necessary.
            
    def goal_test(self, assignment):
        return len(assignment) == self.n

    
if __name__ == '__main__':
    # A sudoku where A1 is prefilled with 1, B1 is prefilled with 2.
    csp = SudokuCSP(A1=1, B1=2) 
    print(csp)
