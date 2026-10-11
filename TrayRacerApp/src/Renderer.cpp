#include "Renderer.h"
#include "Random.h"

namespace TrayRacer {

	void Renderer::OnResize(uint32_t w, uint32_t h) {
		if (m_Image && m_Image->GetWidth() == w && m_Image->GetHeight() == h) return;
			m_Image = std::make_shared<Image>(w, h, ImageFormat::RGBA);
		m_ImageData.resize(w * h);
	}

	void Renderer::Render() {
		for (uint32_t i = 0; i < m_ImageData.size(); i++)
			m_ImageData[i] = 0xff000000 | Random::UInt();
		m_Image->SetData(m_ImageData.data());
	}

}
