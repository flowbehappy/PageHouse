# Copyright 2022 PingCAP, Ltd.
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

add_headers_and_sources(page_storage_v3 ./)
add_headers_and_sources(page_storage_v3 ./spacemap)


list(APPEND page_storage_v3_sources
    ${PageHouse_SOURCE_DIR}/dbms/src/Server/StorageConfigParser.cpp
    ${PageHouse_SOURCE_DIR}/dbms/src/PageUtil.cpp
    ${PageHouse_SOURCE_DIR}/dbms/src/Encryption/RateLimiter.cpp
)

add_library(page_storage_v3 EXCLUDE_FROM_ALL
    ${page_storage_v3_headers} ${page_storage_v3_sources}
    ${io_base_headers} ${io_base_sources}
)

target_link_libraries(page_storage_v3 PSCheckpointProto)