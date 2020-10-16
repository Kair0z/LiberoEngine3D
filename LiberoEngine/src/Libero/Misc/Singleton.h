#pragma once

namespace Libero
{
	template <typename Serv>
	class Singleton
	{
	public:
		virtual ~Singleton() = default;

		static Serv& Get()
		{
			static Serv i;
			return i;
		}

	protected:
		Singleton() = default;
	};
}


