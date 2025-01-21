#pragma once
#define GLFW_INCLUDE_VULKAN
#include "vulkan/vulkan.hpp"
#include <glfw3.h>
#include <stdexcept>
#include <vector>
#include <set>
#include "VulkanUtilities.h"

struct {
	vk::PhysicalDevice physicalDevice;
	vk::Device logicalDevice;
} mainDevice;

struct MVP {
	glm::mat4 projection;
	glm::mat4 view;
	glm::mat4 model;
};

class VulkanRenderer
{
public:
	VulkanRenderer();
	~VulkanRenderer();
	int init(GLFWwindow* windowP);
	void createInstance();
	bool checkInstanceExtensionSupport(const std::vector<const char*>& checkExtensions);
	void clean();
	void draw();


#ifdef NDEBUG
	static const bool enableValidationLayers = false;
#else
	static const bool enableValidationLayers = true;
#endif
	static const std::vector<const char*> validationLayers;

private:
	void getPhysicalDevice();
	bool checkDeviceSuitable(vk::PhysicalDevice device);
	QueueFamilyIndices getQueueFamilies(vk::PhysicalDevice device);
	void createLogicalDevice();
	bool checkValidationLayerSupport();
	std::vector<const char*> getRequiredExtensions();
	VkResult createDebugUtilsMessengerEXT(VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDebugUtilsMessengerEXT* pDebugMessenger);
	void destroyDebugUtilsMessengerEXT(VkInstance instance, VkDebugUtilsMessengerEXT debugMessenger, const VkAllocationCallbacks* pAllocator);
	void populateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& createInfo);
	void setupDebugMessenger();
	GLFWwindow* window;
	vk::Instance instance;
	vk::Queue graphicsQueue;
	VkDebugUtilsMessengerEXT debugMessenger;

	vk::SurfaceKHR surface;
	vk::Queue presentationQueue;
	vk::SurfaceKHR createSurface();
	bool checkDeviceExtensionSupport(vk::PhysicalDevice device);
	SwapchainDetails getSwapchainDetails(vk::PhysicalDevice device);
	void createSwapchain();
	vk::SurfaceFormatKHR chooseBestSurfaceFormat(const std::vector<vk::SurfaceFormatKHR>& formats);
	vk::PresentModeKHR chooseBestPresentationMode(const std::vector<vk::PresentModeKHR>& presentationModes);
	vk::Extent2D chooseSwapExtent(const vk::SurfaceCapabilitiesKHR& surfaceCapabilities);

	vk::ImageView createImageView(vk::Image image, vk::Format format, vk::ImageAspectFlagBits aspectFlags);
	void createGraphicsPipeline();
	VkShaderModule createShaderModule(const std::vector<char>& code);

	vk::Format swapchainImageFormat;
	vk::Extent2D swapchainExtent;

	std::vector<SwapchainImage> swapchainImages;

	vk::SwapchainKHR swapchain;

	vk::PipelineLayout pipelineLayout;

	void createRenderPass();
	vk::RenderPass renderPass;
	vk::Pipeline graphicsPipeline;

	std::vector<vk::Framebuffer> swapchainFramebuffers;
	void createFramebuffers();

	vk::CommandPool graphicsCommandPool;
	void createGraphicsCommandPool();

	std::vector<vk::CommandBuffer> commandBuffers;
	void createGraphicsCommandBuffers();
	void recordCommands();


	std::vector<vk::Semaphore> imageAvailable;
	std::vector<vk::Semaphore> renderFinished;
	const int MAX_FRAME_DRAWS = 2;
	void createSynchronisation();

	int currentFrame = 0;

	std::vector<vk::Fence> drawFences;

	vk::PipelineVertexInputStateCreateInfo vertexInputCreateInfo{};
	vk::PipelineInputAssemblyStateCreateInfo inputAssemblyCreateInfo{};
	vk::PipelineViewportStateCreateInfo viewportStateCreateInfo{};
	vk::PipelineRasterizationStateCreateInfo rasterizerCreateInfo{};
	vk::PipelineMultisampleStateCreateInfo multisamplingCreateInfo{};
	vk::PipelineColorBlendStateCreateInfo colorBlendingCreateInfo{};

	std::vector<class VulkanMesh> meshes;

	MVP mvp;
	vk::DescriptorSetLayout descriptorSetLayout;
	void createDescriptorSetLayout();

	std::vector<vk::Buffer> uniformBuffer;
	std::vector<vk::DeviceMemory> uniformBufferMemory;
	void createUniformBuffers();
	
	vk::DescriptorPool descriptorPool;
	void createDescriptorPool();

	std::vector<vk::DescriptorSet> descriptorSets;
	void createDescriptorSets();
	void updateUniformBuffer(uint32_t imageIndex);
};