#include "Utils.h"
#include "proto_out/Project.pb.h"
#include "../../projects/ProjectProxy.h"
#include "FilePacker.h"
#include "ProtoConverter.h"
//克隆项目后阅读源码前请进行一次生成，将解决报错问题

namespace vocalshaper {
	namespace files {
		namespace vsp3 {
			void shutDownProtobufLibrary()
			{
				::google::protobuf::ShutdownProtobufLibrary();
			}

			bool readProject(
				::vocalshaper::ProjectProxy* project, juce::FileInputStream& stream)
			{
                if (!project) {
                    return false;
                }
                if (!stream.openedOk()) {
                    return false;
                }

                juce::ScopedWriteLock locker(project->getLock());

                std::unique_ptr<Project> ptrProto = std::make_unique<Project>();
                ::vocalshaper::ProjectMeta::MetaObject meta;

                if (!FilePacker::unpackData(stream, ptrProto.get())) {
                    return false;
                }

                if (!ProtoConverter::parseFromProto(
                    ptrProto.get(), project->getPtr(), &meta)) {
                    return false;
                }

                project->getMeta()->resetMeta(meta);

                return true;
			}

			bool writeProject(
				::vocalshaper::ProjectProxy* project, juce::FileOutputStream& stream)
			{
                if (!project) {
                    return false;
                }
                if (!stream.openedOk()) {
                    return false;
                }
                
                stream.setPosition(0);
                if (!stream.truncate().wasOk()) {
                    return false;
                }

                juce::ScopedReadLock locker(project->getLock());

                std::unique_ptr<Project> ptrProto = std::make_unique<Project>();
                if (!ProtoConverter::serilazeToProto(
                    project->getPtr(), &project->getMeta()->toMeta(), ptrProto.get())) {
                    return false;
                }

                if (!FilePacker::packData(ptrProto.get(), stream)) {
                    return false;
                }

                return true;
			}
		}
	}
}
