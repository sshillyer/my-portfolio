Readme

Created by Shawn S. Hillyer
Shawn (dot) Hillyer (at) Gmail (dot) com
Date: 10/08/2015
Github.com/Soularpowered

=====
ABOUT
=====
This framework is to assist in quickly setting up a terminal-based,
console interface program in C++. It includes a makefile which you should
utilize to add any additional source files or header dependencies so that you can
type make all, make default, make zip, etc., as appropriate.

=======
PURPOSE
=======
This framework was developed incrementally as I progressed through a second
"introduction to computer science" course. It was motived by the desire to reduce
code reuse and minimize the amount of time I spent editing the main menu loop,
creating a new "main" entry point, etc.

======
HOW-TO
======
The main.menu file can be edited to type in plaintext menu options. This items
will be automatically enumerated by the Menu class.

The menu is instantiated in Client's constructor, which then calls a main_loop().

You should extend client to call whatever functions you need. If you want to instantiate
a class you are testing and call methods, for example, you could instantiate the class(es)
inside the constructor for Client or inside main_loop depending on how you plan to implement.

Add additional switch cases as necessary.

Note that you could easily create a secondary , ternary, etc. menu by adding
a new file and mimic the creation and loading of the menu file; or, by using a vector of strings
and passing that via the appropriate method (see the Menu.hpp for the various load_ methods)

Once the new menu is loaded, one of the switch cases could be to go to a different loop. You
would likely want to create a new method in Client, like shapes_loop(), in which you use the
same loop logic, but instead call the submenu's methods rather than main menu.


========
USE NOTE
========
I highly recommend you do NOT use this for your CS161 or CS162 assignments if you
attend Oregon State University, although allow it to inspire you. The cheat detection
will likely determine you copied my code. I used ALL parts and many variations of this
framework to complete my assignments and this would be considered cheating to re-use.

If you are attending any other university, please follow their guidelines, but
*always* credit me, the author, and cite my github as the source.

If you have suggestions for improvements, please email me! Thanks.
