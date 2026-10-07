DELAY = 20 # To slow down display
FONTSIZE = 24
WIDTH, HEIGHT = 580, 580 # 
SIZE = (WIDTH * 2, HEIGHT)
BLACK = (0,0,0)
WHITE = (255,255,255)
GRAY = (100, 100, 100)
MARGIN = 2
BORDER = 2

import sys, random, math, copy, time
import nQueensView

import pygame
pygame.init()

pygame.display.set_caption("CISS450: CSP - nqueens")
surface = pygame.display.set_mode(SIZE)

font = pygame.font.Font(None, FONTSIZE)
smallfont = pygame.font.Font(None, FONTSIZE // 2)

def drawtext(s, x, y, color=WHITE, fontsize=FONTSIZE, w=None, h=None):
    font = pygame.font.Font(None, fontsize)
    image = font.render(s, 1, color)
    rect = image.get_rect()
    if w!=None: # center
        offset = (w - rect.w)//2
        rect.x = x + offset
        rect.y = y + offset
    else:
        rect.x = x
        rect.y = y
    surface.blit(image, rect)

def draw_nqueens(x=0, y=0,
                 mat=None, width=FONTSIZE, height=FONTSIZE,
                 color={}):
    # Draw a 2D array
    x += MARGIN
    y += MARGIN
    
    rowsize = len(mat)
    colsize = len(mat[0])

    # 2022/10/08 -- added: don't fit to int now ... do it later
    width = (WIDTH - 2 * MARGIN)// rowsize 
    #height = HEIGHT // 2 // colsize # why // 2?
    height = (HEIGHT - 2 * MARGIN)// colsize # why // 2?
    _ = max(width, height)
    if rowsize * _ + 2 * MARGIN >= WIDTH: _ = (WIDTH - 2 * MARGIN) // rowsize
    width = height = _
    
    for i,x0 in enumerate(range(x, x + width * colsize + 1, width)):
            pygame.draw.line(surface, GRAY,
                             (x0, y), (x0, y + height * rowsize), 1)
    for i,y0 in enumerate(range(y, y + height * rowsize + 1, height)):
        pygame.draw.line(surface, GRAY,
                         (x, y0), (x + width * colsize, y0), 1)
        
    for i,x0 in enumerate(range(x, x + width * colsize + 1, width)):
        if i == 0 or i == colsize:
            pygame.draw.line(surface, WHITE,
                             (x0, y), (x0, y + height * rowsize), BORDER) # 2022/10/18 change width from 5 to BORDER
    for i,y0 in enumerate(range(y, y + height * rowsize + 1, height)):
        if i == 0 or i == colsize:
            pygame.draw.line(surface, WHITE,
                             (x, y0), (x + width * colsize, y0), BORDER) # 2022/10/18 change width from 5 to BORDER

    # 2022/10/18
    fontsize = width
    for r,row in enumerate(mat):
        x0 =  x
        for c,v in enumerate(row):
            drawtext(str(v), x0, y,
                     color=color.get((r,c), WHITE), fontsize=fontsize, w=width, h=height)
            x0 += width
        y += height
    return width

def lineplot(x=WIDTH,
             y=0,
             w=WIDTH,
             h=330,
             points=[],
             xscale=1.0, yscale=3.0,
             target=10):

    # For the drawing below, the (x,y) is the BOTTOM LEFT (not top right).
    x = x + MARGIN
    y = y + h - MARGIN
    w = w - 2 * MARGIN
    h = h - 2 * MARGIN
    
    ylimit = target # target size of assignment
    
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
    pygame.draw.rect(surface, WHITE, pygame.Rect(x,y-h,w+1,h+1), BORDER)


class nQueensGUIView(nQueensView.nQueensView):
    def __init__(self, csp):
        nQueensView.nQueensView.__init__(self, csp)
        self.n = csp.n # warning csp.n can change ... need to keep original n
    def run(self, csp, assignment):
        nQueensView.nQueensView.run(self, csp, assignment)
        n = self.n
        xs = [['' for i in range(n)] for j in range(n)]
        
        for k,v in assignment:
            # k is of the form 'q[column]' where column is 0..(n-1).
            c = int(k[1:])
            v = int(v)
            #print("v,c:", v,c)
            xs[v][c] = 'Q'
            #print(xs)
        surface.fill(BLACK)
        width = draw_nqueens(mat=xs)
        lineplot(x=WIDTH, y=0, h=400, points=self.lengths, target=csp.n)
        
        x, y = WIDTH + MARGIN, 400 + 4 * MARGIN
        if y < HEIGHT/2: y = HEIGHT/2
        drawtext("states examined: %s" % self.count, x, y)
        y += FONTSIZE
        drawtext("current number of assigned variables: %s (of %s)" % (len(assignment), n), x, y)
        y += FONTSIZE
        drawtext("wall clock time: %.4f seconds" % self.wall_clock_time, x, y)
        y += FONTSIZE
        drawtext("user time: %.4f seconds" % self.utime, x, y)
        y += FONTSIZE
        drawtext("system time: %.4f seconds" % self.stime, x, y)
        pygame.display.flip()
        if DELAY > 0: pygame.time.delay(DELAY)
        
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
