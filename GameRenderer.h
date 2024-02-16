#pragma once

#include "GameDevice.h"
#include "GameSwapChain.h"
#include "GameWindow.h"

#include <cassert>
#include <memory>
#include <vector>

namespace misc {
    class GameRenderer {
    public:
        GameRenderer(GameWindow &window, GameDevice &device);
        ~GameRenderer();

        GameRenderer(const GameRenderer&) = delete;
        GameRenderer& operator=(const GameRenderer&) = delete;

        VkRenderPass getSwapChainRenderPass() const { return mySwapChain->getRenderPass(); }
        float getAspectRatio() const { return mySwapChain->extentAspectRatio(); }
        bool isFrameInProgress() const { return isFrameStarted; }

        VkCommandBuffer getCurrentCommandBuffer() const {
            assert(isFrameStarted && "Cannot get command buffer when frame not in progress");
            return commandBuffers[currentFrameIndex];
        }

        int getFrameIndex() const {
            assert(isFrameStarted && "Cannot get frame index when frame not in progress");
            return currentFrameIndex;
        }

        VkCommandBuffer beginFrame();
        void endFrame();
        void beginSwapChainRenderPass(VkCommandBuffer commandBuffer);
        void endSwapChainRenderPass(VkCommandBuffer commandBuffer);

    private:
        void createCommandBuffers();
        void freeCommandBuffers();
        void recreateSwapChain();

        GameWindow& myWindow;
        GameDevice& myDevice;
        std::unique_ptr<GameSwapChain> mySwapChain;
        std::vector<VkCommandBuffer> commandBuffers;

        uint32_t currentImageIndex;
        int currentFrameIndex{ 0 };
        bool isFrameStarted{false};
    };
}  // namespace Game