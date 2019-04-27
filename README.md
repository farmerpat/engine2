Engine take 2
-------------

*Building on Windows*
- Download SDL2\_image 64 bit runtime dlls (theres several of them that SDL2\_image depend on as well) and copy them to c:/windows/system32 to get the program to run.  Some people suggest that putting the dlls in the same folder as the exe will work, so that is probably something to try out...it would be much easier for other people to run the game, and I wouldn't have to statically link for windows. i wonder if a similar approach is possible for linux

- moved SDL2\_image.h to SDL2 include dir as per SDL2DIR environment variable specified in CMakeLists.txt
- moved SDL2\_image bin/ and lib/ contents to SDL2/lib/x64

- installed mingw-w64 in C:\Program\ Files
- added its bin/ to PATH
- copied mingw32-make.exe to make.exe

1. open cmake gui
2. Where is the source code: C:/Users/Patrick/source/repos/engine2
3. Where to build the binaries: C:/Users/Patrick/source/repos/engine2/build
4. <Configure>
5. <Generate>
6. Run make in build/ via cli
