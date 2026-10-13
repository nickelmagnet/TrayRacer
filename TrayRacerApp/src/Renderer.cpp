#include "Renderer.h"
#include "Random.h"
#include "Ray.h"

namespace TrayRacer {

    void Renderer::OnResize(uint32_t w, uint32_t h) {
        if (m_Image && m_Image->GetWidth() == w && m_Image->GetHeight() == h) return;
        m_Image = std::make_shared<Image>(w, h, ImageFormat::RGBA);
        m_ImageData.resize(w * h);
    }

    void Renderer::Render() {
        const uint32_t width = m_Image->GetWidth();
        const uint32_t height = m_Image->GetHeight();

        for (uint32_t y = 0; y < height; y++) {
            for (uint32_t x = 0; x < width; x++) {
                m_ImageData[y * width + x] = PerPixel(x, y);
            }
        }
        m_Image->SetData(m_ImageData.data());
    }


	uint32_t Renderer::PerPixel(uint32_t x, uint32_t y) {
        return PerPixelRay(x, y);
	}

	uint32_t Renderer::PerPixelRay(uint32_t x, uint32_t y) {
		int i = y * m_Image->GetWidth() + x;
		double t = (m_Image->GetWidth() > 1) ? (double)x / (double)(m_Image->GetWidth() - 1) : 0.0;
		double r = (1.0 - t) * 1.0 + t * 0.5;
		double g = (1.0 - t) * 1.0 + t * 0.7;
		double b = (1.0 - t) * 1.0 + t * 1.0;
		uint8_t r_byte = static_cast<uint8_t>(r * 255);
		uint8_t g_byte = static_cast<uint8_t>(g * 255);
		uint8_t b_byte = static_cast<uint8_t>(b * 255);
		return 0xFF000000 | (b_byte << 16) | (g_byte << 8) | r_byte; // ARGB format
	}

    uint32_t Renderer::PerPixelHue(uint32_t x, uint32_t y) {
        int i = y * m_Image->GetWidth() + x;
        double t = (m_Image->GetWidth() > 1) ? (double)x / (double)(m_Image->GetWidth() - 1) : 0.0;

        double hue = t * 6.0;
        int sector = (int)hue;
        double fraction = hue - sector;

        uint8_t r = 0, g = 0, b = 0;
        uint8_t max_val = 255;
        uint8_t slope_up = (uint8_t)(fraction * 255.0);
        uint8_t slope_down = (uint8_t)((1.0 - fraction) * 255.0);

        switch (sector % 6) {
        case 0: r = max_val;    g = slope_up;   b = 0;          break;
        case 1: r = slope_down; g = max_val;    b = 0;          break;
        case 2: r = 0;          g = max_val;    b = slope_up;   break;
        case 3: r = 0;          g = slope_down; b = max_val;    break;
        case 4: r = slope_up;   g = 0;          b = max_val;    break;
        case 5: r = max_val;    g = 0;          b = slope_down; break;
        }
        return 0xFF000000 | (b << 16) | (g << 8) | r;
    }

}