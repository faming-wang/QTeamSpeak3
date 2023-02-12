cmake_minimum_required (VERSION 3.22.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_DEBUG_POSTFIX d)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

set(project_langs C CXX)
if (APPLE)
    set(project_langs C CXX OBJC OBJCXX)
endif()

project(QTeamSpeak3 LANGUAGES ${project_langs} VERSION 0.4.4)

add_subdirectory(src)
add_subdirectory(examples)

include (FeatureSummary)
feature_summary (INCLUDE_QUIET_PACKAGES WHAT
    PACKAGES_FOUND PACKAGES_NOT_FOUND
    ENABLED_FEATURES DISABLED_FEATURES
)
