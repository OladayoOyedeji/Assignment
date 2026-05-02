# Name: Oladayo Oyedeji
# File: main.py

import re

p = re.compile("-?(([0-9]*( *)x(\\^[0-9]+)?)|([0-9]+)) *(([+-]( *))+(([0-9]*x(\\^[0-9]+)?)|([0-9]+))( *))*\\Z")# replace string with correct regex
s = input(">>> ")
print(p.match(s))
while input != '\0':
    s = input(">>> ")
    print(p.match(s))
