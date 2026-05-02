# Name: Oladayo Oyedeji
# File: main.py

N = NFA (alphabet=["0", "1"],
         states=["A", "B", "C", "D", "E"],
         start="A",
         accepts=["C", "D"],
         transitions=[("A", "0", "B"),
                      ("A", "1", "B"),
                      ("B", "", "C")])
