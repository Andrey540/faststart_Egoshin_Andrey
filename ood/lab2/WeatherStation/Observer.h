#pragma once

#include <vector>
#include <iterator>
#include <functional>

class IProvidableName
{
public:
	virtual ~IProvidableName() = default;
	virtual const std::string& GetName() const = 0;
};

/*
Шаблонный интерфейс IObserver. Его должен реализовывать класс, 
желающий получать уведомления от соответствующего IObservable
Параметром шаблона является тип аргумента,
передаваемого Наблюдателю в метод Update
*/
template <typename T>
class IObserver
{
public:
	virtual void Update(T const& data, const IProvidableName & providableName) = 0;
	virtual void GetInterestData(T & info) const = 0;
	virtual ~IObserver() = default;
};

/*
Шаблонный интерфейс IObservable. Позволяет подписаться и отписаться на оповещения, а также
инициировать рассылку уведомлений зарегистрированным наблюдателям.
*/
template <typename T>
class IObservable
{
public:
	virtual ~IObservable() = default;
	virtual void RegisterObserver(IObserver<T> & observer, int priority) = 0;
	virtual void NotifyObservers() = 0;
	virtual void RemoveObserver(IObserver<T> & observer) = 0;
};

// Реализация интерфейса IObservable
template <class T>
class CObservable : public IObservable<T>, public IProvidableName
{
public:
	CObservable(std::string && name = "") : m_name(move(name)) {}
	typedef IObserver<T> ObserverType;
	typedef std::pair<ObserverType *, int> ObserverRecord;

	void RegisterObserver(ObserverType & observer, int priority = 0) override
	{
		auto iter = std::find_if(m_observers.begin(), m_observers.end(), [&observer](ObserverRecord const & a) {
			return std::addressof(*a.first) == std::addressof(observer);
		});
		if (iter == m_observers.end())
		{
			m_observers.push_back(ObserverRecord(&observer, priority));
			std::sort(m_observers.begin(), m_observers.end(), [](ObserverRecord const & a, ObserverRecord const & b){
				return a.second > b.second;
			});
		}		
	}

	void NotifyObservers() override
	{
		T data = GetChangedData();
		auto observers = m_observers;
		for (auto & observer : observers)
		{
			if (IsNeedUpdateObserver(*observer.first))
			{
				observer.first->Update(data, *this);
			}
		}		
	}

	void RemoveObserver(ObserverType & observer) override
	{
		auto iter = std::find_if(m_observers.begin(), m_observers.end(), [&observer](ObserverRecord const & a) {
			return std::addressof(*a.first) == std::addressof(observer);
		});
		if (iter != m_observers.end())
		{
			m_observers.erase(iter);
		}
	}
	
	const std::string& GetName() const override
	{
		return m_name;
	}

protected:
	// Классы-наследники должны перегрузить данный метод, 
	// в котором возвращать информацию об изменениях в объекте
	virtual T GetChangedData() const = 0;
	virtual bool IsNeedUpdateObserver(const ObserverType & observer) const = 0;

private:
	std::vector<ObserverRecord> m_observers;
	std::string m_name;
};
