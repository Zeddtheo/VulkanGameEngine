#pragma once	

#include "GameEngineDevice.h"
#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/glm.hpp>

namespace misc {
	class GameModel {
	public:
		struct Vertex {
			glm::vec2 position;

			static std::vector<VkVertexInputBindingDescription> getBindingDescriptions();
			static std::vector<VkVertexInputAttributeDescription> getAttributeDescriptions();

		};
		GameModel(GameEngineDevice& device, const std::vector<Vertex>& vertices);
		~GameModel();

		GameModel(const GameModel &) = delete;
		GameModel& operator=(const GameModel &) = delete;
		void bind(VkCommandBuffer commandBuffer);
		void draw(VkCommandBuffer commandBuffer);
	private:
		void createVertexBuffer(const std::vector<Vertex>& vertices);

		GameEngineDevice& gameDevice;
		VkBuffer vertexBuffer;
		VkDeviceMemory vertexBufferMemory;
		uint32_t vertexCount;
	};
}
