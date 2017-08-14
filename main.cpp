#include "algorithm/itoa.hpp"

#include <bitset>
#include <iostream>
#include <chrono>

class timer
{
private:
    std::chrono::high_resolution_clock::time_point d_begin;
    std::chrono::high_resolution_clock::time_point d_end;
    bool d_is_timing = false;

public:
    void start()
    {
        if(!d_is_timing)
        {
            d_begin = std::chrono::high_resolution_clock::now();
            d_is_timing = true;
        }
        else
        {
            throw std::logic_error("source code logic error");
        }
    }

    void finish()
    {
        if(d_is_timing)
        {
            d_end = std::chrono::high_resolution_clock::now();
            d_is_timing = false;
        }
        else
        {
            throw std::logic_error("source code logic error");
        }
    }

    auto elapsed_ms()
    {
        return std::chrono::duration_cast<std::chrono::milliseconds>(d_end - d_begin).count();
    }
};

bool check_itoa2_validity()
{
    auto max = std::numeric_limits<std::uintmax_t>::max();
    std::bitset<std::numeric_limits<std::uintmax_t>::digits> max_bits(max);
    std::bitset<std::numeric_limits<std::uintmax_t>::digits> max_minus_1_bits(max - 1);

    if(!(
        ReHu::itoa2<char>(123) == "1111011" &&
        ReHu::itoa2<char>(456) == "111001000" &&
        ReHu::itoa2<char>(789) == "1100010101" &&
        ReHu::itoa2<wchar_t>(19971007) == L"1001100001011101110111111" &&
        ReHu::itoa2<char>(0) == "0" &&
        ReHu::itoa2<char>(1) == "1" &&
        ReHu::itoa2<char>(-123).substr(1) == ReHu::itoa2<char>(123) &&
        ReHu::itoa2<char>(-456).substr(1) == ReHu::itoa2<char>(456) &&
        ReHu::itoa2<char>(-789).substr(1) == ReHu::itoa2<char>(789) &&
        ReHu::itoa2<wchar_t>(-19971007).substr(1) == ReHu::itoa2<wchar_t>(19971007) &&
        ReHu::itoa2<char>(-1).substr(1) == ReHu::itoa2<char>(1) &&
        ReHu::itoa2<char>(max - 1) == max_minus_1_bits.to_string() &&
        ReHu::itoa2<wchar_t>(max) == max_bits.template to_string<wchar_t>()))
    {
        std::cout << "itoa2 validity: false" << std::endl;
        return false;
    }

    return true;
}

void itoa2_benchmark(std::uint32_t time)
{
    timer T;
    std::cout << "================" << std::endl;
    std::cout << "itoa2: ";
    T.start();
    for(std::uint32_t i = time; i > 0; i--)
    {
        ReHu::itoa2<char>(i);
    }
    T.finish();
    std::cout << T.elapsed_ms() << " ms" << std::endl;

    if(time < std::numeric_limits<int>::max())
    {
        char buf[std::numeric_limits<decltype(time)>::digits + 2]{0};
        std::cout << "(C)itoa: ";
        T.start();
        for(auto i = static_cast<int>(time); i > 0; i--)
        {
            itoa(i, buf, 2);
        }
        T.finish();
        std::cout << T.elapsed_ms() << " ms" << std::endl;
    }

    std::cout << "================" << std::endl;
}

bool check_itoa8_validity()
{
    char buf[std::numeric_limits<std::uintmax_t>::digits + 1]{0};
    for(std::uint16_t i = 0; i < std::numeric_limits<std::uint16_t>::max(); i++)
    {
        snprintf(buf, sizeof(buf), "%o", i);
        auto L = ReHu::itoa8<char>(i);
        if(L != buf)
        {
            std::cout << "ERROR: L -> " << L << " R -> " << buf << std::endl;
            return false;
        }
    }

    for(std::int16_t i = 1; i < std::numeric_limits<std::int16_t>::max() / 2; i++)
    {
        snprintf(buf, sizeof(buf), "%o", i);
        auto L = ReHu::itoa8<char>(-i);
        if(L.substr(1) != buf)
        {
            std::cout << "ERROR: L -> " << L.substr(1) << " R -> " << buf << std::endl;
            return false;
        }
    }

    {
        auto max = std::numeric_limits<std::uintmax_t>::max();
        snprintf(buf, sizeof(buf), "%llo", max);
        auto L = ReHu::itoa8<char>(max);
        if(L != buf)
        {
            std::cout << "ERROR: L -> " << L << " R -> " << buf << std::endl;
            return false;
        }
    }

    return true;
}

void itoa8_benchmark(std::uint32_t time)
{
    timer T;
    std::cout << "================" << std::endl;
    std::cout << "itoa8: ";
    T.start();
    for(std::uint32_t i = time; i > 0; i--)
    {
        ReHu::itoa8<char>(i);
    }
    T.finish();
    std::cout << T.elapsed_ms() << " ms" << std::endl;

    std::cout << "snprintf: ";
    char buf[std::numeric_limits<decltype(time)>::digits + 2]{0};
    T.start();
    for(std::uint32_t i = time; i > 0; i--)
    {
        snprintf(buf, sizeof(buf), "%llo", i);
    }
    T.finish();
    std::cout << T.elapsed_ms() << " ms" << std::endl;

    if(time < std::numeric_limits<int>::max())
    {
        std::cout << "(C)itoa: ";
        T.start();
        for(auto i = static_cast<int>(time); i > 0; i--)
        {
            itoa(i, buf, 8);
        }
        T.finish();
        std::cout << T.elapsed_ms() << " ms" << std::endl;
    }

    std::cout << "================" << std::endl;
}

bool check_itoa10_validity()
{
    char buf[std::numeric_limits<std::uintmax_t>::digits + 1]{0};
    for(std::int16_t i = std::numeric_limits<std::int16_t>::min(); i < std::numeric_limits<std::int16_t>::max(); i++)
    {
        snprintf(buf, sizeof(buf), "%d", i);
        auto L = ReHu::itoa10<char>(i);
        if(L != buf)
        {
            std::cout << "ERROR: L -> " << L << " R -> " << buf << std::endl;
            return false;
        }
    }

    {
        auto max = std::numeric_limits<std::uintmax_t>::max();
        snprintf(buf, sizeof(buf), "%llu", max);
        auto L = ReHu::itoa10<char>(max);
        if(L != buf)
        {
            std::cout << "ERROR: L -> " << L << " R -> " << buf << std::endl;
            return false;
        }
    }

    return true;
}

void itoa10_benchmark(std::uint32_t time)
{
    timer T;
    std::cout << "================" << std::endl;
    std::cout << "itoa10: ";
    T.start();
    for(std::uint32_t i = time; i > 0; i--)
    {
        ReHu::itoa10<char>(i);
    }
    T.finish();
    std::cout << T.elapsed_ms() << " ms" << std::endl;

    std::cout << "snprintf: ";
    char buf[std::numeric_limits<decltype(time)>::digits + 2]{0};
    T.start();
    for(std::uint32_t i = time; i > 0; i--)
    {
        snprintf(buf, sizeof(buf), "%lld", i);
    }
    T.finish();
    std::cout << T.elapsed_ms() << " ms" << std::endl;

    if(time < std::numeric_limits<int>::max())
    {
        std::cout << "(C)itoa: ";
        T.start();
        for(auto i = static_cast<int>(time); i > 0; i--)
        {
            itoa(i, buf, 10);
        }
        T.finish();
        std::cout << T.elapsed_ms() << " ms" << std::endl;
    }

    std::cout << "================" << std::endl;
}

bool check_itoa16_validity()
{
    char buf[std::numeric_limits<std::uintmax_t>::digits + 1]{0};
    for(std::uint16_t i = 0; i < std::numeric_limits<std::uint16_t>::max(); i++)
    {
        snprintf(buf, sizeof(buf), "%x", i);
        auto L = ReHu::itoa16<char>(i);
        if(L != buf)
        {
            std::cout << "ERROR: L -> " << L << " R -> " << buf << std::endl;
            return false;
        }
    }

    for(std::int16_t i = 1; i < std::numeric_limits<std::int16_t>::max() / 2; i++)
    {
        snprintf(buf, sizeof(buf), "%x", i);
        auto L = ReHu::itoa16<char>(-i);
        if(L.substr(1) != buf)
        {
            std::cout << "ERROR: L -> " << L.substr(1) << " R -> " << buf << std::endl;
            return false;
        }
    }

    {
        auto max = std::numeric_limits<std::uintmax_t>::max();
        snprintf(buf, sizeof(buf), "%llx", max);
        auto L = ReHu::itoa16<char>(max);
        if(L != buf)
        {
            std::cout << "ERROR: L -> " << L << " R -> " << buf << std::endl;
            return false;
        }
    }

    return true;
}

void itoa16_benchmark(std::uint32_t time)
{
    timer T;
    std::cout << "================" << std::endl;
    std::cout << "itoa16: ";
    T.start();
    for(std::uint32_t i = time; i > 0; i--)
    {
        ReHu::itoa16<char>(i);
    }
    T.finish();
    std::cout << T.elapsed_ms() << " ms" << std::endl;

    std::cout << "snprintf: ";
    char buf[std::numeric_limits<decltype(time)>::digits + 2]{0};
    T.start();
    for(std::uint32_t i = time; i > 0; i--)
    {
        snprintf(buf, sizeof(buf), "%llx", i);
    }
    T.finish();
    std::cout << T.elapsed_ms() << " ms" << std::endl;

    if(time < std::numeric_limits<int>::max())
    {
        std::cout << "(C)itoa: ";
        T.start();
        for(auto i = static_cast<int>(time); i > 0; i--)
        {
            itoa(i, buf, 16);
        }
        T.finish();
        std::cout << T.elapsed_ms() << " ms" << std::endl;
    }

    std::cout << "================" << std::endl;
}

int main()
{
    std::uintmax_t count = 100000000;
    std::cout << "Count: " << count << std::endl;
    if(check_itoa2_validity())
        itoa2_benchmark(count);

    if(check_itoa8_validity())
        itoa8_benchmark(count);

    if(check_itoa10_validity())
        itoa10_benchmark(count);

    if(check_itoa16_validity())
        itoa16_benchmark(count);
}