# SnakeMy
Game of snake in **c++**
![alt text](https://github.com/Macjas1999/SnakeMy/blob/main/Screenshots/Screenshot0.png)
![alt text](https://github.com/Macjas1999/SnakeMy/blob/main/Screenshots/Screenshot1.png)
![alt text](https://github.com/Macjas1999/SnakeMy/blob/main/Screenshots/Screenshot2.png)
![alt text](https://github.com/Macjas1999/SnakeMy/blob/main/Screenshots/Screenshot3.png)

* GUI library is wxWidgets.
* I have drawn snake segments and apples myself.

Building the game requires wxWidgets library insatalled. Compiling the game should be done from the “SnakeMy” directory, for example using:<br>
**g++ -Isource source/snakeMy.cpp `wx-config --cxxflags --libs std` -o snakeMy.exe**<br>
If wxWidgests have been installed properly, this should result in “snakeMy.exe” being created in the main project directory. You need to give this file rights to execute as a program, and now, you can enjoy this interpretation of the well known snake game.  
