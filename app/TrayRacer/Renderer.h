#pragma once

#include <memory>
#include <vector>
#include <cstdint>

#include <glm/glm.hpp>

#include "Camera.h"
#include "Image.h"

namespace TrayRacer {

    class Renderer {
    public:
        void OnResize(uint32_t w, uint32_t h);
        void Render();
        std::shared_ptr<Core::Image> GetImage() const { return m_Image; }
        uint32_t GetImageWidth() const { return m_Image ? m_Image->GetWidth() : 0; }
        uint32_t GetImageHeight() const { return m_Image ? m_Image->GetHeight() : 0; }
        uint32_t PerPixel(glm::vec2 coord);
        uint32_t PerPixelRay(glm::vec2 coord);
        uint32_t PerPixelHue(glm::vec2 coord);

    private:
        std::shared_ptr<Core::Image> m_Image;
        std::vector<uint32_t> m_ImageData;
        float m_LastRenderTime = 0.0f;
        Camera m_Camera;
    };
}
