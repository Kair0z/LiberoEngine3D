#pragma once
#include <string>

namespace Libero
{
#pragma region EventDeftype
#define LBR_E_DEFTYPE(type) \
	public:\
		static Libero::EventType GetStaticType(){return type;}\
		virtual Libero::EventType GetType() const override { return type;};
#pragma endregion

	enum class EventType
	{
		MouseDown,
		MouseUp,
		MouseMove,
		EngineExit,
		KeyDown,
		KeyUp,
		GameStart,
		GameStop
	};

	class IEvent
	{
	public:
		virtual EventType GetType() const = 0;
		bool IsHandled() const;
		void SetHandled(bool handled = true);
		virtual inline std::string ToStr() const { return "Random Event..."; };

	private:
		bool m_IsHandled = false;
	};
}

