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
//
//#include <Encryption/DataKeyManager.h>
////#include <Storages/Transaction/FileEncryption.h>
////#include <Storages/Transaction/ProxyFFI.h>
//
//namespace DB
//{
//DataKeyManager::DataKeyManager(EngineStoreServerWrap * tiflash_instance_wrap_)
//    : tiflash_instance_wrap{tiflash_instance_wrap_}
//{}
//
//FileEncryptionInfo DataKeyManager::getFile(const String & fname)
//{
//    throw Exception("Unsupported operation");
//}
//
//FileEncryptionInfo DataKeyManager::newFile(const String & fname)
//{
//    throw Exception("Unsupported operation");
//}
//
//void DataKeyManager::deleteFile(const String & fname, bool throw_on_error)
//{
//    throw Exception("Unsupported operation");
//}
//
//void DataKeyManager::linkFile(const String & src_fname, const String & dst_fname)
//{
//    throw Exception("Unsupported operation");
//}
//
//} // namespace DB
