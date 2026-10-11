#include "Application.h"
#include "EntryPoint.h"
#include "Image.h"
#include "Timer.h"

#include "Renderer.h"

#include <memory>

using namespace TrayRacer;

class ExampleLayer : public TrayRacer::Layer
{
public:
	virtual void OnUIRender() override
	{
		ImGui::Begin("Settings");
		ImGui::Text("Last Render Time: %.3f ms", m_LastRenderTime);
        if (ImGui::Button("Render")) {
            Render();
        }
		ImGui::End();
		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
		ImGui::Begin("Viewport");
		m_ViewportWidth = ImGui::GetContentRegionAvail().x;
		m_ViewportHeight = ImGui::GetContentRegionAvail().y;
		if (auto image = m_Renderer.GetImage()) {
			ImGui::Image(image->GetDescriptorSet(), ImVec2((float)m_ViewportWidth, (float)m_ViewportHeight));
		}
		ImGui::End();
		ImGui::PopStyleVar();
	}
private:
	void Render() {
		if (m_ViewportWidth == 0 || m_ViewportHeight == 0) return;
		Timer timer;
		m_Renderer.OnResize(m_ViewportWidth, m_ViewportHeight);
		m_Renderer.Render();
		m_LastRenderTime = timer.ElapsedMillis();
	}

	Renderer m_Renderer;
	float m_LastRenderTime = 0.0f;
	uint32_t m_ViewportWidth = 0, m_ViewportHeight = 0;
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
