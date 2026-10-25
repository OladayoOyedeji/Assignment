import random
from math import e as e
from opt2 import opt2_successor
import math

def simulated_annealing(obj, points, successor_method='p2',
                        t=0,
                        T0=10.0**50,
                        r=0.90
                        ):

    """
    The time schedule is T = T0 * (r ** t)
    """
    def schedule():
        return T0 * r**t
        
    # if T == 0: # our case, this will not happen
    #
    N = len(points)
    T = schedule()
    if T == 0:
        return points

    new_points = points.copy()
    best_h = obj(points)
    
    if successor_method == 'p2':
        i, j = random.sample(range(N), 2)
        points[i], points[j] = points[j], points[i]
        new_points = points[:]
        points[i], points[j] = points[j], points[i]
        
    elif successor_method == 'o2':
        i, j = sorted(random.sample(range(N-1), 2))
        new_points = opt2_successor(points, i, j)
        if new_points != None: 
            new_h = obj(new_points)
            

    DE = obj(new_points) - obj(points)
    if DE <= 0:
        return new_points
    else:
        x = random.random()
        if x < math.e**(-DE/T):
            return new_points
        else:
            return points

        
    print("*** NOT IMPLEMENTED***")
