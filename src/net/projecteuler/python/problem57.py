from time import time

start = time()


num = [3, 7, 17, 41]
num_diff = [24]


for i in range(1, 1000):
    new_diff_val = sum(num_diff[0:(len(num_diff) - 1)]) + sum(num_diff[0:(len(num_diff))]) + 4 + 10 + 10 + 10
    num_diff.append(new_diff_val)
    num.append(num[(len(num) - 1)] + num_diff[(len(num_diff) - 1)])

den = [2, 5, 12, 29]
den_diff = [17]

for i in range(1, 1000):
    den_diff.append(sum(den_diff[0:(len(den_diff) - 1)]) + sum(den_diff[0:(len(den_diff))]) + 3 + 7 + 7 + 7)
    den.append(den[(len(den) - 1)] + den_diff[(len(den_diff) - 1)])

count = 0
for i in range(1, 1000):
    if len(str(num[i])) > len(str(den[i])):
        count = count + 1

end = time()
print(count)
print(end-start, 'seconds')

