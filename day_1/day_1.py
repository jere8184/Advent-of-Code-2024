
total = 0
left = []
right =  []
with open("input.txt") as file:
    for line in file.readlines():
        first, second = line.split()
        left.append(int(first))
        right.append(int(second))



for l in left:
    count = 0
    for r in right:
        if r == l:
            count = count + 1
    total = total + (l * count)

print(total)
        