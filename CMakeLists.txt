# ==========================================
# 1. Meta Data & Project Config
# ==========================================
cmake_minimum_required(VERSION 3.10)
project(Four-Color VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ==========================================
# 2. External Dependencies (vcpkg)
# ==========================================
find_package(glfw3 CONFIG REQUIRED)
find_package(glad CONFIG REQUIRED)
find_package(imgui CONFIG REQUIRED)


# ==========================================
# 3. Define Targets (Your Libraries & Executables)
# ==========================================
# Create the main application executable
add_executable(my_executable
    src/Algorithm/main.cpp
    src/Graph/Graph.cpp
    src/Graph/Graph.h
)

# ==========================================
# 4. Target Configuration & Linking
# ==========================================
target_include_directories(my_executable PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_link_libraries(my_executable PRIVATE
    glfw
    glad::glad
    imgui::imgui
)
