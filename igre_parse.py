# -*- coding: utf-8 -*-
#!/usr/bin/python

import sys

uct = [0.3, 0.5, 0.7, 0.9]
n_tre = [30, 50, 80, 100, 120]

sys.stdout.write("-------------------------------------------------\n")
sys.stdout.write("| N\UCT |\t0.3\t0.5\t0.7\t0.9\t|\n")
sys.stdout.write("-------------------------------------------------\n")

for n_value in n_tre:
  sys.stdout.write("|  "+str(n_value)+"   |\t")
  
  for uct_value in uct:
    string = "./mcts-game-uct_"+str(uct_value)+"-n_"+str(n_value)+".pgn"
    f = open(string)
    games = 0
    wins = 0
    for line in f:
	if line[1:7] == "Result":
	  if line[9:11] == "1-":
	    wins = wins+1
	  games = games+1
    
    rate = str(float(wins)/games)
    sys.stdout.write(rate[0:4] + "\t")
  sys.stdout.write("|\n")
sys.stdout.write("-------------------------------------------------\n")
