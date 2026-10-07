import copy
from csp_util import *    

#from CSP import CSP
from SudokuCSP import SudokuCSP
from sudoku_puzzles import sudokus
sudokus = [_.strip() for _ in sudokus.split('\n') if _.strip() != '']


if __name__ == '__main__':
               
    def sudoku_string_to_object(line):
        lines = []
        while line != '':
            x, line = line[:9], line[9:]
            lines.append(list(x))
        xs = lines
        lines = []
        for r,row in enumerate(xs):
            for c,col in enumerate(row):
                if col != '.':
                    a = chr(ord('A') + r)
                    b = c + 1
                    var = '%s%s' % (a, b)
                    val = int(col)
                    lines.append((var,val))
        s = ','.join(['%s=%s' % (var, val) for (var,val) in lines])
        s = 'SudokuCSP(%s)' % s
        x = eval(s)
        return x
    
    def yn_to_bool(s):
        if s == 'y':
            return True
        else:
            return False

    for i, line in enumerate(sudokus):
        print("%2s: %s" % (i, line))
    sudoku_string = input("index of above sudoku strings or your own sudoku string: ")
    sudoku_string = sudoku_string.strip()
    try:
        index = int(sudoku_string)
        sudoku_string = sudokus[index]
    except:
        pass
        
    view_option = input("view (t-text, g-gui): ")

    bt_option = input("[0] bt0  [2] bt2: ")
    if bt_option == '0':
        from bt0 import bt0 as bt
    else:
        from bt2 import bt2 as bt

    option = {}
    option['FC'] = True
    option['NC'] = True
    option['AC'] = True
    option['var_selection'] = 'MRV-MD'
    option['val_selection'] = 'LCV'

    if bt_option == '2':
        FC = input("FC? (y/n): ")
        FC = yn_to_bool(FC)

        NC = input("NC check? (y/n): ")
        NC = yn_to_bool(NC)

        AC = input("AC check? (y/n): ")
        AC = yn_to_bool(AC)

        var_selection = input("variable selection heuristic ([M]RV-MD [n]one): ")
        if var_selection == 'M':
            var_selection = 'MRV-MD'
        else:
            var_selection = None

        val_selection = input("value selection heuristic ([L]CV [n]one): ")

        if val_selection == 'L':
            val_selection = 'LCV'
        else:
            val_selection = None

        option['FC'] = FC
        option['NC'] = NC
        option['AC'] = AC
        option['var_selection'] = var_selection
        option['val_selection'] = val_selection
        
    sudoku = sudoku_string_to_object(sudoku_string)
    
    if view_option in ['g', 'G']:
        from SudokuGUIView import SudokuGUIView
        view = SudokuGUIView(sudoku)
    else:
        from SudokuTextView import SudokuTextView
        view = SudokuTextView(sudoku)

    assignment = []
    flag = bt(sudoku, assignment, view=view, option=option)

    if flag == False:
        print("ERROR: sudoku has no solution")
    view.wait()
    view.save(filename=sudoku_string)
