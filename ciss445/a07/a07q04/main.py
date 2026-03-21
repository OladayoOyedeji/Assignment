# Name: Oladayo Oyedeji
# File: main.py

import re

p = p = re.compile("1*(01*01*)*\\Z") # replace string with correct regex
s = input()
print(p.match(s))
