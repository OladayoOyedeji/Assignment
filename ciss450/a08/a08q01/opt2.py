"""
Utility function for opt-2 successor
"""

def opt2_successor(points, i, j):
    """
    Returns a list of points if points[i]-points[i+1] intersects with
    points[j]-points[j+1] at a unique point. Otherwise, None is returned.

    Note that the new set of points can have a larger length, i.e.,
    this function does not check for lengths.

    Note that if i is j, None is returned.
    """
    N = len(points)
    i = i % N
    j = j % N
    if i == j: return None

    
    # a, b = points[i]
    # c, d = points[i+1]
    
    # A, B = point[j]
    # C, D = point[j+1]
    
    x0, y0 = points[i]
    x1, y1 = points[i+1]

    x2, y2 = points[j]
    x3, y3 = points[j+1]
    x,y=None, None
    if (x0-x1 != 0 and x2-x3 != 0):
        a = (y1 - y0) / (x1 - x0)
        b = (x0 * y1 - x1 * y0) / (x0 - x1)
    
        c = (y2 - y3) / (x2 - x3)
        d = (x2 * y3 - x3 * y2) / (x2 - x3)
        
        if a-c==0: return None
        x = (d-b)/(a-c)
        
        y = a * x + b
    elif x0-x1 == 0 or x2-x3 == 0:
        return None
    elif x0-x1 == 0:
        c = (y2 - y3) / (x2 - x3)
        d = (x2 * y3 - x3 * y2) / (x2 - x3)
        
        x = x0
        y = c * x + d
    else:
        a = (y1 - y0) / (x1 - x0)
        b = (x0 * y1 - x1 * y0) / (x0 - x1)
        
        x = x2
        y = a * x + b
    intersect = (x < max(x0,x1) and x > min(x0,x1) and
                     x < max(x2,x3) and x > min(x2,x3) and
                     y < max(y0,y1) and y > min(y0,y1) and
                     y < max(y2,y3) and y > min(y2,y3))

    # swap points[i+1] and points[j]
    new_list = points[:i+1] + points[i+1:j+1][::-1] + points[j+1:]
    
    # print("*** NOT IMPLEMENTED ***")
    if intersect:
        return new_list
    return None

