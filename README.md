PageHouse
====

An embed Key-Value storage engine. Both key (coded as "PageId") and value (coded as "Page") are arbitrary bytes.

# Key Features

Some features which make PageHouse unique among all kinds of K-V engines:

* PageHouse can store values with any size. And storing large values (e.g. 64KiB to 64 MiBs) is welcome in PageHouse.
* Support snapshot. You can read on a stable view without worrying about the consistency.
* Support reference. You can store a ref-page of another page. Similar to hard link in a file system.
* Support external values. You can store your real value data in anywhere, and then put a link in PageHouse. E.g. files on local disk or object storage.
* Resource efficiency.
    * Each `read(key)` requires exactly 1 Read IO
    * Each `write(key, value)` requires 2 Write IOs
    * The background tasks are carefully designed and try to avoid the influence of foreground tasks.

# Drawbacks

* PageHouse cache all page ids and page meta (including offset, size, and other information) in memory. It could become a bottleneck if your memory is limited.
    * 1 page meta consumes ~500 bytes memory currently.
    * We plan to dramatically reduce the memory usage in the near future.

# License

PageHouse is under the Apache 2.0 license. See the LICENSE file for details.

# Notes

* **PageHouse is not production ready yet! Don't use it in your production environment!**
* PageHouse is used to be part of [TiFlash](https://github.com/pingcap/tiflash)
