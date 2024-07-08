import queue

class Node:
    def __init__(self, state, path):
        self.state = state
        self.path = path
# hata mitavanest baraie func expand az list estefade kard va be oon append kard(chon to eslaid ostad yeidl neveshte manam hamin karo kardam) 
def Expand(values, x, y):
    s1, s2 = values

    if s1 < x:
        yield Node((x, s2), 'fill x')

    if s2 < y:
        yield Node((s1, y), 'fill y')

    if s1 > 0:
        yield Node((0, s2), 'empty x')

    if s2 > 0:
        yield Node((s1, 0), 'empty y')

    if s1 > 0 and s2 < y:
        res = min(s1, y - s2)
        yield Node((s1 - res, s2 + res), 'Move from x to y')

    if s2 > 0 and s1 < x:
        res = min(s2, x - s1)
        yield Node((s1 + res, s2 - res), 'Move from y to x')


def BFS(Start, target, x, y):

    nd = Node(Start,[])
    if nd.state == target:
        return ['without any movement'] , 1
    
    q = queue.Queue()
    Visit = set()
    Visit.add(nd.state)
    q.put(nd)

    visited_nodes = 1

    while (not q.empty()):
        node = q.get()
        for n in Expand(node.state , x , y):
            if n.state == target:
                visited_nodes += 1
                return node.path + [n.path], visited_nodes
            if n.state not in Visit:
                Visit.add(n.state)
                q.put(Node(n.state, node.path + [n.path]))
                visited_nodes += 1

    return None, visited_nodes

x = 10 ; y = 3 ; a = 5 ; b = 0
path, visited_nodes = BFS((0,0), (a, b), x, y)

print('X = ' , x , '  ,  ' , "Y = " , y)
print('A = ' , a , '  ,  ' , "B = " , b)
print('\n-------------------------\n')
print("Total visited nodes = ", visited_nodes)

if not path:
    print('There is no solution !!!!\n')
else:   
    for epoch , string in enumerate(path):
        print(epoch+1 , '.  ' , string)