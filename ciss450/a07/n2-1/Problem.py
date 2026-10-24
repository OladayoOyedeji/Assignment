class Problem(object):

    def __init__(self,
                 initial_state):
        self.initial_state = initial_state
    
    def get_initial_state(self):
        return self.initial_state

    def goal_test(self, state):
        raise NotImplementedError
                 
    def actions(self, state):
        raise NotImplementedError

    def result(self, state, action):
        raise NotImplementedError

    def successors(self, state):
        raise NotImplementedError
    
    def cost(self, state, action):
        return 1

class N2_1Problem(Problem):
    def __init__(self,
                 board=None,
                 initial_state=None,
                 goal_states=None):
        Problem.__init__(self, initial_state)
        self.board = board
        self.goal_states = goal_states

    def goal_test(self, state):
        board1 = state.board
        board2 = self.goal_states.board
        return board1 == board2
                 
    def actions(self, state):
        return self.board.get_directions(state)

    def result(self, state, action):
        return self.board.get_adj_tuple(state, action)

    def successors(self, state):
        dirs = self.actions(state)
        return [(d, self.result(state, d)) for d in dirs]

# class DLSProblem(N2_1Problem):
#     def __init__(self,
#                  board=None,
#                  initial_state=None,
#                  goal_states=None,
#                  max_depth=None):
#         board = DLSBoard
#         N2_1Problem.__init__(self, board, initial_state, goal_states)
#         self.max_depth = max_depth
        
#     def __init__(self,
#                  p, depth):
#         N2_1Problem.__init__(self, p.board, p.initial_state, p.goal_states)
#         self.max_depth = depth
        
#     def actions(self, node):
#         state, depth = node
#         print("node1", node, "state1", state, "depth1", depth)
#         print("max_depth", self.max_depth)
#         if (depth > self.max_depth):
#             return []
#         else:
#             return self.board.get_directions(state)
    
