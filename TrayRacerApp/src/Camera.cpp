#include "Camera.h"

namespace TrayRacer {

    Camera::Camera(glm::vec3 lookfrom, glm::vec3 lookat, glm::vec3 vup, uint32_t width, uint32_t height)
    {
        m_origin = lookfrom;
        float theta = glm::radians(m_vfov);
        float viewport_height = 2.0f * m_focal_length * std::tan(theta / 2.0f);

        float aspect_ratio =static_cast<float>(width)/static_cast<float>(height);
        float viewport_width = viewport_height * aspect_ratio;

        glm::vec3 w = glm::normalize(lookfrom - lookat);
        glm::vec3 u = glm::normalize(cross(vup, w));
        glm::vec3 v = cross(w, u);

        glm::vec3 viewport_u = viewport_width * u;
        glm::vec3 viewport_v = -viewport_height * v;

        m_pixel_delta_u = viewport_u / static_cast<float>(width);
        m_pixel_delta_v = viewport_v / static_cast<float>(height);

        glm::vec3 viewport_upper_left = m_origin - (m_focal_length * w)- viewport_u / 2.0f - viewport_v / 2.0f;

        m_pixel00_loc = viewport_upper_left + 0.5f * (m_pixel_delta_u + m_pixel_delta_v);
    }

    Ray Camera::get_ray(int i, int j) const {
        glm::vec3 pixel_center = m_pixel00_loc + (static_cast<float>(i) * m_pixel_delta_u) + (static_cast<float>(j) * m_pixel_delta_v);
        glm::vec3 ray_direction = pixel_center - m_origin;
        return Ray(m_origin, glm::normalize(ray_direction));
    }
}