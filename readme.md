### current state:
The bot always takes the shortest path. Of course, the snake will sometimes trap itself, making the Dijkstra algorithm useless. When this happens, my strategy is to identify the critical point in the snake's body currently identified by 'X'. In this situation, the snake must take the longest possible path without ever blocking the way from that point. Hopefully, that path will be long enough so that point gets freed and the snake can then find a path to the apple. I need to perfect this path.

![dijkstra-critical-point](https://i.postimg.cc/MTLQMq9x/dijkstra-critical-point.gif)
## This is a snake game projected to the console. 


 The snake follows a fixed path that maximizes its length, at the cost of being slow.

![infinite-game](https://i.postimg.cc/HnZ7v0MQ/infinite-game.gif)


Now it takes the shortest path using the Dijkstra algorithm. The snake teleports Pac-man style through the sides that are not blocked by walls.

![dijkstra](https://i.postimg.cc/fydYXKPj/dijkstra.gif)

A map is a text file containing spaces and '#' like shown in the game. This map has more walls.

![dijkstra-map2](https://i.postimg.cc/wTHSvbZV/dijkstra-map2.gif)

This map has no walls, letting the snake more options to survive.

![dijkstra-map-vide](https://i.postimg.cc/xdRXwZw4/dijkstra-map-vide.gif)
<!-- ![alt text](https://i.imgur.com/jDwq1Bb.gif) -->


The invicible mode lets the user control the snake, but iminent crashes that can be avoided are automatically avoided. It's an hybrid between manual and automatic.

![user-invicible](https://i.postimg.cc/rF7xN6qS/user-invicible.gif)


During my studies at Université Laval, I had to modify a naïve Dijkstra implementation and improve it significantly. My strategy had a complexity of O(u+n) where n is the number of locations and u is the number of possible distances. For further details, see my [report in french](https://docs.google.com/document/d/1tVqNiSNAh0G4h7_7KM4GMVgTxKbfcze4Tr1mpQ7nciI/edit?usp=sharing) produced during this course.
