#version 450

// UBO
layout(binding = 0) uniform UniformBufferObject {
    vec3 color;
} ubo;

// Camera
layout(binding = 1) uniform cameraInfo{ 
    mat4 viewproj;
} camera;

// Vertex Data
layout(location = 0) in vec3 inPosition;
layout(location = 1) in vec3 inNormal;
layout(location = 2) in vec2 inUv;
layout(location = 3) in vec3 inTangent;
layout(location = 4) in vec3 inBitangent;

// Instance Data
layout(location = 5) in mat4 inModel;


// Frag Shader Data
layout(location = 0) out vec3 fragColor;
layout(location = 1) out vec2 fragTexCoord;

void main() {
    gl_Position = camera.viewproj * inModel * vec4(inPosition, 1.0);

    fragColor = ubo.color;
    fragTexCoord = inUv;
}