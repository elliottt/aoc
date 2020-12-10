import collections
lines = sorted([0]+[*map(int,open("input.txt").readlines())])
lines.append(max(lines)+3)
count = collections.defaultdict(int)
for i in range(1,len(lines)): count[lines[i]-lines[i-1]]+=1
print(count[1]*count[3])
arrange = [1]+[0]*lines[-1]
for i in lines[1:]: arrange[i] = arrange[i-3] + arrange[i-2] + arrange[i-1]
print(arrange[-1])
