# Collect all files that may contain translatable texts
FILE( GLOB_RECURSE POT_FILE_DEPENDS RELATIVE ${LIBZYPP_SOURCE_DIR} "*.h" "*.cc" )
SET( POT_FILE_DEPENDS_ZYPP_TUI ${POT_FILE_DEPENDS} PARENT_SCOPE )

INCLUDE_DIRECTORIES ( ${LIBZYPP_SOURCE_DIR} )

ADD_DEFINITIONS( -DLOCALEDIR="${CMAKE_INSTALL_PREFIX}/share/locale" -DTEXTDOMAIN="zypp" -DZYPP_DLL )

FIND_PACKAGE( Readline REQUIRED )

SET( zypp_tui_toplevel_headers
  Application
  application.h
  Config
  config.h
  Table.h
)
INSTALL(  FILES ${zypp_tui_toplevel_headers} DESTINATION "${INCLUDE_INSTALL_DIR}/zypp-tui" )

SET( zypp_tui_output_headers
  output/AliveCursor.h
  output/Out.h
  output/OutNormal.h
  output/PromptOptions
  output/promptoptions.h
  output/Utf8.h
)
INSTALL(  FILES ${zypp_tui_output_headers} DESTINATION "${INCLUDE_INSTALL_DIR}/zypp-tui/output" )

SET( zypp_tui_utils_headers
  utils/ansi.h
  utils/colors.h
  utils/console.h
  utils/richtext.h
  utils/text.h
)
INSTALL(  FILES ${zypp_tui_utils_headers} DESTINATION "${INCLUDE_INSTALL_DIR}/zypp-tui/utils" )


SET( zypp_tui_headers
  ${zypp_tui_toplevel_headers}
  ${zypp_tui_output_headers}
  ${zypp_tui_utils_headers}
)

SET( zypp_tui_SRCS
  application.cc
  config.cc
  Table.cc
  output/Out.cc
  output/OutNormal.cc
  output/promptoptions.cc
  utils/colors.cc
  utils/console.cc
  utils/richtext.cc
  utils/text.cc
)

SET ( zypp_HEADERS
  ${zypp_tui_headers}
)

SET ( zypp_SRCS
  ${zypp_tui_SRCS}
)

set(CMAKE_CXX_VISIBILITY_PRESET "default")
set(CMAKE_VISIBILITY_INLINES_HIDDEN 1)

if ( ZYPP_CXX_CLANG_TIDY OR ZYPP_CXX_CPPCHECK )
  if (ZYPP_CXX_CLANG_TIDY)
    set( CMAKE_CXX_CLANG_TIDY ${ZYPP_CXX_CLANG_TIDY} )
  endif(ZYPP_CXX_CLANG_TIDY)

  if (ZYPP_CXX_CPPCHECK)
    set(CMAKE_CXX_CPPCHECK ${ZYPP_CXX_CPPCHECK})
  endif(ZYPP_CXX_CPPCHECK)
endif( ZYPP_CXX_CLANG_TIDY OR ZYPP_CXX_CPPCHECK )

add_library(objlib OBJECT ${zypp_SRCS})
set_property(TARGET objlib PROPERTY POSITION_INDEPENDENT_CODE 1)
add_library(zypp-tui-static STATIC $<TARGET_OBJECTS:objlib>)
add_library(zypp-tui-shared SHARED $<TARGET_OBJECTS:objlib>)

ADD_LIBRARY( zypp-tui STATIC ${zypp_SRCS} ${zypp_HEADERS} )
add_dependencies( zypp-tui zypp-core )

set_target_properties( zypp-tui PROPERTIES COMPILE_FLAGS "-ffat-lto-objects")

target_link_libraries( zypp-tui PRIVATE zypp_lib_compiler_flags )
target_link_libraries( zypp-tui INTERFACE ${READLINE_LIBRARY})
target_include_directories( zypp-tui PUBLIC ${READLINE_INCLUDE_DIR})
# target_compile_options( zypp-tui PUBLIC ${READLINE_CFLAGS_OTHER})

INSTALL(TARGETS zypp-tui-static ARCHIVE DESTINATION ${LIB_INSTALL_DIR} )
INSTALL(TARGETS zypp-tui-shared LIBRARY DESTINATION ${LIB_INSTALL_DIR} )

# utils/text.* utils/console.* utils/colors.* utils/ansi.h output/Utf8.h output/AliveCursor.h utils/richtext.* output/Out.* output/OutNormal.* Table.*
# -> move config for colors to zypp-tui
