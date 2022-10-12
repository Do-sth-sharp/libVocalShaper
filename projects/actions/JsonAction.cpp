#include "JsonAction.h"
#include "../daos/ProjectDAO.h"
#include "../ProjectProxy.h"

#define VS_CREATE_ROUTINE_JSON_DATA_SWAP_METHOD(_MethodName, _DataMemType, _DAOGetMethodName, _DAOSetMethodName) \
VS_CREATE_ROUTINE_DATA_SWAP_METHOD(_MethodName, Json, _DataMemType, JsonDAO, _DAOGetMethodName, _DAOSetMethodName)

#define VS_CREATE_ROUTINE_JSON_DATA_ADD_METHOD(_MethodName, _SubObjectPtrType, _DAOAddMethodName) \
VS_CREATE_ROUTINE_DATA_ADD_METHOD(_MethodName, Json, _SubObjectPtrType, JsonDAO, _DAOAddMethodName)

#define VS_CREATE_ROUTINE_INSTR_DATA_REMOVE_METHOD(_MethodName, _SubObjectPtrType, _DAORemoveMethodName) \
VS_CREATE_ROUTINE_DATA_REMOVE_METHOD(_MethodName, Json, _SubObjectPtrType, JsonDAO, _DAORemoveMethodName)

#define VS_JSON_SELECT \
ProjectDAO::getAddition(ptr, target->json)

namespace vocalshaper {
	namespace actions {
		namespace json {
			inline bool swapData(vocalshaper::Json* ptrObject, juce::String& data)
			{
				if (!ptrObject) {
					return false;
				}

				auto ptrVar = JsonDAO::getDataMutable(ptrObject);
				if (!ptrVar) {
					return false;
				}

				juce::String dataTemp = juce::JSON::toString(*ptrVar, true);
				juce::JSON::parse(data, *ptrVar);
				data = dataTemp;

				return true;
			}

			VS_CREATE_OBJECT_SELECT_METHOD_BY_ACTION(selectJson, Json, JsonAction, VS_JSON_SELECT);

			VS_CREATE_EDIT_ROUTINE_DATA_ACTION_DEFINEITION(DataAction, selectJson, swapData);
		}
	}
}