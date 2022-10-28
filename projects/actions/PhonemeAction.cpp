#include "PhonemeAction.h"
#include "../daos/ProjectDAO.h"
#include "../ProjectProxy.h"

#define VS_CREATE_ROUTINE_PHONEME_DATA_SWAP_METHOD(_MethodName, _DataMemType, _DAOGetMethodName, _DAOSetMethodName) \
VS_CREATE_ROUTINE_DATA_SWAP_METHOD(_MethodName, Phoneme, _DataMemType, PhonemeDAO, _DAOGetMethodName, _DAOSetMethodName)

#define VS_CREATE_ROUTINE_PHONEME_DATA_ADD_METHOD(_MethodName, _SubObjectPtrType, _DAOAddMethodName) \
VS_CREATE_ROUTINE_DATA_ADD_METHOD(_MethodName, Phoneme, _SubObjectPtrType, PhonemeDAO, _DAOAddMethodName)

#define VS_CREATE_ROUTINE_PHONEME_DATA_REMOVE_METHOD(_MethodName, _SubObjectPtrType, _DAORemoveMethodName) \
VS_CREATE_ROUTINE_DATA_REMOVE_METHOD(_MethodName, Phoneme, _SubObjectPtrType, PhonemeDAO, _DAORemoveMethodName)

#define VS_PHONEME_SELECT \
NoteDAO::getPhoneme(TrackDAO::getNote(ProjectDAO::getTrack(ptr, target->track), target->note), target->phoneme)

namespace vocalshaper {
	namespace actions {
		namespace phoneme {
			VS_CREATE_ROUTINE_PHONEME_DATA_SWAP_METHOD(swapDeviation, double, getDeviation, setDeviation);
			VS_CREATE_ROUTINE_PHONEME_DATA_SWAP_METHOD(swapName, juce::String, getName, setName);
			VS_CREATE_ROUTINE_PHONEME_DATA_SWAP_METHOD(swapIsPre, bool, getIsPre, setIsPre);

			VS_CREATE_ROUTINE_PHONEME_DATA_ADD_METHOD(addPoint, Point, insertTimePoint);
			VS_CREATE_ROUTINE_PHONEME_DATA_REMOVE_METHOD(removePoint, Point, releaseTimePoint);

			VS_CREATE_OBJECT_SELECT_METHOD_BY_ACTION(selectPhoneme, Phoneme, PhonemeAction, VS_PHONEME_SELECT);

			VS_CREATE_EDIT_ROUTINE_DATA_ACTION_DEFINEITION(DeviationAction, selectPhoneme, swapDeviation);
			VS_CREATE_EDIT_ROUTINE_DATA_ACTION_DEFINEITION(NameAction, selectPhoneme, swapName);
			VS_CREATE_EDIT_ROUTINE_DATA_ACTION_DEFINEITION(IsPreAction, selectPhoneme, swapIsPre);

			VS_CREATE_ADD_ROUTINE_DATA_ACTION_DEFINEITION(AddPointAction, selectPhoneme, addPoint, removePoint);
			VS_CREATE_REMOVE_ROUTINE_DATA_ACTION_DEFINEITION(RemovePointAction, selectPhoneme, addPoint, removePoint);
		}
	}
}
