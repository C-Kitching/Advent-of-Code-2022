# Find the pairs of packets that are in the right order, then find the sum of their indices.

with open("Day13/day13_data.txt", "r") as f:
    input = f.read().splitlines()

# Given a packet, return a list of numbers and lists
def transform_packet(packet):
    integers = "0123456789"
    newlist = []

    # Presumably, the first element is an opening bracket, which we don't care about
    i = 1

    # Go until we reach the end of the packet
    while i < len(packet):

        # If this is an integer, then append it to the list. Integers may be multiple digits in length.
        if packet[i] in integers:
            j = i
            while packet[j] in integers:
                j += 1
            newlist.append(int(packet[i:j]))
            i = j

        # If this is an opening bracket, then it is the start of a a list, in which case
        # we need to find the closing bracket. Since lists can be nested, we can keep a tally
        # of opening and closing brackets; when the number of opening brackets equals the number
        # of closing brackets, we are at the end of list. 
        elif packet[i] == "[":
            layers = 0
            j = 0
            for j in range(i, len(packet)):
                if packet[j] == "[":
                    layers += 1
                elif packet[j] == "]":
                    layers -= 1

                # At this point, we have the indices of the sublist: i and j. We use recursion 
                # to transform the sublist and append it to the root list.
                if layers == 0:
                    sublist = transform_packet(packet[i:j+1])
                    newlist.append(sublist)
                    i += j - 1
                    break

        # Other elements, e.g., commas, are ignored
        else:
            i += 1

    return newlist

# Transform the input into a list, where each entry is a pair of packets.
# The packets themselves have correct typing (e.g., consisting of ints and lists).
def transform_input(input):
    packets = []

    for i in range(0, len(input), 3):
        pair1 = transform_packet(input[i])
        pair2 = transform_packet(input[i+1])
        packets.append([pair1, pair2])

    return packets

# Given 2 integers, return whether they are in the right order:
#   - If n1 is less than n2, return 1
#   - If n1 is greater than n1, return -1
#   - If equal, return 0
def compare_ints(n1, n2):
    if n1 < n2:
        return 1
    if n1 > n2:
        return -1
    return 0

# Compare the first value in both lists, then the second value,
# and so on. Call recursively as needed.
#   - If list1 runs out of items first, return 1
#   - If list2 runs out of items first, return -1
#   - Otherwise, return 0
def compare_lists(list1, list2):
    listlen = max(len(list1), len(list2))

    for index in range(listlen):

        # If left side runs out of items, return 1. If right side runs out of items, return -1.
        if index >= len(list1):
            return 1
        if index >= len(list2):
            return -1
        
        # Compare element types
        element1 = list1[index]
        element2 = list2[index]

        # Call the appropriate function based on the element types
        ret = 0
        if type(element1) == int and type(element2) == int:
            ret = compare_ints(element1, element2)
                
        elif type(element1) == list and type(element2) == list:
            ret = compare_lists(element1, element2)

        elif type(element1) == list and type(element2) == int:
            ret = compare_list_and_int(element1, element2, True)

        elif type(element1) == int and type(element2) == list:
            ret = compare_list_and_int(element2, element1, False)

        # Keep going if the return code is 0, otherwise stop
        if ret != 0:
            return ret

    # If we reach the end of the list, simply return 0
    return 0

# Compare a list and an integer by first converting the integer to a list,
# then calling compare_lists.
def compare_list_and_int(list1:list, n2:int, list_is_left:bool):
    list2 = [n2]
    
    # Call compare_lists, depending on which element was the original list.
    if list_is_left:
        return compare_lists(list1, list2)
    return compare_lists(list2, list1)

# Compare all packet pairs and sum the indices of the correctly ordered pairs. 
# Each pair is a list, so we simply call compare_lists on all pairs. A pair is
# correctly ordered if it returns 1.
def compare_packets(packets):
    result = 0
    index = 0
    for packet1, packet2 in packets:
        index += 1
        n = compare_lists(packet1, packet2)
        if n == 1:
            result += index
    return result
        
packets = transform_input(input)
result = compare_packets(packets)
print("Sum of indices: %d" % result)