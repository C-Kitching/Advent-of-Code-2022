import re, numpy

V = lambda *a: numpy.array(a)
k = lambda a: tuple(sum(a))

def parse(line):
    i,a,b,c,d,e,f = map(int, re.findall(r'\d+',line))  # read in only numbers

    # i is bludeprint numbers, remaining numbers are the material costs
    # return 5 arrays representing the costs of productions of each robot
    # type: geode, obsidean, clay, ore and no robot
    # (cost_to_produce_robot(geodes, obsidean, clay, ore), robot_produced(geode, obsidesn, clay, ore))
    return (i, (V(0,0,0,a), V(0,0,0,1)),
               (V(0,0,0,b), V(0,0,1,0)),    
               (V(0,0,d,c), V(0,1,0,0)),    
               (V(0,f,0,e), V(1,0,0,0)),    
               (V(0,0,0,0), V(0,0,0,0)))  


def run(blueprint, t):

    # initially we have 0 matieral and 1 ore robot
    # so can produce 1 ore
    todo = [(V(0,0,0,0), V(0,0,0,1))]

    # loop over all time
    for _ in range(t):

        todo_ = list()  # Queue for the next minute

        # explore all posiblities with current material
        for current_material, material_we_can_produce in todo:

            # look at all robot bluepritns for one we can afford
            for cost_of_robot, material_robot_produces in blueprint:
                
                # we can afford this robot
                if all(current_material >= cost_of_robot):  

                    # update amount of material we have and amount we can 
                    # produce with new robot we just made
                    todo_.append((
                        current_material+material_we_can_produce-cost_of_robot, 
                        material_we_can_produce+material_robot_produces))

        # Prune the search queue.
        todo = sorted(todo_, key=k)[-500:]

    # return the maximum amount geodes cracked
    return max(todo, key=k)[0][0]

part1, part2 = 0, 1
for i, *blueprint in map(parse, open('C:/Users/CKitc/OneDrive/Desktop/GitHub/Advent-of-Code-2022/Day19/day19_data.txt')):
    part1 += run(blueprint, 24) * i
    part2 *= run(blueprint, 32) if i<4 else 1

print(part1, part2)