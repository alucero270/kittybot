add_library(kittybot_core STATIC
    kittybot/logger.cpp
)

target_include_directories(kittybot_core PUBLIC
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

find_package(Threads REQUIRED)
target_link_libraries(kittybot_core
    PRIVATE Threads::Threads
)

target_compile_features(kittybot_core PUBLIC cxx_std_23)
