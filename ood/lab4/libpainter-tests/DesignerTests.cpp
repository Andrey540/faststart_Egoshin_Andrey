#include "stdafx.h"
#include "../libpainter/Designer.h"
#include "../libpainter/PictureDraft.h"
#include "../libpainter/IShapeFactory.h"
#include "../libpainter/ShapeFactory.h"

using namespace std;
using boost::algorithm::all_of;
using boost::copy;

class CMockShape : public CShape
{
public:
	CMockShape(const string& descr)
		: CShape("red"),
		descr(descr)
	{}
	void Draw(ICanvas& canvas) override
	{
		canvas;
	}
	string descr;
};

struct MockShapeFactory : IShapeFactory
{
	vector<string> shapeDescriptions;
	// Inherited via IShapeFactory
	unique_ptr<CShape> CreateShape(const std::string & description) override
	{
		// Запротоколировали описание созданной фигуры
		shapeDescriptions.push_back(description);
		return make_unique<CMockShape>(description);
	}
};

struct Designer_
{
	MockShapeFactory factory;
	CDesigner designer = CDesigner(factory);
};

BOOST_FIXTURE_TEST_SUITE(Designer, Designer_)
	BOOST_AUTO_TEST_SUITE(when_creating_draft)
		BOOST_AUTO_TEST_CASE(returns_empty_draft_when_input_is_empty)
		{
			istringstream input;
			auto draft = designer.CreateDraft(input);
			BOOST_CHECK(draft.IsEmpty());
			BOOST_CHECK(input.eof());
		}

		struct when_creating_draft_with_non_empty_input_ : Designer_
		{
			vector<string> expectedShapeDescriptions = {
				"square", "circle", "triangle"
			};
			stringstream strm;
			CPictureDraft returnedDraft;
			when_creating_draft_with_non_empty_input_()
			{
				copy(expectedShapeDescriptions, ostream_iterator<string>(strm, "\n"));
				returnedDraft = designer.CreateDraft(strm);
			}
		};
		BOOST_FIXTURE_TEST_SUITE(when_creating_draft_with_non_empty_input, when_creating_draft_with_non_empty_input_)
			BOOST_AUTO_TEST_CASE(passes_each_line_from_input_to_shape_factory)
			{
				BOOST_CHECK(factory.shapeDescriptions == expectedShapeDescriptions);
			}
			BOOST_AUTO_TEST_CASE(returns_draft_with_shapes_created_by_factory)
			{
				vector<string> shapeDescriptions;
				std::transform(returnedDraft.begin(), returnedDraft.end(), back_inserter(shapeDescriptions), [](auto & shape) {
					auto shapeAsMockShape = dynamic_cast<const CMockShape*>(&shape);
					BOOST_REQUIRE(shapeAsMockShape);
					return shapeAsMockShape->descr;
				});
				BOOST_CHECK(shapeDescriptions == expectedShapeDescriptions);
			}
		BOOST_AUTO_TEST_SUITE_END()
	BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()


struct RealDesigner_
{
	CShapeFactory factory;
	CDesigner designer = CDesigner(factory);
};

BOOST_FIXTURE_TEST_SUITE(RealDesigner, RealDesigner_)
	BOOST_AUTO_TEST_SUITE(when_creating_draft)

		struct when_creating_draft_with_rectangle_only_ : RealDesigner_
		{
			vector<string> expectedShapeDescriptions = {
				"rectangle red 1 2 4 4"
			};
			stringstream strm;
			CPictureDraft returnedDraft;
			when_creating_draft_with_rectangle_only_()
			{
				copy(expectedShapeDescriptions, ostream_iterator<string>(strm, "\n"));
				returnedDraft = designer.CreateDraft(strm);
			}
		};

		BOOST_FIXTURE_TEST_SUITE(when_creating_draft_with_rectangle_only, when_creating_draft_with_rectangle_only_)
		BOOST_AUTO_TEST_CASE(returns_draft_with_rectangle)
		{
			auto shapesIter = returnedDraft.begin();
			auto shapeAsRectangle = dynamic_cast<const CRectangle*>(&(*shapesIter++));
			BOOST_REQUIRE(shapeAsRectangle);
		}
		BOOST_AUTO_TEST_CASE(returned_draft_has_only_one_element)
		{
			BOOST_CHECK(returnedDraft.size() == 1);
		}
		BOOST_AUTO_TEST_SUITE_END()

		struct when_creating_draft_with_real_shapes_ : RealDesigner_
		{
			vector<string> expectedShapeDescriptions = {
				"rectangle red 1 2 4 4",
				"triangle red 1 2 1 4 5 6",
				"ellipse red 1 1 2 1",
				"regularpolygon red 1 1 2 1"
			};
			stringstream strm;
			CPictureDraft returnedDraft;
			when_creating_draft_with_real_shapes_()
			{
				copy(expectedShapeDescriptions, ostream_iterator<string>(strm, "\n"));
				returnedDraft = designer.CreateDraft(strm);
			}
		};
		BOOST_FIXTURE_TEST_SUITE(when_creating_draft_with_real_shapes, when_creating_draft_with_real_shapes_)
			BOOST_AUTO_TEST_CASE(returns_draft_with_real_shapes)
			{
				auto shapesIter = returnedDraft.begin();
				auto shapeAsRectangle = dynamic_cast<const CRectangle*>(&(*shapesIter++));
				BOOST_REQUIRE(shapeAsRectangle);

				auto shapeAsTriangle = dynamic_cast<const CTriangle*>(&(*shapesIter++));
				BOOST_REQUIRE(shapeAsTriangle);

				auto shapeAsEllipse = dynamic_cast<const CEllipse*>(&(*shapesIter++));
				BOOST_REQUIRE(shapeAsEllipse);

				auto shapeAsRegularPolygon = dynamic_cast<const CRegularPolygon*>(&(*shapesIter++));
				BOOST_REQUIRE(shapeAsRegularPolygon);
			}
			BOOST_AUTO_TEST_CASE(returned_draft_with_real_shapes_has_four_elements)
			{
				BOOST_CHECK(returnedDraft.size() == 4);
			}
		BOOST_AUTO_TEST_SUITE_END()
	BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()