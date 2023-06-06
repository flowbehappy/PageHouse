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

#include <Common/Arena.h>
#include <IO/WriteBuffer.h>
#include <Common/StringRef.h>


namespace DB
{
/** Writes data contiguously into Arena.
  * As it will be located in contiguous memory segment, it can be read back with ReadBufferFromMemory.
  *
  * While using this object, no other allocations in arena are possible.
  */
class WriteBufferFromArena : public WriteBuffer
{
private:
    Arena & arena;
    const char *& begin;

    void nextImpl() override
    {
        /// Allocate more memory. At least same size as used before (this gives 2x growth ratio),
        ///  and at most grab all remaining size in current chunk of arena.
        size_t continuation_size = std::max(count(), arena.remainingSpaceInCurrentChunk());

        /// allocContinue method will possibly move memory region to new place and modify "begin" pointer.

        char * continuation = arena.allocContinue(continuation_size, begin);
        char * end = continuation + continuation_size;

        /// internal buffer points to whole memory segment and working buffer - to free space for writing.
        internalBuffer() = Buffer(const_cast<char *>(begin), end);
        buffer() = Buffer(continuation, end);
    }

public:
    /// begin_ - start of previously used contiguous memory segment or nullptr (see Arena::allocContinue method).
    WriteBufferFromArena(Arena & arena_, const char *& begin_)
        : WriteBuffer(nullptr, 0)
        , arena(arena_)
        , begin(begin_)
    {
        nextImpl();
        pos = working_buffer.begin();
    }

    StringRef finish()
    {
        /// Return over-allocated memory back into arena.
        arena.rollback(buffer().end() - position());
        /// Reference to written data.
        return {position() - count(), count()};
    }
};

} // namespace DB
