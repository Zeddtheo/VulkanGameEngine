#pragma once

#include "GameDevice.h"
#include "GameObject.h"
#include "Gamepipeline.h"
#include "GameCamera.h"
#include "FrameInfo.h"
// std
#include <memory>
#include <vector>

namespace misc {
	class SimpleRenderSystem {
	public:
		SimpleRenderSystem(GameDevice& device, VkRenderPass renderPass, VkDescriptorSetLayout globalSetLayout);
		~SimpleRenderSystem();

		SimpleRenderSystem(const SimpleRenderSystem&) = delete;
		SimpleRenderSystem& operator=(const SimpleRenderSystem&) = delete;

		void renderGameObjects(FrameInfo& frameInfo);

	private:
		void createPipelineLayout(VkDescriptorSetLayout globalSetLayout);
		void createPipeline(VkRenderPass renderPass);

		GameDevice& myDevice;

		std::unique_ptr<GamePipeline> myPipeline;
		VkPipelineLayout pipelineLayout;
	};
}  // namespace lve