#pragma once

#include <algorithm>
#include <numeric>
#include <optional>
#include <sstream>
#include <string>
#include <vector>
#include <iostream>
#include <ranges>
#include <cmath>
#include <thread>
#include <future>

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
    constexpr auto sum_div_by_3_or_5(T const up_to) -> long long
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
    constexpr auto sum_div_by_3_or_5_stl(T const up_to) -> long long
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
    constexpr auto gcd(T a, T b) -> T
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

        static auto from_string(std::string const & str) -> std::optional<IPV4>
        {
            uint8_t ip[4] {};

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

        constexpr auto value() const -> uint32_t 
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

    template <typename T>
    constexpr auto min(std::initializer_list<T> list) -> T
    {
        T m { *list.begin() };
        for( auto elem : list )
        {
            if (elem < m) {
                m = elem;
            }
        }
        return m;
    }


    template <typename T>
    constexpr auto find(std::initializer_list<T> list, std::function<bool(const T&, const T&)> cmp) -> T
    {
        T m{*list.begin()};
        for (auto elem : list)
        {
            if (cmp(elem, m))
            {
                m = elem;
            }
        }
        return m;
    }

    // ----

    template<typename Container, typename T>
    inline auto contains(const Container &c, T t) -> bool
    {
        return std::find(c.cbegin(), c.cend(), t) != c.end();
    }

    template<typename Container, typename T>
    constexpr auto contains_any(const Container &c, T t) -> bool
    {
        return contains(c, t);
    }

    template<typename Container, typename T, typename... Args>
    constexpr auto contains_any(const Container &c, T t, Args... args) -> bool
    {
        return contains_any(c, t) || contains_any(c, args...); 
    }

    // ----

    template<typename Container, typename T>
    constexpr auto contains_all(const Container &c, T t) -> bool
    {
        return contains(c, t);
    }

    template<typename Container, typename T, typename... Args>
    constexpr auto contains_all(const Container &c, T t, Args... args) -> bool
    {
        return contains_all(c, t) && contains_all(c, args...); 
    }

    // ----
    
    template<typename Container, typename T, typename... Args>
    constexpr auto contains_none(const Container &c, T t, Args... args) -> bool
    {
        // return !contains_any(c, t) && !contains_all(c, args...); 
        return !contains_all(c, t, args...);
    }

    constexpr int unique_paths(const int rows, const int cols)
    {
        if (rows == 1 || cols == 1) {
            return 1;
        }

        return unique_paths(rows - 1, cols) + unique_paths(rows, cols - 1);
    }

    /* subset sum attempt #1
     * naive solution = iterate all combinations
     * trying to use "no raw loops"
     */

    template<typename T>
    std::vector<std::vector<T>> subset_sum(std::vector<T> const & nums, T target_sum) {

        std::vector<std::vector<T>> solutions {};
        std::vector<long long> x(std::pow(2, nums.size()));
        std::iota(std::begin(x), std::end(x), 0);
        std::for_each(x.begin(), x.end(), [nums, target_sum, &solutions](auto &n){
            std::vector<T> subset;
            for (typename std::vector<T>::size_type j = 0; j < nums.size(); j++) {
                if (0x1<<j & n) {
                    subset.push_back(nums[j]);
                }
            }
            auto subset_sum = std::accumulate(subset.begin(), subset.end(), 0);
            if (subset_sum == target_sum) {
                solutions.push_back(subset);
            }
         }); 

        return solutions;
    }

    
    template<typename T>
    std::vector<std::vector<T>> subset_sum_2(std::vector<T> const & nums, T target_sum) {
        
        std::vector<std::vector<T>> solutions {};
        std::vector<T> subset;
        for(long long i=0; i<std::pow(2, nums.size()); i++) {
            subset.clear();
             for (typename std::vector<T>::size_type j = 0; j < nums.size(); j++) {
                if (0x1<<j & i) {
                    subset.push_back(nums[j]);
                }
            }
            auto subset_sum = std::accumulate(subset.begin(), subset.end(), 0);
            if (subset_sum == target_sum) {
                solutions.push_back(std::vector(subset));
            }
        }

        return solutions;
    }

    template<typename T>
    std::vector<std::vector<T>> subset_sum_3(std::vector<T> const & nums, T target_sum) {
        std::vector<std::vector<T>> solutions {};

        std::vector<T> subset;
        for (int i : std::views::iota(0, std::pow(2, nums.size()))) {
            subset.clear();
            for (typename std::vector<T>::size_type j = 0; j < nums.size(); j++) {
                if (0x1<<j & i) {
                    subset.push_back(nums[j]);
                }
            }
            auto subset_sum = std::accumulate(subset.begin(), subset.end(), 0);
            if (subset_sum == target_sum) {
                solutions.push_back(subset);
            }
        }
        return solutions;
    }

    template<typename T>
    std::vector<std::vector<T>> subset_sum_4(std::vector<T> const & nums, T target_sum, int job_count = 1) {

        using num_list = std::vector<T>;
        using solution_set = std::vector<num_list>;
        using solution_set_future = std::shared_future<solution_set>;

        solution_set solutions {};
        std::vector<solution_set_future> jobs {};

        const long long chunk_size = std::pow(2, nums.size()) / job_count;

        for (int t : std::views::iota(0, job_count)) {

            solution_set_future subsolution_future = 
            std::async(std::launch::async, [nums, target_sum, t, chunk_size]() {

                solution_set subsolutions;
                num_list subset;
                const long long begin = t * chunk_size;
                for (int i : std::views::iota(begin, begin + chunk_size)) {
                    subset.clear();
                    for (typename std::vector<T>::size_type j = 0; j < nums.size(); j++) {
                        if (0x1<<j & i) {
                            subset.push_back(nums[j]);
                        }
                    }
                    auto subset_sum = std::accumulate(subset.begin(), subset.end(), 0);
                    if (subset_sum == target_sum) {
                        subsolutions.push_back(subset);
                    }
                }
                return subsolutions;
            });
            jobs.push_back(subsolution_future);
        }

        for( auto job : jobs ) {
            auto s = job.get();
            solutions.insert(std::end(solutions), std::begin(s), std::end(s));
        }

        return solutions;
    }
}

