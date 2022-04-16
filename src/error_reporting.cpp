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

#include "dbc/error_reporting.hpp"
#include <chrono>
#include <thread>

namespace dbc
{

auto operator<<(std::ostream& os, const violation_context& context) -> std::ostream&
{
    return os << to_string_view(context.type) << " violation: (" << context.condition
              << "), with expansion: "
              << "(" << context.decomposition << ") "
              << "function: " << context.function << ", file: " << context.file
              << ", line: " << context.line << ", thread id: " << context.thread_id
              << ", timestamp (ms): " << context.timestamp << "." << '\n'
              << context.message;
}

namespace
{
    auto thread_id() noexcept
    {
        using namespace std;

        return hash<thread::id>()(this_thread::get_id());
    }

    auto timestamp()
    {
        using namespace std::chrono;

        const auto until_now = system_clock::now().time_since_epoch();
        return duration_cast<milliseconds>(until_now).count();
    }
} // namespace

namespace details
{

    auto make_context(contract type, std::string_view condition, const std::string& decomposition,
                      std::string_view function, std::string_view file, int32_t line,
                      std::string_view message) -> violation_context
    {
        return violation_context{type, condition,   decomposition, function, file,
                                 line, thread_id(), timestamp(),   message};
    }

} // namespace details

} // namespace dbc