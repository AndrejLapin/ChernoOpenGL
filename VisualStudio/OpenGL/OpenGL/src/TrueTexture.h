#pragma once

#include "Renderer.h"
#include <string>

class TrueTexture
{
private:
    unsigned int m_RendererID;
    std::string m_FilePath;
    unsigned char* m_LocalBuffer;
    int m_Width, m_Height, m_BPP;
public:
    TrueTexture(const std::string& path);
    ~TrueTexture();

    void Bind(unsigned int slot = 0) const;
    void Unbind() const;

    inline int GetWidth() const { return m_Width; }
    inline int GetHeight() const { return m_Height; }
    inline unsigned int GetRendererId() const { return m_RendererID; }
};

