#pragma once

#include "Renderer.h"
#include <string>

class Texture
{
public:
    enum FilteringType : unsigned int
    {
        UNDEFINED = 0,
        LINEAR = GL_LINEAR,
        NEAREST = GL_NEAREST,
    };
protected:
    unsigned int m_RendererID;
    std::string m_FilePath;
    unsigned char* m_LocalBuffer;
    int m_Width, m_Height, m_BPP;
public:
    Texture(const std::string& path, FilteringType filtering = LINEAR);
    ~Texture();

    void Bind(unsigned int slot = 0) const;
    void Unbind() const;

    inline int GetWidth() const { return m_Width; }
    inline int GetHeight() const { return m_Height; }
    inline unsigned int GetRendererId() const { return m_RendererID; }
};

