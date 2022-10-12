#设置输出路径
set (MESSAGE_CPP_DIR ${CMAKE_CURRENT_SOURCE_DIR})
if (EXISTS "${MESSAGE_CPP_DIR}" AND IS_DIRECTORY "${MESSAGE_CPP_DIR}")
        set (PROTO_META_BASE_DIR ${MESSAGE_CPP_DIR})
else ()
        file (MAKE_DIRECTORY ${MESSAGE_CPP_DIR})
        set (PROTO_META_BASE_DIR ${MESSAGE_CPP_DIR})
endif ()

#设置protoc的搜索路径
set (MESSAGE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/proto)
list (APPEND PROTO_FLAGS -I${MESSAGE_DIR})

#获取需要编译的proto文件
file (GLOB_RECURSE MSG_PROTOS ${MESSAGE_DIR}/*.proto)
set (MESSAGE_SRC "")
set (MESSAGE_HDRS "")

foreach (msg ${MSG_PROTOS})
        get_filename_component (FIL_WE ${msg} NAME_WE)

        list (APPEND MESSAGE_SRC "${MESSAGE_CPP_DIR}/${FIL_WE}.pb.cc")
        list (APPEND MESSAGE_HDRS "${MESSAGE_CPP_DIR}/${FIL_WE}.pb.h")

		# 使用自定义命令
        add_custom_command (
          OUTPUT "${MESSAGE_CPP_DIR}/${FIL_WE}.pb.cc"
                 "${MESSAGE_CPP_DIR}/${FIL_WE}.pb.h"
          COMMAND $<TARGET_FILE:protobuf::protoc>
          ARGS --cpp_out=dllexport_decl=VSAPI:${PROTO_META_BASE_DIR}
            -I ${MESSAGE_DIR}
            ${msg}
          DEPENDS ${msg}
          COMMENT "Running C++ protocol buffer compiler on ${msg}"
          VERBATIM
        )
endforeach ()

#设置文件属性为 GENERATED
set_source_files_properties (${MESSAGE_SRC} ${MESSAGE_HDRS} PROPERTIES GENERATED TRUE)

#添加自定义target
add_custom_target (files_vsp3_proto_generate ALL
                DEPENDS ${MESSAGE_SRC} ${MESSAGE_HDRS}
                COMMENT "generate message target"
                VERBATIM
                )

#添加protoc依赖
add_dependencies (
	files_vsp3_proto_generate
	protobuf::protoc
)
