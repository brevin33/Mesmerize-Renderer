#pragma once
#include <Mesmerize/Renderer.h>

namespace MZ {

	void setupDefaults();

	extern UniformBufferID mainCameraBuffer;
	extern UniformBufferID cullingBuffer;
	extern ComputeShaderID cullingShader;
	extern ComputeID mainCullingCompute;
}