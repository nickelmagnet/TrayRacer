#pragma once

namespace TrayRacer {

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
	return TrayRacer::Main(argc, argv);
}
