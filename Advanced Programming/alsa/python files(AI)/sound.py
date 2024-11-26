from time import sleep
import pyttsx3
file1 = open('sound.txt', 'r')
Lines = file1.readlines()
st = ''
text = ""
for i in Lines:
    i+=st
    
file_product = open('D:/ALI/build-MENU_-Desktop_Qt_6_2_4_MinGW_64_bit-Debug/prudoct.txt', 'r')
Lines2 = file_product.readlines()
for j in Lines2:
    l = j.split(',')
    if(l[-2] == st):
        break
flag = 0    
if(l[-1] == 'l\n'):
    for t in l:
        if flag == 11:
            break
        sound = pyttsx3.init()
        sound.setProperty('rate', 110)
        if flag == 0:
            sound.say("buyer is") 
        elif flag == 1:
            sound.say("and product is")    
        elif flag == 2:
            sound.say("and price of this laptop is")   
        elif flag == 3:
            sound.say("Number of this laptop is")   
        elif flag == 4:
            sound.say("also  color of this laptop is")
        elif flag == 5:
            sound.say("also discounts of this laptop is")
        elif flag == 6:
            sound.say("and Visit of this product is")  
        elif flag == 7:
            sound.say("also Number of goods purchased is")
        elif flag == 8:
            sound.say("and ram of laptop is")
        elif flag == 9:
            sound.say("and Laptop memory is")   
        else:
            sound.say("The rest of the description is")
        sound.say(t)
        sound.runAndWait();     
        sleep(0.5)
        flag+=1
flag = 0
if (l[-1] == 'p\n'):
      for t in l:
        if flag == 11:
            break
        sound = pyttsx3.init()
        sound.setProperty('rate', 110)
        if flag == 0:
            sound.say("buyer is") 
        elif flag == 1:
            sound.say("and product is")    
        elif flag == 2:
            sound.say("and price of this phone is")   
        elif flag == 3:
            sound.say("Number of this phone is")   
        elif flag == 4:
            sound.say("also color of this phone is")
        elif flag == 5:
            sound.say("also discounts of this phone is")
        elif flag == 6:
            sound.say("and Visit of this phone is")  
        elif flag == 7:
            sound.say("also Number of goods purchased is")
        elif flag == 8:
            sound.say("and and Android phone is")
        elif flag == 9:
            sound.say("and phone memory is")   
        else:
            sound.say("The rest of the description is")
        sound.say(t)
        sound.runAndWait();     
        sleep(0.5)
        flag+=1
flag = 0
if(l[-1] == 'c\n'):
    for t in l:
        if flag == 11:
            break
        sound = pyttsx3.init()
        sound.setProperty('rate', 110)
        if flag == 0:
            sound.say("buyer is") 
        elif flag == 1:
            sound.say("and product is")    
        elif flag == 2:
            sound.say("and price of this dress is")   
        elif flag == 3:
            sound.say("Number of this dress is")   
        elif flag == 4:
            sound.say("also dresses color is")
        elif flag == 5:
            sound.say("also discounts of this dress is")
        elif flag == 6:
            sound.say("and Visit of this dress is")  
        elif flag == 7:
            sound.say("also Number of goods purchased is")
        elif flag == 8:
            sound.say("and  size of dress is")
        elif flag == 9:
            sound.say("and material of dress is")   
        else:
            sound.say("The rest of the description is")
        sound.say(t)
        sound.runAndWait();     
        sleep(0.5)
        flag+=1 
flag = 0
if(l[-1] == 'w\n'):
    for t in l:
        if flag == 11:
            break
        sound = pyttsx3.init()
        sound.setProperty('rate', 110)
        if flag == 0:
            sound.say("buyer is") 
        elif flag == 1:
            sound.say("and product is")    
        elif flag == 2:
            sound.say("and price of this Clock is")   
        elif flag == 3:
            sound.say("Number of this Clock is")   
        elif flag == 4:
            sound.say("also Clock color is")
        elif flag == 5:
            sound.say("also discounts of this Clock is")
        elif flag == 6:
            sound.say("and Visit of this Clock is")  
        elif flag == 7:
            sound.say("also Number of goods purchased is")
        elif flag == 8:
            sound.say("and type of Clock is")
        elif flag == 9:
            sound.say("and brand of Clock is")   
        else:
            sound.say("The rest of the description is")
        sound.say(t)
        sound.runAndWait();     
        sleep(0.5)
    
        flag+=1       
file3 = open('sound.txt', 'w')
file3.close()