#include "stdafx.h"
#include "Rectangle.h"
#include <string>
#include <iostream>

using namespace std;

CRectangle::CRectangle(int left, int top, int width, int height)
          : m_Left(left),
            m_Top(top)
{
    SetWidth(width);
    SetHeight(height);
}

CRectangle::CRectangle(void)
          : m_Left(0),
            m_Top(0),
            m_Width(0),
            m_Height(0)
{}

CRectangle::~CRectangle(void)
{
}

void CRectangle::SetWidth(int width)
{
    m_Width = (width > 0) ? width : 0;
}

unsigned CRectangle::GetWidth() const
{
    return m_Width;
}

void CRectangle::SetHeight(int height)
{
    m_Height = (height > 0) ? height : 0;
}

unsigned CRectangle::GetHeight() const
{
    return m_Height;
}

void CRectangle::SetLeft(int left)
{
    m_Left = left;
}

int CRectangle::GetLeft() const
{
    return m_Left;
}

void CRectangle::SetTop(int top)
{
    m_Top = top;
}

int CRectangle::GetTop() const
{
    return m_Top;
}

void CRectangle::SetRight(int right)
{
    m_Width = (right > m_Left) ? (right - m_Left) : 0;
}

int CRectangle::GetRight() const
{
    return m_Left + m_Width;
}

void CRectangle::SetBottom(int bottom)
{
    m_Height = (bottom > m_Top) ? (bottom - m_Top) : 0;
}

int CRectangle::GetBottom() const
{
    return m_Top + m_Height;
}

int CRectangle::GetArea() const
{
    return m_Width * m_Height;
}

int CRectangle::GetPerimeter() const
{
    return (m_Width * 2) + (m_Height * 2);
}

void CRectangle::Move(int dx, int dy)
{
    m_Left += dx;
    m_Top += dy;
}

void CRectangle::Scale(int sx, int sy)
{
    if (sx < 0 || sy < 0)
    {
        return;
    }

    m_Width *= sx;
    m_Height *= sy;
}

bool CRectangle::Intersect(CRectangle const& other)
{
    bool result = false;
    int otherLeft = other.GetLeft();
    int otherRight = other.GetLeft() + other.GetWidth();
    int otherTop = other.GetTop();
    int otherBottom = other.GetTop() + other.GetHeight();

    if (((m_Left <= otherLeft && (m_Left + m_Width) >= otherLeft) ||
         (m_Left <= otherRight && (m_Left + m_Width) >= otherRight) ||
         (m_Left >= otherLeft && (m_Left + m_Width) <= otherRight)) &&
        ((m_Top <= otherTop && (m_Top + m_Height) >= otherTop) ||
         (m_Top <= otherBottom && (m_Top + m_Height) >= otherBottom) ||
         (m_Top >= otherTop && (m_Top + m_Height) <= otherBottom)))
    {
        result = true;        
        int right  = (m_Left + m_Width < otherRight) ? (m_Left + m_Width) : otherRight;
        int bottom = (m_Top + m_Height < otherBottom) ? (m_Top + m_Height) : otherBottom;
        m_Left = (m_Left > otherLeft) ? m_Left : otherLeft;
        m_Top  = (m_Top > otherTop) ? m_Top : otherTop;
        m_Width  = right - m_Left;
        m_Height = bottom - m_Top;
    }
    else
    {
        m_Width = 0;
        m_Height = 0;
    }

    return result;
}

void CRectangle::Print(string title)
{
    char* indent = "    ";
    cout << title << endl;
    cout << indent << "Left top: (" << m_Left << "; " << m_Top << " )" << endl;
    cout << indent << "Size: " << m_Width << "*" << m_Height << endl;
    cout << indent << "Right bottom: (" << GetRight() << "; " << GetBottom() << " )" << endl;
    cout << indent << "Area: " << GetArea() << endl;
    cout << indent << "Perimeter: " << GetPerimeter() << endl;
    return;
}

