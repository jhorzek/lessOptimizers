# This file was generated with cmake-init by friendlyanon at https://github.com/friendlyanon/cmake-init

if(PROJECT_IS_TOP_LEVEL)
  set(
      CMAKE_INSTALL_INCLUDEDIR "include/lesstimate-${PROJECT_VERSION}"
      CACHE PATH ""
  )
endif()

# Project is configured with no languages, so tell GNUInstallDirs the lib dir
set(CMAKE_INSTALL_LIBDIR lib CACHE PATH "")

include(CMakePackageConfigHelpers)
include(GNUInstallDirs)

# find_package(<package>) call for consumers to find this project
set(package lesstimate)

install(
    DIRECTORY include/
    DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}"
    COMPONENT lesstimate_Development
)

install(
    TARGETS lesstimate_lesstimate
    EXPORT lesstimateTargets
    INCLUDES DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}"
)

write_basic_package_version_file(
    "${package}ConfigVersion.cmake"
    COMPATIBILITY SameMajorVersion
    ARCH_INDEPENDENT
)

# Allow package maintainers to freely override the path for the configs
set(
    lesstimate_INSTALL_CMAKEDIR "${CMAKE_INSTALL_DATADIR}/${package}"
    CACHE PATH "CMake package config location relative to the install prefix"
)
mark_as_advanced(lesstimate_INSTALL_CMAKEDIR)

install(
    FILES cmake/install-config.cmake
    DESTINATION "${lesstimate_INSTALL_CMAKEDIR}"
    RENAME "${package}Config.cmake"
    COMPONENT lesstimate_Development
)

install(
    FILES "${PROJECT_BINARY_DIR}/${package}ConfigVersion.cmake"
    DESTINATION "${lesstimate_INSTALL_CMAKEDIR}"
    COMPONENT lesstimate_Development
)

install(
    EXPORT lesstimateTargets
    NAMESPACE lesstimate::
    DESTINATION "${lesstimate_INSTALL_CMAKEDIR}"
    COMPONENT lesstimate_Development
)

if(PROJECT_IS_TOP_LEVEL)
  include(CPack)
endif()
