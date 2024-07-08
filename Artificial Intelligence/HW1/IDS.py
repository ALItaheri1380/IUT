from math import inf

class Node:
    def __init__(self, state, path, depth):
        self.state = state
        self.path = path
        self.depth = depth

# hata mitavanest baraie func expand az list estefade kard va be oon append kard(chon to eslaid ostad yeidl neveshte manam hamin karo kardam) 
def Expand(values, x, y):
    s1, s2 = values
    
    if s1 < x:
        yield Node((x, s2), 'fill x', inf)
    
    if s2 < y:
        yield Node((s1, y), 'fill y', inf)
    
    if s1 > 0:
        yield Node((0, s2), 'empty x', inf)
    
    if s2 > 0:
        yield Node((s1, 0), 'empty y', inf)
    
    if s1 > 0 and s2 < y:
        res = min(s1, y - s2)
        yield Node((s1 - res, s2 + res), 'Move from x to y', inf)
    
    if s2 > 0 and s1 < x:
        res = min(s2, x - s1)
        yield Node((s1 + res, s2 - res), 'Move from y to x', inf)

def IDS(start, target, x, y):
    depth = 0
    visited_nodes = 0

    while True:
        path, nodes = DLS(start, target, x, y, depth)
        visited_nodes += nodes
        if path != "cutoff":
            return visited_nodes, path
        depth+=1

def DLS(node, target, x, y, depth):
    stack = [node]
    visited_nodes = 0
    Visit = set()
    Visit.add(node.state)
    result = "failure"

    while stack:
        node = stack.pop()
        visited_nodes += 1
        if node.state == target:
            if node.depth == 0:
                return ['without any movement'], visited_nodes
            return node.path, visited_nodes
        if node.depth == depth:
            result = "cutoff"
        else:
            for n in Expand(node.state, x, y):
                if n.state not in Visit:
                    Visit.add(n.state)
                    n.depth = node.depth + 1
                    n.path = node.path + [n.path]
                    stack.append(n)

    return result, visited_nodes

x = 10 ; y = 3 ; a = 5 ; b = 0
visited_nodes, path = IDS(Node((0,0), [], 0), (a, b), x, y)

print('X = ' , x , '  ,  ' , "Y = " , y)
print('A = ' , a , '  ,  ' , "B = " , b)
print('\n-------------------------\n')
print("Total visited nodes =", visited_nodes)

if path == "failure":
    print(path)
else:
    for epoch, string in enumerate(path):
        print(epoch+1, '.  ', string)
