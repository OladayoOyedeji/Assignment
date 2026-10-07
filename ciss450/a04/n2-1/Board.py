import math
import random
import hashlib

def matrix(n, s, seperator=None):

    if seperator != None:
        s = s.split(seperator)
    
    i = 0
    j = 0
    ret = []
    l = []
    
    while len(s) != 0:
        if i == n:
            ret.append(l)
            l = []
            i = 0
        l.append(s[0])
        s = s[1:]
        i += 1
    ret.append(l)
    return ret

def adj_tuple(rc, direction):
    ''' return (row, col) adjacent to (r0, c0) in the given direction '''
    (r0,c0) = rc
    if direction == 'N':
        return (r0 - 1, c0)
    if direction == 'S':
        return (r0 + 1, c0)
    if direction == 'E':
        return (r0, c0 + 1)
    if direction == 'W':
        return (r0, c0 - 1)
    raise ValueError('invalid direction %s' % str(direction))

class Board:
    def __init__(self, n, board, seperator=None):
        self.board = matrix(n, board, seperator)
        self.size = n
        i = 0
        for c in board:
            if c == ' ':
                break
            i += 1
        self.pos = (i // n, i % n)

    def __str__(self):
        return str(self.board)

    def __eq__(self, other):
        return self.board == other.board
    
    def __hash__(self):
        s = str(self.board)
        return hash(tuple(tuple(row) for row in self.board))
    
    def copy(self):
        board = []
        for lists in self.board:
            board += lists
        return Board(self.size, board)
    def valid_tuple(self, t):
        (r, c) = t
        return (0 <= r < self.size) and (0 <= c < self.size)

    def get_adj_tuple(self, rc, direction):
        tup = adj_tuple(rc, direction)

        return tup

    def get_directions(self):
        rc = self.pos
        dirs = []
        for d in ['N', 'S', 'E', 'W']:
            t = adj_tuple(rc, d)
            if self.valid_tuple(t):
                dirs.append(d)
                
        return dirs

    def goal_states(self):
        size = self.size * self.size
        lis = [str(x) for x in range(size)]
        lis[size-1] = ' '
        
        return Board(self.size, lis)
        
    def printl(self):
        for lists in self.board:
            for l in lists:
                print(l, end=', ')
            print()
            
    def move(self, direction):
        # To be completed
        i, j = self.pos
        # print(self.pos, i, j)
        if direction == 'N':
            if i - 1 >= 0:
                self.board[i][j] = self.board[i-1][j]
                self.board[i-1][j] = ' '
                i = i - 1
        elif direction == "S":
            if i + 1 < self.size:
                self.board[i][j] = self.board[i+1][j]
                self.board[i+1][j] = ' '
                i = i + 1
        elif direction == "W":
            if j - 1 >= 0:
                self.board[i][j] = self.board[i][j-1]
                self.board[i][j-1] = ' '
                j = j - 1
        elif direction == "E":
            if j + 1 < self.size:
                self.board[i][j] = self.board[i][j+1]
                self.board[i][j+1] = ' '
                j = j + 1
        else:
            raise NotImplementedError
        self.pos = i, j


class RandomBoard(Board):
    def __init__(self, n=3):
        size = n * n
        lis = [str(x) for x in range(n*n)]
        lis[size-1] = ' '
        
        random.shuffle(lis)
        Board.__init__(self, n, lis)

if __name__ == '__main__':
    r = RandomBoard(3)
    print(r)
    # r.printl()
    # r.move('N')
    
    # r.printl()
    # r.move('S')

    # r.printl()
    # r.move('E')

    # r.printl()
    # r.move('W')

    # r.printl()
    # r.move('S')

    # r.printl()
    # r.move('W')
