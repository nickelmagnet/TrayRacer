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
    private:
        std::shared_ptr<Image> m_Image;
        std::vector<uint32_t> m_ImageData;
        float m_LastRenderTime = 0.0f;
        uint32_t m_ViewportWidth = 0, m_ViewportHeight = 0;
    };

}
