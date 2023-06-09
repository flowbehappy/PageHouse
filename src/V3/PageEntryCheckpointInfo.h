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

#include <Common/defines.h>
#include <fmt/format.h>

namespace DB::PS::V3
{

// A more memory compact struct compared to std::optional<CheckpointInfo>
struct OptionalCheckpointInfo
{
    /**
     * Whether this object contains valid value or not
     *
     * Share the padding with following bits in this struct
     */
    bool is_valid = false;

    /**
     * Whether the PageEntry's local BlobData has been reclaimed.
     * If the data is reclaimed, you can only read out its data from the checkpoint.
     */
    bool is_local_data_reclaimed = false;

    std::string toDebugString() const
    {
        if (is_valid)
        {
            return fmt::format("{{local_data_reclaimed: {}, data_location: {}}}", is_local_data_reclaimed, "");
        }
        else
        {
            return "invalid";
        }
    }

public:
    ALWAYS_INLINE bool has_value() const { return is_valid; } // NOLINT(readability-identifier-naming)
};

} // namespace DB::PS::V3
