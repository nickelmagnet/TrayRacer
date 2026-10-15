#pragma once

#include "glm/glm.hpp"

namespace TrayRacer {
	class Ray {
	public:
		Ray() = default;
		Ray(const glm::vec3& origin, const glm::vec3& direction);
		inline const glm::vec3& GetOrigin() const { return m_Origin; }
		inline const glm::vec3& GetDirection() const { return m_Direction; }
		glm::vec3 At(float t) const;
	private:
		glm::vec3 m_Origin;
		glm::vec3 m_Direction;
	};
}