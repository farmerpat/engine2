#include "include/util.hpp"

SDL_Texture *Util::loadTexture (std::string file, SDL_Renderer *renderer) {
  SDL_Texture *texture = 0;
  SDL_Surface *surface = 0;

  surface = IMG_Load(file.c_str());

  if (surface) {
    texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
  }

  return texture;
}

// TODO:
// allow for setting style via TTF_SetFontStyle later
SDL_Texture *Util::loadFontTexture
(std::string file, std::string text, int pt, SDL_Color color, SDL_Renderer *rend) {
  SDL_Texture *texture = 0;
  SDL_Surface *surface = 0;

  TTF_Font *font = TTF_OpenFont(file.c_str(), pt);

  if (font) {
    surface = TTF_RenderText_Solid(font, text.c_str(), color);

    if (surface) {
      texture = SDL_CreateTextureFromSurface(rend, surface);
      SDL_FreeSurface(surface);
    }


    TTF_CloseFont(font);
  }

  return texture;
}

bool Util::fileExists(std::string f) {
  std::ifstream file(f);
  return file.good();
}

int Util::getNumLinesInFile(std::string f) {
  int numLines = -1;
  std::ifstream file(f);

  if (file.good()) {
    numLines = 0;
    std::string line;

    while (std::getline(file, line)) {
      numLines++;
    }
  }

  return numLines;
}

int Util::getNumColsInCsvFile(std::string f) {
  int numCols = -1;
  std::ifstream file(f);

  if (file.good()) {
    numCols = 0;
    std::string firstLine;
    std::getline(file, firstLine);
    int len = firstLine.length();

    for (int i=0; i<len; i++) {
      if (firstLine[i] == ',') {
        numCols++;
      }
    }

    if (numCols) {
      numCols++;
    }
  }

  return numCols;
}

std::vector<std::string> Util::fileToVector(std::string f) {
  std::vector<std::string> lines;
  std::ifstream file(f);

  std::string line;
  while(std::getline(file, line)) {
    lines.push_back(line);
  }

  return lines;
}

std::vector<std::vector<int>> Util::csvToVectorOfVectorsOfInts(std::string f) {
  std::vector<std::vector<int>> v;

  if (Util::fileExists(f)) {
    std::ifstream file(f);
    std::string line;

    while(std::getline(file, line)) {
      std::vector<int> row;
      for (int ch=0; ch<line.length(); ch++) {
        if (line[ch] == ' ' || line[ch] == ',') continue;

        // if we want double digit numbers, this will have to become
        // more flexible
        row.push_back((int)line[ch]-48);
      }

      v.push_back(row);
    }
  }

  return v;
}
