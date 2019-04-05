
def reverse_slicing(s):
    return s[::-1]

a =[
[0, 0, 0, 0, 8, 0, 0, 0, 0, 0, 8, 0, 0, 0, 0],
[0, 0, 8, 8, 0, 0, 0, 0, 0, 0, 0, 8, 8, 0, 0],
[0, 8, 8, 8, 0, 0, 0, 0, 0, 0, 0, 8, 8, 8, 0],
[8, 8, 8, 8, 0, 6, 0, 0, 0, 6, 0, 8, 8, 8, 8],
[8, 8, 8, 8, 6, 6, 0, 0, 0, 6, 6, 8, 8, 8, 8],
[8, 8, 8, 8, 6, 6, 0, 0, 0, 6, 6, 8, 8, 8, 8],
[8, 8, 8, 0, 1, 1, 1, 1, 1, 1, 1, 0, 8, 8, 8],
[8, 8, 8, 1, 1, 6, 1, 1, 1, 6, 1, 1, 8, 8, 8],
[8, 8, 8, 1, 1, 6, 1, 1, 1, 6, 1, 1, 8, 8, 8],
[8, 8, 8, 1, 1, 6, 1, 1, 1, 6, 1, 1, 8, 8, 8],
[8, 8, 8, 0, 1, 1, 1, 6, 1, 1, 1, 0, 8, 8, 8],
[8, 8, 8, 0, 0, 1, 6, 1, 6, 1, 0, 0, 8, 8, 8],
[8, 8, 0, 0, 0, 0, 6, 0, 6, 0, 0, 0, 0, 8, 8],
[8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 8],
[0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0]
];


b = []
d = []

for i in range(len(a)):
    
    c = ["","","","","","","",""]
    
    for j in range(len(a[0])):
        t = ""
        
        #if (a[i][j] != 0):
        #    a[i][j] -= 3
        
        t = reverse_slicing(bin(a[i][j]).replace("0b",""))
        #print(t)
        
        while len(t)<4:
            t+="0"
        #print(" "+t)
            
        c[int(j/2)] += reverse_slicing(reverse_slicing(t))
        
    
        
    for j in range(8):
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