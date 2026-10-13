#pragma once

#include "glm/vec3.hpp"
#include "Ray.h"

namespace TrayRacer {
    class Camera {
    private:
        glm::vec3 m_origin;
        glm::vec3 m_pixel00_loc;
        glm::vec3 m_pixel_delta_u;
        glm::vec3 m_pixel_delta_v;

        const float m_focal_length = 1.0f;
        const float m_vfov = 90.0f;

    public:
        Camera() = default;
        Camera(glm::vec3 lookfrom, glm::vec3 lookat, glm::vec3 vup, int image_width, int image_height);
        Ray get_ray(int i, int j) const;
    };
}
