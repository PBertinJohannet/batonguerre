#on windows : 

gcc -o Test main.c -I"C:\Users\p bertin-johannet\CSFML\include" -L"C:\Users\p bertin-johannet\CSFML\lib\msvc" -lcsfml-graphics -lcsfml-window -lcsfml-audio

voila pour la comppilation : 
instructions : 


how to :
first : gcc 
https://sourceforge.net/projects/mingw-w64/files/Toolchains%20targetting%20Win64/Personal%20Builds/mingw-builds/
clicker sur x86_64-posix-sjlj en dessous de MinGW-W64 GCC-7.1.0

second : sfml 

download csfml from site (win64)
paste to C: or D:
create windows compilesfml.bat script to make sure it works
if it compiles go


jansson... ?? maybe change library ?

use https://github.com/kgabis/parson​
works on windows
and if no on unix then make json in #define windows etc...

#on unix-like :
brew/apt install sfml csfml make make install 
git clone 
go !
