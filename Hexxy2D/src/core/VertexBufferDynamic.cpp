#include "VertexBufferDynamic.h"
#include "Renderer.h"

VertexBufferDynamic::VertexBufferDynamic(unsigned int size)
{
    GLCall(glGenBuffers(1, &m_RendererID));
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_RendererID));
    GLCall(glBufferData(GL_ARRAY_BUFFER, size, nullptr, GL_DYNAMIC_DRAW));
}

VertexBufferDynamic::~VertexBufferDynamic()
{
    GLCall(glDeleteBuffers(1, &m_RendererID));
}

void VertexBufferDynamic::Bind() const
{
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_RendererID));
}

void VertexBufferDynamic::Unbind() const
{
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
}