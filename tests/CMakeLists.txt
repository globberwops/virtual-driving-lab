find_package(GTest CONFIG REQUIRED)
find_package(mp-units CONFIG REQUIRED)
find_package(doctest CONFIG REQUIRED)
include(doctest)

add_executable(VirtualDrivingLabTest)
target_sources(
    VirtualDrivingLabTest
    PRIVATE IIdentifiableTest.cpp
            IStepableTest.cpp
            VirtualDrivingLabTest.cpp
            ChannelTest.cpp
            FlagsTest.cpp
            PublisherTest.cpp
            SubscriberTest.cpp
            EntityRepositoryTest.cpp)
# TypesTest.cpp)
target_compile_features(VirtualDrivingLabTest PRIVATE cxx_std_23)
target_include_directories(VirtualDrivingLabTest PRIVATE "${PROJECT_SOURCE_DIR}/include")
target_link_libraries(VirtualDrivingLabTest VirtualDrivingLab::Communication GTest::gtest doctest::doctest)

doctest_discover_tests(VirtualDrivingLabTest)

find_package(benchmark CONFIG REQUIRED)

add_executable(VirtualDrivingLabBench)
target_compile_features(VirtualDrivingLabBench PRIVATE cxx_std_23)
target_sources(VirtualDrivingLabBench PRIVATE EntityRepositoryBench.cpp)
target_include_directories(VirtualDrivingLabBench PRIVATE "${PROJECT_SOURCE_DIR}/include")
target_link_libraries(VirtualDrivingLabBench mp-units::si benchmark::benchmark_main)
