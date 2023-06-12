PageHouse
====

A embed Key-Value storage engine. Both key (coded as "PageId") and value (coded as "Page") are arbitrary bytes.

Some features which make PageHouse unique among all kinds of K-V engines:

* PageHouse can store value with any size. And storing large values is welcome in PageHouse.
* Support snapshot. You can read on a stable view without worry the consistency.
* Support reference. You can store a ref-page of another page into PageHouse. Similar to hard link in a file system.
* Support external values. You can store your real value data in anywhere, and then put a link in PageHouse. E.g. external files on local disk or object storage.
* Resource efficiency.
    * Each `read(key)` requires 1 Read IO
    * Each `write(key, value)` requires 2 Write IOs
    * The background tasks are carefully designed and try to avoid the influence to foreground tasks.

Drawbacks:

* PageHouse cache all pageids and page meta (including offset, size, and other information) in memory.
    * 1 page consumes 1 KiB memory currently.
    * We plan to redunce to 100 bytes in the near future.
