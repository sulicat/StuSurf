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
 - (class) **Menu**
 - (class) **MenuItem**
 
 
 
## Using Menus:
You first create the menu. Then give it a title. Like this:

`Menu menu = Menu("title");`
 
Then you can add MenuItems to it. You have a few choices:

`menu.add( MenuItem("Item Label") );`

`menu.add( MenuItem("Item Label", void(void*) callback) );`

`menu.add( MenuItem("item Label", void(void*) callback, &anotherMenu) );`

The first option adds a menu item that does nothing. Just a label. The second option adds a menu item that will lauch a callback of type void(void* _a). The parameters can be set by declaring the MenuItem before-hand and just giving it in as an argument. The third type, you give it the memory adrress of another Menu object, allowing you to have submenus.

In order to enable the menu, use the following command:

`menu.enable();`

Enabling the menu will force stusurf to stop giving input to other screens until the menu no longer requires input. This is controlled by the guiManager. The menu will be disabled if you trigger one of its functions or press escape. If you open a sub-menu, the original menu will go into a hiding state, allowing you to revet by pressing backspace. Pressing escape, or triggering an action will disable the menu and call the function. In code, you can also call:

`menu.disable();`

Or you can always controll the guiManager directly. However there should be little reason to do so.
