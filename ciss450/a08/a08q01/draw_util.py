from config import *
import pygame, sys, random, math
pygame.init()

pygame.display.set_caption("TSP")
surface = pygame.display.set_mode(SIZE)

X0 = 0
Y0 = 0
X1 = WIDTH
Y1 = HEIGHT // 2

BLACK = (0,0,0)
WHITE = (255,255,255)

font = pygame.font.Font(None, FONTSIZE)
smallfont = pygame.font.Font(None, FONTSIZE // 2)

def drawtext(s, x, y):
    image = font.render(s, 1, WHITE)
    rect = image.get_rect()
    rect.x = x
    rect.y = y
    surface.blit(image, rect)

def drawsmalltext(s, x, y):
    image = smallfont.render(s, 1, WHITE)
    rect = image.get_rect()
    rect.x = x
    rect.y = y
    surface.blit(image, rect)
    
def draw2(x0=X1, y0=0,
          points=None, N=None, M=None, iteration=None,
          initial_h=None, total_time=None, state=None,
          obj=None):
    length = obj(points)
    # draw path
    tpoints = [(x0+x, y0+y) for x,y in points]
    pygame.draw.polygon(surface, WHITE, tpoints, 1)
    # draw points
    for i,p in enumerate(points):
        pygame.draw.circle(surface, WHITE, (p[0]+x0, p[1]+y0), 5)
        
    # print text
    x = 10; y = Y1 + 10
    drawtext("N: %s" % N, x, y); y += FONTSIZE
    drawtext("M: %s" % M, x, y); y += FONTSIZE
    drawtext("iteration: %s" % iteration, x, y); y += FONTSIZE
    drawtext("total time: %.4f secs" % (total_time/1000.0), x, y); y += FONTSIZE
    drawtext("initial length: %.4f" % initial_h, x, y); y += FONTSIZE
    drawtext("current length: %.4f" % length, x, y); y += FONTSIZE
    drawtext(("percentage improvement: %.2f" % ((initial_h - length) * 100.0 / initial_h)) + '%', x, y); y += FONTSIZE
    drawtext(state, x, y); y += FONTSIZE

def draw1(x0, y0, points,obj):
    length = obj(points)
    # draw path
    tpoints = [(x0+x, y0+y) for x,y in points]
    pygame.draw.polygon(surface, WHITE, tpoints, 1)
    # draw points
    for i,p in enumerate(points):
        pygame.draw.circle(surface, WHITE, (p[0]+x0, p[1]+y0), 5)
        
def draw3(x0=X1, y0=Y1, w0=WIDTH, h0=Y1,
          graph=None,
          minx=0, maxx=100, miny=0, maxy=10000):
    """
    Draw a 2d graph plot
              x0
          +----------------------+    Draw a 2d plot of points in graph
          |                      |    in the window with top left corner
          |                      |    of (x0,y0), width w0, and height
          |               w0     |    h0.
        y0|          +---------+ |
          |          |         | |
          |       h0 |         | |
          |          +---------+ |
          |                      |
          +----------------------+
    """
    maxx0  = max(x for x,y in graph)
    if maxx0 > maxx: maxx = maxx0
    maxy0  = max(y for x,y in graph)
    if maxy0 > maxy: maxy = maxy0
    
    margin = 8
    x0 = x0 + margin
    y0 = y0 + margin
    w0 = w0 - 2 * margin
    h0 = h0 - 2 * margin

    pygame.draw.rect(surface, WHITE, [x0-4, y0-4, w0+1+8, h0+1+8], 1)

    if len(graph) > 1:
        dx = float(maxx - minx)
        dy = float(maxy - miny)
        tgraph= [(x0+(x-minx)/dx*w0, y0+h0-(y-miny)/dy*h0) \
                 for (x, y) in graph]
        pygame.draw.lines(surface, WHITE, False, tgraph, 2)


def draw(points=None, graph=None, N=None, M=None, iteration=None,
         initial_h=None, total_time=None, state=None, obj=None, oldpoints=None):
    surface.fill(BLACK)
    draw2(points=points, N=N, M=M, iteration=iteration,
          initial_h=initial_h, total_time=total_time, state=state, obj=obj)
    draw1(0, 0, oldpoints, obj=obj)
    draw3(graph=graph)
    pygame.display.flip()
    pygame.time.delay(DELAY)

def pause():
    while 1:    
        for event in pygame.event.get():
            if event.type == pygame.QUIT:     
                sys.exit()
        pygame.time.delay(100)
