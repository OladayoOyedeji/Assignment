from latextool_basic import *
p = Plot()
p += Line(points=[(0,4.25),(0,0),(12,0)])
points = [(0.5,0), (0.5,2), (2,2), (2,4),
(4,4),(4,1),(5,1),(5,2.5), (5.5,2.5),
(5.5,1), (7,1), (7,0), (7.5,0), (7.5,2),(8,2),(8,3),(8.25,3),
(8.25,3.5),(9.5,3.5),(9.5,2),(11,2),(11,0)]
p += Line(points=points,
          linecolor='red', linewidth=0.1)

for i,point in enumerate(points):
    x,y = point
    label = r'$(x_{%s},y_{%s})$' % (i, i)
    if i == 0:
        p += Rect(x0=x, y0=y-0.5, x1=x, y1=y-0.5,
             label=label, linewidth=0)
    elif i == 1:
        p += Rect(x0=x+0.4, y0=y+0.5, x1=x+0.4, y1=y+0.5,
             label=label, linewidth=0)
    elif i == 2:
        p += Rect(x0=x, y0=y-0.5, x1=x, y1=y-0.5,
             label=label, linewidth=0)
    elif i == 3:
        p += Rect(x0=x, y0=y+0.5, x1=x, y1=y+0.5,
             label=label, linewidth=0)

    p += Circle(x=x, y=y, r=0.12, background='red', linecolor='red')

print(p)

