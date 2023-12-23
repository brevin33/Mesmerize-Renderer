#include <GLFW/glfw3.h>
#include <Mesmerize/Renderer.h>
#include "Model.h"

constexpr int WIDTH = 1920;
constexpr int HEIGHT = 1080;



void spin(MZ::VertexBufferID instanceBuffer) {
	static auto startTime = std::chrono::high_resolution_clock::now();

	auto currentTime = std::chrono::high_resolution_clock::now();
	float time = std::chrono::duration<float, std::chrono::seconds::period>(currentTime - startTime).count();

	glm::mat4 model = glm::rotate(glm::mat4(1.0f), time * glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
	MZ::updateCPUMutVertexBuffer(instanceBuffer, &model, sizeof(glm::mat4));
}

void updateCamera(MZ::UniformBufferID cameraBuffer) {
	glm::mat4 view = glm::lookAt(glm::vec3(2.0f, 2.0f, 2.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
	glm::mat4 proj = glm::perspective(glm::radians(45.0f), MZ::getRenderWidth() / (float)MZ::getRenderHeight(), 0.1f, 10.0f);
	proj[1][1] *= -1;
	view = proj * view;
	MZ::updateCPUMutUniformBuffer(cameraBuffer,&view, sizeof(glm::mat4));
}


void main() {
	glfwInit();

	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, GraphicsAPI, nullptr, nullptr);
	MZ::setup(window);

	//loading shader
	std::vector<MZ::VertexValueType> vertValues = Vertex::getVertexValueTypes();
	MZ::VertexValueType instanceValue = MZ::VTfloat4x4;
	MZ::ShaderID unlitShader = MZ::createShader("../../../shaders/unlitVert.spv", "../../../shaders/unlitFrag.spv", 1, 1, 1, vertValues.data(), vertValues.size(), &instanceValue, 1);

	//creating camera buffer
	glm::mat4 view = glm::lookAt(glm::vec3(2.0f, 2.0f, 2.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
	glm::mat4 proj = glm::perspective(glm::radians(45.0f), MZ::getRenderWidth() / (float)MZ::getRenderHeight(), 0.1f, 10.0f);
	proj[1][1] *= -1;
	glm::mat4 viewPerspectiveMatrix = proj * view;
	MZ::UniformBufferID cameraBuffer = MZ::createCPUMutUniformBuffer(&viewPerspectiveMatrix, sizeof(glm::mat4));

	// load model from file
	Model backpack("../../../models/backpack/backpack.obj");

	// loading model Textures
	std::unordered_map<std::string, MZ::TextureID> pathToTexture;
	std::vector<std::vector<MZ::TextureID>> backpackTextures(backpack.modelTextures.size());
	for (size_t i = 0; i < backpack.modelTextures.size(); i++)
	{
		for (size_t j = 0; j < backpack.modelTextures[i].size(); j++)
		{
			std::string path = backpack.modelTextures[i][j];
			if (pathToTexture.find(path) != pathToTexture.end()) {
				backpackTextures[i].push_back(pathToTexture[path]);
				continue;
			}
			MZ::TextureID textureID = MZ::createTexture(path);
			pathToTexture[path] = textureID;
			backpackTextures[i].push_back(textureID);
		}
	}

	//creating material
	std::unordered_map<uint32_t, MZ::MaterialID> assimpMaterialToMZMaterial;
	std::vector<MZ::MaterialID> backpackMaterials;
	for (size_t i = 0; i < backpack.assimpMaterialID.size(); i++)
	{
		uint32_t assimpMat = backpack.assimpMaterialID[i];
		if (assimpMaterialToMZMaterial.find(assimpMat) != assimpMaterialToMZMaterial.end()) {
			backpackMaterials.push_back(assimpMaterialToMZMaterial[assimpMat]);
			continue;
		}
		MZ::MaterialID matID = MZ::createMaterial(unlitShader, backpackTextures[i].data(), backpackTextures[i].size(), &cameraBuffer, 1);
		backpackMaterials.push_back(matID);
		assimpMaterialToMZMaterial[assimpMat] = matID;
	}

	//loading Vertices and Indices
	std::vector<MZ::VertexBufferID> backpackVertexBuffers;
	std::vector<MZ::IndexBufferID> backpackIndexBuffers;
	for (size_t i = 0; i < backpack.modelVertices.size(); i++)
	{
		backpackVertexBuffers.push_back(MZ::createVertexBuffer(backpack.modelVertices[i].data(), backpack.modelVertices[i].size(), sizeof(Vertex) * backpack.modelVertices[i].size()));
		backpackIndexBuffers.push_back(MZ::createIndexBuffer(backpack.modelIndices[i].data(), backpack.modelIndices[i].size() * sizeof(uint32_t)));
	}

	//creating a instance Buffer
	glm::mat4 modelMatrix = glm::mat4(1);
	MZ::VertexBufferID instanceBuffer = MZ::createCPUMutVertexBuffer(&modelMatrix, 1, sizeof(glm::mat4), sizeof(glm::mat4));

	//telling the renderer to render backpack
	for (size_t i = 0; i < backpack.modelVertices.size(); i++)
	{
		MZ::addRenderObject(backpackMaterials[i], backpackVertexBuffers[i], backpackIndexBuffers[i], instanceBuffer);
	}

	backpack.unload();

	while (!glfwWindowShouldClose(window)) {
		glfwPollEvents();
		
		spin(instanceBuffer);

		MZ::drawFrame();
	}

	MZ::cleanup();
	glfwDestroyWindow(window);
}