#include "Application.h"
#include "EntryPoint.h"
#include "Image.h"
#include "Random.h"
#include "Timer.h"

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
		ImGui::Image(m_Image ? m_Image->GetDescriptorSet() : nullptr, ImVec2((float)m_ViewportWidth, (float)m_ViewportHeight));
		ImGui::End();
		ImGui::PopStyleVar();
	}
	void Render()
	{
		Timer timer;
		if (!m_Image || m_Image->GetWidth() != m_ViewportWidth || m_Image->GetHeight() != m_ViewportHeight) {
			m_Image = std::make_shared<Image>(m_ViewportWidth, m_ViewportHeight, ImageFormat::RGBA);
			delete[] m_ImageData;
			m_ImageData = new uint32_t[m_ViewportWidth * m_ViewportHeight];
		}
		for (uint32_t i = 0; i < m_ViewportWidth * m_ViewportHeight; i++) {
			m_ImageData[i] = Random::UInt();
			m_ImageData[i] |= 0xFF000000;
		}
		m_Image->SetData(m_ImageData);
		m_LastRenderTime = timer.ElapsedMillis();
	}
private:
	std::shared_ptr<Image> m_Image;
	uint32_t* m_ImageData = nullptr;
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
