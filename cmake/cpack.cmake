include(CPackComponent)
if(WIN32)
    set(APP_DESTINATION ".")
    set(DOC_DESTINATION "docs")
    set(CPACK_GENERATOR "NSIS")
elseif(UNIX AND NOT APPLE)
    set(APP_DESTINATION "")
    set(DOC_DESTINATION "docs/${APP_NAME_LOW}")
    set(CPACK_GENERATOR "RPM")
endif()

# Files
install(
    TARGETS ${APP_NAME_LOW}_cli ${APP_NAME_LOW}
    RUNTIME
    DESTINATION "${APP_DESTINATION}"
    COMPONENT major
)
install(
    TARGETS ${APP_NAME_LOW}_lib
    LIBRARY
    COMPONENT major
)
install(
    FILES README.md 
    DESTINATION "${DOC_DESTINATION}" 
    COMPONENT major
)

# Config
cpack_add_component(
    major
    DISPLAY_NAME "Core Program"
    DESCRIPTION "The main application"
    REQUIRED
)

# NSIS
set(CPACK_NSIS_DISPLAY_NAME "${APP_NAME}")
set(CPACK_NSIS_INSTALLED_ICON_NAME "${APP_NAME}")
set(CPACK_NSIS_MUI_LICENSE_PAGE ON)
set(CPACK_NSIS_HELP_LINK "https://etheryo.fr/vpscraft/help")
set(CPACK_NSIS_URL_INFO_ABOUT "https://etheryo.fr/vpscraft")
set(CPACK_NSIS_CONTACT "support@etheryo.fr")

# RPM
set(CPACK_RPM_PACKAGE_RELEASE_DIST  ON)
set(CPACK_RPM_COMPONENT_INSTALL ON)
set(CPACK_RPM_MAIN_COMPONENT major)
set(CPACK_RPM_FILE_NAME "RPM-DEFAULT")
set(CPACK_RPM_DEBUGINFO_SINGLE_PACKAGE OFF)

# CPack properties
set(CPACK_COMPONENTS_ALL major)
set(CPACK_PACKAGE_INSTALL_DIRECTORY "${APP_NAME}")
set(CPACK_PACKAGE_VENDOR "Yohan Boujon")
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/LICENSE")
include(CPack)
