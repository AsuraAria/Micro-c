
def reverse_slicing(s):
    return s[::-1]

a =[
[250,250,250,250,250,250,250,250,250,250,250,250,250,250,250],
[250,250,250,250,250, 7, 7,250,250,250,250,250, 7, 7,250],
[250,250,250,250, 7, 9, 9, 7,250,250,250, 7, 9, 9, 7],
[250,250,250,250, 7, 9, 9, 9, 7,250, 7, 9, 9, 9, 7],
[250,250,250,250, 7, 9, 9, 9, 7, 7, 7, 9, 9, 9, 7],
[250,250,250,250, 7, 9, 7, 7, 9, 9, 9, 7, 7, 9, 7],
[250,250,250,250,250, 7, 9, 9, 9, 9, 9, 9, 9, 7,250],
[250,250,250,250,250, 7, 9, 9, 9, 9, 9, 9, 9, 7,250],
[250,250,250,250, 7, 9, 9, 9, 9, 9, 9, 9, 9, 9, 7],
[250,250,250,250, 7, 9, 9, 9, 9, 7, 9, 9, 9, 9, 7],
[250,250,250,250, 7, 9, 9, 9, 10, 7, 10, 9, 9, 9, 7],
[250,250,250,250,250, 7, 9, 10, 9, 10, 9, 10, 9, 7,250],
[250,250,250,250,250,250, 7, 7, 10, 7, 10, 7, 7,250,250],
[250,250,250,250,250,250,250,250, 7, 7,250,250,250,250,250],
[250,250,250,250,250,250,250, 7, 7,250,250,250,250,250,250]];


b = []
d = []

for i in range(len(a)):
    
    c = ["","","","",""]
    
    for j in range(len(a[0])):
        t = ""
        
        if (a[i][j] != 0):
            a[i][j] -= 3
        
        t = reverse_slicing(bin(a[i][j]).replace("0b",""))
        #print(t)
        
        while len(t)<2:
            t+="0"
        #print(" "+t)
            
        c[int(j/4)] += reverse_slicing(reverse_slicing(t))
        
    
        
    for j in range(5):
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