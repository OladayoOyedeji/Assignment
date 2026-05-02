import math

p = [(0.0, 0.0), (3.1, -1.0), (4.2, 2.0), (2.1, 3.1), (-1.0, 1.1)]

def dist(pi, pj):
    # print("dist", math.sqrt((pi[0]-pj[0])**2 + (pi[1]-pj[1])**2))
    return math.sqrt((pi[0]-pj[0])**2 + (pi[1]-pj[1])**2)

# cost = [c(0,1), cost[0]+c(1,2), cost[1]+c(2, 3)]
#           0            1               2

cost = [0.0]
sum_ = 0
for i in range(len(p)-1):
    dist_ = dist(p[i], p[i+1]) + sum_
    cost.append(dist_)
    sum_ = dist_
print(cost)

for i in range(len(p)):
    for j in range(i+1, len(p)):
        print(c(i,j), cost[j]-cost[i])

def c(i, j):
    # cost = 0
    # for k in range(i,j):
    #     cost += dist(p[k], p[k+1])
    # return cost
    return cost[j]-cost[i]

table = []

def C(i, j):
    if (j <= i + 1):
        return 0
    min_ = math.inf
    for k in range(i+1, j):
        print(i, k, j)
        x = C(i, k) + C(k,j) + c(i,k) + c(k,j)
        # print(x)
        if x < min_:
            min_ = x
    return min_

# print(C(0, len(p)-1))
