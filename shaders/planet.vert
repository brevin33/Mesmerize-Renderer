#version 450

layout(binding = 0) uniform UniformBufferObject {
    mat4 model;
} ubo;

layout(binding = 1) uniform cameraInfo{ 
    mat4 viewproj;
} camera;

layout(location = 0) in vec3 inPosition;
layout(location = 1) in vec3 inNormal;
layout(location = 2) in vec2 inUv;
layout(location = 3) in vec3 inTangent;
layout(location = 4) in vec3 inBitangent;

layout(location = 0) out vec3 fragColor;
layout(location = 1) out vec2 fragTexCoord;

void main() {   
    gl_Position = camera.viewproj * ubo.model * vec4(inPosition, 1.0);

    fragColor = vec3(1,1,1);
    fragTexCoord = inUv;
}