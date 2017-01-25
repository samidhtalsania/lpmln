#script (python)
 
import gringo
import ipdb
import math
from sympy import *
# from profilehooks import profile

# @profile
def main(prg):
    mode = 0
    var = raw_input("Enter query...\n")
    if len(var) != 0:
        mode = 1
        var = var.split(",")


    def on_model(m):
        Node.modelCount = Node.modelCount + 1
        node = Node()
 
        for i,val in enumerate(m.atoms()):

            if val.name() in var:
                args = val.args()
                t = tuple(args)
                if Node.parentDict.has_key(val.name()):
                    literalDict = Node.parentDict[val.name()].getDict()
                    if literalDict.has_key(t):
                        literalDict[t].append(Node.modelCount)
                    else:
                        literalDict[t] = [Node.modelCount]
                else:
                    Node.parentDict[val.name()] = Query()
                    Node.parentDict[val.name()].getDict()[t] = [Node.modelCount]

            
            if val.name() == 'unsat':
               
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
    ipdb.set_trace()
    sym = symbols('a')
 
    normalizedExpr = 0
 
    maxValue = -1
    for key, value in Node.modelNodeMap.iteritems():
        normalizedExpr = normalizedExpr + exp(value.getAlpha()*sym + value.getSoft())
        maxValue = max(maxValue, -value.getAlpha())
    print '\n'
   
    maxExpr = exp(maxValue*sym)
 

    normalizedExpr = normalizedExpr*maxExpr
 
    # ipdb.set_trace()
    for key, value in Node.modelNodeMap.iteritems():
        expr = exp(value.getAlpha()*sym + value.getSoft())
        expr = expr*maxExpr
        expr = expr/normalizedExpr
        # if mode == 0:
        probability = float(limit(expr, sym, oo).evalf())
        if not probability == 0:
            print 'Probability of Answer %s : %s' % (key, probability)
        # else:
            Node.probDict[key] = probability
        else:
            Node.probDict[key] = 0
        

    print "\n"
    if mode == 1:
        for k, val in Node.parentDict.iteritems():
            for key, value in val.getDict().iteritems():
                lim = 0
                for model in value:
                    # if Node.calculatedLimitsDict.has_key(model):
                    #     lim = lim + Node.calculatedLimitsDict[model]
                    # else:
                    #     # l = float(limit(Node.probDict[model], sym, oo).evalf())
                    #     Node.calculatedLimitsDict[model] = l
                    #     lim = lim + l
                    lim += Node.probDict[model]
                if not lim == 0:
			
                    if len(key) == 1:
                    	print '%s(%s) %s' % (k, key[0], lim)
                    elif len(key) == 0:
                        print '%s %s' % (k, lim)

                    else:
                    	print '%s%s %s' % (k, key, lim)


    print '\n'
 
 
class Node(object):
    modelNodeMap = {}
    modelCount = 0
    literalDict = {}
    probDict = {}
    calculatedLimitsDict = {}
    parentDict = {}
 
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

class Query(object):

    def __init__(self):
        super(Query, self).__init__()
        self.literalDict = {}

    def getDict(self):
        return self.literalDict;


 
 
#end.
