import re

ints = lambda s: map(int, re.findall(r'-?\d+', s))
dist = lambda x,y,p,q: abs(x-p) + abs(y-q)
data = [(x, y, dist(x,y,p,q)) for x,y,p,q in map(ints, open('Day15/day15_data.txt'))]

A, B = 2_000_000, 4_000_000

print(max(x - abs(A-y) + d for x,y,d in data) 
    - min(x + abs(A-y) - d for x,y,d in data))

f = lambda x,y,d,p,q,r: ((p+q+r+x-y-d)//2, (p+q+r-x+y+d)//2+1)

for X, Y in [f(*a,*b) for a in data for b in data]:
    if 0<X<B and 0<Y<B and all(dist(X,Y,x,y)>d for x,y,d in data):
        print(B*X + Y)