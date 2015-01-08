#include <string>

#pragma once
class CRectangle
{
public:    
    CRectangle(void);
    CRectangle(int left, int top, int width, int height);
    ~CRectangle(void);
    void SetWidth(int width);
    unsigned GetWidth() const;
    void SetHeight(int height);
    unsigned GetHeight() const;
    void SetLeft(int left);
    int GetLeft() const;
    void SetTop(int top);
    int GetTop() const;
    void SetRight(int right);
    int GetRight() const;
    void SetBottom(int bottom);
    int GetBottom() const;
    int GetArea() const;
    int GetPerimeter() const;
    void Move(int dx, int dy);
    void Scale(int sx, int sy);
    bool Intersect(CRectangle const& other);
    void Print(std::string tilte = "");

private:
    int m_Left;
    int m_Top;
    int m_Width;
    int m_Height;
};

