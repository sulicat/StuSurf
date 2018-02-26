# STUSURF - Documentation / Use

## Things your module has access to:
 - (object) **screenManager**
   - This is the main screenManager that handles which screen recieves input and so on.
 - (object) **guiManager**
   - This is the object that deals with things such as menus and buttons etc... 
   - You can use it to control the GUI elements more precisley. Although most of the time, in-built GUI elements will handle this themeselves.
 - (object) **window**
    - this is the main render window. Use it to draw.
 - (function) **common::____**
 - (class) **Command**
 - (class) **Menu**
 - (class) **MenuItem**
 - (class) **CommandBox**
 
 
 
## Using Menus:
You first create the menu. Then give it a title. Like this:

`Menu menu = Menu("title");`
 
Then you can add MenuItems to it. You have a few choices:

```
menu.add( MenuItem("Item Label") );
menu.add( MenuItem("Item Label", void(void*) callback) );
menu.add( MenuItem("Item Label", void(void*) callback, void* callback_argument) );
menu.add( MenuItem("item Label", void(void*) callback, &anotherMenu) );
menu.add( MenuItem("item Label", void(void*) callback, void* callback_argument, &anotherMenu) );
```

The first option adds a menu item that does nothing. Just a label. The second option adds a menu item that will lauch a callback of type void(void* _a). The parameters can be set by declaring the MenuItem before-hand and just giving it in as an argument. The third type, you give it the memory adrress of another Menu object, allowing you to have submenus.

In order to enable the menu, use the following command:

`menu.enable();`

Enabling the menu will force stusurf to stop giving input to other screens until the menu no longer requires input. This is controlled by the guiManager. The menu will be disabled if you trigger one of its functions or press escape. If you open a sub-menu, the original menu will go into a hiding state, allowing you to revet by pressing backspace. Pressing escape, or triggering an action will disable the menu and call the function. In code, you can also call:

`menu.disable();`

Or you can always controll the guiManager directly. However there should be little reason to do so.

You can also create a menu from a directory, using the `menuFromDir( std::string dir, std::function<void(void*)> callback)` function. It takes in a callback. It will automatically pass the file path as the parameter for the callback as `std::string* param`. If you do not want to create a new std::function every time. I like using lambda functions, like this: `menuFromDir( somedir, [](void* _d){ ...do...stuff; } );`

## Using Command Boxes
Command boxes are pretty simple. The idea is to have an input that you can type, however it only allows you a set amount of options. A CommandBox will take in a pointer to a vector of Commands. The basic use case is as follow: 

- Create a vector of commands that will include all the possible commands you want to show in your command box. `std::vector<Command> Main_Commands;` It is important to note that Commands are basically callbacks that are linked to a name, think of it as a class that has a callback a string for the name.
- Now create the CommandBox and set the link.
```
CommandBox textbox_commands = CommandBox( );
textbox_commands.set( &Main_Commands );
```
- Now Every time we want the command box to show and be used, we simply call `textbox_commands.enable()`. This will allow it to intercept keybaord input and it will eventually die when the transaction is complete. (The GuiManager is the thing that handles all of this)
