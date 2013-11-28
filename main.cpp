#include <iostream>
#include <stdexcept>
#include "Game.hpp"


using namespace std;


//===========================================
// main
//===========================================
int main(int argc, char** argv) {
  try {
    Game game;
    game.launch(argc, argv);
  }
  catch (runtime_error& e) {
    cerr << "Encountered fatal error; " << e.what() << "\n";
    return EXIT_FAILURE;
  }
  catch (...) {
    cerr << "Encountered fatal error; Cause unknown\n";
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
