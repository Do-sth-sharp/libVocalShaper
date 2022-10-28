#include "NoteAction.h"
#include "../daos/ProjectDAO.h"
#include "../ProjectProxy.h"

#define VS_CREATE_ROUTINE_NOTE_DATA_SWAP_METHOD(_MethodName, _DataMemType, _DAOGetMethodName, _DAOSetMethodName) \
VS_CREATE_ROUTINE_DATA_SWAP_METHOD(_MethodName, Note, _DataMemType, NoteDAO, _DAOGetMethodName, _DAOSetMethodName)

#define VS_CREATE_ROUTINE_NOTE_DATA_ADD_METHOD(_MethodName, _SubObjectPtrType, _DAOAddMethodName) \
VS_CREATE_ROUTINE_DATA_ADD_METHOD(_MethodName, Note, _SubObjectPtrType, NoteDAO, _DAOAddMethodName)

#define VS_CREATE_ROUTINE_NOTE_DATA_REMOVE_METHOD(_MethodName, _SubObjectPtrType, _DAORemoveMethodName) \
VS_CREATE_ROUTINE_DATA_REMOVE_METHOD(_MethodName, Note, _SubObjectPtrType, NoteDAO, _DAORemoveMethodName)

#define VS_NOTE_SELECT \
TrackDAO::getNote(ProjectDAO::getTrack(ptr, target->track), target->note)

namespace vocalshaper {
	namespace actions {
		namespace note {
			VS_CREATE_ROUTINE_NOTE_DATA_SWAP_METHOD(swapStartTime, double, getSt, setSt);
			VS_CREATE_ROUTINE_NOTE_DATA_SWAP_METHOD(swapLength, double, getLength, setLength);
			VS_CREATE_ROUTINE_NOTE_DATA_SWAP_METHOD(swapPitch, uint8_t, getPitch, setPitch);
			VS_CREATE_ROUTINE_NOTE_DATA_SWAP_METHOD(swapTenuto, bool, getTenuto, setTenuto);
			VS_CREATE_ROUTINE_NOTE_DATA_SWAP_METHOD(swapName, juce::String, getName, setName);
			VS_CREATE_ROUTINE_NOTE_DATA_SWAP_METHOD(swapFlag, juce::String, getFlag, setFlag);

			VS_CREATE_ROUTINE_NOTE_DATA_ADD_METHOD(addPhoneme, Phoneme, insertPhoneme);
			VS_CREATE_ROUTINE_NOTE_DATA_REMOVE_METHOD(removePhoneme, Phoneme, releasePhoneme);

			VS_CREATE_ROUTINE_NOTE_DATA_ADD_METHOD(addParam, Param, insertParam);
			VS_CREATE_ROUTINE_NOTE_DATA_REMOVE_METHOD(removeParam, Param, releaseParam);

			VS_CREATE_OBJECT_SELECT_METHOD_BY_ACTION(selectNote, Note, NoteAction, VS_NOTE_SELECT);

			VS_CREATE_EDIT_ROUTINE_DATA_ACTION_DEFINEITION(StartTimeAction, selectNote, swapStartTime);
			VS_CREATE_EDIT_ROUTINE_DATA_ACTION_DEFINEITION(LengthAction, selectNote, swapLength);
			VS_CREATE_EDIT_ROUTINE_DATA_ACTION_DEFINEITION(PitchAction, selectNote, swapPitch);
			VS_CREATE_EDIT_ROUTINE_DATA_ACTION_DEFINEITION(TenutoAction, selectNote, swapTenuto);
			VS_CREATE_EDIT_ROUTINE_DATA_ACTION_DEFINEITION(NameAction, selectNote, swapName);
			VS_CREATE_EDIT_ROUTINE_DATA_ACTION_DEFINEITION(FlagAction, selectNote, swapFlag);

			VS_CREATE_ADD_ROUTINE_DATA_ACTION_DEFINEITION(AddPhonemeAction, selectNote, addPhoneme, removePhoneme);
			VS_CREATE_REMOVE_ROUTINE_DATA_ACTION_DEFINEITION(RemovePhonemeAction, selectNote, addPhoneme, removePhoneme);

			VS_CREATE_ADD_ROUTINE_DATA_ACTION_DEFINEITION(AddParamAction, selectNote, addParam, removeParam);
			VS_CREATE_REMOVE_ROUTINE_DATA_ACTION_DEFINEITION(RemoveParamAction, selectNote, addParam, removeParam);
		}
	}
}
