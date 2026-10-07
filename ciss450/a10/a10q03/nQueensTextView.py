import sys, random, math, copy
import nQueensView

class nQueensTextView(nQueensView.nQueensView):
    
    def __init__(self, csp):
        nQueensView.nQueensView.__init__(self, csp)
        self.output = ''

    def run(self, csp, assignment):
        nQueensView.nQueensView.run(self, csp, assignment)
        n = csp.n
        print(csp)
        x = [[' ' for i in range(n)] for j in range(n)]
        for k,v in assignment:
            c = int(k[1:]) # k = 'q0',...
            r = int(v)
            x[r][c] = 'Q'

        s = ''
        s += '+' + ('+'.join('-' for _ in range(n))) + "+\n"
        for row in x:
            s += '|' + ('|'.join(row)) + "|\n"
            s += '+' + ('+'.join('-' for _ in range(n))) + "+\n"
            
        s += "states examined: %s\n" % self.count
        s += "current number of assigned variables: %s (of 81)\n" % len(assignment)
        s += "wall clock time: %.4f seconds\n" % self.wall_clock_time
        s += "user time: %.4f seconds\n" % self.utime
        s += "system time: %.4f seconds\n" % self.stime
        self.output = s
        print(s)

    def save(self, filename=None):
        if filename == None:
            import random; random.seed()
            filename = random.randrange(10000000,1000000000)
            filename = str(filename)
        filename = filename.replace('.', '-')
        open(filename + ".txt", 'w').write(self.output)
        
    def wait(self):
        #raw_input("Press enter ...")
        pass
    
if __name__ == '__main__':
    pass
