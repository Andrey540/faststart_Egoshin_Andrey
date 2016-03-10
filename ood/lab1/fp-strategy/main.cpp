#include <algorithm>
#include <functional>
#include <iostream>
#include <memory>
#include <cassert>
#include <vector>

using namespace std;

class FlyWithWings
{
public:
	void operator ()()
	{
		cout << "I'm flying with wings!! It is sortie number" << ++m_sortiesCount << endl;
	}
private:
	size_t m_sortiesCount = 0;
};

void FlyNoWayFunc()
{}
void QuackFunc()
{
    cout << "Quack Quack!!!" << endl;
}
void SqueakFunc()
{
    cout << "Quack Quack!!!" << endl;
}
void MuteQuackFunc()
{}
void DanceWaltzFunc()
{
    cout << "I'm dancing waltz!!" << endl;
}
void DanceMinuetFunc()
{
    cout << "I'm dancing minuet!!" << endl;
}
void NoDanceFunc()
{}

class Duck
{
public:
	Duck(function<void()> fly, function<void()> quack, function<void()> dance)
		: m_fly(fly),
          m_quack(quack),
          m_dance(dance)
	{}
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
		m_fly();
	}
    void SetFlyBehavior(function<void()> fly)
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
    function<void()> m_fly; 
    function<void()> m_quack;
    function<void()> m_dance;
};

class MallardDuck : public Duck
{
public:
	MallardDuck()
		: Duck(FlyWithWings(), QuackFunc, DanceWaltzFunc)
	{}
	void Display() const override
	{
		cout << "I'm mallard duck" << endl;
	}
};

class RedheadDuck : public Duck
{
public:
	RedheadDuck()
		: Duck(FlyWithWings(), QuackFunc, DanceMinuetFunc)
	{}
	void Display() const override
	{
		cout << "I'm redhead duck" << endl;
	}
};
class DeckoyDuck : public Duck
{
public:
	DeckoyDuck()
		: Duck(FlyNoWayFunc, MuteQuackFunc, NoDanceFunc)
	{}
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
		: Duck(FlyNoWayFunc, SqueakFunc, NoDanceFunc)
	{}
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
		: Duck(FlyNoWayFunc, QuackFunc, NoDanceFunc)
	{}
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
	modelDuck.SetFlyBehavior(FlyWithWings());
	PlayWithDuck(modelDuck);
}
