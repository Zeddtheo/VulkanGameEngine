#pragma once

#include "GameCamera.h"
#include "GameObject.h"
// lib
#include <vulkan/vulkan.h>

namespace misc {
	struct FrameInfo {
		int frameIndex;
		float frameTime;
		VkCommandBuffer commandBuffer;
		GameCamera& camera;
		VkDescriptorSet globalDescriptorSet;
		GameObject::Map& gameObjects;
	};
}  // namespace misc
