# custom_processors/CMakeLists.txt

zephyr_library()

zephyr_library_sources_if_ok(dominant_axis_processor.c)
