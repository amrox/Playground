#pragma once

#include <algorithm>
// #include <istream>
#include <numeric>
#include <optional>
#include <sstream>
#include <string>
#include <vector>

namespace playground {

    template<typename T>
    auto kth(std::vector<T> const &v, int k) -> std::optional<T> {

        // Guard
        if (k < 1 || k > v.size()) {
            return {};
        }

        // Naive approach - sort and then index into the array
        // Must copy the vector to sort it
        // auto v2 = v;
        // std::sort(v2.begin(), v2.end());
        // return v2.at(k-1);

        // Better approach - build a min-heap, and pop off k elements
        // Must copy the vector to heapify it
        auto h = v;
        std::make_heap(h.begin(), h.end(), std::greater{});
        for (int i=1; i<k; i++) {
            std::pop_heap(h.begin(), h.end(), std::greater{});
            h.pop_back();
        }

        return h.front();
    }

    // straightforward, imperative
    template<typename T>
    auto sum_div_by_3_or_5(T const up_to) -> long long
    {
        static_assert(std::is_integral<T>::value, "Integral required.");

        long long out(0);

        for (T i = 3; i <= up_to; i += 3) {
            out += i;
        }

        for (T i = 5; i <= up_to; i += 5) {
            out += i;
        }
        return out;
    }

    // sorta functional approach using stl 
    template<typename T>
    auto sum_div_by_3_or_5_stl(T const up_to) -> long long
    {
        static_assert(std::is_integral<T>::value, "Integral required.");

        // generate all numbers up to limit
        std::vector<T> all_up_to(up_to);
        std::generate(all_up_to.begin(), all_up_to.end(), [n = 1] () mutable { return n++; });

        // filter list 
        std::vector<T> filtered_up_to;
        std::copy_if(all_up_to.begin(), all_up_to.end(),
                     std::back_inserter(filtered_up_to),
                     [&](const auto &elem) {
                         return elem % 3 == 0 || elem % 5 == 0;
                     });

        // sum
        return std::accumulate(filtered_up_to.begin(), filtered_up_to.end(), 0);
    }

    template <typename T>
    auto gcd(T a, T b) -> T
    {
        static_assert(std::is_integral<T>::value, "Integral required.");
        
        while (a != b) {
            if (a > b) {
                a = a - b;
            } else {
                b = b - a;
            }
        }
        return a;
    }

    class IPV4 {

    public:
        IPV4(uint8_t o1, uint8_t o2, uint8_t o3, uint8_t o4) : _ip{o1, o2, o3, o4}
        {
        }

        static std::optional<IPV4> from_string(std::string const & str)
        {
            uint8_t ip[4];

            std::vector<std::string> tokens;
            std::string token;
            std::istringstream token_stream(str);
            while (std::getline(token_stream, token, '.'))
            {
                tokens.push_back(token);
            }

            if (tokens.size() != 4)
            {
                return std::nullopt;
            }

            for (int i = 0; i < 4; i++)
            {
                unsigned long t = std::stol(tokens.at(i));
                if (t <= 255) // TODO: some limit constant
                {
                    ip[i] = t;
                }
                else
                {
                    return std::nullopt;
                }
            }

            return IPV4(ip[0], ip[1], ip[2], ip[3]);
        }

        IPV4() = delete;

        IPV4(IPV4 const & other) = default;

        IPV4 &operator=(IPV4 const & other) = default;

        auto value() const -> uint32_t 
        {
            // TODO: this isn't right
            return static_cast<uint32_t>(*_ip);
        }

        auto to_string() const -> std::string 
        {
            // TODO: fmt would be nice here
            std::ostringstream ss;
            ss << std::to_string(_ip[0]) << ".";
            ss << std::to_string(_ip[1]) << ".";
            ss << std::to_string(_ip[2]) << ".";
            ss << std::to_string(_ip[3]);
            return ss.str();
        }

    private:
        uint8_t _ip[4];
    };

    inline bool operator==(const IPV4 &lhs, const IPV4 &rhs)
    {
        return lhs.value() == rhs.value();
    }
}

