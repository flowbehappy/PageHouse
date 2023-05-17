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

#include <PageDefinesBase.h>

namespace DB
{
using BlobFileId = UInt64;
using BlobFileOffset = UInt64;
static constexpr BlobFileId INVALID_BLOBFILE_ID = 0;
static constexpr BlobFileOffset INVALID_BLOBFILE_OFFSET = std::numeric_limits<BlobFileOffset>::max();
} // namespace DB
