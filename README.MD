# StuSurf - Student Surface <br>

## Goal:
<br>
This project doesn't really have an intention. It is simply a program that would help me write quick programs in the future that are easily accessible and usable. The idea is that I create a new program, say test.cpp and test.h. As long as the main class the program is housed in inherints from Base, and I place it in the modules folder, I can implement it within stusurf.
<br>

The program is split into different parts.<br>
- The first part is the Stusurf itself. There is only 1 instance of this per running program.<br>
- The second is what I call "screens". A screen is simply a text file, located in the screen folder. You can have multiple screens per instance of Stusurf. You can only view 1 screen at a time, however can freely edit and switch between screens at will.<br>
- The third is modules. These are the homebrew scripts that I or any user of the program would make. They can do whatever, they have access to input and rendering. Many modules can be places within a screen.

<br><br>

So what ?<br>
- Well, I don't know, you can make a screen with a bunch of modules that would allow you to turn on various devices connected to your computer.<br>
- Then you can make a screen with modules dedicated specifically to sending quick test requests to some URL and printing the results. <br>
- You can make a screen with modules that can help you keep your life organized... calender/task list etc... <br>
- You can share modules with others, all you need to do is move it to the modules folder and recompile. <br>
- Then you can switch between all of these screens with ease. <br>
You can probably tell there is not much direction. More than anything this is a learning project for me, so criticism is appreciated.

## Use:
- Go to main directory and compile using make.<br>
- the executable should then be created as /bin/run <br>
## dependancies:
- opengl
- c++11
- currently linux only.... will work on windows version eventually.
## Please note that this is a wip, and the source code is pretty messy .... especially main.cpp .... 
