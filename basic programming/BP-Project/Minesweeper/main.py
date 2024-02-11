import random
def Production_Neighbors(n, k):
    if n==15:
       mylist=[0]*15 
       www = [[0 for row in range(n)] for column in range(20)]
    else:
        mylist=[0]*n
        www = [[0 for row in range(n)] for column in range(n)]   
    num=0   
    if n==15:
        z=20
    else:
        z=n    
    while num <(k):
        x = random.randint(0,n-1)
        y = random.randint(0,z-1)
        flag=0
        if www[y][x] == '\u273a':
            continue
        mylist[x]+=1
        for t in mylist:
            if t==4:
                flag=1
                mylist[x]-=1
        if flag==1:
            continue
        www[y][x] = '\u273a'
        if (x >=0 and x <= n-2) and (y >= 0 and y <= z-1):
            if www[y][x+1] != '\u273a':
                www[y][x+1] += 1 
        if (x >=1 and x <= n-1) and (y >= 0 and y <= z-1):
            if www[y][x-1] != '\u273a':
                www[y][x-1] += 1 
        if (x >= 1 and x <= n-1) and (y >= 1 and y <= z-1):
            if www[y-1][x-1] != '\u273a':
                www[y-1][x-1] += 1 
        if (x >= 0 and x <= n-2) and (y >= 1 and y <= z-1):
            if www[y-1][x+1] != '\u273a':
                www[y-1][x+1] += 1 
        if (x >= 0 and x <= n-1) and (y >= 1 and y <= z-1):
            if www[y-1][x] != '\u273a':
                www[y-1][x] += 1 
        if (x >=0 and x <= n-2) and (y >= 0 and y <= z-2):
            if www[y+1][x+1] != '\u273a':
                www[y+1][x+1] += 1 
        if (x >= 1 and x <= n-1) and (y >= 0 and y <= z-2):
            if www[y+1][x-1] != '\u273a':
                www[y+1][x-1] += 1 
        if (x >= 0 and x <= n-1) and (y >= 0 and y <= z-2):
            if www[y+1][x] != '\u273a':
                www[y+1][x] += 1 
        num+=1        
    return www
def first_table(n):
    if n==15:
       arr = [['■' for row in range(n)] for column in range(20)]
    else:
        arr = [['■' for row in range(n)] for column in range(n)] 
    return arr
def final_table(map):
    for row in map:
        print(" ".join(str(cell) for cell in row))
        print("")
def CheckWon(map):
    for row in map:
        for cell in row:
            if cell == '■':
                return False
    return True
def CheckContinueGame(score):
    print("Your score: ", score)
    bazidobare= input("Do you want to try again? (Rematch/Exit) :")
    if bazidobare== 'Exit':
        return False
    return True
def Game():
    global tlat
    global win
    global profile_
    global lose
    GameStatus = True
    while GameStatus:
        Table_size  = input("pls Select Table size\u2694 \u2694 \u2694 \u2694 \u2694 \u2694???(9*9,12*12,15*20):")
        if Table_size== '9*9':
            n = 9
            k = 10
        elif Table_size == '12*12':
            n = 12
            k = 20
        elif Table_size=='15*20':
            n = 15
            k = 40
        else:
            print('Wrong input....!!!!!')
            continue
        minesweeper_map =Production_Neighbors(n, k)        
        player_map = first_table(n)
        score = 0
        flag=0
        if Table_size== '9*9':
            sw=81
        elif Table_size == '12*12':
            sw=144
        elif Table_size=='15*20':
            sw=300             
        import time
        now = time.time()
        future = now + (sw*5)
        while time.time() < future: 
            if CheckWon(player_map) == False:
                print("Enter the coordinates :)")
                x = input("Coordinates X : ")
                y = input("Coordinates Y  : ")
                if Table_size== '9*9':
                  if x in ['1','2','3','4','5','6','7','8','9'] and y in ['1','2','3','4','5','6','7','8','9']:
                    x = int(x) -1
                    y = int(y) - 1 
                  else:
                      continue                  
                elif Table_size == '12*12':
                    if  x in ['1','2','3','4','5','6','7','8','9','10','11','12'] and y in ['1','2','3','4','5','6','7','8','9','10','11','12']:
                          x = int(x) -1
                          y = int(y) - 1 
                    else:
                        continue
                elif Table_size=='15*20':
                    if x in ['1','2','3','4','5','6','7','8','9','10','11','12','13','14','15'] and y in ['1','2','3','4','5','6','7','8','9','10','11','12','13','14','15','16','17','18','19','20']:
                         x = int(x) -1
                         y = int(y) - 1 
                    else:
                        continue                              
                else:
                    print('Wrong input....!!!!!')
                    continue
                parcham=input('Do you want a flag?if yes inter yes :')                
                if k>0:
                    if parcham=='yes':
                        flag+=1
                        if flag==1:
                           e=minesweeper_map[y][x]
                        k-=1
                        print('Number of flags remaining:',k) 
                        player_map[y][x]="\u2690"
                        if minesweeper_map[y][x]=='\u273a':
                            minesweeper_map[y][x]="\u2690"
                if (minesweeper_map[y][x] == '\u273a'):
                    print("Game Over!")
                    p='''                   
                                ,d8888888888b,_
                            _,d889'        8888b,
                        _,d8888'          8888888b,
                    _,d8889'           888888888888b,_
                _,d8889'             888888889'688888, /b
            _,d8889'               88888889'     `6888d 6,_
         ,d88886'              _d888889'           ,8d  b888b,  
       ,d889'888,             d8889'               8d   9888888 
     ,d889'   `88,          ,d88'                 d8    `,88aa88 
    d889'      `88,        ,88'                 `8b     )88a88'
   d88'         `88       ,88    YOU LOSE!!!!  88 `8b,_ d888888
  d89            88,      88                  d888b  `88`_  8888
  88             88b      88                 d888888 8: (6`) 88')
  88             8888b,   88                d888aaa8888, `   'Y'
  88b          ,888888888888                 `d88aa `88888b ,d8
  `88b       ,88886 `88888888                 d88a  d8a88` `8/
   `q8b    ,88'`888  `888'"`88          d8b  d8888,` 88/ 9)_6
     88  ,88"   `88  88p    `88        d88888888888bd8( Z/
     88b 8p      88 68'      `88      88888888' `688889`
     `88 8        `8 8,       `88    888 `8888,   `qp'
       8 8,        `q 8b       `88  88"    `888b
       q8 8b        "888        `8888'
        "888                     `q88b
                                  "888'''
                    print(p)              
                    profile_+=1
                    lose+=1               
                    final_table(minesweeper_map)
                    GameStatus = CheckContinueGame(score)
                    break
                else:
                    vardashtanparcham=input('Do you want to pick up the flag?if yes inter YES :')
                    if vardashtanparcham=='YES':
                        k+=1
                        if player_map[y][x]=="\u2690":

                            minesweeper_map[y][x]=e
                            player_map[y][x]='■'
                            final_table(player_map)
                            score+=1
                    elif player_map[y][x]=="\u2690":
                        final_table(player_map)
                        score += 1
                    else:
                        player_map[y][x] = minesweeper_map[y][x]
                        final_table(player_map)
                        score += 1
                    last = ''
                    for xz in range(len(minesweeper_map)) :
                        for yz in range(len(minesweeper_map[0])) :
                            last += f'{minesweeper_map[xz][yz]}'
                        last += '\n'
                    tlat=' '
                    for x2 in last :
                        tlat=tlat+x2+' '
                    with open('fifi.txt','w') as show:
                        for q2 in tlat:
                            try:
                                show.write(str(q2))
                            except:
                               if q2=='\u273a':
                                   show.write('v')
                               if q2=="\u2690":
                                   show.write('f')               
            else:
                print("You have Won!")
                a='''                        
                    / /"`.\.--"""--./,'"\ )
                    \ \    _       _    / /
                     `./  / __   __ \  \,'
                      (    /_O)_(_O\    )
                      |  .-'  ___  `-.  |
                   .--|       \_/       |--.
                 ,'    \   \   |   /   /    `.
                (       `.  `--^--'  ,'       )
             .-"""""-.    `--.___.--'     .-"""""-.
.-----------/         \------------------/         \--------------.
| .---------\         /----------------- \         /------------. |
| |          `-`--`--'                    `--'--'-'             | |
| |                                                             | |
| |                                                             | |
| |                                                             | |
| |                                                             | |
| |                        YOU WIN!!!!                          | |
| |                                                             | |
| |                                                             | |
| |                                                             | |
| |                                                             | |
| |                                                             | |
| |                                                             | |
| |                                                             | |
| |_____________________________________________________________| |
|_________________________________________________________________|
                   )__________|__|__________(
                  |            ||            |
                  |____________||____________|
                    ),-----.(      ),-----.(
                  ,'   ==.   \    /  .==    `.
                 (            )  (            )
                 `==========='    `==========='''
                print(a) 
                profile_+=1
                win+=1
                #profile_=profile_+1
                GameStatus = CheckContinueGame(score)
                break
        else:
            lose+=1
            print("time up!!!!!!!!!!!!!!!!!!!!!")
            break
#********************************File********************************#

Password=int(input('INTER YOUR Password:'))
if Password==123003:
    with open("profile.txt","a")as profile:
        profile.write("")
    with open("profile.txt","r")as profile:   
        InfoList = []
        profile_ = 0
        for line in profile:
            InfoList.append(line)
    if len(InfoList)==0:
        name=input("please enter your name: ")
        win=0
        lose=0
        with open("profile.txt","w")as profile:
            profile.write(f"name:{name}"+"\n")
            profile.write(f"win:0"+"\n")
            profile.write(f"lose:0")
        print(f"welcome {name}")
        z='''
  \  :  /       \  :  /       \  :  /       \  :  /       \  :  /
`. __/ \__ .' `. __/ \__ .' `. __/ \__ .' `. __/ \__ .' `. __/ \__ .'
_ _\     /_ _ _ _\     /_ _ _ _\     /_ _ _ _\     /_ _ _ _\     /_ _
   /_   _\       /_   _\       /_   _\       /_   _\       /_   _)
 .'  \ /  `.   .'  \ /  `.   .'  \ /  `.   .'  \ /  `.   .'  \ /  `.
   /  |  \       /  :  \       /  :  \       /  :  \          |  
      |                                                       |
   \  |  /                                                 \  |  /
`. __/ \__ .'                                           `. __/ \__ .'
_ _\     /_ _                                           _ _\     /_ _
   /_   _\                                                 /_   _)
 .'  \ /  `.                                             .'  \ /  `.
   /  |  \                                                    |  
      |                      WELCOME LOL                      |
   \  |  /                                                 \  |  /
`. __/ \__ .'                                           `. __/ \__ .'
_ _\     /_ _                                           _ _\     /_ _
   /_   _\                                                 /_   _)
 .'  \ /  `.                                             .'  \ /  `.
   /  |  \                                                    |  
      |                                                       |
   \  |  /       \  :  /       \  :  /       \  :  /       \  |  /
`. __/ \__ .' `. __/ \__ .' `. __/ \__ .' `. __/ \__ .' `. __/ \__ .'
_ _\     /_ _ _ _\     /_ _ _ _\     /_ _ _ _\     /_ _ _ _\     /_ _
   /_   _\       /_   _\       /_   _\       /_   _\       /_   _)
 .'  \ /  `.   .'  \ /  `.   .'  \ /  `.   .'  \ /  `.   .'  \ /  `.
   /  :  \       /  :  \       /  :  \       /  :  \       /  :  \   
'''      
        print(z)
        print(f"win:0")
        print(f"lose:0")
    elif len(InfoList)>0:
        name = (InfoList[0]).split(":")[1]
        win = int((InfoList[1]).split(":")[1])
        lose = int((InfoList[2]).split(":")[1])
        print(f"welcome back {name}")
        print(f"win:{win}")
        print(f"lose:{lose}")

    while(profile_>=0):
        order = input("please enter your order(Change Name or Play! or History): ")
        
        if order=="Change Name":
            new_name = input("please enter your name: ")
            with open("profile.txt","w") as profile:
                profile.write(f"name:{new_name}"+"\n")
                profile.write(f"win:{win}"+"\n")
                profile.write(f"lose:{lose}")

        elif order=="History":
            print(f"win{win}")
            print(f"lose:{lose}")
            with open('fifi.txt','r') as dic:
                dic2=dic.readlines()
            for o in dic2:
                for o2 in o:
                    if o2=='v':
                        o2='\u273a'
                    elif o2=='f':
                        o2="\u2690"
                    print(o2,end='')        
        elif order=="Play!":
            if __name__ == "__main__":
                try:
                   Game()
                except KeyboardInterrupt:
                    print('\nEnd of Game:///!')
            with open("profile.txt", "r") as profile:
                updatedname = profile.readlines(1)
            with open("profile.txt","w") as profile:
                
                profile.write(updatedname[0])
                profile.write(f"win:{win}"+"\n")
                profile.write(f"lose:{lose}")
            profile_=0


else:
    print('Suspected of fraud')            