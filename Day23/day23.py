from itertools import cycle
from collections import defaultdict

# read input and determine set of elf points
def read_input():
    with open (r'Day23\day23_data.txt') as f:
        return set((x,y) for y, l in enumerate(f.readlines()) 
            for x, c in enumerate(l) if c == '#')

# function to move elves in 1 round
def move_elves(elves, first_direction):

    proposals = defaultdict(list)
    start_facing = next(first_direction) # get the new direction

    # check all elves
    for elf in elves:

        # if no elves in any adjacent positions, do nothing
        if not any((elf[0] + looking[0], elf[1] + looking[1]) in elves for looking in omni_elf):
            continue

        # else check all 4 positions for a move
        for i in range(4):
            crowded = False
            for direction in directions[(start_facing + i) % 4]:
                if (elf[0] + direction[0], elf[1] + direction[1]) in elves:
                    crowded = True
                    break
            if not crowded:
                direction = directions[(start_facing + i) % 4][1]
                proposals[(elf[0] + direction[0], elf[1] + direction[1])].append(elf)
                break
    
    for proposal in proposals:
        if len(proposals[proposal]) == 1:
            elves.remove(proposals[proposal][0])
            elves.add(proposal)
    
    return len(proposals) == 0

# part 1 
def solve_part_1():
    elves = read_input()
    first_direction = cycle(range(4))  # directions cycle through N, S, W, E

    # perform 10 rounds of moving
    for _ in range(10):
        move_elves(elves, first_direction)
    
    # find the edges of the box
    min_x = min(elves, key=lambda x: x[0])[0]
    max_x = max(elves, key=lambda x: x[0])[0]
    min_y = min(elves, key=lambda x: x[1])[1]
    max_y = max(elves, key=lambda x: x[1])[1]
    
    return sum((x, y) not in elves for y in range(min_y, max_y + 1) 
        for x in range(min_x, max_x + 1))

def solve_part_2():
    elves = read_input()
    first_direction = cycle(range(4))

    round = 0
    while True:
        round += 1
        if move_elves(elves, first_direction):
            break
    
    return round

# list 8 possible directions
directions = [[(-1, -1), (0, -1), (1, -1)], 
              [(1, 1), (0, 1), (-1, 1)], 
              [(-1, 1), (-1, 0), (-1, -1)], 
              [(1, -1), (1, 0), (1, 1)]]

omni_elf = [(-1,-1), (0,-1), (1,-1), (1,1), (0,1), (-1,1), (-1,0), (1,0)]

print ("Part 1:", solve_part_1())
print ("Part 2:", solve_part_2())