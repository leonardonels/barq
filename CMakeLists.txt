cmake_minimum_required(VERSION 3.5)
project(barq)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(ament_cmake REQUIRED)

add_library(barq SHARED
  src/barq.cpp
)

target_include_directories(barq PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>
)

target_link_libraries(barq
  rt
  pthread
)

target_compile_options(barq PRIVATE -Wall)

# Install library
install(TARGETS barq
  EXPORT barqTargets
  ARCHIVE DESTINATION lib
  LIBRARY DESTINATION lib
  RUNTIME DESTINATION bin
)

# Install headers
install(DIRECTORY include/
  DESTINATION include
)

# Export targets so find_package(barq) works
ament_export_targets(barqTargets HAS_LIBRARY_TARGET)
ament_export_include_directories(include)
ament_export_libraries(barq)

ament_package()
