# Tutorial – Setup Bootstrap
 

## Introduction:
In this tutorial we are going to be familiarizing ourselves with the 2D drawing functionality of the AIE Bootstrap framework. 

We won’t be concerning ourselves with any gameplay in this lecture. Instead, we will focus on drawing some 2D shapes.

While our program won’t be interactive and will contain no game logic, you could extend this program throughout this course to create your own game.

## Downloading and Installing:
If you haven’t already done so, download the AIE Bootstrap framework from GitHub via this link:
https://github.com/AcademyOfInteractiveEntertainment/aieBootstrap/archive/master.zip 
This will directly download the framework for you to begin working with. 

Even if you already have a copy of this project, it is a good idea to download a fresh copy. This project is continually being updated, and the latest changes add support for Visual Studio 2022.

Alternatively, you may wish to set up your own Git project and clone the repository. Cloning the repository is not necessary, although it will allow you to be notified when updates and changes are made to the framework.

The landing page for this project contains some additional information, including video tutorials on how to set up a Git project: ```https://github.com/AcademyOfInteractiveEntertainment/aieBootstrap```

Once you have download the project, extract it to a folder on your machine. The project comes complete with a solution and a 2D and 3D demonstration project.

Before opening the solution, install the project templates if you have not already done so. You may need to restart the machine a few times to detect it once it is in place, you also must launch Visual Studio once already.

Locate the project templates in the ```aieBootstrap-master\tools\ProjectTemplates``` folder.

Copy the two .zip files into the Visual Studio templates directory. You’ll find this in your MyDocuments folder, for example:
	```Documents\Visual Studio 2022\Templates\ProjectTemplates\Visual C++ Project\```

Copy both of the .zip files to this location. Do not extract the .zip files.

After restarting Visual Studio you will now see two new project templates available whenever you create a new Visual C++ project.

## Clearing the Template Cache (Unlikely To Do):
If you already have the templates installed and you wish to update them, you’ll need to clear the Visual Studio template cache.

The easiest way to do this is to use the Developer Command Prompt for Visual Studio 2022.

Before beginning, make sure Visual Studio is closed.

From the Windows Start menu, search for and open the Developer Command Prompt for VS 2022

This will launch a console window. Type the following command:
devenv /updateconfiguration

This will update the project template cache. Open Visual Studio again and you should now see both the 2D and 3D bootstrap project templates when you create a new project.

## Working with AIE Bootstrap:

The AIE Bootstrap framework comes with a provided Visual Studio solution (Bootstrap.sln). 

Open this solution in Visual Studio, or double-click on the .sln file.

The Bootstrap project is the framework itself. Every 2D or 3D project you make will link with this library to enable features like drawing using OpenGL, or handling keyboard input.

You will need to build the Bootstrap project. You can also build and execute the 2D and 3D projects if you wish to run these provided demonstration programs.

### Bootstrap contains:

#### Classes:

- **Application.h**: this is the pure-virtual base class that wraps up an application for us. We derive our own applications from this class when making a project from the template.
- **Font.h**: a class for wrapping up an opengl texture image.
- **Texture.h**: a class for wrapping up an opengl texture image.
- **Renderer2D.h**:  a class for rendering 2D sprites and font.
- **Input.h**: a giant list of input codes for keyboard and mouse and a singleton class that manages Input from the keyboard and mouse.
- **Gizmos.h**: a singleton class for rendering immediate-mode 3-D primitives.

#### Third-Party Libraries:
- **ImGUI**: a bloat-free graphical user interface library for C++. It outputs optimized vertex buffers that you can render anytime in your 3D-pipeline-enabled application. It is fast, portable, renderer agnostic, and self-contained. https://github.com/ocornut/imgui 
- **GLFW**: an Open Source, multi-platform library for OpenGL development on the desktop. It provides a simple API for creating windows, contexts and surfaces, receiving input and events. https://www.glfw.org/ 
- **GLM**: OpenGL Mathematics (GLM) is a header only C++ mathematics library for graphics software based on the OpenGL Shading Language (GLSL) specifications. https://github.com/g-truc/glm 
- **STB**: ingle-file public domain libraries for C/C++ https://github.com/nothings/stb 

#### *YourProject*App
When creating an application via the template provided it creates the following functions to use:
- **startup()**: This handles initialisation.
- **shutdown()**: This handles deletion and memory clean up.
- **update(float deltaTime)**: this is for real time functionality.
- **draw()**: this is for rendering images, font, etc.

#### Bin Folder
Whenever you want a file to be loaded you place it in the bin folder, you can look at Project2D and Project3D to see how it is used.

## Creating a New Project:

When working on a new tutorial, you will need to add your project to this solution.

Adding your project to this solution is much easier than creating a new solution for each tutorial and trying to import the Bootstrap library manually.

To create a new project, right-click on the solution name in the Solution Explorer and select **Add -> New Project**.

Select the **2D project template** (since we will be creating our physics simulation in 2D) you will know it is the right one if the AIE logo is there. 

In the **Solution Explorer**, right-click on your new project and select **Retarget Projects**, a pop-up called **Review Solution Actions** will appear, press **OK**

Then right-click on your new project and select **Set as StartUp Project**. This means that when you press the Compile button, this is the project that will be compiled.

Next you want to Right-click on your new project and select <b>Build Dependancies -> Project Dependencies...</b>

In here make sure the **Project** is set to *your new project's name* and make sure you tick that it *depends on* **Bootstrap**.

Finally, we need to set the execution path of the project.

Right-click on your new project and select **Properties**. 

Make sure the **Configuration** to **Debug** and the **Platform** to **x64** and do the following in order: 

- In the **Configuration Properties**, go to **Debugging** then change the **Working Directory** from <b>```$(ProjectDir)```</b> to <b>```$(SolutionDir)bin\```</b>. This will allow you to find the fonts and assets you may want to use in a 2D or 3D project.

- In the **Configuration Properties**, go to **VC++ Directories** then ensure the <b>Include Directories</b> is set to <b>```$(SolutionDir)bootstrap;$(SolutionDir)dependencies/imgui;$(SolutionDir)dependencies/glm;$(VC_IncludePath);$(WindowsSDK_IncludePath);```</b> and Library Directories is set to<b>```$(SolutionDir)dependencies\bootstrap\$(Platform)\$(Configuration);$(VC_LibraryPath_x64);$(WindowsSDK_LibraryPath_x64);$(NETFXKitsDir)Lib\um\x64```</b>


- In the **Configuration Properties**, go to **C/C++ -> General** then ensure the <b>Additional Include Directories</b> is set to <b>```$(SolutionDir)bootstrap;$(SolutionDir)dependencies/imgui;$(SolutionDir)dependencies/glm;%(AdditionalIncludeDirectories)```</b>

- In the **Configuration Properties**, go to **Linker -> General** then ensure the <b>Additional Library Directories</b> is set to <b>```$(SolutionDir)temp\Bootstrap\$(Platform)\$(Configuration)\;%(AdditionalLibraryDirectories)```</b>

- In the **Configuration Properties**, go to **Linker -> Input** then ensure the <b>Additional  Dependencies</b> is set to <b>```bootstrap.lib;kernel32.lib;user32.lib;gdi32.lib;winspool.lib;comdlg32.lib;advapi32.lib;shell32.lib;ole32.lib;oleaut32.lib;uuid.lib;odbc32.lib;odbccp32.lib;%(AdditionalDependencies)```</b>

- In the **Configuration Properties**, go to **Build Events -> General** then ensure the <b>Command Line</b> is empty.

This will ensure the program can find all required libraries and resource files when it executes in Debug mode.

You’ve just created a new project that uses the AIEBootstrap library. 

## How to Submit a Release Build and Source Files for Bootstrap

### Source Files:
Go to the bootstrap folder with the Bootstrap.sln file in it and grab everything that level of the project and zip it, remember to remove the temporary files before doing so. The easiest way to do so is to grab a zip from GitHub and extract it to test if it still works.

### Release Build:
To make a successful release build, you will follow the steps outlined above in **Creating a New Project**, however you must:
- Make sure the **Configuration** to **Release** and the **Platform** to **x64**. 
- In the **Configuration Properties**, go to **Debugging** then change the **Working Directory** to <b>```$(ProjectDir)```</b>. This will allow you to drop the bin folder in the same level as the executable made and allow it to find the fonts and assets you may want to use in a 2D or 3D project.

Once you have built the project successfully as a Release x64 via Visual Studio go to ```aieBootstrap-2025 -> temp -> *YourProjectsName* -> x64 -> Release```.
In here will be the generated executable file and where we will make a copy of the project's bin folder as stated above.

## Task 1: Lets Test How You Can Render Text Using Bootstrap

Jump down to the draw function inside of your project, it should look something like this:

``` c++
void PhysicsApp::draw() {
    // wipe the screen to the background colour
    clearScreen();

    // begin drawing sprites
    m_2dRenderer->begin();

    // draw your stuff here!
    static float aspectRatio = 16 / 9.f;
    aie::Gizmos::draw2D(glm::ortho<float>(-100, 100, -100 / aspectRatio, 100 / aspectRatio, -1.0f, 1.0f));

    // output some text, uses the last used colour
    m_2dRenderer->drawText(m_font, "Press ESC to quit", 0, 0);
    // done drawing sprites
    m_2dRenderer->end();
}
```

What we want to do is use the *m_2dRenderer->drawText()* in order to render the term "Hello World" to the center of the screen. Keep in mind our Bootstraps renderer starts at 0,0 in the bottom left hand corner and in our ***main.cpp*** we set it as part of the *Application->run()*
Replace Application with whatever you called your Application-derived class.
``` c++
#include "Application2D.h"

int main() {
	
	// allocation
	auto app = new Application2D();

	// initialise and loop
	app->run("AIE", 1280, 720, false); //1280 by 720 being the size of the window by default in pixels

	// deallocation
	delete app;

	return 0;
}
```

Finally to ensure it is centered take into account the size of the font used, most likely *m_font*.

## Task 2: Lets Test How You Can Render an Image Using Bootstrap
Just like loading a message to the screen, we need to allocate resources to get image data and then load the image data, luckily we have the functions to do so. 

Inside of your Application-derived class you will need to use the *startup()* and *draw()* functions
``` c++
#include "Application2D.h"
#include "Texture.h"
#include "Font.h"
#include "Input.h"

...

bool Application2D::startup() {
	
	m_2dRenderer = new aie::Renderer2D();

	// TODO: remember to change this when redistributing a build!
	// the following path would be used instead: "./font/consolas.ttf"
	m_font = new aie::Font("../bin/font/consolas.ttf", 32);

	return true;
}

...

void Application2D::draw() {

	// wipe the screen to the background colour
	clearScreen();

	// begin drawing sprites
	m_2dRenderer->begin();

	// draw your stuff here!
	// 
	// output some text, uses the last used colour
	m_2dRenderer->drawText(m_font, "Press ESC to quit", 0, 0);

	// done drawing sprites
	m_2dRenderer->end();
}
```

You will need to declare a new variable called *m_texture*, place the file in the bin folder, I recommend using the *ship.png* and use Bootstrap's function *aie::Texture("./textures/ship.png")*;

To bind this and draw our desired image we need to add our functionality under *m_2dRenderer->begin();* and above *m_2dRenderer->end();* writing it out as follows:

``` c++
// Render a simple sprite
m_2dRenderer->setUVRect(0,0,1,1);
m_2dRenderer->drawSprite(m_texture, 200, 200, 100, 100);
```

## Task 3: Lets Test How You Can Render a Gizmo using Bootstrap
Lets start by talking about Gizmos, inside of bootstrap there is a class called *Gizmos*, this is a singleton class for rendering 2D and 3D primitives. This is how we will debug a lot of things in physics until we may want to use sprites. In order to use a Gizmo we must do the following to set it up:

1. Make sure we add the Gizmo class header to our Application-derived class. In that class' *startup()* we need to create a pool of resources for the Gizmos to use, this is done with the ```aie::Gizmos::create``` function. 
``` c++
bool PhysicsApp::startup() { 
    // increase the 2d line count to maximize the number of objects we can draw
    aie::Gizmos::create(255U, 255U, 65535U, 65535U);

    m_2dRenderer = new aie::Renderer2D();
    m_font = new aie::Font("./font/consolas.ttf", 32);

    return true;
}
```
2. In the *update()* we will want to clear the last frame's rendered gizmos
```c++
void PhysicsApp::update(float deltaTime) {
    // input example
    aie::Input* input = aie::Input::getInstance();

    aie::Gizmos::clear();

    // exit the application
    if (input->isKeyDown(aie::INPUT_KEY_ESCAPE))
        quit();
}
```

3. Next in the *draw()* we need to set up the space for the projections, this is done in one of two ways:
	1.   We can create a scaled view space based on an arbitrary value. In the example below we are scaling our screen to a 16/9 ratio and the origin point (0,0) to the middle of the screen, sitting at -100 on the far left and 100 on the far right of the window.
	```c++
	void PhysicsApp::draw() {

	// wipe the screen to the background colour
	clearScreen();

	// begin drawing sprites
	m_2dRenderer->begin();

	// draw your stuff here!
	aie::Gizmos::add2DCircle(glm::vec2(0), 3, 15, glm::vec4(1));

	static float aspectRatio = 16.f / 9.f;
	aie::Gizmos::draw2D(glm::ortho<float>(-100, 100,
		-100 / aspectRatio, 100 / aspectRatio, -1.f, 1.f));

	// done drawing sprites
	m_2dRenderer->end();
	}
	```
	2. We can set it to pixel values, this means unlike the example above we will not be able to easily scale the gizmos and instead have their origin point at the bottom left of the screen for rendering.<br>
	This better works best when working with the default rendering of images.
	```c++
	void PhysicsApp::draw() {

	// wipe the screen to the background colour
	clearScreen();

	// begin drawing sprites
	m_2dRenderer->begin();

	// draw your stuff here!
	aie::Gizmos::add2DCircle(glm::vec2(620, 340), 20, 15, glm::vec4(1));

	aie::Gizmos::draw2D(glm::ortho<float>(0, 1280,
	0, 720, -1.f, 1.f));

	// done drawing sprites
	m_2dRenderer->end();
	}
	```

For the following Tutorials we will be using option 1, the scaled projection with center origin, by default.


## Task 4: Lets Make an FPS Counter
Inside of Bootstraps Application class there is a function called *getFPS()*, Using what you know figure out a way to output an updating FPS counter.