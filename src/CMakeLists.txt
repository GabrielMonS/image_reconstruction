find_package(OpenCV 4.2 REQUIRED)

add_executable(image_reconstruction)

target_sources(
    image_reconstruction
    PRIVATE
    reconstruction.cpp
    main.cpp
)

target_include_directories(
  image_reconstruction
  PUBLIC
    ${OpenCV_INCLUDE_DIRS}
)

target_link_libraries(
  image_reconstruction
  PUBLIC
    ${OpenCV_LIBS}
)

target_compile_features(
    image_reconstruction
    PUBLIC
    cxx_std_17
)