#include <iostream>
#include <iterator>
#include <raylib.h>

#include "CPU.hpp"
#include "instructions.hpp"

using namespace std;

int main(int argc, char *argv[]) {

    // chequeo de cantidad de argumentos
    if (argc != 2){
        cout << "USAGE: fnes [rom.nes] \n";
        return 0;
    }

    string gamepath = argv[1];

    // un path de menos de 4 caracteres nunca puede ser una rom (además rompe el checkeo de extension)
    if (gamepath.size()<4) {
        cout << "El archivo especificado no es una ROM\n";
        return 0;
   }

    string* tipo = new string();
    // chequeo de que el archivo sea .nes
    *tipo = gamepath.substr(gamepath.size()-4, 4);
    if (*tipo != ".nes") {
        delete tipo;
        cout << "El archivo especificado no es una ROM\n";
        return 0;
    }
    delete tipo;


    // Creacion de una ventana con el nombre de la rom
    string winame = "FNES: ";
    winame += gamepath.substr(0, gamepath.size()-4);
    InitWindow(600, 400, winame.c_str());
    SetTargetFPS(60);

    //declaracion del hardware de nes
    nes::cpu a;

    //main loop
    while(!WindowShouldClose()){

        BeginDrawing();

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
