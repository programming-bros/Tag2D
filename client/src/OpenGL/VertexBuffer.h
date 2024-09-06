#pragma once

#include <glad/glad.h>

#include <vector>

namespace Tag2D
{
	class VertexBuffer
	{
	public:
		VertexBuffer();
		~VertexBuffer();

		void Init();
		void Bind() const;
		void Unbind() const;
		void AssignVertices(const void* data, unsigned int size);

	private:
		unsigned int m_RendererID;
	};
}