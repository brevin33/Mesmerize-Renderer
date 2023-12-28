#include <GenericRenderer/DefaultRenderer.h>

namespace MZ {
	RenderObjectID addRenderObject(MaterialID material, VertexBufferID vertexBuffer, IndexBufferID indexBuffer, BoundingSphere boundingSphere) {
		RenderObjectID i = addRenderObject(material, vertexBuffer, indexBuffer);
		addToCullingBuffer(boundingSphere, i);
		return i;
	}
	RenderObjectID addRenderObject(MaterialID material, VertexBufferID vertexBuffer, IndexBufferID indexBuffer, VertexBufferID instanceBuffer, BoundingSphere boundingSphere) {
		RenderObjectID i = addRenderObject(material, vertexBuffer, indexBuffer, instanceBuffer);
		addToCullingBuffer(boundingSphere, i);
		return i;
	}

}
