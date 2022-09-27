#include "FilePacker.h"
#include "Project.pb.h"

#define VSP3_FILE_HEAD "vsp3"
#define VSP3_FMT_HEAD "fmt\0"
#define VSP3_DATA_HEAD "data"

namespace vocalshaper {
	namespace files {
		namespace vsp3 {
			bool FilePacker::unpackData(juce::InputStream& stream, Project* proto)
			{
				if (!proto) {
					return false;
				}

				const char* fileHead = VSP3_FILE_HEAD;
				const char* fmtHead = VSP3_FMT_HEAD;
				const char* dataHead = VSP3_DATA_HEAD;

				const uint32_t szFileHead = 4 * sizeof(char);
				const uint32_t szFileSize = sizeof(uint32_t);
				const uint32_t szFmtHead = 4 * sizeof(char);
				const uint32_t szFmtSize = sizeof(uint32_t);
				const uint32_t szProtoVer = sizeof(uint32_t);
				const uint32_t szDataHash = 32U;//==> 256 / 8
				const uint32_t szDataHead = 4 * sizeof(char);
				const uint32_t szDataSize = sizeof(uint32_t);

				if (stream.getTotalLength() < 0i64 + szFileHead + szFileSize) {
					return false;
				}
				if (stream.getTotalLength() > UINT32_MAX) {
					return false;
				}

				//vsp3块头
				char fileHeadT[szFileHead]{};
				if (stream.read(fileHeadT, static_cast<size_t>(szFileHead)) != szFileHead) {
					return false;
				}
				if (!FilePacker::checkHead(fileHeadT, fileHead)) {
					return false;
				}
				uint32_t fileSize = 0;
				if (stream.read(&fileSize, static_cast<size_t>(szFileSize)) != szFileSize) {
					return false;
				}
				fileSize = juce::ByteOrder::swapIfBigEndian<uint32_t>(fileSize);
				if (fileSize < szFmtHead + szFmtSize + szProtoVer + szDataHash + szDataHead + szDataSize) {
					return false;
				}

				//fmt块头
				if (stream.getNumBytesRemaining() < szFmtHead) {
					return false;
				}
				char fmtHeadT[szFmtHead]{};
				if (stream.read(fmtHeadT, static_cast<size_t>(szFmtHead)) != szFmtHead) {
					return false;
				}
				if (!FilePacker::checkHead(fmtHeadT, fmtHead)) {
					return false;
				}
				if (stream.getNumBytesRemaining() < szFmtSize) {
					return false;
				}
				uint32_t fmtSize = 0;
				if (stream.read(&fmtSize, static_cast<size_t>(szFmtSize)) != szFmtSize) {
					return false;
				}
				fmtSize = juce::ByteOrder::swapIfBigEndian<uint32_t>(fmtSize);
				if (fmtSize < szProtoVer + szDataHash) {
					return false;
				}

				//fmt块数据
				if (stream.getNumBytesRemaining() < szProtoVer) {
					return false;
				}
				uint32_t protoVer = 0;
				if (stream.read(&protoVer, static_cast<size_t>(szProtoVer)) != szProtoVer) {
					return false;
				}
				protoVer = juce::ByteOrder::swapIfBigEndian<uint32_t>(protoVer);
				if (protoVer > GOOGLE_PROTOBUF_VERSION) {
					return false;
				}
				if (stream.getNumBytesRemaining() < szDataHash) {
					return false;
				}
				char ptrHash[szDataHash]{};
				if (stream.read(ptrHash, static_cast<size_t>(szDataHash)) != szDataHash) {
					return false;
				}
				uint32_t szOther = fmtSize - (szProtoVer + szDataHash);
				stream.skipNextBytes(szOther);

				//data块头
				if (stream.getNumBytesRemaining() < szDataHead) {
					return false;
				}
				char dataHeadT[szDataHead]{};
				if (stream.read(dataHeadT, static_cast<size_t>(szDataHead)) != szDataHead) {
					return false;
				}
				if (!FilePacker::checkHead(dataHeadT, dataHead)) {
					return false;
				}
				if (stream.getNumBytesRemaining() < szDataSize) {
					return false;
				}
				uint32_t dataSize = 0;
				if (stream.read(&dataSize, static_cast<size_t>(szDataSize)) != szDataSize) {
					return false;
				}
				dataSize = juce::ByteOrder::swapIfBigEndian<uint32_t>(dataSize);

				//data块数据
				if (stream.getNumBytesRemaining() < dataSize) {
					return false;
				}
				std::unique_ptr<char[]> ptrData = std::unique_ptr<char[]>(new char[dataSize]);
				if (!ptrData) {
					return false;
				}
				if (stream.read(ptrData.get(), static_cast<size_t>(dataSize)) != dataSize) {
					return false;
				}
				if (!FilePacker::checkHash(ptrData.get(), dataSize, ptrHash)) {
					jassertfalse;
					return false;
				}

				proto->Clear();
				return proto->ParseFromArray(ptrData.get(), dataSize);
			}

			bool FilePacker::packData(const Project* proto, juce::OutputStream& stream)
			{
				if (!proto) {
					return false;
				}

				size_t protoLength = proto->ByteSizeLong();
				std::unique_ptr<char[]> ptrData = std::unique_ptr<char[]>(new char[protoLength]);
				if (!ptrData) {
					return false;
				}
				if (!proto->SerializeToArray(ptrData.get(), protoLength)) {
					return false;
				}
				
				const char* fileHead = VSP3_FILE_HEAD;
				const char* fmtHead = VSP3_FMT_HEAD;
				const char* dataHead = VSP3_DATA_HEAD;

				const uint32_t szFileHead = 4 * sizeof(char);
				const uint32_t szFileSize = sizeof(uint32_t);
				const uint32_t szFmtHead = 4 * sizeof(char);
				const uint32_t szFmtSize = sizeof(uint32_t);
				const uint32_t szProtoVer = sizeof(uint32_t);
				const uint32_t szDataHash = 32U;//==> 256 / 8
				const uint32_t szDataHead = 4 * sizeof(char);
				const uint32_t szDataSize = sizeof(uint32_t);
				const uint32_t szData = protoLength;

				if (protoLength > UINT32_MAX - (szFileHead + szFileSize
					+ szFmtHead + szFmtSize + szProtoVer + szDataHash
					+ szDataHead + szDataSize)) {
					return false;
				}

				//vsp3块头
				if (!stream.write(fileHead, szFileHead)) {
					return false;
				}
				auto fileSize = juce::ByteOrder::swapIfBigEndian<uint32_t>(
					szFmtHead + szFmtSize + szProtoVer + szDataHash
					+ szDataHead + szDataSize + szData);
				if (!stream.write(&fileSize, szFileSize)) {
					return false;
				}

				//fmt块头
				if (!stream.write(fmtHead, szFmtHead)) {
					return false;
				}
				auto fmtSize = juce::ByteOrder::swapIfBigEndian<uint32_t>(
					szProtoVer + szDataHash);
				if (!stream.write(&fmtSize, szFmtSize)) {
					return false;
				}

				//fmt块数据
				uint32_t protoVer = juce::ByteOrder::swapIfBigEndian<uint32_t>(GOOGLE_PROTOBUF_VERSION);
				if (!stream.write(&protoVer, szProtoVer)) {
					return false;
				}
				char ptrHash[szDataHash]{};
				FilePacker::getHash(ptrData.get(), protoLength).copyTo(ptrHash, 0, szDataHash);
				if (!stream.write(ptrHash, szDataHash)) {
					return false;
				}

				//data块头
				if (!stream.write(dataHead, szDataHead)) {
					return false;
				}
				auto dataSize = juce::ByteOrder::swapIfBigEndian<uint32_t>(szData);
				if (!stream.write(&dataSize, szDataSize)) {
					return false;
				}

				//data块数据
				if (!stream.write(ptrData.get(), szData)) {
					return false;
				}

				stream.flush();
				return true;
			}

			bool FilePacker::checkHead(const char* p1, const char* p2)
			{
				if (!p1 || !p2) {
					return false;
				}
				return
					p1[0] == p2[0] &&
					p1[1] == p2[1] &&
					p1[2] == p2[2] &&
					p1[3] == p2[3];
			}

			juce::MemoryBlock FilePacker::getHash(const char* ptrData, const size_t size)
			{
				if (!ptrData) {
					return juce::MemoryBlock();
				}
				juce::SHA256 hash(ptrData, size);
				return hash.getRawData();
			}

			bool FilePacker::checkHash(const char* ptrData, const size_t size,
				const char* ptrHash)
			{
				if (!ptrData || !ptrHash) {
					return false;
				}
				return FilePacker::getHash(ptrData, size).matches(ptrHash, 32U);
			}
		}
	}
}