#include <time/performance_counter.h>
#include <time/sleep.h>
#include <time/time.h>

#include <stdio.h>

int main()
{
    const Base::PerformanceCounter::Timer timer = Base::PerformanceCounter::StartTimer();

    for(int i = 0; i < 50; i++)
    {
        Base::Time::ThreadSleep(100 * 1000);
    }

    const Float64 end = Base::PerformanceCounter::EndTimer(timer); 

    printf("%lf\n", end * 1000);

    return 0;
}