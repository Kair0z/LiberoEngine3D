#pragma once
#include "IEvent.h"
#include "Libero/Math/LiberoMath.h"

namespace Libero
{
	class EventMouse : public IEvent
	{
	public:
		EventMouse(LPARAM lParam, WPARAM wParam) : m_lParam{ lParam }, m_wParam{ wParam }, m_Pos{ (float)GET_X_LPARAM(lParam), (float)GET_Y_LPARAM(lParam) }{}

		LPARAM GetlParam() const { return m_lParam; };
		WPARAM GetwParam() const { return m_wParam; };
		Vector2f GetPos() const { return m_Pos; };

		bool IsCTRLDown() const { return m_wParam & MK_CONTROL; };
		bool IsLBDown() const { return m_wParam & MK_LBUTTON; };
		bool IsMBDown() const { return m_wParam & MK_MBUTTON; };
		bool IsRBDown() const { return m_wParam & MK_RBUTTON; };
		bool IsShiftDown() const { return m_wParam & MK_SHIFT; };

	protected:
		LPARAM m_lParam;
		WPARAM m_wParam;
		Vector2f m_Pos;
	};

	class EventMouseDown final : public EventMouse
	{
	public:
		EventMouseDown(LPARAM lParam, WPARAM wParam) : EventMouse(lParam, wParam) {};
		LBR_E_DEFTYPE(EventType::MouseDown);
	};

	class EventMouseUp final : public EventMouse
	{
	public:
		EventMouseUp(LPARAM lParam, WPARAM wParam) : EventMouse(lParam, wParam) {};
		LBR_E_DEFTYPE(EventType::MouseUp);
	};

	class EventMouseMove final : public EventMouse
	{
	public:
		EventMouseMove(LPARAM lParam, WPARAM wParam) : EventMouse(lParam, wParam) {};
		~EventMouseMove() { m_LatestPos = GetPos(); } // On destruction, set latest pos

		LBR_E_DEFTYPE(EventType::MouseMove);

		Vector2f GetDelta() const
		{
			return GetPos() - m_LatestPos;
		}

	private:
		static Vector2f m_LatestPos;
	};
}