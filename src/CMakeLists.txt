add_subdirectory(Communication)

find_package(spdlog CONFIG REQUIRED)

add_executable(VirtualDrivingLab)
add_executable(VirtualDrivingLab::VirtualDrivingLab ALIAS VirtualDrivingLab)
target_sources(VirtualDrivingLab PRIVATE Main.cpp)
target_compile_features(VirtualDrivingLab PRIVATE cxx_std_23)
target_include_directories(VirtualDrivingLab PRIVATE "${PROJECT_SOURCE_DIR}/include")
target_link_libraries(VirtualDrivingLab PRIVATE spdlog::spdlog)
