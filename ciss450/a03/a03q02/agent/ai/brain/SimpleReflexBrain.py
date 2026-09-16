import random
from Brain import Brain

class SimpleReflexBrain(Brain):
    def __init__(self, actions=None):
        Brain.__init__(self)
        if actions == None: actions = []
        self.actions = actions

    def run(self, percept):
        if percept['room_status'] == 'Dirty':
            return 'Suck'
        elif percept['location'] == 'A':
            return 'Right'
        elif percept['location'] == 'B':
            return 'Left'
