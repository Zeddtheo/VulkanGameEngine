#include "FirstApp.h"
#include "SimpleRenderSystem.h"

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>

#include <array>
#include <stdexcept>

namespace misc {
	FirstApp::FirstApp() {
		loadGameObjects();
	}

	FirstApp::~FirstApp() {
		
	}

	void FirstApp::run() {
		SimpleRenderSystem simpleRenderSystem(myDevice, myRenderer.getSwapChainRenderPass());
		while (!myWindow.shouldClose()) {
			glfwPollEvents();
			if(auto commandBuffer = myRenderer.beginFrame()){
				myRenderer.beginSwapChainRenderPass(commandBuffer);
				simpleRenderSystem.renderGameObjects(commandBuffer, gameObjects);
				myRenderer.endSwapChainRenderPass(commandBuffer);
				myRenderer.endFrame();
			}
		}
		vkDeviceWaitIdle(myDevice.device());
	}

	void FirstApp::loadGameObjects(){
		std::vector<GameModel::Vertex> vertices{
	 {{0.0f, -0.5f}, {1.0f, 0.0f, 0.0f}},
	 {{0.5f, 0.5f}, {0.0f, 1.0f, 0.0f}},
	 {{-0.5f, 0.5f}, {0.0f, 0.0f, 1.0f}} };
		auto gameModel = std::make_shared<GameModel>(myDevice, vertices);

		auto triangle = GameObject::createGameObject();
		triangle.model = gameModel;
		triangle.color = { .1f, .8f, .1f };
		triangle.transform2d.translation.x = .2f;
		triangle.transform2d.scale = { 2.f, .5f };
		triangle.transform2d.rotation = .25f * glm::two_pi<float>();

		gameObjects.push_back(std::move(triangle));

	}

}  // namespace misc