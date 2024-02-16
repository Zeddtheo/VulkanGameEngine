#pragma once

#include "GameModel.h"

#include <memory>

namespace misc {
	struct Transform2dComponent {
		glm::vec2 translation{};
		glm::vec2 scale{ 1.0f, 1.0f };
		float rotation;

		glm::mat2 mat2() {
			const float s = sin(rotation);
			const float c = cos(rotation);
			glm::mat2 rotMatrix{ {c,s},{-s,c} };
			glm::mat2 scaleMat{ {scale.x, 0.0f}, {0.0f, scale.y} };
			return rotMatrix * scaleMat;
		}
	};
	class GameObject {
	public:
		using id_t = unsigned int;

		static GameObject createGameObject() {
			static id_t currentId = 0;
			return GameObject{ currentId++ };
		}

		GameObject(const GameObject&) = delete;
		GameObject& operator=(const GameObject&) = delete;
		GameObject(GameObject&&) = default;
		GameObject& operator=(GameObject&&) = default;

		id_t getId() const { return id; }

		std::shared_ptr<GameModel> model{};
		glm::vec3 color{};
		Transform2dComponent transform2d{};
	private:
		GameObject(id_t objId) : id{ objId } {}
		id_t id;
	};	
}