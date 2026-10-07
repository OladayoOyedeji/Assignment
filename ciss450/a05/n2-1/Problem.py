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
