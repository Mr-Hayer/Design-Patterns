#ifndef _TIMER_H_
#define _TIMER_H_

namespace HYR {
	namespace UTILITIES {

		struct Timer
		{	// Timer object to calculate time.. Here the object life time standards are used!!
			std::chrono::time_point<std::chrono::steady_clock> T1, T2;
			std::chrono::duration<float> duration;
			explicit Timer()
			{	// Start time of Timer Object
				T1 = std::chrono::high_resolution_clock::now();
			}
			~Timer()
			{	// End time of Timer Object
				T2 = std::chrono::high_resolution_clock::now();
				duration = T2 - T1;
		
				// To print in [ms]
				if (duration.count() < 0)
				{
					float ms = duration.count() * 1000.0f;
					std::cout << "\nProgram execution took: " << ms << " [ ms ]" << "\n\n";
				}
				else
					std::cout << "\nProgram execution took: " << duration.count() << " [ s ]" << "\n\n";
			}
		};
	}
}
#endif //_TIMER_H_
