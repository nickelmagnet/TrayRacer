#include "Renderer.h"
#include "Random.h"
#include "Ray.h"

#include <cmath>

namespace TrayRacer {

    void Renderer::OnResize(uint32_t w, uint32_t h) {
        if(m_Image) m_Image->Resize(w, h);
        else m_Image = std::make_shared<Core::Image>(w, h, Core::ImageFormat::RGBA);
        m_ImageData.resize(w * h);
		m_Camera = Camera({ 0.0f, 0.0f, 0.0f },{ 0.0f, 0.0f, -1.0f },{ 0.0f, 1.0f, 0.0f }, w, h);
    }

    void Renderer::Render() {
        const uint32_t width = GetImageWidth();
        const uint32_t height = GetImageHeight();

        for (uint32_t y = 0; y < height; y++) {
            for (uint32_t x = 0; x < width; x++) {
                m_ImageData[y * width + x] = PerPixel(glm::vec2((float)x, (float)y));
            }
        }
        m_Image->SetData(m_ImageData.data());
    }


	uint32_t Renderer::PerPixel(glm::vec2 coord) {
        return PerPixelRay(coord);
	}

	uint32_t Renderer::PerPixelRay(glm::vec2 coord) {
		uint8_t clr = 0, clg = 0, clb = 0;
        Ray ray = m_Camera.get_ray(coord.x, coord.y);
        glm::vec3 center{ 0.0f, 0.0f, -1.0f };
        float radius = 0.5f;
        glm::vec3 oc = center - ray.GetOrigin();
        float a = glm::dot(ray.GetDirection(), ray.GetDirection());
        float b = -2.0f * glm::dot(ray.GetDirection(), oc);
        float c = glm::dot(oc, oc) - radius * radius;
        float discriminant = b * b - 4 * a * c;
        if (discriminant >= 0) {
            float t = (-b - std::sqrt(discriminant)) / (2.0f * a);
			// its solution is t = (-b ± sqrt(discriminant)) / (2.0 * a); 
			// ray is origin + t * direction,-b is positive so -b-sqrt(discriminant) is closer to cam
			glm::vec3 hit_point = ray.At(t);
            glm::vec3 normal = glm::normalize(hit_point - center);
            clr = static_cast<uint8_t>(glm::clamp(normal.x, 0.0f, 1.0f) * 255.0f);
            clg = static_cast<uint8_t>(glm::clamp(normal.y, 0.0f, 1.0f) * 255.0f);
            clb = static_cast<uint8_t>(glm::clamp(normal.z, 0.0f, 1.0f) * 255.0f);
        }
        else
        {
            glm::vec3 dir = ray.GetDirection();
            float yray = dir.y;
            float t = 0.5f * (yray + 1.0f);
            glm::vec3 color = (1.0f - t) * glm::vec3(1.0f, 1.0f, 1.0f) + t * glm::vec3(0.5f, 0.7f, 1.0f);
            clr = static_cast<uint8_t>(glm::clamp(color.r, 0.0f, 1.0f) * 255.0f);
            clg = static_cast<uint8_t>(glm::clamp(color.g, 0.0f, 1.0f) * 255.0f);
            clb = static_cast<uint8_t>(glm::clamp(color.b, 0.0f, 1.0f) * 255.0f);
        }
        return 0xFF000000 | (clb << 16) | (clg << 8) | clr;
	}

    uint32_t Renderer::PerPixelHue(glm::vec2 coord) {
        double t = (GetImageWidth() > 1) ? (double)coord.x / (double)(GetImageWidth() - 1) : 0.0;

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
