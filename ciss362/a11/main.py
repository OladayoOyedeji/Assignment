from latextool_basic import *
p = Plot()
m = [[r'$\{B_b,C_b\}$',         r'$\{A_a\}$',           r'$\{A_a\}$',           r'$\{A_a\}$',           r'$\{A_a\}$',           r'$\{B_b,C_b\}$'],
     [r'$\emptyset$',           r'$\{C_{(1,2),(1,3)}\}$', r'$\{C_{(1,3),(1,4)}\}$', r'$\{C_{(1,4),(1,5)}\}$', r'$\{S_{(1,5),(1,6)}\}$', r''],
     [r'$\{A_{(1,1),(2,2)}\}$',   r'$\{S_{(1,2),(2,3)}\}$', r'$\{S_{(1,3),(2,4)}\}$', r'$\{B_{(2,4),(1,6)}\}$', r'',                    r''],
     [r'$\{C_{(3,1),(1,4)}\}$',   r'$\emptyset$',         r'$\{S_{(1,3),(3,4)}\}$', r'',                   r'',                    r''],
     [r'$\{S_{(3,1),(2,4)}\}$',   r'$\{B_{(2,2),(3,4)}\}$', r'',                    r'',                   r'',                    r''],
     [r'$\{B_{(1,1),(2,5)}$ $S_{(3,1),(3,4)}\}$', r'',      r'',                    r'',                   r'',                    r''],
     ]
def getrect():
    width = 2.6  # width of cell
    height = 1.4 # height of cell
    def rect(x):
        return Rect(x0=0, y0=0, x1=width, y1=height,
                    innersep=0.2,
                    s='%s' % x, align='t')
    return rect

cyk(p, m, w='baaaab', fontsize='small', rect=getrect())
print(p)

