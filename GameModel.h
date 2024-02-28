#pragma once	

#include "GameDevice.h"
#include "GameBuffer.h"

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/glm.hpp>

#include <memory>
#include <vector>
namespace misc {
	class GameModel {
	public:
		struct Vertex {
			glm::vec3 position{};
			glm::vec3 color{};
			glm::vec3 normal{};
			glm::vec2 uv{};

			static std::vector<VkVertexInputBindingDescription> getBindingDescriptions();
			static std::vector<VkVertexInputAttributeDescription> getAttributeDescriptions();

			bool operator==(const Vertex& other) const {
				return position == other.position && color == other.color && normal == other.normal &&
					uv == other.uv;
			}
		};

		struct Builder {
			std::vector<Vertex> vertices{};
			std::vector<uint32_t> indices{};
			void loadModel(const std::string& filepath);
		};

		GameModel(GameDevice& device, const GameModel::Builder &builder);
		~GameModel();

		GameModel(const GameModel &) = delete;
		GameModel& operator=(const GameModel &) = delete;

		static std::unique_ptr<GameModel> createModelFromFile(
			GameDevice& device, const std::string& filepath);

		void bind(VkCommandBuffer commandBuffer);
		void draw(VkCommandBuffer commandBuffer);
	private:
		void createVertexBuffers(const std::vector<Vertex>& vertices);
		void createIndexBuffers(const std::vector<uint32_t>& indices);

		GameDevice& myDevice;

		std::unique_ptr<GameBuffer> vertexBuffer;
		uint32_t vertexCount;

		bool hasIndexBuffer = false;
		std::unique_ptr<GameBuffer> indexBuffer;
		uint32_t indexCount;
	};
}
