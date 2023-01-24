find_package(Doxygen REQUIRED dot)

set(DOXYGEN_BUILTIN_STL_SUPPORT YES)
set(DOXYGEN_DISABLE_INDEX NO)
set(DOXYGEN_DOT_IMAGE_FORMAT svg)
set(DOXYGEN_DOT_TRANSPARENT YES)
set(DOXYGEN_FULL_SIDEBAR NO)
set(DOXYGEN_GENERATE_TREEVIEW YES)
set(DOXYGEN_HTML_EXTRA_FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/header.html doxygen-awesome-css/doxygen-awesome-darkmode-toggle.js
    doxygen-awesome-css/doxygen-awesome-fragment-copy-button.js doxygen-awesome-css/doxygen-awesome-interactive-toc.js
    doxygen-awesome-css/doxygen-awesome-paragraph-link.js)
set(DOXYGEN_HTML_EXTRA_STYLESHEET
    doxygen-awesome-css/doxygen-awesome.css doxygen-awesome-css/doxygen-awesome-sidebar-only.css
    doxygen-awesome-css/doxygen-awesome-sidebar-only-darkmode-toggle.css)
set(DOXYGEN_HTML_HEADER header.html)
set(DOXYGEN_USE_MDFILE_AS_MAINPAGE README.md)

doxygen_add_docs(VirtualDrivingLabDocs "${PROJECT_SOURCE_DIR}/README.md" "${PROJECT_SOURCE_DIR}/include")
