#pragma once
namespace Libero
{
	class IEvent;
	class IObserver
	{
	public:
		virtual ~IObserver() = default;
		virtual void OnEvent(IEvent& e) = 0;
	};
}


