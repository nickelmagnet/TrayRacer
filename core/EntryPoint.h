#pragma once

#include "Application.h"

namespace Core {

	int Main(int argc, char** argv)
	{
		Application* app = CreateApplication(argc, argv);
		app->Run();
		delete app;
		return 0;
	}

}

int main(int argc, char** argv)
{
	return Core::Main(argc, argv);
}
