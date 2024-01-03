import sys

try:
  while True:
    line = sys.stdin.readline().rstrip("\n")
    if(line == ""):
      break
    print(line)
except:
  print();