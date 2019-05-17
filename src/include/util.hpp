#ifndef UTIL_HPP
#define UTIL_HPP

#include <string>
#include <vector>
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include <fstream>

class Util {
  public:
    static SDL_Texture* loadTexture(std::string, SDL_Renderer*);
    static SDL_Texture* loadFontTexture(std::string, std::string, int, SDL_Color, SDL_Renderer*);
    static bool fileExists(std::string);
    static int getNumLinesInFile(std::string);
    static int getNumColsInCsvFile(std::string);
    static std::vector<std::string> fileToVector(std::string);
    static std::vector<std::vector<int>> csvToVectorOfVectorsOfInts(std::string);

};
#endif
