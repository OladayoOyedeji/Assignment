import sys
sys.path.append('../../')
from GLOBALS import ACTIONS
sys.path.append('../../brain')
from brain.SimpleReflexBrain import SimpleReflexBrain

class SimpleReflexVacuumCleanerRobotBrain(SimpleReflexBrain):
    def __init__(self):
        SimpleReflexBrain.__init__(self, actions=ACTIONS)

if __name__ == '__main__':
    brain = SimpleReflexVacuumCleanerRobotBrain()
    print(brain.run(None))
    print(brain.run(None))
    print(brain.run(None))
    print(brain.run(None))
