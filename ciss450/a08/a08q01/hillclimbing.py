import random
from opt2 import opt2_successor

def hillclimbing(obj, points, successor_method='p2'):
    """
    old_h:  objective value of the original input points
    best_h: best running object value as we run through all successors
    good_pointss: list of best running paths
    """

    best_h = obj(points)
    old_h = best_h
    good_pointss = [points[:]]
    N = len(points)
    for i in range(N):
        for j in range(i + 1, N-1):

            new_h = None
            new_points = None
    
            if successor_method== 'p2':
                points[i], points[j] = points[j], points[i]
                new_h = obj(points)
                if new_h <= best_h:
                    new_points = points[:]
                else:
                    new_h = None
                points[i], points[j] = points[j], points[i]
            
            elif successor_method == 'o2':
                new_points = opt2_successor(points, i, j)
                if new_points != None: 
                    new_h = obj(new_points)

            if new_h != None:
                if new_h < best_h:
                    best_h = new_h
                    good_pointss = [new_points]
                elif new_h == best_h:
                    good_pointss.append(new_points)
                    
    if best_h == old_h:
        return False
    else:
        return random.choice(sorted(good_pointss))

        
