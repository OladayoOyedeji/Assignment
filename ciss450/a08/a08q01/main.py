from draw_util import *

#==============================================================================
# User input
# You need not change anything in this section.
# The program prompts the user for
# N               : number of points
# seed            : seed for randomization
# M               : maximum number of iterations
# successor_method: method for generating successor states 
# method          : local search method (Hill climbing, etc.)
#==============================================================================
# 2022/10/4
shape = input("r-random points, c-circle, 2-2 circles, 3-2 separate circles: ")
shape = shape.strip()
if shape=='': shape = 'r'

N = input("N (number of points, default: 50): ")
if N.strip() == '':
    N = 50
else:
    N = int(N)
seed = input("seed (default 0): ")
if seed.strip() == '':
    seed = 0
else:
    seed = int(seed)
M = input("M (max iterations, default: 100): ")
if M.strip() == '':
    M = 100
else:
    M = int(M)

successor_method = input("successor generation method (p2-permute two, o2-opt2, default: p2): ")
if successor_method.strip() == '':
    successor_method = 'p2'
    
method = input("local search method (hc-hill climbing, shc-stochastic hc, fchc-first choice hc, rrhc-random restart hc, sa-simulated annealing, default: hc): ")
if method.strip() == '': method = 'hc'

random.seed(seed)

def randompoints(N):
    return [(random.randrange(X0+10, X1-10), random.randrange(Y0+10,Y1-10)) \
            for _ in range(N)]

#==============================================================================
# ***** Local search algorithms *****
#
# Modify the following to include your local search algorithms
#
# This is where you add your various local search functions
# A local search funtion has this prototype:
#
#     def localsearch(obj, points, **args):
#         ...
#         return ret
#
# where obj is the objective function (provided below) and points is the
# list of points/cities to visit. The function returns either a set of points
# if this sete of points has a better objective value the the input or it
# returns False to indicate the local search has terminated.
#
# To show you how things work, I have included the compiled bytecode
# for hillclimbing -- I'm not providing you the source code. You will need to
# write your own.
#==============================================================================
def obj(points):
    """ Objective function """
    length = 0.0
    for i in range(len(points)):
        p = points[i]
        q = points[(i + 1) % N]
        length += math.sqrt((p[0] - q[0])**2 + (p[1] - q[1])**2)
    return length

if successor_method == 'p2' and method == 'hc':
    from hillclimbing import hillclimbing as localsearch

elif successor_method == 'o2' and method == 'hc':
    from hillclimbing import hillclimbing as f
    def localsearch(obj, points):
        return f(obj, points, 'o2')
    
elif successor_method == 'p2' and method == 'fchc':
    from first_choice_hillclimbing import first_choice_hillclimbing as \
         localsearch
    
elif successor_method == 'o2' and method == 'fchc':
    from first_choice_hillclimbing import first_choice_hillclimbing as f
    def localsearch(obj, points):
        return f(obj, points,'o2')
    
elif successor_method == 'p2' and method == 'rrhc':
    from random_restart_hillclimbing import random_restart_hillclimbing as \
         localsearch

elif successor_method == 'o2' and method == 'rrhc':
    from random_restart_hillclimbing import random_restart_hillclimbing as localsearch
    localsearch.successor_method = 'o2'
    
elif successor_method == 'p2' and method == 'shc':
    from stochastic_hillclimbing import stochastic_hillclimbing as \
         localsearch

elif successor_method == 'o2' and method == 'shc':
    from stochastic_hillclimbing import stochastic_hillclimbing as f
    def localsearch(obj, points):
        return f(obj, points, 'o2')
    
elif successor_method == 'p2' and method == 'sa':
    from simulated_annealing import simulated_annealing as \
         localsearch

elif successor_method == 'o2' and method == 'sa':
    from simulated_annealing import simulated_annealing as f
    def localsearch(obj, points, t):
        return f(obj, points, 'o2', t=t)
    
# ADD OTHER LOCAL SEARCHES HERE


#==============================================================================
# Run simulation
# You need not change anything below.
#==============================================================================
# Compute points, a list of N random points 
if shape == 'r':
    points = randompoints(N)
elif shape == 'c':
    x0,y0 = (X0 + X1) / 2, (Y0 + Y1) / 2
    r = min(abs(X0 + 10 - x0), abs(X1 - 10 - x0), abs(Y0 + 10 - y0), abs(Y1 - 10 - y0)) 
    dt = 2 * math.pi / N
    points = [(int(x0 + r * math.cos(dt * i)), int(y0 + r * math.sin(dt * i))) for i in range(N)]
    random.shuffle(points)
    print("radius:", r, "circumference:", 2 * r * math.pi)
elif shape == '2':
    x0,y0 = (X0 + X1) / 2, (Y0 + Y1) / 2
    r = min(abs(X0 + 10 - x0), abs(X1 - 10 - x0), abs(Y0 + 10 - y0), abs(Y1 - 10 - y0)) 
    r0 = r / 2
    x1, y1 = x0 - r0 / 2, y0
    x2, y2 = x0 + r0 / 2, y0
    dt = 2 * math.pi / (N // 2)
    points0 = [(int(x1 + r * math.cos(dt * i)), int(y1 + r * math.sin(dt * i))) for i in range(N // 2)]
    dt = 2 * math.pi / (N - N // 2)
    points1 = [(int(x2 + r * math.cos(dt * i)), int(y2 + r * math.sin(dt * i))) for i in range(N - N // 2)]
    points = points0 + points1
    random.shuffle(points)
elif shape == '3':
    x0,y0 = (X0 + X1) / 2, (Y0 + Y1) / 2
    r = min(abs(X0 + 10 - x0), abs(X1 - 10 - x0), abs(Y0 + 10 - y0), abs(Y1 - 10 - y0)) 
    r0 = r * 1.25
    x1, y1 = x0 - r0 / 2, y0
    x2, y2 = x0 + r0 / 2, y0
    dt = 2 * math.pi / (N // 2)
    points0 = [(int(x1 + r0/2 * math.cos(dt * i)), int(y1 + r0/2 * math.sin(dt * i))) for i in range(N // 2)]
    dt = 2 * math.pi / (N - N // 2)
    points1 = [(int(x2 + r0/2 * math.cos(dt * i)), int(y2 + r0/2 * math.sin(dt * i))) for i in range(N - N // 2)]
    points = points0 + points1
    random.shuffle(points)
    print("radius:", r0/2, "2 * circumference:", 2 * r0 * math.pi)


initial_h = obj(points)
iteration = 0
total_time = 0
print("iteration %s: %s" % (iteration, obj(points)))

draw2(points=points, N=N, M=M, iteration=iteration,
      initial_h=initial_h, total_time=total_time, state='THINKING ...',
      obj=obj)
draw1(0, 0, points, obj)

oldpoints = points[:]
graph = []

while 1:
    
    for event in pygame.event.get():
        if event.type == pygame.QUIT:     
            sys.exit()

    iteration += 1
    if iteration > M:
        iteration = M
        if method == 'rrhc':
            points = localsearch.final(obj, points)
            graph.append((iteration, obj(points)))
            print("final %s: %s" % (iteration, obj(points)))
        break
    
    # Compute new path
    if method != 'sa':
        start = pygame.time.get_ticks()
        flag = localsearch(obj, points)
        end = pygame.time.get_ticks()
    else:
        start = pygame.time.get_ticks()
        flag = localsearch(obj, points, t=iteration)
        end = pygame.time.get_ticks()
    total_time += (end - start)
    if not isinstance(flag, bool):
        points = flag
        print("iteration %s: %s" % (iteration, obj(points)))

    # add data to graph
    graph.append((iteration, obj(points)))
    draw(points=points, graph=graph,
         N=N, M=M, iteration=iteration,
         initial_h=initial_h, total_time=total_time, state='THINKING',
         obj=obj, oldpoints=oldpoints)
    if isinstance(flag, bool): break

#==============================================================================
# At this point, animation is over.
#==============================================================================
surface.fill(BLACK)
draw(points=points, graph=graph,
     N=N, M=M, iteration=iteration,
     initial_h=initial_h, total_time=total_time, state='DONE',
     obj=obj, oldpoints=oldpoints)
print("close graphics window to halt ...", flush=True)
pause()
