from nQueensCSP import nQueensCSP

if __name__ == '__main__':    
    
    def yn_to_bool(s):
        if s == 'y':
            return True
        else:
            return False

    n = input("n (for n-by-n board for n-queens): ")
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
    option['val_selection'] = None

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
        
    nqueens = nQueensCSP(n=n)
    
    if view_option in ['g', 'G']:
        from nQueensGUIView import nQueensGUIView
        view = nQueensGUIView(nqueens)
    else:
        from nQueensTextView import nQueensTextView
        view = nQueensTextView(nqueens)

    assignment = []
    flag = bt(nqueens, assignment, view=view, option=option)

    if flag == False:
        print("ERROR: nqueens has no solution for n")
    view.wait()
    view.save(filename='%squeens' % n)
