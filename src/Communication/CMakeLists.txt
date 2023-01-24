find_package(Boost REQUIRED)

add_library(Communication)
add_library(VirtualDrivingLab::Communication ALIAS Communication)
target_compile_features(Communication PUBLIC cxx_std_20)
target_sources(Communication PRIVATE Publisher.cpp Subscriber.cpp)
target_include_directories(Communication PRIVATE "${PROJECT_SOURCE_DIR}/include")
target_link_libraries(Communication PUBLIC Boost::boost)
