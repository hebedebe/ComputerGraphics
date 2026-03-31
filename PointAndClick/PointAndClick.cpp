#include <iostream>

#include "MainMenuLoader.h"
#include "../ComputerGraphics/ComputerGraphicsApp.h"

int main()
{
    ComputerGraphicsApp* app = ComputerGraphicsApp::Get();

    app->startupCompleteSignal.ConnectOneshot([](auto) {Loader::StaticLoad<MainMenu>(); });

    app->run("Test", 640, 480, false);

    delete app;

    return EXIT_SUCCESS;
}
