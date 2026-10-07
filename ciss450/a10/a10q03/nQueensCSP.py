from CSP import CSP

class nQueensCSP(CSP):
    
    def __init__(self,
                 n=None,
                 vars=None, dom=None, constraint=None):
        """
        construct vars, dom, constraints and then call parent class constructor
        """
        CSP.__init__(self,
                     vars=vars,
                     dom=dom,
                     constraint=constraint)
        

if __name__ == '__main__':
    print("Testing ...")
    csp = nQueensCSP(4)
    print(csp)
