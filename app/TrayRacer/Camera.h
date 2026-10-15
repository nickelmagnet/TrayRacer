#pragma once

#include <cstdint>

#include "glm/glm.hpp"
#include "Ray.h"

namespace TrayRacer {
    class Camera {
    private:
        glm::vec3 m_origin;
        glm::vec3 m_pixel00_loc;
        glm::vec3 m_pixel_delta_u;
        glm::vec3 m_pixel_delta_v;

        float m_focal_length = 1.0f;
        float m_vfov = 90.0f;

    public:
        Camera(glm::vec3 lookfrom = {0.0f, 0.0f, 0.0f}, glm::vec3 lookat = {0.0f, 0.0f, -1.0f}, glm::vec3 vup = {0.0f, 1.0f, 0.0f}
        , uint32_t width = 1, uint32_t height = 1);
        Ray get_ray(int i, int j) const;
    };
}
