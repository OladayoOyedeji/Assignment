import sys, random, math, copy
import SudokuView

class SudokuTextView(SudokuView.SudokuView):
    
    def __init__(self, csp):
        SudokuView.SudokuView.__init__(self, csp)
        self.output = ''

    def run(self, csp, assignment):
        SudokuView.SudokuView.run(self, csp, assignment)
        x = [[0 for i in range(9)] for j in range(9)]
        for k,v in assignment:
            r,c = k
            r = ord(r) - ord('A')
            c = ord(c) - ord('1')
            x[r][c] = v

        s = ''
        for r,row in enumerate(x):
            if r % 3 == 0:
                s += "+-------" * 3 + '+' + '\n'
            for c,col in enumerate(row):
                if c % 3 == 0: s += '|' + ' '
                s += str(col) + ' '
            s += '|\n'
        s += "+-------" * 3 + '+' + '\n'
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
        pass

    
if __name__ == '__main__':
    pass
