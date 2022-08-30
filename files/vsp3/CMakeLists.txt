#����Protobuf��
find_package (Protobuf 3 REQUIRED)

#�������·��
set (MESSAGE_CPP_DIR ${CMAKE_CURRENT_SOURCE_DIR})
if (EXISTS "${MESSAGE_CPP_DIR}" AND IS_DIRECTORY "${MESSAGE_CPP_DIR}")
        set (PROTO_META_BASE_DIR ${MESSAGE_CPP_DIR})
else ()
        file (MAKE_DIRECTORY ${MESSAGE_CPP_DIR})
        set (PROTO_META_BASE_DIR ${MESSAGE_CPP_DIR})
endif ()

#����protoc������·��
set (MESSAGE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/proto)
list (APPEND PROTO_FLAGS -I${MESSAGE_DIR})

#��ȡ��Ҫ�����proto�ļ�
file (GLOB_RECURSE MSG_PROTOS ${MESSAGE_DIR}/*.proto)
set (MESSAGE_SRC "")
set (MESSAGE_HDRS "")

foreach (msg ${MSG_PROTOS})
        get_filename_component (FIL_WE ${msg} NAME_WE)

        list (APPEND MESSAGE_SRC "${MESSAGE_CPP_DIR}/${FIL_WE}.pb.cc")
        list (APPEND MESSAGE_HDRS "${MESSAGE_CPP_DIR}/${FIL_WE}.pb.h")

		# ʹ���Զ�������
        add_custom_command (
          OUTPUT "${MESSAGE_CPP_DIR}/${FIL_WE}.pb.cc"
                 "${MESSAGE_CPP_DIR}/${FIL_WE}.pb.h"
          COMMAND ${PROTOBUF_PROTOC_EXECUTABLE}
          ARGS --cpp_out=dllexport_decl=VSAPI:${PROTO_META_BASE_DIR}
            -I ${MESSAGE_DIR}
            ${msg}
          DEPENDS ${msg}
          COMMENT "Running C++ protocol buffer compiler on ${msg}"
          VERBATIM
        )
endforeach ()

#�����ļ�����Ϊ GENERATED
set_source_files_properties (${MESSAGE_SRC} ${MESSAGE_HDRS} PROPERTIES GENERATED TRUE)

#�����Զ���target
add_custom_target (files_vsp3_proto_generate ALL
                DEPENDS ${MESSAGE_SRC} ${MESSAGE_HDRS}
                COMMENT "generate message target"
                VERBATIM
                )