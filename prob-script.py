#script (python)
 
import gringo
import ipdb
import math
from sympy import *
 
def main(prg):
    def on_model(m):
        Node.modelCount = Node.modelCount + 1
        node = Node()
 
        for i,val in enumerate(m.atoms()):

            if val.name() == 'unsat':
                # ipdb.set_trace()
                args = val.args()
 
                # Process soft Rules
                if True:
                    # Unsat for this atom was false
                    # calculate its weight
                    
                    if args[1].__str__() == 'a':
                        node.setAlpha()
                    else:
                        node.setSoft(args[1])

        Node.modelNodeMap[Node.modelCount] = node
       
    prg.ground([("base", [])])
    prg.solve(on_model = on_model)
 
    sym = symbols('a')
 
    normalizedExpr = 0
 
    maxValue = -1
    for key, value in Node.modelNodeMap.iteritems():
        normalizedExpr = normalizedExpr + exp(value.getAlpha()*sym + value.getSoft())
        maxValue = max(maxValue, -value.getAlpha())
    print '\n'
   
    maxExpr = exp(maxValue*sym)
 
    normalizedExpr = normalizedExpr*maxExpr
    for key, value in Node.modelNodeMap.iteritems():
        expr = exp(value.getAlpha()*sym + value.getSoft())
        expr = expr*maxExpr
        expr = expr/normalizedExpr
        probability = limit(expr, sym, oo)

        probValue = probability.evalf()
        if not probValue.is_zero:
            print 'Probability of model %s :  %s = %s' % (key, probability, probValue)

    print '\n'
 
 
class Node(object):
    modelNodeMap = {}
    modelCount = 0
 
    """docstring for Node"""
    def __init__(self):
        super(Node, self).__init__()
        self.alpha = 0
        self.soft = 0
 
    def setAlpha(self):
        self.alpha = self.alpha + 1
 
    def setSoft(self, softVal):
        self.soft = self.soft + softVal
   
    def getAlpha(self):
        return -self.alpha
 
    def getSoft(self):
        return -self.soft
 
 
#end.
