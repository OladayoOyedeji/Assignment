import random
from opt2 import opt2_successor

def first_choice_hillclimbing(obj, points,
                              successor_method='p2',
                              maxtries=None):
    """
    Termination condition: max number of tries if len(points) by default
    """
    N = len(points)
    if N == 1: return False

    if maxtries == None:
        maxtries = N
    
    best_h = obj(points)
    old_h = best_h
    good_point = points
    
    for k in range(maxtries):
        tpoints = points
        new_h = None
        new_points = None
        if successor_method=='p2':
            i, j = random.sample(range(N), 2)
            points[i], points[j] = points[j], points[i]
            
            new_h = obj(points)
            if new_h <= best_h:
                new_points = points[:]
            else:
                new_h = None
            points[i], points[j] = points[j], points[i]

        elif successor_method == 'o2':
            i, j = sorted(random.sample(range(N-1), 2))
            new_points = opt2_successor(points, i, j)
            if new_points != None: 
                new_h = obj(new_points)

        if new_h != None:
            if new_h < best_h:
                best_h = new_h
                points = new_points
                good_point = points[:]
            
    if best_h == old_h:
        return False
    else:
        return good_point
    
