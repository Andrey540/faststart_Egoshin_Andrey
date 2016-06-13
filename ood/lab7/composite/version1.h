#pragma once
#include "Shape.h"

namespace version1
{
class CRectangle : public CShape
{
public:
	CRectangle(std::shared_ptr<ILineStyle> lineStyle, std::shared_ptr<IStyle> fillStyle, RectD rect)
		: CShape(lineStyle, fillStyle, rect)
	{}
	
	void Draw(ICanvas & canvas) final
	{
		auto rect = GetFrame();
		auto lineStyle = GetOutlineStyle();
		if (lineStyle->IsEnabled())
		{
			canvas.SetLineColor(*lineStyle->GetColor());
			canvas.SetLineWidth(lineStyle->GetLineWidth());
		}
		auto fillStyle = GetFillStyle();
		if (fillStyle->IsEnabled())
		{
			canvas.BeginFill(*fillStyle->GetColor());
		}
		canvas.MoveTo(rect.left, rect.top);
		canvas.LineTo(rect.left, rect.top + rect.height);
		canvas.LineTo(rect.left + rect.width, rect.top + rect.height);
		canvas.LineTo(rect.left + rect.width, rect.top);
		canvas.LineTo(rect.left, rect.top);
		if (fillStyle->IsEnabled())
		{
			canvas.EndFill();
		}
	}
};

class CEllipse : public CShape
{
public:
	CEllipse(std::shared_ptr<ILineStyle> lineStyle, std::shared_ptr<IStyle> fillStyle, RectD rect)
		: CShape(lineStyle, fillStyle, rect)
	{}
	void Draw(ICanvas & canvas) final
	{
		auto rect = GetFrame();
		auto lineStyle = GetOutlineStyle();
		if (lineStyle->IsEnabled())
		{
			canvas.SetLineColor(*lineStyle->GetColor());
			canvas.SetLineWidth(lineStyle->GetLineWidth());
		}
		auto fillStyle = GetFillStyle();
		if (fillStyle->IsEnabled())
		{
			canvas.BeginFill(*fillStyle->GetColor());
		}
		canvas.MoveTo(rect.top, rect.left);
		canvas.DrawEllipse(rect.left, rect.top, rect.width, rect.height);
		{
			canvas.EndFill();
		}
	}
};

class CTriangle : public CShape
{
public:
	CTriangle(std::shared_ptr<ILineStyle> lineStyle, std::shared_ptr<IStyle> fillStyle, RectD rect)
		: CShape(lineStyle, fillStyle, rect)
	{}
	void Draw(ICanvas & canvas) final
	{
		auto rect = GetFrame();
		auto lineStyle = GetOutlineStyle();
		if (lineStyle->IsEnabled())
		{
			canvas.SetLineColor(*lineStyle->GetColor());
			canvas.SetLineWidth(lineStyle->GetLineWidth());
		}
		auto fillStyle = GetFillStyle();
		if (fillStyle->IsEnabled())
		{
			canvas.BeginFill(*fillStyle->GetColor());
		}
		canvas.MoveTo(rect.left, rect.top);
		canvas.LineTo(rect.left, rect.top + rect.height);
		canvas.LineTo(rect.left + rect.width, rect.top + rect.height);
		canvas.LineTo(rect.left, rect.top);
		if (fillStyle->IsEnabled())
		{
			canvas.EndFill();
		}
	}
};
}