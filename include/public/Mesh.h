#pragma once
#include <Vertex.h>
#include <Vertex.h>

namespace MZ {
	struct Mesh {
		std::vector<Vertex> vertices;
		std::vector<uint32_t> indices;

		void makeCircle(int subdivisions);
	};
}