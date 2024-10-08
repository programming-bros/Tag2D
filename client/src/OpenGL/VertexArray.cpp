#include "VertexArray.h"
#include "Logger.h"

namespace Tag2D
{
	VertexArray::VertexArray() 
		: m_RendererID(0)
	{
	}

	VertexArray::~VertexArray()
	{
		// FIXME: Using glDeleteVertexArrays or glDeleteBuffers in VertexArray and VertexBuffer desctructors will delete the buffers
		//glDeleteVertexArrays(1, &m_RendererID);
	}

	void VertexArray::Init()
	{
		glGenVertexArrays(1, &m_RendererID);
		glBindVertexArray(m_RendererID);
	}

	void VertexArray::Bind() const
	{
		glBindVertexArray(m_RendererID);
	}

	void VertexArray::Unbind() const
	{
		glBindVertexArray(0);
	}

	void VertexArray::Draw() const
	{
		Bind();
		glDrawArrays(GL_TRIANGLES, 0, 3);
	}

	void VertexArray::AssingData(const VertexBuffer& vertex_buffer)
	{
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
		glEnableVertexAttribArray(0);
	}
}
