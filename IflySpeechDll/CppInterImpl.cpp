#include "CppInterAnnounce.h"
#include <iostream>
//语音识别
#include "ISE.h"
//文字转语音
#include "TTS.h"



//进行初始化科大的语音识别
CPPDLL_API int __stdcall InitIflyISE() {
	std::cout << "初始化语音识别\n"<<std::endl;
	onInitalISE();
	return 1;
}


// 用来停止当前的语音
CPPDLL_API void __stdcall StopRecognier() {
	onStopRecoginer();
	
}



//用来开启当前的语音
CPPDLL_API void  StartRecognier(Resoult result, SpeechBegin begin, SpeechEnd end ,const char* accent) {

	
	if (result&&begin&&end){
		onStartRecognier(result, begin, end ,accent);
	}
	else
		return;
 }
////用来处理当前开始的状态
//CPPDLL_API void  RecognierIsBegin(SpeechBegin begin) {
//
//
// }
////用来处理当前的结束状态
//CPPDLL_API void  RecognierIsEnd(SpeechEnd end) {
//
// }

//用来设置当前语音合成
CPPDLL_API void __stdcall StartSynthesizer(const char* content, AudioNeedStart audio) {
	 onTextToSpeech(content, audio);
 }



//用来注销当前的操作
CPPDLL_API void __stdcall onDestory() {
	onDestoryISE();
}