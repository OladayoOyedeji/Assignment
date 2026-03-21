# Name: Oladayo Oyedeji
# File: main.py

M = DFA(alphabet=["0", "1"],
        states=["q0", "q1", "q2", "q3"],
        start="q0",
        accepts=["q1"],
        transitions=[("q0", "1", "q1"),
                     ("q1", "1", "q0"),
                     ("q1", "0", "q2"),
                     ("q2", "0", "q1"),
                     ("q2", "1", "q3"),
                     ("q3", "1", "q2"),
                     ("q3", "0", "q0"),
                     ("q0", "0", "q3")])
