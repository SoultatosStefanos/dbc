///////////////////////////////////////////////////////////////////////////////
//
// MIT License
//
// Copyright (c) 2021 SoultatosStefanos
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to
// deal in the Software without restriction, including without limitation the
// rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
// sell copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
// FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
// IN THE SOFTWARE.
//
///////////////////////////////////////////////////////////////////////////////

#define DBC_ASSERT_LEVEL_POSTCONDITIONS

#include "dbc/dbc.hpp"
#include <algorithm>
#include <set>
#include <unordered_map>

namespace
{

template <typename Iterator>
auto has_duplicate(Iterator first, Iterator last) -> bool
{
    std::set<int> s{first, last};
    return v.size() - s.size();
}

// crediting me2
template <typename Resource, typename Tag, typename FactoryFunc, typename Hash = std::hash<Tag>>
class resource_registry
{
public:
    auto contains(const Tag& tag) const -> bool { return registry.contains(tag); }

    auto get(const Tag& tag) const -> const Resource&
    {
        INVARIANT(!has_duplicate(std::begin(registry), std::end(registry)));
        REQUIRE(contains(tag), "Did not find tag: " + std::to_string(tag));
        ENSURE(registry.at(tag));
        return *registry.at(tag);
    }

    auto get(const Tag& tag) -> Resource&
    {
        return const_cast<Resource&>(std::as_const(*this).Get());
    }

    void insert(const Tag& tag)
    {
        INVARIANT(!has_duplicate(std::begin(registry), std::end(registry)));
        REQUIRE(!contains(tag));
        registry[tag] = factory(tag);
        ENSURE(contains(tag));
        INVARIANT(!has_duplicate(std::begin(registry), std::end(registry)));
    }

private:
    using Registry = std::unordered_map<Tag, Resource, Hash>;

    FactoryFunc factory;
    Registry registry;
};

} // namespace