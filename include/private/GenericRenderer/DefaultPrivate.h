#pragma once
#include <Mesmerize/Renderer.h>
#include <pch.h>



namespace MZ {

	void createCullingBuffer();

	void createMainCameraBuffer();

	void addToCullingBuffer(BoundingSphere& boundingSphere, RenderObjectID renderObjectID);

	ComputeID createCullingCompute(UniformBufferID cameraBuffer);
}