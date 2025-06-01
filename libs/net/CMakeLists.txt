add_library(net STATIC
    src/Net.cpp
    src/enet_impl.cpp
)

target_include_directories(net PUBLIC include)

target_link_libraries(net PUBLIC core)
