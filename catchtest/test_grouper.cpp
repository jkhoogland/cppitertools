#include <grouper.hpp>

#include <vector>
#include <array>
#include <string>
#include <utility>

#include "helpers.hpp"
#include "catch.hpp"

using iter::grouper;
using Vec = std::vector<int>;
using ResVec = std::vector<Vec>;

TEST_CASE("grouper: basic test", "[grouper]") {
    Vec ns = {1,2,3,4,5,6};
    ResVec results;
    for (auto&& g : grouper(ns, 2)) {
        results.emplace_back(std::begin(g), std::end(g));
    }

    ResVec rc = { {1, 2}, {3, 4}, {5, 6} };

    REQUIRE( results == rc );
}

TEST_CASE("grouper: len(iterable) % groupsize != 0", "[grouper]") {
    Vec ns = {1,2,3,4,5,6,7};
    ResVec results;
    for (auto&& g : grouper(ns, 3)) {
        results.emplace_back(std::begin(g), std::end(g));
    }

    ResVec rc = { {1, 2, 3}, {4, 5, 6}, {7} };

    REQUIRE( results == rc );
}
