
import re

with open("input.txt") as file:
    text = file.read()

    active_code = []
    do = 0
    while True:
        dont = text.find("don't()", do)
        if dont == -1:
            break
        active_code.append(text[do : dont])
        do = text.find("do()", dont)
        if dont == -1:
            break

    muls = []
    for code in active_code:
        muls.extend(re.findall("mul\([0-9]{1,3},[0-9]{1,3}\)", code))
        
    total = 0
    for mul in muls:
        first = int(mul[4 : mul.find(",")])
        print(first)

        second = int(mul[ mul.find(",") + 1 : mul.find(")")])
        print(second)

        total +=  first * second
    print(total)
