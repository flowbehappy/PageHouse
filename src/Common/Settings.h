#pragma

#include <Common/types.h>

namespace DB
{
struct Settings
{
    UInt64 dt_segment_limit_rows = 1000000;
    UInt64 dt_segment_limit_size = 536870912;
    UInt64 dt_segment_force_split_size = 1610612736;
    UInt64 dt_segment_delta_limit_rows = 80000;
    UInt64 dt_segment_delta_limit_size = 42991616;
    UInt64 dt_segment_force_merge_delta_deletes = 10;
    UInt64 dt_segment_force_merge_delta_rows = 134217728;
    UInt64 dt_segment_force_merge_delta_size = 1073741824;
    UInt64 dt_segment_stop_write_delta_rows = 268435456;
    UInt64 dt_segment_stop_write_delta_size = 2147483648;
    UInt64 dt_segment_delta_cache_limit_rows = 4096;
    UInt64 dt_segment_delta_cache_limit_size = 4194304;
    UInt64 dt_segment_delta_small_pack_rows = 2048;
    UInt64 dt_segment_delta_small_pack_size = 8388608;
    UInt64 dt_segment_delta_small_column_file_rows = 2048;
    UInt64 dt_segment_delta_small_column_file_size = 8388608;
    Float32 dt_segment_wait_duration_factor = 1;
    UInt64 dt_bg_gc_check_interval = 60;
    Int64 dt_bg_gc_max_segments_to_check_every_round = 100;
    Float32 dt_bg_gc_ratio_threhold_to_trigger_gc = 1;
    Float32 dt_bg_gc_delta_delete_ratio_to_trigger_gc = 0;
    UInt64 dt_insert_max_rows = 0;
    bool dt_enable_rough_set_filter = true;
    bool dt_raw_filter_range = true;
    bool dt_read_delta_only = false;
    bool dt_read_stable_only = false;
    bool dt_enable_logical_split = false;
    bool dt_flush_after_write = false;
    bool dt_enable_relevant_place = false;
    bool dt_enable_skippable_place = true;
    bool dt_enable_stable_column_cache = true;

    UInt64 dt_open_file_max_idle_seconds = 15;
    UInt64 dt_page_num_max_expect_legacy_files = 100;
    Float32 dt_page_num_max_gc_valid_rate = 1;
    Float32 dt_page_gc_low_write_prob = 0;
    UInt64 dt_storage_pool_log_write_slots = 4;
    UInt64 dt_storage_pool_log_gc_min_file_num = 10;
    UInt64 dt_storage_pool_log_gc_min_legacy_num = 3;
    UInt64 dt_storage_pool_log_gc_min_bytes = 128;
    Float32 dt_storage_pool_log_gc_max_valid_rate = 0;
    UInt64 dt_storage_pool_data_write_slots = 1;
    UInt64 dt_storage_pool_data_gc_min_file_num = 10;
    UInt64 dt_storage_pool_data_gc_min_legacy_num = 3;
    UInt64 dt_storage_pool_data_gc_min_bytes = 128;
    Float32 dt_storage_pool_data_gc_max_valid_rate = 0;
    UInt64 dt_storage_pool_meta_write_slots = 2;
    UInt64 dt_storage_pool_meta_gc_min_file_num = 10;
    UInt64 dt_storage_pool_meta_gc_min_legacy_num = 3;
    UInt64 dt_storage_pool_meta_gc_min_bytes = 128;
    Float32 dt_storage_pool_meta_gc_max_valid_rate = 0;
    Float64 dt_page_gc_threshold = 0;
    bool dt_enable_read_thread = true;
    bool dt_enable_bitmap_filter = true;
    Float64 dt_read_thread_count_scale = 1;
    Float64 dt_filecache_max_downloading_count_scale = 1;
    UInt64 dt_filecache_min_age_seconds = 1800;
    UInt64 dt_small_file_size_threshold = 128;
    Float64 dt_merged_file_max_size = 1024;
};

} // namespace DB