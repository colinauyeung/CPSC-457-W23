import random

mainstr = "{"

top = 200
for i in range(1,top+1):
    substr = "{{"
    substr = substr + str(random.randint(0,200)) + "," + str(random.randint(0,200)) + "},{" + str(random.randint(0,200)) + "," + str(random.randint(0,200)) + "}}"
    if(i != top):
        mainstr = mainstr + substr + ","
        if(i%5 ==0):
            mainstr = mainstr + "\n"
        

    else:
        mainstr = mainstr + substr

mainstr = mainstr + "}"
print(mainstr)
