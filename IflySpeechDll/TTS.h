#pragma once
#ifndef __TTS_SPEECH
#define __TTS_SPEECH
#include "CppInterAnnounce.h"

#ifdef __cplusplus
extern "C" {
#endif // !__cplusplus
	//进行文本转文字
	extern void onTextToSpeech(const char* content, AudioNeedStart audio);

#ifdef __cplusplus
}
#endif // !__cplusplus

#endif // !__ISE_SPEECH
