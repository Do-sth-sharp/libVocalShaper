# 在CMake下使用libVocalShaper创建模块

## 环境要求
- CMake 3.15及更高版本。  
- Windows平台下使用支持C++20的MSVC编译器。  
- Linux及Mac平台暂未提供官方支持，但理应使用支持C++20的编译器。  

## 编译JUCE
在编译JUCE时，应提前指定以下CMake变量： 
- `OUT_DIR` 编译生成的dll的输出位置，否则默认输出至CMakeLists.txt目录下的Out目录中。  
- `JUCEHEADER_DIR` JuceHeader.h文件及相应的cpp和mm文件保存的目录，一般这些文件可以用Projucer生成，如果无法使用Projucer生成这些文件，可以使用JuceHearder-template目录中的文件。  
- `JUCELIBRARY_DIR` JUCE库的modules目录路径。  

## 编译libVocalShaper
在编译libVocalShaper时，应提前指定以下CMake变量：  
- `OUT_DIR` 指定编译生成的dll的输出位置，否则默认输出至CMakeLists.txt目录下的Out目录中。  
- `JUCEHEADER_DIR` JuceHeader.h文件及相应的cpp和mm文件保存的目录，一般这些文件可以用Projucer生成，如果无法使用Projucer生成这些文件，可以使用JuceHearder-template目录中的文件。  
- `JUCELIBRARY_DIR` JUCE库的modules目录路径。  

## 编译模块
在编译模块时，应提前指定以下CMake变量：
- `OUT_DIR` 指定编译生成的dll的输出位置，否则默认输出至CMakeLists.txt目录下的Out目录中。***注意！实际的模块输出目录将会是该目录下modules/模块名目录，如果想要实时测试模块，请将该目录设为VocalShaper软件目录。***  
- `JUCEHEADER_DIR` JuceHeader.h文件及相应的cpp和mm文件保存的目录，一般这些文件可以用Projucer生成，如果无法使用Projucer生成这些文件，可以使用JuceHearder-template目录中的文件。  
- `JUCELIBRARY_DIR` JUCE库的modules目录路径。  
- `LIBJMODULE_DIR` libJModule库目录。  
- `VSLIBRARY_DIR` libVocalShaper库目录。  

***使用下方的CMakeLists.txt模板编译模块时应保证目录名与模块ID相同***

## 编译JUCE的CMakeLists.txt模板
```cmake
#设置基本属性
cmake_minimum_required (VERSION 3.15)

project (JUCE VERSION 7.1.0 LANGUAGES CXX C)

if (NOT DEFINED CMAKE_BUILD_TYPE)
    set (CMAKE_BUILD_TYPE "Release"  CACHE STRING "Choose the type of build." FORCE)
endif (NOT DEFINED CMAKE_BUILD_TYPE)

set(CMAKE_CXX_STANDARD 20)#使用C++20
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_C_STANDARD 17)#使用C17
set(CMAKE_C_EXTENSIONS OFF)
set(CMAKE_C_STANDARD_REQUIRED ON)

set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>DLL")#MSVC下使用/MD和/MDd

#初始化库目录
if (NOT DEFINED OUT_DIR)
	set (OUT_DIR ${CMAKE_CURRENT_SOURCE_DIR}/Out)
endif ()
if (NOT DEFINED JUCEHEADER_DIR)
	set (JUCEHEADER_DIR ${CMAKE_CURRENT_SOURCE_DIR}/JuceLibraryCode)
endif ()
if (NOT DEFINED JUCELIBRARY_DIR)
	set (JUCELIBRARY_DIR ${CMAKE_CURRENT_SOURCE_DIR}/JUCE/modules)
endif ()

#设置通用属性
set (DYNAMIC_LIBRARY JUCE)

if (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
add_compile_definitions (JUCE_DLL_BUILD=1)
add_compile_definitions (JUCE_DISABLE_DLL_ALLOCATORS=1)
endif ()
add_compile_definitions (JUCE_MODAL_LOOPS_PERMITTED=1)

###############################################################################
# Xcode (macOS)
###############################################################################

if (APPLE)

add_library (${DYNAMIC_LIBRARY} SHARED
    ${JUCEHEADER_DIR}/include_juce_analytics.cpp
    ${JUCEHEADER_DIR}/include_juce_audio_basics.mm
    ${JUCEHEADER_DIR}/include_juce_audio_devices.mm
    ${JUCEHEADER_DIR}/include_juce_audio_formats.mm
    ${JUCEHEADER_DIR}/include_juce_audio_processors.mm
    ${JUCEHEADER_DIR}/include_juce_audio_utils.mm
    ${JUCEHEADER_DIR}/include_juce_box2d.cpp
    ${JUCEHEADER_DIR}/include_juce_core.mm
    ${JUCEHEADER_DIR}/include_juce_cryptography.mm
    ${JUCEHEADER_DIR}/include_juce_data_structures.mm
    ${JUCEHEADER_DIR}/include_juce_dsp.mm
    ${JUCEHEADER_DIR}/include_juce_events.mm
    ${JUCEHEADER_DIR}/include_juce_graphics.mm
    ${JUCEHEADER_DIR}/include_juce_gui_basics.mm
    ${JUCEHEADER_DIR}/include_juce_gui_extra.mm
    ${JUCEHEADER_DIR}/include_juce_opengl.mm
    ${JUCEHEADER_DIR}/include_juce_osc.cpp
    ${JUCEHEADER_DIR}/include_juce_product_unlocking.mm
    ${JUCEHEADER_DIR}/include_juce_video.mm
    ${JUCEHEADER_DIR}/JuceHeader.h
)

set_source_files_properties (${JUCEHEADER_DIR}/JuceHeader.h PROPERTIES HEADER_FILE_ONLY TRUE)

set_target_properties (${DYNAMIC_LIBRARY} PROPERTIES SUFFIX ".dylib")

#------------------------------------------------------------------------------
# Config: Debug
#------------------------------------------------------------------------------

if (CMAKE_BUILD_TYPE STREQUAL Debug)

execute_process (COMMAND uname -m OUTPUT_VARIABLE JUCE_ARCH_LABEL OUTPUT_STRIP_TRAILING_WHITESPACE)

target_include_directories (${DYNAMIC_LIBRARY} PRIVATE
    ${JUCEHEADER_DIR}
    ${JUCELIBRARY_DIR}
)

target_compile_definitions (${DYNAMIC_LIBRARY} PRIVATE
    _DEBUG=1
    DEBUG=1
    JUCE_DISPLAY_SPLASH_SCREEN=0
    JUCE_USE_DARK_SPLASH_SCREEN=1
    JUCE_MODULE_AVAILABLE_juce_analytics=1
    JUCE_MODULE_AVAILABLE_juce_audio_basics=1
    JUCE_MODULE_AVAILABLE_juce_audio_devices=1
    JUCE_MODULE_AVAILABLE_juce_audio_formats=1
    JUCE_MODULE_AVAILABLE_juce_audio_processors=1
    JUCE_MODULE_AVAILABLE_juce_audio_utils=1
    JUCE_MODULE_AVAILABLE_juce_box2d=1
    JUCE_MODULE_AVAILABLE_juce_core=1
    JUCE_MODULE_AVAILABLE_juce_cryptography=1
    JUCE_MODULE_AVAILABLE_juce_data_structures=1
    JUCE_MODULE_AVAILABLE_juce_dsp=1
    JUCE_MODULE_AVAILABLE_juce_events=1
    JUCE_MODULE_AVAILABLE_juce_graphics=1
    JUCE_MODULE_AVAILABLE_juce_gui_basics=1
    JUCE_MODULE_AVAILABLE_juce_gui_extra=1
    JUCE_MODULE_AVAILABLE_juce_opengl=1
    JUCE_MODULE_AVAILABLE_juce_osc=1
    JUCE_MODULE_AVAILABLE_juce_product_unlocking=1
    JUCE_MODULE_AVAILABLE_juce_video=1
    JUCE_GLOBAL_MODULE_SETTINGS_INCLUDED=1
    JUCE_STRICT_REFCOUNTEDPOINTER=1
    JUCE_STANDALONE_APPLICATION=0
    JucePlugin_Build_VST=0
    JucePlugin_Build_VST3=0
    JucePlugin_Build_AU=0
    JucePlugin_Build_AUv3=0
    JucePlugin_Build_RTAS=0
    JucePlugin_Build_AAX=0
    JucePlugin_Build_Standalone=0
    JucePlugin_Build_Unity=0
)

target_compile_options (${DYNAMIC_LIBRARY} PRIVATE
    -mmacosx-version-min=10.11
    -O0
    -stdlib=libc++
)

set_target_properties (${DYNAMIC_LIBRARY} PROPERTIES
    OUTPUT_NAME "JUCE"
    CXX_STANDARD 20
    CXX_EXTENSIONS OFF
    XCODE_ATTRIBUTE_MTL_HEADER_SEARCH_PATHS "${JUCEHEADER_DIR} ${JUCELIBRARY_DIR}"
    XCODE_ATTRIBUTE_CLANG_LINK_OBJC_RUNTIME NO
    XCODE_ATTRIBUTE_CODE_SIGN_IDENTITY ""
    XCODE_ATTRIBUTE_COMBINE_HIDPI_IMAGES YES
    XCODE_ATTRIBUTE_CONFIGURATION_BUILD_DIR "${OUT_DIR}/build"
    XCODE_ATTRIBUTE_COPY_PHASE_STRIP NO
    XCODE_ATTRIBUTE_EXCLUDED_ARCHS ""
    XCODE_ATTRIBUTE_GCC_DYNAMIC_NO_PIC NO
    XCODE_ATTRIBUTE_GCC_VERSION com.apple.compilers.llvm.clang.1_0
    XCODE_ATTRIBUTE_PRODUCT_BUNDLE_IDENTIFIER com.RawMaterialSoftware.JUCE
    XCODE_ATTRIBUTE_PRODUCT_NAME "JUCE"
    XCODE_ATTRIBUTE_USE_HEADERMAP NO
    XCODE_ATTRIBUTE_VALIDATE_WORKSPACE_SKIPPED_SDK_FRAMEWORKS OpenGL
    XCODE_ATTRIBUTE_VALID_ARCHS "i386 x86_64 arm64 arm64e"
)

target_link_libraries (${DYNAMIC_LIBRARY} PRIVATE
    "-framework Accelerate"
    "-framework AudioToolbox"
    "-framework AVFoundation"
    "-framework AVKit"
    "-framework Carbon"
    "-framework Cocoa"
    "-framework CoreAudio"
    "-framework CoreAudioKit"
    "-framework CoreMedia"
    "-framework CoreMIDI"
    "-framework DiscRecording"
    "-framework Foundation"
    "-framework IOKit"
    "-framework OpenGL"
    "-framework QuartzCore"
    "-framework WebKit"
)

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-common -Wswitch -Wunused-variable -Wparentheses -Wnon-virtual-dtor -Wshorten-64-to-32 -Wundeclared-selector -Wuninitialized -Wunused-function -Wbool-conversion -Wcomma -Wconstant-conversion -Wempty-body -Wenum-conversion -Winfinite-recursion -Wint-conversion -Wrange-loop-analysis -Wstrict-prototypes -Wmove -Wunreachable-code -Wduplicate-method-match -Wreorder -fvisibility-inlines-hidden")
set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${CMAKE_CXX_FLAGS}")

endif (CMAKE_BUILD_TYPE STREQUAL Debug)

#------------------------------------------------------------------------------
# Config: Release
#------------------------------------------------------------------------------

if (CMAKE_BUILD_TYPE STREQUAL Release)

execute_process (COMMAND uname -m OUTPUT_VARIABLE JUCE_ARCH_LABEL OUTPUT_STRIP_TRAILING_WHITESPACE)

target_include_directories (${DYNAMIC_LIBRARY} PRIVATE
    ${JUCEHEADER_DIR}
    ${JUCELIBRARY_DIR}
)

target_compile_definitions (${DYNAMIC_LIBRARY} PRIVATE
    _NDEBUG=1
    NDEBUG=1
    JUCE_DISPLAY_SPLASH_SCREEN=0
    JUCE_USE_DARK_SPLASH_SCREEN=1
    JUCE_MODULE_AVAILABLE_juce_analytics=1
    JUCE_MODULE_AVAILABLE_juce_audio_basics=1
    JUCE_MODULE_AVAILABLE_juce_audio_devices=1
    JUCE_MODULE_AVAILABLE_juce_audio_formats=1
    JUCE_MODULE_AVAILABLE_juce_audio_processors=1
    JUCE_MODULE_AVAILABLE_juce_audio_utils=1
    JUCE_MODULE_AVAILABLE_juce_box2d=1
    JUCE_MODULE_AVAILABLE_juce_core=1
    JUCE_MODULE_AVAILABLE_juce_cryptography=1
    JUCE_MODULE_AVAILABLE_juce_data_structures=1
    JUCE_MODULE_AVAILABLE_juce_dsp=1
    JUCE_MODULE_AVAILABLE_juce_events=1
    JUCE_MODULE_AVAILABLE_juce_graphics=1
    JUCE_MODULE_AVAILABLE_juce_gui_basics=1
    JUCE_MODULE_AVAILABLE_juce_gui_extra=1
    JUCE_MODULE_AVAILABLE_juce_opengl=1
    JUCE_MODULE_AVAILABLE_juce_osc=1
    JUCE_MODULE_AVAILABLE_juce_product_unlocking=1
    JUCE_MODULE_AVAILABLE_juce_video=1
    JUCE_GLOBAL_MODULE_SETTINGS_INCLUDED=1
    JUCE_STRICT_REFCOUNTEDPOINTER=1
    JUCE_STANDALONE_APPLICATION=0
    JucePlugin_Build_VST=0
    JucePlugin_Build_VST3=0
    JucePlugin_Build_AU=0
    JucePlugin_Build_AUv3=0
    JucePlugin_Build_RTAS=0
    JucePlugin_Build_AAX=0
    JucePlugin_Build_Standalone=0
    JucePlugin_Build_Unity=0
)

target_compile_options (${DYNAMIC_LIBRARY} PRIVATE
    -mmacosx-version-min=10.11
    -O3
    -flto
    -stdlib=libc++
)

set_target_properties (${DYNAMIC_LIBRARY} PROPERTIES
    OUTPUT_NAME "JUCE"
    CXX_STANDARD 20
    CXX_EXTENSIONS OFF
    XCODE_ATTRIBUTE_MTL_HEADER_SEARCH_PATHS "${JUCEHEADER_DIR} ${JUCELIBRARY_DIR}"
    XCODE_ATTRIBUTE_CLANG_LINK_OBJC_RUNTIME NO
    XCODE_ATTRIBUTE_CODE_SIGN_IDENTITY ""
    XCODE_ATTRIBUTE_COMBINE_HIDPI_IMAGES YES
    XCODE_ATTRIBUTE_CONFIGURATION_BUILD_DIR "${OUT_DIR}/build"
    XCODE_ATTRIBUTE_DEAD_CODE_STRIPPING YES
    XCODE_ATTRIBUTE_EXCLUDED_ARCHS ""
    XCODE_ATTRIBUTE_GCC_GENERATE_DEBUGGING_SYMBOLS NO
    XCODE_ATTRIBUTE_GCC_VERSION com.apple.compilers.llvm.clang.1_0
    XCODE_ATTRIBUTE_PRODUCT_BUNDLE_IDENTIFIER com.RawMaterialSoftware.JUCE
    XCODE_ATTRIBUTE_PRODUCT_NAME "JUCE"
    XCODE_ATTRIBUTE_USE_HEADERMAP NO
    XCODE_ATTRIBUTE_VALIDATE_WORKSPACE_SKIPPED_SDK_FRAMEWORKS OpenGL
    XCODE_ATTRIBUTE_VALID_ARCHS "i386 x86_64 arm64 arm64e"
)

target_link_libraries (${DYNAMIC_LIBRARY} PRIVATE
    "-framework Accelerate"
    "-framework AudioToolbox"
    "-framework AVFoundation"
    "-framework AVKit"
    "-framework Carbon"
    "-framework Cocoa"
    "-framework CoreAudio"
    "-framework CoreAudioKit"
    "-framework CoreMedia"
    "-framework CoreMIDI"
    "-framework DiscRecording"
    "-framework Foundation"
    "-framework IOKit"
    "-framework OpenGL"
    "-framework QuartzCore"
    "-framework WebKit"
)

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-common -Wswitch -Wunused-variable -Wparentheses -Wnon-virtual-dtor -Wshorten-64-to-32 -Wundeclared-selector -Wuninitialized -Wunused-function -Wbool-conversion -Wcomma -Wconstant-conversion -Wempty-body -Wenum-conversion -Winfinite-recursion -Wint-conversion -Wrange-loop-analysis -Wstrict-prototypes -Wmove -Wunreachable-code -Wduplicate-method-match -Wreorder -fvisibility-inlines-hidden")
set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${CMAKE_CXX_FLAGS}")

endif (CMAKE_BUILD_TYPE STREQUAL Release)

endif()

###############################################################################
# Linux Makefile
###############################################################################

if (UNIX AND NOT APPLE)

find_package (PkgConfig REQUIRED)
pkg_search_module (ALSA REQUIRED alsa)
pkg_search_module (FREETYPE2 REQUIRED freetype2)
pkg_search_module (LIBCURL REQUIRED libcurl)
pkg_search_module (WEBKIT2GTK-4.0 REQUIRED webkit2gtk-4.0)
pkg_search_module (GTK+-X11-3.0 REQUIRED gtk+-x11-3.0)

add_library (${DYNAMIC_LIBRARY} SHARED
    ${JUCEHEADER_DIR}/include_juce_analytics.cpp
    ${JUCEHEADER_DIR}/include_juce_audio_basics.cpp
    ${JUCEHEADER_DIR}/include_juce_audio_devices.cpp
    ${JUCEHEADER_DIR}/include_juce_audio_formats.cpp
    ${JUCEHEADER_DIR}/include_juce_audio_processors.cpp
    ${JUCEHEADER_DIR}/include_juce_audio_utils.cpp
    ${JUCEHEADER_DIR}/include_juce_box2d.cpp
    ${JUCEHEADER_DIR}/include_juce_core.cpp
    ${JUCEHEADER_DIR}/include_juce_cryptography.cpp
    ${JUCEHEADER_DIR}/include_juce_data_structures.cpp
    ${JUCEHEADER_DIR}/include_juce_dsp.cpp
    ${JUCEHEADER_DIR}/include_juce_events.cpp
    ${JUCEHEADER_DIR}/include_juce_graphics.cpp
    ${JUCEHEADER_DIR}/include_juce_gui_basics.cpp
    ${JUCEHEADER_DIR}/include_juce_gui_extra.cpp
    ${JUCEHEADER_DIR}/include_juce_opengl.cpp
    ${JUCEHEADER_DIR}/include_juce_osc.cpp
    ${JUCEHEADER_DIR}/include_juce_product_unlocking.cpp
    ${JUCEHEADER_DIR}/include_juce_video.cpp
    ${JUCEHEADER_DIR}/JuceHeader.h
)

set_source_files_properties (${JUCEHEADER_DIR}/JuceHeader.h PROPERTIES HEADER_FILE_ONLY TRUE)

set_target_properties (${DYNAMIC_LIBRARY} PROPERTIES SUFFIX ".so")

#------------------------------------------------------------------------------
# Config: Debug
#------------------------------------------------------------------------------

if (CMAKE_BUILD_TYPE STREQUAL Debug)

execute_process (COMMAND uname -m OUTPUT_VARIABLE JUCE_ARCH_LABEL OUTPUT_STRIP_TRAILING_WHITESPACE)

include_directories (
    ${JUCEHEADER_DIR}
    ${JUCELIBRARY_DIR}
    ${ALSA_INCLUDE_DIRS}
    ${FREETYPE2_INCLUDE_DIRS}
    ${LIBCURL_INCLUDE_DIRS}
    ${WEBKIT2GTK-4.0_INCLUDE_DIRS}
    ${GTK+-X11-3.0_INCLUDE_DIRS}
)

find_library (RT rt
)

find_library (DL dl
)

find_library (PTHREAD pthread
)

find_library (GL GL
)

set_target_properties (${DYNAMIC_LIBRARY} PROPERTIES
    OUTPUT_NAME "JUCE"
    CXX_STANDARD 20
    CXX_EXTENSIONS OFF
)

target_compile_definitions (${DYNAMIC_LIBRARY} PRIVATE
    LINUX=1
    DEBUG=1
    _DEBUG=1
    JUCE_DISPLAY_SPLASH_SCREEN=0
    JUCE_USE_DARK_SPLASH_SCREEN=1
    JUCE_MODULE_AVAILABLE_juce_analytics=1
    JUCE_MODULE_AVAILABLE_juce_audio_basics=1
    JUCE_MODULE_AVAILABLE_juce_audio_devices=1
    JUCE_MODULE_AVAILABLE_juce_audio_formats=1
    JUCE_MODULE_AVAILABLE_juce_audio_processors=1
    JUCE_MODULE_AVAILABLE_juce_audio_utils=1
    JUCE_MODULE_AVAILABLE_juce_box2d=1
    JUCE_MODULE_AVAILABLE_juce_core=1
    JUCE_MODULE_AVAILABLE_juce_cryptography=1
    JUCE_MODULE_AVAILABLE_juce_data_structures=1
    JUCE_MODULE_AVAILABLE_juce_dsp=1
    JUCE_MODULE_AVAILABLE_juce_events=1
    JUCE_MODULE_AVAILABLE_juce_graphics=1
    JUCE_MODULE_AVAILABLE_juce_gui_basics=1
    JUCE_MODULE_AVAILABLE_juce_gui_extra=1
    JUCE_MODULE_AVAILABLE_juce_opengl=1
    JUCE_MODULE_AVAILABLE_juce_osc=1
    JUCE_MODULE_AVAILABLE_juce_product_unlocking=1
    JUCE_MODULE_AVAILABLE_juce_video=1
    JUCE_GLOBAL_MODULE_SETTINGS_INCLUDED=1
    JUCE_STRICT_REFCOUNTEDPOINTER=1
    JUCE_STANDALONE_APPLICATION=0
    JucePlugin_Build_VST=0
    JucePlugin_Build_VST3=0
    JucePlugin_Build_AU=0
    JucePlugin_Build_AUv3=0
    JucePlugin_Build_RTAS=0
    JucePlugin_Build_AAX=0
    JucePlugin_Build_Standalone=0
    JucePlugin_Build_Unity=0
)

target_compile_options (${DYNAMIC_LIBRARY} PRIVATE
    -fPIC
    -fvisibility=default
)

target_link_libraries (${DYNAMIC_LIBRARY} PRIVATE
    
    -shared
    -fvisibility=default
    ${RT}
    ${DL}
    ${PTHREAD}
    ${GL}
    ${ALSA_LIBRARIES}
    ${FREETYPE2_LIBRARIES}
    ${LIBCURL_LIBRARIES}
)

set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS}  -pthread -fPIC -g -ggdb -O0")
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${CMAKE_C_FLAGS}" )

endif (CMAKE_BUILD_TYPE STREQUAL Debug)

#------------------------------------------------------------------------------
# Config: Release
#------------------------------------------------------------------------------

if (CMAKE_BUILD_TYPE STREQUAL Release)

execute_process (COMMAND uname -m OUTPUT_VARIABLE JUCE_ARCH_LABEL OUTPUT_STRIP_TRAILING_WHITESPACE)

include_directories (
    ${JUCEHEADER_DIR}
    ${JUCELIBRARY_DIR}
    ${ALSA_INCLUDE_DIRS}
    ${FREETYPE2_INCLUDE_DIRS}
    ${LIBCURL_INCLUDE_DIRS}
    ${WEBKIT2GTK-4.0_INCLUDE_DIRS}
    ${GTK+-X11-3.0_INCLUDE_DIRS}
)

find_library (RT rt
)

find_library (DL dl
)

find_library (PTHREAD pthread
)

find_library (GL GL
)

set_target_properties (${DYNAMIC_LIBRARY} PROPERTIES
    OUTPUT_NAME "JUCE"
    CXX_STANDARD 20
    CXX_EXTENSIONS OFF
)

target_compile_definitions (${DYNAMIC_LIBRARY} PRIVATE
    LINUX=1
    NDEBUG=1
    JUCE_DISPLAY_SPLASH_SCREEN=0
    JUCE_USE_DARK_SPLASH_SCREEN=1
    JUCE_MODULE_AVAILABLE_juce_analytics=1
    JUCE_MODULE_AVAILABLE_juce_audio_basics=1
    JUCE_MODULE_AVAILABLE_juce_audio_devices=1
    JUCE_MODULE_AVAILABLE_juce_audio_formats=1
    JUCE_MODULE_AVAILABLE_juce_audio_processors=1
    JUCE_MODULE_AVAILABLE_juce_audio_utils=1
    JUCE_MODULE_AVAILABLE_juce_box2d=1
    JUCE_MODULE_AVAILABLE_juce_core=1
    JUCE_MODULE_AVAILABLE_juce_cryptography=1
    JUCE_MODULE_AVAILABLE_juce_data_structures=1
    JUCE_MODULE_AVAILABLE_juce_dsp=1
    JUCE_MODULE_AVAILABLE_juce_events=1
    JUCE_MODULE_AVAILABLE_juce_graphics=1
    JUCE_MODULE_AVAILABLE_juce_gui_basics=1
    JUCE_MODULE_AVAILABLE_juce_gui_extra=1
    JUCE_MODULE_AVAILABLE_juce_opengl=1
    JUCE_MODULE_AVAILABLE_juce_osc=1
    JUCE_MODULE_AVAILABLE_juce_product_unlocking=1
    JUCE_MODULE_AVAILABLE_juce_video=1
    JUCE_GLOBAL_MODULE_SETTINGS_INCLUDED=1
    JUCE_STRICT_REFCOUNTEDPOINTER=1
    JUCE_STANDALONE_APPLICATION=0
    JucePlugin_Build_VST=0
    JucePlugin_Build_VST3=0
    JucePlugin_Build_AU=0
    JucePlugin_Build_AUv3=0
    JucePlugin_Build_RTAS=0
    JucePlugin_Build_AAX=0
    JucePlugin_Build_Standalone=0
    JucePlugin_Build_Unity=0
)

target_compile_options (${DYNAMIC_LIBRARY} PRIVATE
    -fPIC
    -fvisibility=default
)

target_link_libraries (${DYNAMIC_LIBRARY} PRIVATE
    
    -shared
    -fvisibility=default
    ${RT}
    ${DL}
    ${PTHREAD}
    ${GL}
    ${ALSA_LIBRARIES}
    ${FREETYPE2_LIBRARIES}
    ${LIBCURL_LIBRARIES}
)

set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS}  -pthread -fPIC -O3")
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${CMAKE_C_FLAGS}" )

endif (CMAKE_BUILD_TYPE STREQUAL Release)

endif()

###############################################################################
# Code::Blocks (Windows)
###############################################################################

if (WIN32)

add_library (${DYNAMIC_LIBRARY} SHARED
    ${JUCEHEADER_DIR}/include_juce_analytics.cpp
    ${JUCEHEADER_DIR}/include_juce_audio_basics.cpp
    ${JUCEHEADER_DIR}/include_juce_audio_devices.cpp
    ${JUCEHEADER_DIR}/include_juce_audio_formats.cpp
    ${JUCEHEADER_DIR}/include_juce_audio_processors.cpp
    ${JUCEHEADER_DIR}/include_juce_audio_utils.cpp
    ${JUCEHEADER_DIR}/include_juce_box2d.cpp
    ${JUCEHEADER_DIR}/include_juce_core.cpp
    ${JUCEHEADER_DIR}/include_juce_cryptography.cpp
    ${JUCEHEADER_DIR}/include_juce_data_structures.cpp
    ${JUCEHEADER_DIR}/include_juce_dsp.cpp
    ${JUCEHEADER_DIR}/include_juce_events.cpp
    ${JUCEHEADER_DIR}/include_juce_graphics.cpp
    ${JUCEHEADER_DIR}/include_juce_gui_basics.cpp
    ${JUCEHEADER_DIR}/include_juce_gui_extra.cpp
    ${JUCEHEADER_DIR}/include_juce_opengl.cpp
    ${JUCEHEADER_DIR}/include_juce_osc.cpp
    ${JUCEHEADER_DIR}/include_juce_product_unlocking.cpp
    ${JUCEHEADER_DIR}/include_juce_video.cpp
    ${JUCEHEADER_DIR}/JuceHeader.h
)

set_source_files_properties (${JUCEHEADER_DIR}/JuceHeader.h PROPERTIES HEADER_FILE_ONLY TRUE)

set_target_properties (${DYNAMIC_LIBRARY} PROPERTIES PREFIX "")
set_target_properties (${DYNAMIC_LIBRARY} PROPERTIES SUFFIX ".dll")

include_directories (
    ${JUCEHEADER_DIR}
    ${JUCELIBRARY_DIR}
)

set_target_properties (${DYNAMIC_LIBRARY} PROPERTIES
    OUTPUT_NAME "JUCE"
    CXX_STANDARD 20
    CXX_EXTENSIONS OFF
)

if (CMAKE_BUILD_TYPE STREQUAL Debug)
target_compile_definitions (${DYNAMIC_LIBRARY} PRIVATE
    DEBUG=1
    _DEBUG=1
    JUCE_DISPLAY_SPLASH_SCREEN=0
    JUCE_USE_DARK_SPLASH_SCREEN=1
    JUCE_MODULE_AVAILABLE_juce_analytics=1
    JUCE_MODULE_AVAILABLE_juce_audio_basics=1
    JUCE_MODULE_AVAILABLE_juce_audio_devices=1
    JUCE_MODULE_AVAILABLE_juce_audio_formats=1
    JUCE_MODULE_AVAILABLE_juce_audio_processors=1
    JUCE_MODULE_AVAILABLE_juce_audio_utils=1
    JUCE_MODULE_AVAILABLE_juce_box2d=1
    JUCE_MODULE_AVAILABLE_juce_core=1
    JUCE_MODULE_AVAILABLE_juce_cryptography=1
    JUCE_MODULE_AVAILABLE_juce_data_structures=1
    JUCE_MODULE_AVAILABLE_juce_dsp=1
    JUCE_MODULE_AVAILABLE_juce_events=1
    JUCE_MODULE_AVAILABLE_juce_graphics=1
    JUCE_MODULE_AVAILABLE_juce_gui_basics=1
    JUCE_MODULE_AVAILABLE_juce_gui_extra=1
    JUCE_MODULE_AVAILABLE_juce_opengl=1
    JUCE_MODULE_AVAILABLE_juce_osc=1
    JUCE_MODULE_AVAILABLE_juce_product_unlocking=1
    JUCE_MODULE_AVAILABLE_juce_video=1
    JUCE_GLOBAL_MODULE_SETTINGS_INCLUDED=1
    JUCE_STRICT_REFCOUNTEDPOINTER=1
    JUCE_STANDALONE_APPLICATION=0
    JucePlugin_Build_VST=0
    JucePlugin_Build_VST3=0
    JucePlugin_Build_AU=0
    JucePlugin_Build_AUv3=0
    JucePlugin_Build_RTAS=0
    JucePlugin_Build_AAX=0
    JucePlugin_Build_Standalone=0
    JucePlugin_Build_Unity=0
)
endif (CMAKE_BUILD_TYPE STREQUAL Debug)
if (CMAKE_BUILD_TYPE STREQUAL Release)
target_compile_definitions (${DYNAMIC_LIBRARY} PRIVATE
    NDEBUG=1
    JUCE_DISPLAY_SPLASH_SCREEN=0
    JUCE_USE_DARK_SPLASH_SCREEN=1
    JUCE_MODULE_AVAILABLE_juce_analytics=1
    JUCE_MODULE_AVAILABLE_juce_audio_basics=1
    JUCE_MODULE_AVAILABLE_juce_audio_devices=1
    JUCE_MODULE_AVAILABLE_juce_audio_formats=1
    JUCE_MODULE_AVAILABLE_juce_audio_processors=1
    JUCE_MODULE_AVAILABLE_juce_audio_utils=1
    JUCE_MODULE_AVAILABLE_juce_box2d=1
    JUCE_MODULE_AVAILABLE_juce_core=1
    JUCE_MODULE_AVAILABLE_juce_cryptography=1
    JUCE_MODULE_AVAILABLE_juce_data_structures=1
    JUCE_MODULE_AVAILABLE_juce_dsp=1
    JUCE_MODULE_AVAILABLE_juce_events=1
    JUCE_MODULE_AVAILABLE_juce_graphics=1
    JUCE_MODULE_AVAILABLE_juce_gui_basics=1
    JUCE_MODULE_AVAILABLE_juce_gui_extra=1
    JUCE_MODULE_AVAILABLE_juce_opengl=1
    JUCE_MODULE_AVAILABLE_juce_osc=1
    JUCE_MODULE_AVAILABLE_juce_product_unlocking=1
    JUCE_MODULE_AVAILABLE_juce_video=1
    JUCE_GLOBAL_MODULE_SETTINGS_INCLUDED=1
    JUCE_STRICT_REFCOUNTEDPOINTER=1
    JUCE_STANDALONE_APPLICATION=0
    JucePlugin_Build_VST=0
    JucePlugin_Build_VST3=0
    JucePlugin_Build_AU=0
    JucePlugin_Build_AUv3=0
    JucePlugin_Build_RTAS=0
    JucePlugin_Build_AAX=0
    JucePlugin_Build_Standalone=0
    JucePlugin_Build_Unity=0
)
endif (CMAKE_BUILD_TYPE STREQUAL Release)

if (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
#------------------------------------------------------------------------------
# Config: Debug
#------------------------------------------------------------------------------

if (CMAKE_BUILD_TYPE STREQUAL Debug)

target_compile_options (${DYNAMIC_LIBRARY} PRIVATE
    /permissive-#符合模式:是
	/GS#安全检查:启用安全检查
	/Zc:wchar_t#将WChar_t视为内置类型:是
	/Gm-#启用最小重新生成:否
	/sdl#SDL检查:是
	/fp:precise#浮点模型:精度
	/Zc:forScope#强制For循环范围中的合规性:是
	/Gd#调用约定:__cdecl
	/nologo#取消显示启动版权标志:是
	/bigobj#较大生成对象:是
)
add_link_options (
	/MANIFEST#生成清单:是
	/NXCOMPAT#数据执行保护(DEP):是
	/DYNAMICBASE#随机基址:是
	/LARGEADDRESSAWARE#启用大地址:是
	/SUBSYSTEM:WINDOWS#子系统:窗口
	/MANIFESTUAC:NO#启用用户账户控制:否
	/NOLOGO#取消显示启动版权标志:是
)
#target_link_libraries (${DYNAMIC_LIBRARY} PRIVATE
#    -m64
#    -lgdi32
#    -luser32
#    -lkernel32
#    -lcomctl32
#    -lwinmm
#    -luuid
#    -lwsock32
#    -lwininet
#    -lversion
#    -lole32
#    -lws2_32
#    -loleaut32
#    -limm32
#    -lcomdlg32
#    -lshlwapi
#    -lrpcrt4
#    -lopengl32
#)
endif (CMAKE_BUILD_TYPE STREQUAL Debug)

#------------------------------------------------------------------------------
# Config: Release
#------------------------------------------------------------------------------

if (CMAKE_BUILD_TYPE STREQUAL Release)

target_compile_options (${DYNAMIC_LIBRARY} PRIVATE
    /permissive-#符合模式:是
	/GS#安全检查:启用安全检查
	/GL#全程序优化:是
	/Gy#启用函数级链接:是
	/Zc:wchar_t#将WChar_t视为内置类型:是
	/Gm-#启用最小重新生成:否
	/sdl#SDL检查:是
	/fp:precise#浮点模型:精度
	/Zc:forScope#强制For循环范围中的合规性:是
	/Gd#调用约定:__cdecl
	/Oi#启用内部函数:是
	/nologo#取消显示启动版权标志:是
	/bigobj#较大生成对象:是
)
add_link_options (
	/MANIFEST#生成清单:是
	/LTCG:incremental#链接时间代码生成:使用快速链接时间代码生成
	/NXCOMPAT#数据执行保护(DEP):是
	/DYNAMICBASE#随机基址:是
	/LARGEADDRESSAWARE#启用大地址:是
	/OPT:REF#引用:是
	/SUBSYSTEM:WINDOWS#子系统:窗口
	/MANIFESTUAC:NO#启用用户账户控制:否
	/OPT:ICF#启用COMDAT折叠:是
	/NOLOGO#取消显示启动版权标志:是
)
#target_link_libraries (${DYNAMIC_LIBRARY} PRIVATE
#    -m64
#    -s
#    -lgdi32
#    -luser32
#    -lkernel32
#    -lcomctl32
#    -lwinmm
#    -luuid
#    -lwsock32
#    -lwininet
#    -lversion
#    -lole32
#    -lws2_32
#    -loleaut32
#    -limm32
#    -lcomdlg32
#    -lshlwapi
#    -lrpcrt4
#    -lopengl32
#)
endif (CMAKE_BUILD_TYPE STREQUAL Release)

#set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${CMAKE_CXX_FLAGS}")
else ()
#------------------------------------------------------------------------------
# Config: Debug
#------------------------------------------------------------------------------

if (CMAKE_BUILD_TYPE STREQUAL Debug)

target_compile_options (${DYNAMIC_LIBRARY} PRIVATE
    "-m64"
    "-O0"
    "-mstackrealign"
    "-g"
)

target_link_libraries (${DYNAMIC_LIBRARY} PRIVATE
    -m64
    -lgdi32
    -luser32
    -lkernel32
    -lcomctl32
    -lwinmm
    -luuid
    -lwsock32
    -lwininet
    -lversion
    -lole32
    -lws2_32
    -loleaut32
    -limm32
    -lcomdlg32
    -lshlwapi
    -lrpcrt4
    -lopengl32
)
endif (CMAKE_BUILD_TYPE STREQUAL Debug)

#------------------------------------------------------------------------------
# Config: Release
#------------------------------------------------------------------------------

if (CMAKE_BUILD_TYPE STREQUAL Release)

target_compile_options (${DYNAMIC_LIBRARY} PRIVATE
    "-m64"
    "-O3"
    "-mstackrealign"
)

target_link_libraries (${DYNAMIC_LIBRARY} PRIVATE
    -m64
    -s
    -lgdi32
    -luser32
    -lkernel32
    -lcomctl32
    -lwinmm
    -luuid
    -lwsock32
    -lwininet
    -lversion
    -lole32
    -lws2_32
    -loleaut32
    -limm32
    -lcomdlg32
    -lshlwapi
    -lrpcrt4
    -lopengl32
)
endif (CMAKE_BUILD_TYPE STREQUAL Release)

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wno-strict-aliasing -Wno-strict-overflow")
set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${CMAKE_CXX_FLAGS}")
endif ()

endif()

set_target_properties (
	${DYNAMIC_LIBRARY}
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY ${OUT_DIR}
    LIBRARY_OUTPUT_DIRECTORY ${OUT_DIR}
    RUNTIME_OUTPUT_DIRECTORY ${OUT_DIR}
)

```

## 编译模块时使用的CMakeLists.txt模板
```cmake
#获取当前目录名
string (REGEX REPLACE ".*/\(.*\)" "\\1" CURRENT_FOLDER ${CMAKE_CURRENT_SOURCE_DIR})

#设置基本属性
cmake_minimum_required (VERSION 3.15)

project (${CURRENT_FOLDER} VERSION 0.0.1 LANGUAGES CXX C)

if (NOT DEFINED CMAKE_BUILD_TYPE)
    set (CMAKE_BUILD_TYPE "Release"  CACHE STRING "Choose the type of build." FORCE)
endif (NOT DEFINED CMAKE_BUILD_TYPE)

set(CMAKE_CXX_STANDARD 20)#使用C++20
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_C_STANDARD 17)#使用C17
set(CMAKE_C_EXTENSIONS OFF)
set(CMAKE_C_STANDARD_REQUIRED ON)

set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>DLL")#MSVC下使用/MD和/MDd

#初始化库目录
if (NOT DEFINED OUT_DIR)
	set (OUT_DIR ${CMAKE_CURRENT_SOURCE_DIR}/Out)
endif ()
if (NOT DEFINED JUCEHEADER_DIR)
	set (JUCEHEADER_DIR ${CMAKE_CURRENT_SOURCE_DIR}/JuceLibraryCode)
endif ()
if (NOT DEFINED JUCELIBRARY_DIR)
	set (JUCELIBRARY_DIR ${CMAKE_CURRENT_SOURCE_DIR}/JUCE/modules)
endif ()
if (NOT DEFINED JMADF_DIR)
	set (JMADF_DIR ${CMAKE_SOURCE_DIR}/JMADF)
endif ()
if (NOT DEFINED LIBJMODULE_DIR)
	set (LIBJMODULE_DIR ${JMADF_DIR}/libJModule)
endif ()
if (NOT DEFINED VSLIBRARY_DIR)
	set (VSLIBRARY_DIR ${CMAKE_SOURCE_DIR}/libVocalShaper)
endif ()

#文件搜索目录
include_directories (${CMAKE_SOURCE_DIR})
include_directories (${JUCEHEADER_DIR})
include_directories (${JUCELIBRARY_DIR})
include_directories (${LIBJMODULE_DIR})
include_directories (${VSLIBRARY_DIR})

#使用libJModule库
add_subdirectory (${LIBJMODULE_DIR} libJModule)

#设置目标名称
set (TARGET_NAME ${CURRENT_FOLDER})

#设置编译宏
if (CMAKE_BUILD_TYPE AND (CMAKE_BUILD_TYPE STREQUAL "Debug"))
	add_compile_definitions (_DEBUG)
elseif (CMAKE_BUILD_TYPE AND (CMAKE_BUILD_TYPE STREQUAL "Release"))
	add_compile_definitions (NDEBUG)
endif()
add_compile_definitions (JUCE_GLOBAL_MODULE_SETTINGS_INCLUDED=1)
if (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
add_compile_definitions (JUCE_DLL=1)
add_compile_definitions (JUCE_DISABLE_DLL_ALLOCATORS=1)
add_compile_definitions (_SILENCE_CXX20_CISO646_REMOVED_WARNING=1)
endif ()
add_compile_definitions (JUCE_MODAL_LOOPS_PERMITTED=1)

#设置编译器参数
if (CMAKE_BUILD_TYPE AND (CMAKE_BUILD_TYPE STREQUAL "Debug"))
	if (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
		add_compile_options (
			/permissive-#符合模式:是
			/GS#安全检查:启用安全检查
			/Zc:wchar_t#将WChar_t视为内置类型:是
			/Gm-#启用最小重新生成:否
			/sdl#SDL检查:是
			/fp:precise#浮点模型:精度
			/Zc:forScope#强制For循环范围中的合规性:是
			/Gd#调用约定:__cdecl
			/nologo#取消显示启动版权标志:是
			/bigobj#较大生成对象:是
		)
		add_link_options (
			/MANIFEST#生成清单:是
			/NXCOMPAT#数据执行保护(DEP):是
			/DYNAMICBASE#随机基址:是
			/LARGEADDRESSAWARE#启用大地址:是
			/SUBSYSTEM:WINDOWS#子系统:窗口
			/MANIFESTUAC:NO#启用用户账户控制:否
			/NOLOGO#取消显示启动版权标志:是
		)
	else ()
		add_compile_options (-fPIC)
		#add_link_options (-mbig-obj)
	endif ()
elseif (CMAKE_BUILD_TYPE AND (CMAKE_BUILD_TYPE STREQUAL "Release"))
	if (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
		add_compile_options (
			/permissive-#符合模式:是
			/GS#安全检查:启用安全检查
			/GL#全程序优化:是
			/Gy#启用函数级链接:是
			/Zc:wchar_t#将WChar_t视为内置类型:是
			/Gm-#启用最小重新生成:否
			/sdl#SDL检查:是
			/fp:precise#浮点模型:精度
			/Zc:forScope#强制For循环范围中的合规性:是
			/Gd#调用约定:__cdecl
			/Oi#启用内部函数:是
			/nologo#取消显示启动版权标志:是
			/bigobj#较大生成对象:是
		)
		add_link_options (
			/MANIFEST#生成清单:是
			/LTCG:incremental#链接时间代码生成:使用快速链接时间代码生成
			/NXCOMPAT#数据执行保护(DEP):是
			/DYNAMICBASE#随机基址:是
			/LARGEADDRESSAWARE#启用大地址:是
			/OPT:REF#引用:是
			/SUBSYSTEM:WINDOWS#子系统:窗口
			/MANIFESTUAC:NO#启用用户账户控制:否
			/OPT:ICF#启用COMDAT折叠:是
			/NOLOGO#取消显示启动版权标志:是
		)
	else ()
		add_compile_options (-fPIC)
		#add_link_options (-mbig-obj)
	endif ()
endif()

#添加目录内所有源文件
aux_source_directory(. TARGET_SOURCE)

#编译的文件
add_library (
	${TARGET_NAME} SHARED
	${LIBJMODULE_SRC}
	${TARGET_SOURCE}
)

#链接库
target_link_libraries (
	${TARGET_NAME}
	JUCE
	libVocalShaper
)

#设置目标位置
set_target_properties (
	${TARGET_NAME}
    PROPERTIES
	PREFIX ""
    ARCHIVE_OUTPUT_DIRECTORY ${OUT_DIR}/modules/${TARGET_NAME}
    LIBRARY_OUTPUT_DIRECTORY ${OUT_DIR}/modules/${TARGET_NAME}
    RUNTIME_OUTPUT_DIRECTORY ${OUT_DIR}/modules/${TARGET_NAME}
)

#添加依赖
add_dependencies (
	${TARGET_NAME}
	JUCE
	libVocalShaper
)

```