#StuSurf - Student Surface <br>

## Goal:
<br>
This project is an attempt at me hitting two birds with one stone. I recently bought a surface and thought to myslef wouyldnt it be cool if i made a custom note taking app..... but then thought I would also like to make something that will help me understand OpenGL a bit more, and at the same time allow me to forget about opengl when making programs that need graphics. So this program is basically a wrapper for opengl that will allow you to create buttons and other input feilds etc... while I am testing this wrapper, I am kinda using it to make the note taking app aswell. I am finding this to be a great apporach because I add features as I need them
<br>

#Features:
<br>
	. Image Loader (done: bmp)
	. Font Loader (wip)
	. Input handling
		. Draw Area
		. Button (wip)
		. Text Fields (wip)
	. Different "windows"
	. Multiple program states. 
	. Will write the rest later.....


# Use:
<br>

	. create Global window object
	. init your glut
	. Create screens..... each screen represents a program state
	. add objects to screens.... objects can have callbacks in order to trigger events
	. add the sceens to the window
	. call glut mainloop

<br>

## Please note that this is a wip, and the source code is pretty messy .... especially main.cpp .... 