#include <iostream>

#include "MainMenuLoader.h"
#include "../ComputerGraphics/ComputerGraphicsApp.h"

#ifdef _DEBUG
#define _CRTDBG_MAP_ALLOC
#include <cstdlib>
#include <crtdbg.h>
#endif

int main()
{
    ComputerGraphicsApp* app = ComputerGraphicsApp::Get();

    app->startupCompleteSignal.ConnectOneshot([](auto) {Loader::StaticLoad<MainMenu>(); });

    app->Run("Test", 640, 480, false);

    delete app;

#ifdef _DEBUG
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    _CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_DEBUG);
#endif

    return EXIT_SUCCESS;
}
