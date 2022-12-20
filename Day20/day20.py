from time import time

input_file = "Day20/day20_data.txt"

decryption_key = 811589153

def mix(file, n = 1):
    l = len(file)
    file_index = [i for i in range(l)]
    for _ in range(n):
        for i, v in enumerate(file):
            if v == 0: continue
            j = file_index.index(i)  # find element
            x = file_index.pop(j)  # remove element
            k = (j + v) % (l - 1)  # calculate new position
            file_index.insert(k, x)  # insert element in new position
    return [file[i] for i in file_index]

def grove_coords(file):
    l = len(file)
    return sum(file[i] for i in ((file.index(0)+m)%l for m in [1000, 2000, 3000]))

def main():

    start_time = time()

    with open(input_file, 'r') as f:
        file = list(map(int, (n.strip() for n in f.readlines())))

    print("Part 1: {}".format(grove_coords(mix(file))))

    file = [n*decryption_key for n in file]
    print("Part 2: {}".format(grove_coords(mix(file, 10))))

if __name__ == "__main__":
    main()