include(CPackComponent)
if(WIN32)
    set(APP_DESTINATION ".")
    set(LIB_DESTINATION "lib")
    set(DOC_DESTINATION "docs")
    set(CPACK_GENERATOR "NSIS")
elseif(UNIX AND NOT APPLE)
    set(APP_DESTINATION "")
    set(LIB_DESTINATION "")
    set(DOC_DESTINATION "docs/hello")
    set(CPACK_GENERATOR "RPM")
endif()

# Files
qt_generate_deploy_app_script(
    TARGET ${APP_NAME}
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)
install(
    SCRIPT
    ${deploy_script}
    COMPONENT major
)
install(
    TARGETS ${APP_NAME} ${APP_NAME_LOW}_lib
    BUNDLE  DESTINATION ${APP_DESTINATION}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
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
set(CPACK_NSIS_CREATE_ICONS_EXTRA
    "CreateShortCut '$SMPROGRAMS\\\\$STARTMENU_FOLDER\\\\${APP_NAME}.lnk' '$INSTDIR\\\\bin\\\\${APP_NAME}.exe'"
    "CreateShortCut '$DESKTOP\\\\${APP_NAME}.lnk' '$INSTDIR\\\\bin\\\\${APP_NAME}.exe'"
)
set(CPACK_NSIS_DELETE_ICONS_EXTRA
    "Delete '$SMPROGRAMS\\\\$STARTMENU_FOLDER\\\\${APP_NAME}.lnk'"
    "Delete '$DESKTOP\\\\${APP_NAME}.lnk'"
)
set(CPACK_NSIS_MUI_WELCOMEFINISHPAGE_BITMAP "${CMAKE_CURRENT_SOURCE_DIR}\\\\res\\\\welcome.bmp")
set(CPACK_NSIS_MUI_ICON "${CMAKE_CURRENT_SOURCE_DIR}\\\\res\\\\icon_install.ico")
set(CPACK_NSIS_MUI_UNIICON "${CMAKE_CURRENT_SOURCE_DIR}\\\\res\\\\icon_remove.ico")
set(CPACK_NSIS_DISPLAY_NAME "${APP_NAME}")
set(CPACK_NSIS_INSTALLED_ICON_NAME "${APP_NAME}")
set(CPACK_NSIS_MUI_LICENSE_PAGE ON)
set(CPACK_NSIS_URL_INFO_ABOUT "https://etheryo.fr")
set(CPACK_NSIS_CONTACT "yoboujon@etheryo.fr")

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
