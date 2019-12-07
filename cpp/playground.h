#pragma once

#include <optional>
#include <vector>
#include <algorithm>

namespace playground {

    template<typename T>
    auto kth(std::vector<T> const &v, int k) -> std::optional<T> {

        // Guard
        if (k < 1 || k > v.size()) {
            return {};
        }

        // Must copy the vector to sort it
        // auto v2 = v;
        // std::sort(v2.begin(), v2.end());
        // return v2.at(k-1);

        // Must copy the vector to heapify it
        auto h = v;
        std::make_heap(h.begin(), h.end(), std::greater{});
        for (int i=1; i<k; i++) {
            std::pop_heap(h.begin(), h.end(), std::greater{});
            h.pop_back();
        }

        return h.front();
    }
}