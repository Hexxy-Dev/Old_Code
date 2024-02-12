#pragma once

class VertexBufferDynamic
{
private:
	unsigned int m_RendererID;
public:
	VertexBufferDynamic(unsigned int size);
	~VertexBufferDynamic();

	void Bind() const;
	void Unbind() const;
};