#include <iostream>
#include <stdexcept>
#include <string>
#include <boost/format.hpp>
#include <cstdint>
#include <iomanip>

using namespace std;

// Пространство имен графической библиотеки (недоступно для изменения)
namespace graphics_lib
{
// Холст для рисования
class ICanvas
{
public:
	virtual void SetColor(uint32_t rgbColor) = 0;
	virtual void MoveTo(int x, int y) = 0;
	virtual void LineTo(int x, int y) = 0;
	virtual ~ICanvas() = default;
};

// Реализация холста для рисования
class CCanvas : public ICanvas
{
public:
	void MoveTo(int x, int y) override
	{
		cout << "MoveTo (" << x << ", " << y << ")" << endl;
	}
	void LineTo(int x, int y) override
	{
		cout << "LineTo (" << x << ", " << y << ")" << endl;
	}
	void SetColor(uint32_t rgbColor) override
	{
		cout << "SetColor(#";
		cout << std::hex << setw(8) << setfill('0') << rgbColor;
		cout << ")" << std::endl;
	}
};
}

// Пространство имен библиотеки для рисования фигур (использует graphics_lib)
// Код библиотеки недоступен для изменения
namespace shape_drawing_lib
{
struct Point
{
	int x;
	int y;
};

// Интерфейс объектов, которые могут быть нарисованы на холсте из graphics_lib
class ICanvasDrawable
{
public:
	virtual void Draw(graphics_lib::ICanvas & canvas)const = 0;
	virtual ~ICanvasDrawable() = default;
};

class CTriangle : public ICanvasDrawable
{
public:
	CTriangle(const Point & p1, const Point & p2, const Point & p3)
		: m_p1(p1),
		  m_p2(p2),
		  m_p3(p3)
	{}

	void Draw(graphics_lib::ICanvas & canvas)const override
	{
		canvas.MoveTo(m_p1.x, m_p1.y);
		canvas.LineTo(m_p2.x, m_p2.y);
		canvas.LineTo(m_p3.x, m_p3.y);
		canvas.LineTo(m_p1.x, m_p1.y);
	}
private:
	const Point m_p1;
	const Point m_p2;
	const Point m_p3;
};

class CRectangle : public ICanvasDrawable
{
public:
	CRectangle(const Point & leftTop, int width, int height)
		: m_leftTop(leftTop),
		  m_width(width),
		  m_height(height)
	{}

	void Draw(graphics_lib::ICanvas & canvas)const override
	{
		canvas.MoveTo(m_leftTop.x, m_leftTop.y);
		canvas.LineTo(m_leftTop.x, m_leftTop.y + m_height);
		canvas.LineTo(m_leftTop.x + m_width, m_leftTop.y + m_height);
		canvas.LineTo(m_leftTop.x + m_width, m_leftTop.y);
		canvas.LineTo(m_leftTop.x, m_leftTop.y);
	}
private:
	const Point m_leftTop;
	int m_width;
	int m_height;
};

// Художник, способный рисовать ICanvasDrawable-объекты на ICanvas
class CCanvasPainter
{
public:
	CCanvasPainter(graphics_lib::ICanvas & canvas)
		: m_canvas(canvas)
	{}

	void SetColor(uint32_t color)
	{
		m_canvas.SetColor(color);
	}
	void Draw(const ICanvasDrawable & drawable)
	{
		drawable.Draw(m_canvas);
	}
private:
	graphics_lib::ICanvas & m_canvas;
};
}

// Пространство имен современной графической библиотеки (недоступно для изменения)
namespace modern_graphics_lib
{
class CPoint
{
public:
	CPoint(int x, int y) :x(x), y(y) {}

	int x;
	int y;
};

// Цвет в формате RGBA, каждый компонент принимает значения от 0.0f до 1.0f
class CRGBAColor
{
public:
	CRGBAColor(float r, float g, float b, float a) :r(r), g(g), b(b), a(a) {}
	float r, g, b, a;
};

// Класс для современного рисования графики
class CModernGraphicsRenderer
{
public:
	CModernGraphicsRenderer(ostream & strm) : m_out(strm)
	{
	}

	~CModernGraphicsRenderer()
	{
		if (m_drawing) // Завершаем рисование, если оно было начато
		{
			EndDraw();
		}
	}

	// Этот метод должен быть вызван в начале рисования
	void BeginDraw()
	{
		if (m_drawing)
		{
			throw logic_error("Drawing has already begun");
		}
		m_out << "<draw>" << endl;
		m_drawing = true;
	}

	// Выполняет рисование линии
	void DrawLine(const CPoint & start, const CPoint & end, const CRGBAColor& color)
	{
		if (!m_drawing)
		{
			throw logic_error("DrawLine is allowed between BeginDraw()/EndDraw() only");
		}
		m_out << boost::format(R"(<line fromX="%1%" fromY="%2%" toX="%3%" toY="%4%"/>)") %start.x %start.y %end.x %end.y << endl;
		m_out << boost::format(R"(  <color r="%1%" g="%2%" b="%3%" a="%4%"/>)") %color.r %color.g %color.b %color.a << endl;
		m_out << "</line>" << endl;
	}

	// Этот метод должен быть вызван в конце рисования
	void EndDraw()
	{
		if (!m_drawing)
		{
			throw logic_error("Drawing has not been started");
		}
		m_out << "</draw>" << endl;
		m_drawing = false;
	}
private:
	ostream & m_out;
	bool m_drawing = false;
};
}

// Пространство имен приложения (доступно для модификации)
namespace app
{
void PaintPicture(shape_drawing_lib::CCanvasPainter & painter)
{
	using namespace shape_drawing_lib;

	CTriangle triangle({ 10, 15 }, { 100, 200 }, { 150, 250 });
	CRectangle rectangle({ 30, 40 }, 18, 24);

	painter.SetColor(25);
	painter.Draw(rectangle);
	painter.SetColor(1125);
	painter.Draw(triangle);
}

void PaintPictureOnCanvas()
{
	graphics_lib::CCanvas simpleCanvas;
	shape_drawing_lib::CCanvasPainter painter(simpleCanvas);
	PaintPicture(painter);
}

class CModernCanvasAdapter : public graphics_lib::ICanvas
{
public:
	CModernCanvasAdapter(modern_graphics_lib::CModernGraphicsRenderer & renderer)
		: m_renderer(renderer),
		  m_startPosition(0, 0),
		  m_color(0, 0, 0, 1)
	{
		m_renderer.BeginDraw();
	}
	~CModernCanvasAdapter()
	{
		m_renderer.EndDraw();
	}
	void SetColor(uint32_t rgbColor) override
	{
		uint32_t color = rgbColor;
		static const uint32_t MAX_CCOLOR_VALUE = 255;
		m_color.b = (float)(color % 256) / MAX_CCOLOR_VALUE;
		color /= 256;
		m_color.g = (float)(color % 256) / MAX_CCOLOR_VALUE;
		color /= 256;
		m_color.r = (float)(color % 256) / MAX_CCOLOR_VALUE;
		color /= 256;		
	}
	void MoveTo(int x, int y) override
	{
		m_startPosition = {x, y};
	}
	void LineTo(int x, int y) override
	{
		m_renderer.DrawLine(m_startPosition, {x, y}, m_color);
		m_startPosition = { x, y };
	}
private:
	modern_graphics_lib::CModernGraphicsRenderer& m_renderer;
	modern_graphics_lib::CPoint m_startPosition;
	modern_graphics_lib::CRGBAColor m_color;
};

class CModernCanvasInheritableAdapter : public graphics_lib::ICanvas, private modern_graphics_lib::CModernGraphicsRenderer
{
public:
	CModernCanvasInheritableAdapter(ostream & strm)
	    : modern_graphics_lib::CModernGraphicsRenderer(strm),
		  m_startPosition(0, 0),
	      m_color(0, 0, 0, 1)
	{
		BeginDraw();
	}
	~CModernCanvasInheritableAdapter()
	{
		EndDraw();
	}
	void SetColor(uint32_t rgbColor) override
	{
		uint32_t color = rgbColor;
		static const uint32_t MAX_CCOLOR_VALUE = 255;
		m_color.b = (float)(color % 256) / MAX_CCOLOR_VALUE;
		color /= 256;
		m_color.g = (float)(color % 256) / MAX_CCOLOR_VALUE;
		color /= 256;
		m_color.r = (float)(color % 256) / MAX_CCOLOR_VALUE;
		color /= 256;
	}
	void MoveTo(int x, int y) override
	{
		m_startPosition = { x, y };
	}
	void LineTo(int x, int y) override
	{
		DrawLine(m_startPosition, { x, y }, m_color);
		m_startPosition = { x, y };
	}
private:
	modern_graphics_lib::CPoint m_startPosition;
	modern_graphics_lib::CRGBAColor m_color;
};

void PaintPictureOnModernGraphicsRenderer()
{
	/*modern_graphics_lib::CModernGraphicsRenderer renderer(cout);
	auto canvasAdapter = CModernCanvasAdapter(renderer);
	shape_drawing_lib::CCanvasPainter painter(canvasAdapter);
	PaintPicture(painter);*/

	auto canvasAdapter = CModernCanvasInheritableAdapter(cout);
	shape_drawing_lib::CCanvasPainter painter(canvasAdapter);
	PaintPicture(painter);
}
}

int main()
{
	cout << "Should we use new API (y)?";
	string userInput;
	if (getline(cin, userInput) && (userInput == "y" || userInput == "Y"))
	{
		app::PaintPictureOnModernGraphicsRenderer();
	}
	else
	{
		app::PaintPictureOnCanvas();
	}

	return 0;
}
