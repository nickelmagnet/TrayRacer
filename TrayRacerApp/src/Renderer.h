#pragma once

#include <memory>
#include <vector>
#include "Image.h"

class Renderer {
public:
    void OnResize(uint32_t w, uint32_t h);
    void Render();                       
    std::shared_ptr<Image> GetImage(uint32_t w, uint32_t h);
private:
    std::shared_ptr<Image> m_Image;
    std::vector<uint32_t> m_ImageData = nullptr;
    float m_LastRenderTime = 0.0f;
    uint32_t m_ViewportWidth = 0, m_ViewportHeight = 0;
};
