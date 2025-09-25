include(CPackComponent)
if(WIN32)
    set(APP_DESTINATION ".")
    set(LIB_DESTINATION "lib")
    set(DOC_DESTINATION "docs")
    set(CPACK_GENERATOR "INNOSETUP")
elseif(UNIX AND NOT APPLE)
    set(APP_DESTINATION "")
    set(LIB_DESTINATION "")
    set(DOC_DESTINATION "docs/hello")
    set(CPACK_GENERATOR "RPM")
endif()

# Files
if(WIN32)
    set(deploy_tool_options_arg
    --release
    )
    qt_generate_deploy_app_script(
    TARGET ${APP_NAME}
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
    NO_TRANSLATIONS
    DEPLOY_TOOL_OPTIONS ${deploy_tool_options_arg}
    )
    install(
    SCRIPT
    ${deploy_script}
    COMPONENT major
    )

    string(REPLACE "\\" "/" VCPKG_PATH $ENV{VCPKG_ROOT})
    file(GLOB OPENSSL_DLLS
        "${VCPKG_PATH}/installed/x64-windows/bin/ssh.dll"
        "${VCPKG_PATH}/installed/x64-windows/bin/libcrypto*.dll"
    )
    install(
        FILES ${OPENSSL_DLLS}
        DESTINATION ${CMAKE_INSTALL_BINDIR}
        COMPONENT major
    )
endif()
install(
    TARGETS ${APP_NAME} ${APP_NAME_LOW}_cli ${APP_NAME_LOW}_lib
    RUNTIME
    DESTINATION ${CMAKE_INSTALL_BINDIR}
    COMPONENT major
)
# Config
cpack_add_component(
    major
    DISPLAY_NAME "Core Program"
    DESCRIPTION "The main application"
    REQUIRED
)

# Inno Setup
set(CPACK_INNOSETUP_SETUP_DisableWelcomePage OFF)
set(CPACK_INNOSETUP_SETUP_DisableProgramGroupPage ON)
set(CPACK_INNOSETUP_SETUP_WizardImageFile "${CMAKE_CURRENT_SOURCE_DIR}/res/welcome.bmp")
set(CPACK_INNOSETUP_SETUP_UninstallDisplayIcon "${CMAKE_CURRENT_SOURCE_DIR}/res/icon.ico")
set(CPACK_INNOSETUP_SETUP_DisableFinishedPage OFF)
# set(CPACK_INNOSETUP_SETUP_WizardSmallImageFile "${CMAKE_CURRENT_SOURCE_DIR}/res/icon.bmp")
set(CPACK_INNOSETUP_EXTRA_SCRIPTS "${CMAKE_CURRENT_SOURCE_DIR}/cmake/setup.iss")
set(CPACK_INNOSETUP_USE_MODERN_WIZARD ON)
set(CPACK_INNOSETUP_ICON_FILE "${CMAKE_CURRENT_SOURCE_DIR}/res/icon_install.ico")

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
