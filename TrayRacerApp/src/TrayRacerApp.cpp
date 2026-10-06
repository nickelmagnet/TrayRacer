#include "Application.h"
#include "EntryPoint.h"

#include "Image.h"

class ExampleLayer : public TrayRacer::Layer
{
public:
	virtual void OnUIRender() override
	{
		ImGui::Begin("Hello");
		ImGui::Button("Button");
		ImGui::End();

		ImGui::ShowDemoWindow();
	}
};

TrayRacer::Application* TrayRacer::CreateApplication(int argc, char** argv)
{
	TrayRacer::ApplicationSpecification spec;
	spec.Name = "TrayRacer";

	TrayRacer::Application* app = new TrayRacer::Application(spec);
	app->PushLayer<ExampleLayer>();
	app->SetMenubarCallback([app]()
	{
		if (ImGui::BeginMenu("File"))
		{
			if (ImGui::MenuItem("Exit"))
			{
				app->Close();
			}
			ImGui::EndMenu();
		}
	});
	return app;
}
