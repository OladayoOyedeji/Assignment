import random
from opt2 import opt2_successor

def stochastic_hillclimbing(obj, points, successor_method='p2'):

    print("*** NOT IMPLEMENTED ***")

    best_h = obj(points)
    old_h = best_h
    good_pointss = [(best_h,points[:])]

    N = len(points)

    for i in range(N):
        for j in range(i+1, N-1):
            new_h = None
            new_points = None

            if successor_method=="p2":
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
                    good_pointss = [(best_h, new_points)]
                elif new_h == best_h:
                    good_pointss.append((best_h, new_points))

    if best_h == old_h:
        return False
    else:
        # calculate the distance from the base
        dist = [abs(h - 10) for h, _ in good_pointss]
            
        # create lists of intervals
        s0, _ = good_pointss[0]

        intervals = []
        for i in range(len(good_pointss)):
            intervals.append((s0 + sum(dist[:i]), s0 + sum(dist[:i+1])))
        i,_ = intervals[0]
        _,j = intervals[-1]

        x = random.uniform(i, j)

        i = 0
        for a,b in intervals[:-1]:
            if x >= a and x < b:
                break
            
        return good_pointss[i][1]
