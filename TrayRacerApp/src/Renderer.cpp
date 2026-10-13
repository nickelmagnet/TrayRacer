#include "Renderer.h"
#include "Random.h"
#include "Ray.h"

namespace TrayRacer {

    void Renderer::OnResize(uint32_t w, uint32_t h) {
        if (m_Image && GetImageWidth() == w && GetImageHeight() == h) return;
        m_Image = std::make_shared<Image>(w, h, ImageFormat::RGBA);
        m_ImageData.resize(w * h);
		m_Camera = Camera({ 0.0f, 0.0f, 0.0f },{ 0.0f, 0.0f, -1.0f },{ 0.0f, 1.0f, 0.0f }, w, h);
    }

    void Renderer::Render() {
        const uint32_t width = GetImageWidth();
        const uint32_t height = GetImageHeight();

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

    bool hitting(const glm::vec3& center, float radius, Ray& r) {
        glm::vec3 oc = center - r.GetOrigin();
        auto a = dot(r.GetDirection(), r.GetDirection());
        auto b = -2.0 * dot(r.GetDirection(), oc);
        auto c = dot(oc, oc) - radius * radius;
        auto discriminant = b * b - 4 * a * c;
        return (discriminant >= 0);
    }

	uint32_t Renderer::PerPixelRay(uint32_t x, uint32_t y) {
        Ray ray = m_Camera.get_ray(x, y);
        if (hitting(glm::vec3{ 0.0f, 0.0f, -1.0f }, 0.5f, ray)) {
			return 0xFF369DF8; // Orange color for hit
		}
		glm::vec3 dir = ray.GetDirection();
        float yray = dir.y;
		float t = 0.5f * (yray + 1.0f);
		glm::vec3 color = (1.0f - t) * glm::vec3(1.0f, 1.0f, 1.0f) + t * glm::vec3(0.5f, 0.7f, 1.0f);
        uint8_t r = static_cast<uint8_t>(glm::clamp(color.r, 0.0f, 1.0f) * 255.0f);
        uint8_t g = static_cast<uint8_t>(glm::clamp(color.g, 0.0f, 1.0f) * 255.0f);
        uint8_t b = static_cast<uint8_t>(glm::clamp(color.b, 0.0f, 1.0f) * 255.0f);

		return 0xFF000000 | (b << 16) | (g << 8) | r;
	}

    uint32_t Renderer::PerPixelHue(uint32_t x, uint32_t y) {
        double t = (GetImageWidth() > 1) ? (double)x / (double)(GetImageWidth() - 1) : 0.0;

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