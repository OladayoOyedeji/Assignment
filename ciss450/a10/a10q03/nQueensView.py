import time, copy, resource

def get_ustime():
    usage = resource.getrusage(resource.RUSAGE_SELF)
    return getattr(usage, 'ru_utime'), getattr(usage, 'ru_stime')

    
class nQueensView:
    def __init__(self, csp):
        self.csp = copy.deepcopy(csp)
        self.count = 0               # count increments by 1 each time run()
                                     #     is called
        self.lengths = []            # lengths is a list of
                                     #     (count, len(assignment))
        self.start_wall_clock_time = time.time() # wall clock time
        utime, stime = get_ustime()
        self.start_utime = utime 
        self.start_stime = stime 
        self.wall_clock_time = 0.0   # wall clock time taken 
        self.utime = 0.0
        self.stime = 0.0

    def run(self, csp, assignment):
        self.wall_clock_time = (time.time() - self.start_wall_clock_time)
        utime, stime = get_ustime()
        self.utime = utime - self.start_utime
        self.stime = stime - self.start_stime
        self.count += 1
        self.lengths.append((self.count, len(assignment)))
                    
    def wait(self):
        pass
