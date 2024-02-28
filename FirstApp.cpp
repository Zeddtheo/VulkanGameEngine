#include "FirstApp.h"
#include "SimpleRenderSystem.h"
#include "GameCamera.h"
#include "GameBuffer.h"
#include "KeyboardMovementController.h"
#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>

#include <array>
#include <stdexcept>
#include <chrono>

namespace misc {
    struct GlobalUbo {
        glm::mat4 projectionView{ 1.f };
        glm::vec4 ambientLightColor{ 1.f, 1.f, 1.f, .08f };//.02f  // w is intensity
        glm::vec3 lightPosition{ -1.f };
        alignas(16) glm::vec4 lightColor{ 1.f };  // w is light intensity
    };

	FirstApp::FirstApp() {
        globalPool =
            DescriptorPool::Builder(myDevice)
            .setMaxSets(GameSwapChain::MAX_FRAMES_IN_FLIGHT)
            .addPoolSize(VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, GameSwapChain::MAX_FRAMES_IN_FLIGHT)
            .build();
        loadGameObjects();
	}

	FirstApp::~FirstApp() {
		
	}

    void FirstApp::run() {
        std::vector<std::unique_ptr<GameBuffer>> uboBuffers(GameSwapChain::MAX_FRAMES_IN_FLIGHT);
        for (int i = 0; i < uboBuffers.size(); i++) {
            uboBuffers[i] = std::make_unique<GameBuffer>(
                myDevice,
                sizeof(GlobalUbo),
                1,
                VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT,
                VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT);
            uboBuffers[i]->map();
        }

        auto globalSetLayout =
            DescriptorSetLayout::Builder(myDevice)
            .addBinding(0, VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, VK_SHADER_STAGE_ALL_GRAPHICS)
            .build();

        std::vector<VkDescriptorSet> globalDescriptorSets(GameSwapChain::MAX_FRAMES_IN_FLIGHT);
        for (int i = 0; i < globalDescriptorSets.size(); i++) {
            auto bufferInfo = uboBuffers[i]->descriptorInfo();
            DescriptorWriter(*globalSetLayout, *globalPool)
                .writeBuffer(0, &bufferInfo)
                .build(globalDescriptorSets[i]);
        }

        SimpleRenderSystem simpleRenderSystem{
            myDevice,
            myRenderer.getSwapChainRenderPass(),
            globalSetLayout->getDescriptorSetLayout() };

        GameCamera camera{};

        auto viewerObject = GameObject::createGameObject();
        viewerObject.transform.translation.z = -2.5f;
        KeyboardMovementController cameraController{};

        auto currentTime = std::chrono::high_resolution_clock::now();
        while (!myWindow.shouldClose()) {
            glfwPollEvents();

            auto newTime = std::chrono::high_resolution_clock::now();
            float frameTime =
                std::chrono::duration<float, std::chrono::seconds::period>(newTime - currentTime).count();
            currentTime = newTime;

            cameraController.moveInPlaneXZ(myWindow.getGLFWwindow(), frameTime, viewerObject);
            camera.setViewYXZ(viewerObject.transform.translation, viewerObject.transform.rotation);

            float aspect = myRenderer.getAspectRatio();
            camera.setPerspectiveProjection(glm::radians(50.f), aspect, 0.1f, 100.f);

            if (auto commandBuffer = myRenderer.beginFrame()) {
                int frameIndex = myRenderer.getFrameIndex();
                FrameInfo frameInfo{
                  frameIndex,
                  frameTime,
                  commandBuffer,
                  camera,
                  globalDescriptorSets[frameIndex],
                    gameObjects };

                // update
                GlobalUbo ubo{};
                ubo.projectionView = camera.getProjection() * camera.getView();
                uboBuffers[frameIndex]->writeToBuffer(&ubo);
                uboBuffers[frameIndex]->flush();

                // render
                myRenderer.beginSwapChainRenderPass(commandBuffer);
                simpleRenderSystem.renderGameObjects(frameInfo);
                myRenderer.endSwapChainRenderPass(commandBuffer);
                myRenderer.endFrame();
            }
        }

        vkDeviceWaitIdle(myDevice.device());
    }

    void FirstApp::loadGameObjects() {
        std::shared_ptr<GameModel> myModel =
            GameModel::createModelFromFile(myDevice, "Models/smooth_vase.obj");
        auto flatVase = GameObject::createGameObject();
        flatVase.model = myModel;
        flatVase.transform.translation = { -.5f, .5f, 0.f };
        flatVase.transform.scale = { 3.f, 1.5f, 3.f };
        gameObjects.emplace(flatVase.getId(), std::move(flatVase));

        myModel = GameModel::createModelFromFile(myDevice, "Models/flat_vase.obj");
        auto smoothVase = GameObject::createGameObject();
        smoothVase.model = myModel;
        smoothVase.transform.translation = { .5f, .5f, 0.f };;
        smoothVase.transform.scale = { 3.f, 1.5f, 3.f };
        gameObjects.emplace(smoothVase.getId(), std::move(smoothVase));

        myModel = GameModel::createModelFromFile(myDevice, "Models/quad.obj");
        auto floor = GameObject::createGameObject();
        floor.model = myModel;
        floor.transform.translation = { 0.f, .5f, 0.f };
        floor.transform.scale = { 3.f, 1.f, 3.f };
        gameObjects.emplace(floor.getId(), std::move(floor));
    }
    
}  // namespace misc