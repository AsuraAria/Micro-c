import matplotlib.image as img

image = img.imread("Untitled fi i.png")

print(str(image))
print(str(image.size/image[0].size) + " " + str(image[0].size/3))

f= open("guru99.txt","a")

f.write("{")
for i in range(int(image.size/image[0].size)):
    f.write("{")
    #print(str(int(image[0].size/3-1))+" yger")
    for j in range(int(image[0].size/3)):
        #f.write(str(image[i][j][0])+str(image[i][j][1])+str(image[i][j][2])+",")
        #print(j)
        if (j == int(image[0].size/3)-1):#int(image[0].size/3-1)):
            if (image[i][j][0] <= 0.1):
                f.write("7")
            elif (image[i][j][0]<=0.35):
                f.write("13")
            elif (image[i][j][0] <=0.66):
                f.write("12")
            else:
                f.write("8")
        else:
            if (image[i][j][0] <= 0.1):
                f.write("7,")
            elif (image[i][j][0] <=0.35):
                f.write("13,")
            elif (image[i][j][0] <=0.66):
                f.write("12,")
            else:
                f.write("8,")
            
    f.write("},\n")
    #f.write("\n")
f.write("}\n")
f.close()