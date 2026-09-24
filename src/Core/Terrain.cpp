#include "Terrain.hpp"

constexpr std::uint32_t VertexCount = 128;
constexpr std::uint32_t Size = 800;

Terrain::Terrain(const glm::uvec2& grid, const std::shared_ptr<Texture>& texture) {
    const float xOffset = static_cast<float>(grid.x) * Size;
    const float zOffset = static_cast<float>(grid.y) * Size;

	std::vector<Vertex> vertices;
	vertices.reserve(VertexCount * VertexCount);

	for (std::uint32_t i = 0; i < VertexCount; i++)
		for (std::uint32_t j = 0; j < VertexCount; j++) {
			const glm::vec3 position = {
			    xOffset + static_cast<float>(j) / (static_cast<float>(VertexCount) - 1.0f) * Size,
				-5.0f,
				zOffset + static_cast<float>(i) / (static_cast<float>(VertexCount) - 1.0f) * Size
			};
			const glm::vec2 texCoords = {
			    static_cast<float>(j) / (static_cast<float>(VertexCount) - 1.0f),
				static_cast<float>(i) / (static_cast<float>(VertexCount) - 1.0f)
			};

			vertices.emplace_back(position, texCoords, texture->GetSlot());
		}

	std::vector<std::uint32_t> indices;
	indices.reserve(6 * (VertexCount - 1) * (VertexCount - 1));
	for (auto i = 0u; i < VertexCount - 1; i++) {
		for (auto j = 0u; j < VertexCount -  1; j++) {
			int topLeft = (i * VertexCount) + j;
			int topRight = topLeft + 1;
			int bottomLeft = ((i + 1) * VertexCount) + j;
			int bottomRight = bottomLeft + 1;

			indices.emplace_back(topLeft);
			indices.emplace_back(bottomLeft);
			indices.emplace_back(topRight);
			indices.emplace_back(topRight);
			indices.emplace_back(bottomLeft);
			indices.emplace_back(bottomRight);
		}
	}

	rawModel = std::make_unique<RawModel>(vertices, indices);
}
