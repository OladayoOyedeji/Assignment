import random
from hillclimbing import hillclimbing

class Random_Restart_Hillclimbing:
    def __init__(self):
        self.prev_points = None
        self.successor_method = 'p2'
    def __call__(self,
                 obj, points, successor_method='p2'):
        new_points = hillclimbing(obj,points,successor_method)
        
        if new_points:
            if self.prev_points == None or \
               obj(new_points) < obj(self.prev_points):
                self.prev_points = new_points
                self.successor_method = successor_method
                
                return new_points
        
        random.shuffle(self.prev_points)
        return self.prev_points
            
        print("*** NOT IMPLEMENTED ***")

    def final(self, obj, points):
        if obj(points) < obj(self.prev_points):
            return points
        else:
            return self.prev_points
        
random_restart_hillclimbing = Random_Restart_Hillclimbing()
