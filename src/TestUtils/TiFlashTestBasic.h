// Copyright 2022 PingCAP, Ltd.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#pragma once

#include <Common/Exception.h>
#include <Poco/File.h>
#include <Poco/Path.h>
#include <Poco/SortedDirectoryIterator.h>
#include <TestUtils/TiFlashTestEnv.h>
#include <TestUtils/TiFlashTestException.h>
#include <fmt/core.h>

#include <string>

#if !__clang__
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wsign-compare"
#else
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wsign-compare"
#endif

#include <gtest/gtest.h>

#if !__clang__
#pragma GCC diagnostic pop
#else
#pragma clang diagnostic pop
#endif


namespace DB
{
namespace tests
{
#define CATCH                                                                          \
    catch (const ::DB::tests::TiFlashTestException & e)                                \
    {                                                                                  \
        std::string text = e.displayText();                                            \
        text += "\n\n";                                                                \
        if (text.find("Stack trace") == std::string::npos)                             \
            text += fmt::format("Stack trace:\n{}\n", e.getStackTrace().toString());   \
        FAIL() << text;                                                                \
    }                                                                                  \
    catch (const ::DB::Exception & e)                                                  \
    {                                                                                  \
        std::string text = fmt::format("Code: {}. {}\n\n", e.code(), e.displayText()); \
        if (text.find("Stack trace") == std::string::npos)                             \
            text += fmt::format("Stack trace:\n{}\n", e.getStackTrace().toString());   \
        FAIL() << text;                                                                \
    }                                                                                  \
    catch (...)                                                                        \
    {                                                                                  \
        ::DB::tryLogCurrentException(__PRETTY_FUNCTION__);                             \
        FAIL();                                                                        \
    }

} // namespace tests
} // namespace DB
