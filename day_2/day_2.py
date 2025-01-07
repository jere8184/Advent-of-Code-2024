import copy

with open("input.txt") as file:
    safe_count = 0
    for line in file.readlines():
        vals = line.split()
        permutations = []
        for i in range(len(vals)):
            temp = copy.deepcopy(vals)
            temp.pop(i)
            permutations.append(temp)


        for permuation in permutations:
            prev = 0
            first = True
            up = False
            down = False
            valid = True
            for val in permuation:
                if first:
                    prev = val
                    first = False
                    continue
                
                if int(val) > int(prev):
                    up = True 
                if int(val) < int(prev):
                    down = True

                diff = int(val) - int(prev)
                prev = val

                if up and down or diff == 0 or abs(diff) > 3:
                    valid = False
                    
            
            if valid:
                safe_count += 1
                print(vals, "safe")
                break


    print(safe_count)







