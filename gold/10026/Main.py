d = []

a = int(input())
listIn = []
slistn = []
listInr = []
slistr = []
cntn = 0
cntr = 0

for q in range(a):
  inp = input() 
  listIn.append(inp)
  slforn = []
  slforr = []
  for i in range(len(inp)):
    slforn.append(False)
    slforr.append(False)
  slistn.append(slforn)
  slistr.append(slforr)

      


for i in listIn:
  a = i.replace('G', 'R')
  listInr.append(a)
      

def traversal(list, slist, color, x, y):
  slist[y][x] = True
  for i in range(1, -2, -2):
    if(0 <= y < len(list) and 0 <= x + i < len(list) and not slist[y][x + i] and list[y][x + i] == color):
      d.append([x + i, y])
    if(0 <= y + i < len(list) and 0 <= x < len(list) and not slist[y + i][x] and list[y + i][x] == color):
      d.append([x, y + i])



def color_search(list, slist, search_type) :
  global cntn
  global cntr
  for i in range(0, len(list), 1):
    for j in range(0, len(list), 1):
      if(not slist[i][j]):
        d.append([j, i])
        color = list[i][j]
        while(len(d) != 0):
          location = d.pop()
          traversal(list, slist, color, location[0], location[1])
        if(search_type == "n"):
          cntn += 1
        elif(search_type == "r"):
          cntr += 1




# 재귀로 할 때

# def traversal(list, slist, color, x, y):
#   for i in range(1, -2, -2):
#     if(0 <= y < len(list) and 0 <= x + i < len(list) and not slist[y][x + i] and list[y][x + i] == color):
#       slist[y][x + i] = True
#       traversal(list, slist, color, x + i, y)
#     if(0 <= y + i < len(list) and 0 <= x < len(list) and not slist[y + i][x] and list[y + i][x] == color):
#       slist[y + i][x] = True
#       traversal(list, slist, color, x, y + i)

# def color_search(list, slist, search_type) :
#   global cntn
#   global cntr
#   for i in range(0, len(list), 1):
#     for j in range(0, len(list), 1):
#       if(not slist[i][j]):
#         color = list[i][j]
#         slist[i][j] = True
#         traversal(list, slist, color, j, i)
#         if(search_type == "n"):
#           cntn += 1
#         elif(search_type == "r"):
#           cntr += 1

color_search(listIn, slistn, "n")
color_search(listInr, slistr, "r")


print(f"{cntn} {cntr}")
