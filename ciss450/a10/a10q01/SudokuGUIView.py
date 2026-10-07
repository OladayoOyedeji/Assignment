DELAY = 0 # To slow down display
FONTSIZE = 32
WIDTH, HEIGHT = 400, 600
SIZE = (WIDTH * 2, HEIGHT)
BLACK = (0,0,0)
WHITE = (255,255,255)
GRAY = (100, 100, 100)

import sys, random, math, copy, time
import SudokuView

import pygame
pygame.init()

pygame.display.set_caption("CISS450: CSP - sudoku")
surface = pygame.display.set_mode(SIZE)

font = pygame.font.Font(None, FONTSIZE)
smallfont = pygame.font.Font(None, FONTSIZE // 2)

def drawtext(s, x, y, color=WHITE):
    image = font.render(s, 1, color)
    rect = image.get_rect()
    rect.x = x
    rect.y = y
    surface.blit(image, rect)

def draw_sudoku(x=10, y=10, mat=None, width=FONTSIZE, height=FONTSIZE,
                color={}):
    
    rowsize = len(mat)
    colsize = len(mat[0])

    for i,x0 in enumerate(range(x, x + width * colsize + 1, width)):
        if not(i % 3 == 0 or i == colsize):
            pygame.draw.line(surface, GRAY,
                             (x0, y), (x0, y + height * rowsize), 1)
    for i,y0 in enumerate(range(y, y + height * rowsize + 1, height)):
        if not(i % 3 == 0 or i == colsize):
            pygame.draw.line(surface, GRAY,
                             (x, y0), (x + width * colsize, y0), 1)
        
    for i,x0 in enumerate(range(x, x + width * colsize + 1, width)):
        if i % 3 == 0 or i == colsize:
            pygame.draw.line(surface, WHITE,
                             (x0, y), (x0, y + height * rowsize), 5)
    for i,y0 in enumerate(range(y, y + height * rowsize + 1, height)):
        if i % 3 == 0 or i == colsize:
            pygame.draw.line(surface, WHITE,
                             (x, y0), (x + width * colsize, y0), 5)

    xoffset = width - FONTSIZE / 1.5
    yoffset = height - FONTSIZE / 1.25

    for r,row in enumerate(mat):
        x0 =  x
        for c,v in enumerate(row):
            drawtext(str(v), x0 + xoffset, y + yoffset,
                     color=color.get((r,c), WHITE))
            x0 += width
        y += height


def lineplot(x=WIDTH+10, y=300, w=2*WIDTH-WIDTH-20, h=290, points=[],
             xscale=1.0, yscale=3.0):
    ylimit = 81
    
    points = [(int(x0 * xscale), int(y0 * yscale)) for x0,y0 in points]
    ylimit = int(ylimit * yscale)

    #==========================================================================
    # scale only when max is outside
    #==========================================================================
    maxx = max(x for x,_ in points)
    maxy = max(y for _,y in points)
    xscale = 1.0
    if maxx > w: xscale = float(w)/maxx
    yscale = 1.0
    if maxy > h: yscale = float(h)/maxy
    points = [(int(x0 * xscale), int(y0 * yscale)) for x0,y0 in points]
    ylimit = int(ylimit * yscale)
    #==========================================================================
    # transform
    #==========================================================================
    points = [(x+x0,y-y0) for x0,y0 in points]
    ylimit = y - ylimit
    #==========================================================================
    # draw
    #==========================================================================
    if len(points) < 0: return
    if len(points) == 1:
        pygame.draw.aalines(surface, WHITE, 0, points + points, 1)
    else:
        pygame.draw.aalines(surface, WHITE, 0, points, 1)
    pygame.draw.aalines(surface, (255,0,0), 0, [(x,ylimit),(x+w,ylimit)], 1)
    pygame.draw.rect(surface, WHITE, pygame.Rect(x,y-h,w+1,h+1), 1)


class SudokuGUIView(SudokuView.SudokuView):
    def __init__(self, csp):
        SudokuView.SudokuView.__init__(self, csp)

    def run(self, csp, assignment):
        SudokuView.SudokuView.run(self, csp, assignment)
        
        xs = [['' for i in range(9)] for j in range(9)]
        for k,v in assignment:
            r,c = k
            r = ord(r) - ord('A')
            c = ord(c) - ord('1')
            xs[r][c] = v
        surface.fill(BLACK)
        color = {}
        for i,x in enumerate(assignment):
            k,v = x
            r,c = k
            r = ord(r) - ord('A')
            c = ord(c) - ord('1')
            if i == len(assignment) - 1:
                if len(assignment) < 81:
                    color[(r,c)] = (0,255,0)
                else:
                    color[(r,c)] = WHITE
            else:
                if (r,c) in self.given_rc:
                    color[(r,c)] = (255,0,0)
                else:
                    color[(r,c)] = WHITE
        draw_sudoku(mat=xs, color=color)
        lineplot(points=self.lengths)
        drawtext("states examined: %s" % self.count, 10, 320)
        drawtext("current number of assigned variables: %s (of 81)" % \
                 len(assignment), 10, 342)
        drawtext("wall clock time: %.4f seconds" % self.wall_clock_time, 10, 364)
        drawtext("user time: %.4f seconds" % self.utime, 10, 386)
        drawtext("system time: %.4f seconds" % self.stime, 10, 408)
        pygame.display.flip()
        
        for event in pygame.event.get():
                if event.type == pygame.QUIT:
                    sys.exit()
                    
    def wait(self):
        stop = False
        while 1:
            for event in pygame.event.get():
                if event.type == pygame.QUIT:
                    stop = True
                    break
            if stop: break
            if DELAY > 0: pygame.time.delay(DELAY)

    def save(self, filename=None):
        if filename == None:
            import random; random.seed()
            filename = random.randrange(10000000,1000000000)
            filename = str(filename)
        pygame.image.save(surface, '%s.jpg' % filename)
        
if __name__ == '__main__':
    pass
