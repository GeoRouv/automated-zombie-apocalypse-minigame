# Automated-Zombie-Apocalypse-Minigame
A project in OOP programming in order to practise "new" and "delete" operators, copy constructor functions, "this", inheritance, and virtual functions.

## Game Description & Rules
We have two creatures: good creature and bad creature. The creatures live side by side, each in a specific position. 
  
The creatures have the following characteristics:<br/>
• Every creature has a name. <br/>
• Each creature has a life expectancy to live. When is born its life equals with L> 0 (L is common to all creatures).<br/>
• When the life of a creature hits zero, the creature falls into the zombie state. For creatures in zombie mode, the following actions have no effect.<br/>
• A creature can be cloned in place of another creature. In this case, the other creature is destroyed and a new creature(created as a copy of the first) takes its position.<br/>
• Every creature can either be blessed or hit. In the first case, its lifespan is increased by one unit. In the second case, it decreases by one unit.<br/>

  Good creatures, when blessed and robust enough, are cloned to occupy the next place in the community (the next position of the last is the first). They are considered "robust" if their current life is greater than a threshold(good_thrsh) which is common to all good creatures.<br/><br/>
  Bad creatures, when blessed and robust enough, are cloned by occupying all their next consecutive positions in the community occupied by zombie creatures (unless the bad creature blessed is at the end). They are considered "robust" if their current life is greater than a threshold(bad_thrsh) that is common to all bad creatures.<br/><br/>
  At each moment a creature is randomly selected and an action is randomly applied, bless or beat. This process is repeated M times. It is possible that the same creature will be selected more than once. The result is considered positive when, ultimately, the community consists of good creatures only.

## Compile
    $ g++ classes.h main.c++ text.c++ text.h
  
## Run	
    $ ./a.out
