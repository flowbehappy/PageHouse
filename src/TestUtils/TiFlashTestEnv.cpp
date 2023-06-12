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

#include <Common/UnifiedLogFormatter.h>
#include <Common/logger_useful.h>
#include <Encryption/FileProvider.h>
#include <Poco/AutoPtr.h>
#include <Poco/ConsoleChannel.h>
#include <Poco/FormattingChannel.h>
#include <Poco/Logger.h>
#include <Poco/PatternFormatter.h>
#include <TestUtils/TiFlashTestEnv.h>

#include <memory>

namespace DB::tests
{

String TiFlashTestEnv::getTemporaryPath(const std::string_view test_case, bool get_abs)
{
    String path = ".";
    const char * temp_prefix = getenv("TIFLASH_TEMP_DIR");
    if (temp_prefix != nullptr)
        path = DB::String(temp_prefix);
    path += "/tmp/";
    if (!test_case.empty())
        path += std::string(test_case);

    Poco::Path poco_path(path);
    if (get_abs)
        return poco_path.absolute().toString();
    else
        return poco_path.toString();
}

void TiFlashTestEnv::tryCreatePath(const std::string & path)
{
    try
    {
        Poco::File p(path);
        if (!p.exists())
            p.createDirectories();
    }
    catch (...)
    {
        tryLogCurrentException("gtest", fmt::format("while removing dir `{}`", path));
    }
}

void TiFlashTestEnv::tryRemovePath(const std::string & path, bool recreate)
{
    try
    {
        // drop the data on disk
        Poco::File p(path);
        if (p.exists())
        {
            p.remove(true);
        }

        // re-create empty directory for testing
        if (recreate)
        {
            p.createDirectories();
        }
    }
    catch (...)
    {
        tryLogCurrentException("gtest", fmt::format("while removing dir `{}`", path));
    }
}

void TiFlashTestEnv::setupLogger(const String & level, std::ostream & os)
{
    Poco::AutoPtr<Poco::ConsoleChannel> channel = new Poco::ConsoleChannel(os);
    Poco::AutoPtr<Poco::Formatter> formatter(new UnifiedLogFormatter<true>());
    Poco::AutoPtr<Poco::FormattingChannel> formatting_channel(new Poco::FormattingChannel(formatter, channel));
    Poco::Logger::root().setChannel(formatting_channel);
    Poco::Logger::root().setLevel(level);
}

} // namespace DB::tests
