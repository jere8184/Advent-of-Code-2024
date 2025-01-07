
def look(word_search, x, line_direction, position_direction):
    count = 0
    for line, position in x:
        if (word_search[line + line_direction][position + position_direction] == "M" and word_search[line + line_direction*2][position + position_direction*2] == "A"
            and word_search[line + line_direction*3][position + position_direction*3] == "S"):
                count += 1
        else:
            continue
    return count


def x_mas(word_search, a, new_file):
    count = 0
    lines, positions = len(word_search), len(word_search[0])
    for line, position in a:
        if 0 <= line - 1 and line + 1 < lines and 0 <= position - 1 and position + 1 < positions and \
        (((word_search[line - 1][position - 1] == "M" and word_search[line + 1][position + 1] == "S") or 
        (word_search[line - 1][position - 1] == "S" and word_search[line + 1][position + 1] == "M")) and
        ((word_search[line - 1][position + 1] == "M" and word_search[line + 1][position - 1] == "S") or
        (word_search[line - 1][position + 1] == "S" and word_search[line + 1][position - 1] == "M"))):
            count += 1
            new_file.seek(line*(positions + line + 1) + position)
            new_file.write("A")
            new_file.seek((line- 1)*(positions + line + 1)  + position - 1)
            new_file.write(word_search[line - 1][position - 1])
            new_file.seek((line+1)*(positions + line + 1) + position + 1)
            new_file.write(word_search[line + 1][position + 1])
            new_file.seek((line-1)*(positions + line + 1) + position + 1)
            new_file.write(word_search[line - 1][position + 1])
            new_file.seek((line+1)*(positions + line + 1) + position - 1)
            new_file.write(word_search[line + 1][position - 1])
        else:
            continue
    return count



def part_1():
    with open("input.txt") as file:
        word_search = file.readlines()
        i = 0
        x = []
        for line in word_search:
            
            res = line.find("X")
            while res != -1:
                x.append([i, res])
                res = line.find("X", res + 1)
            i += 1

    total = 0
    total += look(word_search, x, 1, 0)
    total += look(word_search, x, -1, 0)
    total += look(word_search, x, 0, 1)
    total += look(word_search, x, 0, -1)
    total += look(word_search, x, 1, 1) 
    total += look(word_search, x, -1, 1)
    total += look(word_search, x, -1, -1)
    total += look(word_search, x, 1, -1)

    return total

def part_2():
    with open("input.txt") as file:
        new_file = open("output.txt", "w")
        word_search = file.readlines()

        for line in word_search:
            new_file.write(str("." * len(line)) + "\n")

        i = 0
        a = []
        for line in word_search:
            res = line.find("A")
            while res != -1:
                a.append([i, res])
                res = line.find("A", res + 1)

            i += 1

    total = 0
    total += x_mas(word_search, a, new_file)

    return total
    




print(part_2())