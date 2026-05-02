from latextool_basic import *
p = Plot()
p0 = (0,0)
p1 = (3,-1)
p2 = (4.5,0.8)
p3 = (4,2)
p4 = (2,3)
p5 = (0.5,2.5)
p6 = (-1,1)

p += Line(points=[p0,p1,p2,p3,p4,p5,p6,p0])
#p += Line(points=[p1,p4], linecolor='red')
p += Line(points=[p0,p3], linecolor='red')
p += Line(points=[p3,p6], linecolor='red')
#p += Line(points=[p4,p0], linecolor='red')

from latexcircuit import *

X = POINT(x=p0[0], y=p0[1], label='$p_0$', anchor='east'); p += str(X)
X = POINT(x=p1[0], y=p1[1], label='$p_1$', anchor='north'); p += str(X)
X = POINT(x=p2[0], y=p2[1], label='$p_2$', anchor='west'); p += str(X)
X = POINT(x=p3[0], y=p3[1], label='$p_3$', anchor='south west'); p += str(X)
X = POINT(x=p4[0], y=p4[1], label='$p_4$', anchor='south'); p += str(X)
X = POINT(x=p5[0], y=p5[1], label='$p_5$', anchor='south east'); p += str(X)
X = POINT(x=p6[0], y=p6[1], label='$p_6$', anchor='east'); p += str(X)

print(p)

