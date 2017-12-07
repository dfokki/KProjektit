
#ifndef UTIL_H
#define UTIL_H

#include <UtH/UtHEngine.hpp>
#include <random>
#include <chrono>

namespace util
{
	struct UtH
	{
		template<typename T>
		static T* getGrandparent(uth::Object* obj)
		{
			static_assert(std::is_base_of<uth::Object, T>::value, "error: type must be derived from 'uth::Object'");

			if (obj)
			{
				while (obj->Parent() != nullptr) obj = obj->Parent();
				return static_cast<T*>(obj);
			}

			return nullptr;
		}
	};

	struct Math
	{
		template<typename T>
		// val is clamped between 0..1
		static T clamp(T val)
		{
			return val < 0 ? 0 : val > 1 ? 1 : val;
		}

		template<typename T>
		// val is clamped between min..max
		static T clamp(T val, T min, T max)
		{
			return val < min ? min : val > max ? max : val;
		}

		template<typename T>
		static T lerp(T min, T max, float phase)
		{
			return (1.0f - phase) * min + phase * max;
		}
	};

	struct Random
	{
	private:
		static std::default_random_engine& getGenerator()
		{
			static std::default_random_engine generator;
			return generator;
		}
	public:
		template<class T>
		static T next()
		{
			if (std::is_floating_point<T>::value)
				return nextf();

			if (std::is_integral<T>::value)
				return nexti();
		}

		template<class T>
		static T next(T min, T max)
		{
			if (std::is_floating_point<T>::value)
				return nextf(static_cast<float>(min), static_cast<float>(max));

			if (std::is_integral<T>::value)
				return nexti(static_cast<int>(min), static_cast<int>(max));
		}
	private:
		static float nextf()
		{
			static std::uniform_real_distribution<float> distribution;
			return 0.0f;
		}

		static float nextf(float min, float max)
		{
			return std::uniform_real_distribution<float>(min, max)(getGenerator());
		}

		static int nexti()
		{
			static std::uniform_int_distribution<int> distribution;
			return 0;
		}

		static int nexti(int min, int max)
		{
			return std::uniform_int_distribution<int>(min, max)(getGenerator());

		}
	};
} // namespace util

#endif // UTIL_H