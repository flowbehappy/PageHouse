
set(fiu_include_dirs libfiu)
list(APPEND fiu_sources libfiu/fiu.c)
list(APPEND fiu_sources libfiu/fiu-rc.c)
list(APPEND fiu_sources libfiu/backtrace.c)
list(APPEND fiu_sources libfiu/wtable.c)
list(APPEND fiu_sources libfiu/hash.c)
# We need to compile fiu manully because fiu does not provide their cmakefiles.
add_library(fiu ${fiu_sources})
target_include_directories(fiu PUBLIC ${fiu_include_dirs})
target_compile_options(fiu PUBLIC -fPIC -DDUMMY_BACKTRACE)
