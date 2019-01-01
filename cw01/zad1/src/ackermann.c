#include <assert.h>

unsigned long ackermann(
    const unsigned long m,
    const unsigned long n)
{
    if (m == 0)
        return n + 1;
    else if (n == 0)
    {
        assert(m > 0);
        return ackermann(m - 1, 1);
    }
    else
    {
        assert(m > 0);
        assert(n > 0);
        return ackermann(m - 1, ackermann(m, n - 1));
    }
}