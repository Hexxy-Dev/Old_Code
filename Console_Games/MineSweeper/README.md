A very basic and really bad implementation of Minesweeper

**The mine reveal logic is completely wrong**

Controls:
```
1 to 9 coords
RowColumn[Flag]

ex1: 25f =>
-1 0  1  2  3  4  5
0  #  #  #  #  #  #
1  #  #  #  #  #  #
2  #  #  #  #  #  F

ex2: 11 =>
-1 0  1  2
0  #  #  #
1  #  1  1
2  #  1  #
```
Warning: wrong inputs will crash the app