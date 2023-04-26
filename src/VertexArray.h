#pragma once

class VertexBuffer;
class VertexBufferLayout;

class VertexArray
{
protected:
	unsigned int m_RendererID;
public:
	VertexArray();
	~VertexArray();

	virtual void AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout);

	virtual void Bind() const;
	virtual void Unbind() const;
};

