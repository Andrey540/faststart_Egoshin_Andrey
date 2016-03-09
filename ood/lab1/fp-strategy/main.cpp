#include <algorithm>
#include <functional>
#include <iostream>
#include <memory>
#include <cassert>
#include <vector>

using namespace std;

void flyWithWings(unsigned& sortiesCount)
{
    ++sortiesCount;
	cout << "I'm flying with wings!! It's sortie number" << sortiesCount << endl;
}
void flyNoWay(unsigned& sortiesCount)
{}
void quack()
{
    cout << "Quack Quack!!!" << endl;
}
void squeak()
{
    cout << "Quack Quack!!!" << endl;
}
void muteQuack()
{}
void danceWaltz()
{
    cout << "I'm dancing waltz!!" << endl;
}
void danceMinuet()
{
    cout << "I'm dancing minuet!!" << endl;
}
void noDance()
{}

class Duck
{
public:
	Duck(function<void(unsigned&)> fly, function<void()> quack, function<void()> dance)
		: m_fly(fly),
          m_quack(quack),
          m_dance(dance)
	{
        m_SortiesCount = 0;
	}
	void Quack() const
	{
		m_quack();
	}
	void Swim()
	{
		cout << "I'm swimming" << endl;
	}
	void Fly()
	{
		m_fly(m_SortiesCount);
	}
    void SetFlyBehavior(function<void(unsigned&)> fly)
	{
		m_fly = fly;
	}
	virtual void Dance()
	{
		m_dance();
	}
	virtual void Display() const = 0;
	virtual ~Duck() {};
private:
    function<void(unsigned&)> m_fly; 
    function<void()> m_quack;
    function<void()> m_dance;

    unsigned m_SortiesCount;
};

class MallardDuck : public Duck
{
public:
	MallardDuck()
		: Duck(flyWithWings, quack, danceWaltz)
	{
	}

	void Display() const override
	{
		cout << "I'm mallard duck" << endl;
	}
};

class RedheadDuck : public Duck
{
public:
	RedheadDuck()
		: Duck(flyWithWings, quack, danceMinuet)
	{
	}
	void Display() const override
	{
		cout << "I'm redhead duck" << endl;
	}
};
class DeckoyDuck : public Duck
{
public:
	DeckoyDuck()
		: Duck(flyNoWay, muteQuack, noDance)
	{
	}
	void Display() const override
	{
		cout << "I'm deckoy duck" << endl;
	}
	void Dance() override {}
};
class RubberDuck : public Duck
{
public:
	RubberDuck()
		: Duck(flyNoWay, squeak, noDance)
	{
	}
	void Display() const override
	{
		cout << "I'm rubber duck" << endl;
	}
	void Dance() override {}
};

class ModelDuck : public Duck
{
public:
	ModelDuck()
		: Duck(flyNoWay, quack, noDance)
	{
	}
	void Display() const override
	{
		cout << "I'm model duck" << endl;
	}
	void Dance() override {}
};

void DrawDuck(Duck const& duck)
{
	duck.Display();
}

void PlayWithDuck(Duck & duck)
{
	duck.Quack();
	duck.Dance();
	duck.Fly();
	DrawDuck(duck);
	duck.Fly();
}

void main()
{
    MallardDuck mallarDuck;
	PlayWithDuck(mallarDuck);
	RedheadDuck redheadDuck;
	PlayWithDuck(redheadDuck);
	RubberDuck rubberDuck;
	PlayWithDuck(rubberDuck);
	DeckoyDuck deckoyDuck;
	PlayWithDuck(deckoyDuck);
	ModelDuck modelDuck;
	PlayWithDuck(modelDuck);
    modelDuck.SetFlyBehavior(flyWithWings);
	PlayWithDuck(modelDuck);
}
