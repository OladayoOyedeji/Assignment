import random
from math import e as e
from opt2 import opt2_successor

def simulated_annealing(obj, points, successor_method='p2',
                        t=0,
                        T0=10.0**50,
                        r=0.90
                        ):

    """
    The time schedule is T = T0 * (r ** t)
    """
    
    T = T0 * r**t
        
    if T == 0: # our case, this will not happen
        return points

        
    print("*** NOT IMPLEMENTED***")
