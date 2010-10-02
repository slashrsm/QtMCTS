# -*- coding: utf-8 -*-
#!/usr/bin/python

import sys

uct = [0.7]
n_tre = [90]
tim = [30]

for t in tim:
  for n_value in n_tre:
    
    for uct_value in uct:
      string = "./mcts-BH_random-limit_100-KRK-"+str(t)+"s-uct_"+str(uct_value)+"-n_"+str(n_value)+".pgn"
      f = open(string)
      games = 0
      wins = 0
      for line in f:
	  if line[1:7] == "Result":
	    if line[9:11] == "1-":
	      wins = wins+1
	    games = games+1
      
      rate = str(float(wins)/games)
      print string, wins, games, rate
