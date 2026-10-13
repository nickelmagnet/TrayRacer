#pragma once

#include <memory>
#include <vector>
#include <cstdint>
#include "Image.h"

namespace TrayRacer {

    class Renderer {
    public:
        void OnResize(uint32_t w, uint32_t h);
        void Render();
        std::shared_ptr<Image> GetImage() const { return m_Image; }
		uint32_t PerPixel(uint32_t x, uint32_t y);
        uint32_t PerPixelRay(uint32_t x, uint32_t y);
        uint32_t PerPixelHue(uint32_t x, uint32_t y);

    private:
        std::shared_ptr<Image> m_Image;
        std::vector<uint32_t> m_ImageData;
        float m_LastRenderTime = 0.0f;
    };
}
