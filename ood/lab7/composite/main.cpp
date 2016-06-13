#include <cstdint>
#include "Slide.h"
#include "version1.h"

int main()
{
	CCanvas canvas;
	CSlide slide;
	auto groupShape = std::make_shared<CGroupShape>();

	auto lineStyleRect = std::make_shared<CLineStyle>(12, 2);
	auto fillStyleRect = std::make_shared<CStyle>(15);
	auto rect = std::make_shared<version1::CRectangle>(lineStyleRect, fillStyleRect, RectD{ 1, 1, 4, 2 });

	auto lineStyleEllipse = std::make_shared<CLineStyle>(22, 1);
	auto fillStyleEllipse = std::make_shared<CStyle>(25);
	auto ellipse = std::make_shared<version1::CEllipse>(lineStyleEllipse, fillStyleEllipse, RectD{ 6, 1, 2, 2 });

	auto lineStyleTriangle = std::make_shared<CLineStyle>(32, 3);
	auto fillStyleTriangle = std::make_shared<CStyle>(35);
	auto triangle = std::make_shared<version1::CTriangle>(lineStyleTriangle, fillStyleTriangle, RectD{ 9, 1, 4, 2 });

	groupShape->InsertShape(rect);
	groupShape->InsertShape(ellipse);
	groupShape->InsertShape(triangle);

	auto groupFrame = groupShape->GetFrame();
	std::cout << "left: " << groupFrame.left << " top: " << groupFrame.top << " width: " << groupFrame.width << " height: " << groupFrame.height << std::endl;

	groupShape->Draw(canvas);
	std::cout << "-----------------------------------------------------------" << std::endl;

	groupShape->SetFrame({3, 0, 6, 4});
	groupShape->Draw(canvas);
	std::cout << "-----------------------------------------------------------" << std::endl;

	lineStyleRect = std::make_shared<CLineStyle>(11, 2);
	fillStyleRect = std::make_shared<CStyle>(16);
	rect = std::make_shared<version1::CRectangle>(lineStyleRect, fillStyleRect, RectD{ 1, 4, 4, 2 });

	lineStyleTriangle = std::make_shared<CLineStyle>(21, 1);
	fillStyleTriangle = std::make_shared<CStyle>(17);
	triangle = std::make_shared<version1::CTriangle>(lineStyleTriangle, fillStyleTriangle, RectD{ 9, 4, 4, 2 });

	slide.InsertShape(rect);
	slide.InsertShape(triangle);
	slide.InsertShape(groupShape);

	slide.Draw(canvas);
	std::cout << "-----------------------------------------------------------" << std::endl;

	auto lineStyleSlide = std::make_shared<CLineStyle>(42, 4);
	auto fillStyleSlide = std::make_shared<CStyle>(45);
	slide.SetOutlineStyle(lineStyleSlide);
	slide.SetFillStyle(fillStyleSlide);

	slide.Draw(canvas);
	std::cout << "-----------------------------------------------------------" << std::endl;
}
