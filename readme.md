Conecpt
-------

Call the **getver** program in the pre-commit state and give it the following arguments: "tag", "branch", "git describe".

With these parameters, the program should modify the *fwid.cpp* file, which store these. 

The current **Makefile** could build either the **getver** or the **fwid** programs. It also links the right script as a pre-commit hook. Look inside the Makefile for more information.


