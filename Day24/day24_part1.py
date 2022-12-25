from collections import defaultdict
import heapq

# function to read input
def read_input():

    # translations that each blizzard makes
    dirdict = {'<': (-1, 0), '>': (1, 0), '^': (0, -1), 'v': (0, 1)}

    # read data from file
    with open(r"Day24\day24_data.txt") as f:
        lines = f.read().splitlines()
        board_height = len(lines) - 2
        board_width = len(lines[1]) - 2
        elf_start = (lines[0].index(".") - 1, -1)
        elf_end = (lines[-1].index(".") - 1, board_height)

        # position of blizard and translation its about to undergo
        blizzards = [((x-1, y-1), dirdict[lines[y][x]]) \
            for y in range(1, board_height+1) for x in range(1, board_width+1) if lines[y][x] in dirdict]

    return elf_start, elf_end, blizzards, board_width, board_height

# function to evolve blizzard configuration
def move_blizzards(blizzards, time):

    # check if we have already found blizzard config
    if time in blizzard_dict: return blizzard_dict[time]

    # update blizzard configuration
    new_blizzards = defaultdict(list)
    for blizzard in blizzards:
        x, y = (blizzard[0][0] + blizzard[1][0] * time) % board_width, \
            (blizzard[0][1] + blizzard[1][1] * time) % board_height
        new_blizzards[(x, y)].append(blizzard)

    # store configuration at that time
    blizzard_dict[time] = new_blizzards

    return new_blizzards

# calculate possible moves we can made from our position given the blizzards
def calc_moves(pos, blizzards, time):

    delta_force = [(0, 0), (1, 0), (-1, 0), (0, 1), (0, -1)] # possible moves 

    new_blizzard_pos = move_blizzards(blizzards, time+1) # move blizzards

    # test which moves arent blizzard positions
    moves = []
    for delta in delta_force:
        x, y = pos[0] + delta[0], pos[1] + delta[1]
        if (x, y) not in new_blizzard_pos and ((x, y) == elf_end or (x, y) == elf_start or (x >= 0 and x < board_width and y >= 0 and y < board_height)):
            moves.append((x, y))
    
    return moves

# function to find time to navigate blizzard with bfs 
def find_path_time(blizzards, start_pos, end_pos, time):

    heap = []
    heapq.heappush(heap, (0, start_pos, time)) # push inital pose and time
    visited = set()

    # bfs
    while heap:
        _, pos, time = heapq.heappop(heap) # get current pos
        if pos == end_pos: return time # if finished then return time

        # else if we haven't visited that position
        if (pos, time) not in visited:
            visited.add((pos, time)) # record new position

            # calc all possible moves 
            for move in calc_moves(pos, blizzards, time):
                heapq.heappush(heap, (abs(pos[0] - end_pos[0]) + abs(pos[1] - end_pos[1]) + time, move, time+1))


# get data
elf_start, elf_end, blizzards, board_width, board_height = read_input()
blizzard_dict = {}

# move from start to end
part1_time = find_path_time(blizzards, elf_start, elf_end, 0)
print ("Part 1:", part1_time)

# start at end, back to start, then back to end
print ("Part 2:", find_path_time(blizzards, elf_start, elf_end, 
        find_path_time(blizzards, elf_end, elf_start, part1_time)))
