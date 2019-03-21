
def reverse_slicing(s):
    return s[::-1]

a =[
[2, 2, 2, 2, 2, 2, 2, 2, 0, 0, 2, 2, 2, 2, 2, 2],
[2, 1, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 1, 1, 2],
[2, 1, 0, 1, 0, 0, 0, 1, 0, 0, 2, 0, 0, 0, 1, 2],
[2, 1, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 2],
[2, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 2],
[2, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2],
[1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2],
[1, 0, 1, 0, 0, 0, 0, 1, 0, 1, 1, 0, 0, 0, 0, 2],
[2, 0, 0, 0, 1, 0, 0, 0, 0, 1, 2, 0, 0, 0, 0, 2],
[2, 0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 0, 0, 0, 0, 2],
[2, 1, 1, 0, 0, 0, 0, 0, 0, 0, 2, 1, 1, 1, 1, 2],
[2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2]];


b = []
d = []

for i in range(len(a)):
    
    c = ["","","",""]
    
    for j in range(len(a[0])):
        t = ""
        
        #if (a[i][j] != 0):
        #    a[i][j] -= 3
        
        t = reverse_slicing(bin(a[i][j]).replace("0b",""))
        #print(t)
        
        while len(t)<2:
            t+="0"
        #print(" "+t)
            
        c[int(j/4)] += reverse_slicing(reverse_slicing(t))
        
    
        
    for j in range(4):
        c[j] = reverse_slicing(c[j])
    
    b.append(c.copy())
    print(c)


for i in range(len(b)):
    d.append([])
    for j in range(len(b[0])):
        #print("i"+str(i)+"j"+str(j))
        d[i].append(int(b[i][j],2))
    
        
print("")
print(str(d))#.replace("], ","],\n").replace("]],","]]\n,"))

f= open("matrix.txt","w+")
f.write(str(d).replace("], ","],\n").replace("]],","]]\n,").replace("[","{").replace("]","}"))
f.close()