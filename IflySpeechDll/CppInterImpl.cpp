#include "CppInterAnnounce.h"
#include <iostream>
//����ʶ��
#include "ISE.h"
//����ת����
#include "TTS.h"



//���г�ʼ���ƴ������ʶ��
CPPDLL_API int __stdcall InitIflyISE() {
	std::cout << "��ʼ������ʶ��\n"<<std::endl;
	onInitalISE();
	return 1;
}


// ����ֹͣ��ǰ������
CPPDLL_API void __stdcall StopRecognier() {
	onStopRecoginer();
	
}



//����������ǰ������
CPPDLL_API void  StartRecognier(Resoult result, SpeechBegin begin, SpeechEnd end ,const char* accent) {

	
	if (result&&begin&&end){
		onStartRecognier(result, begin, end ,accent);
	}
	else
		return;
 }
////��������ǰ��ʼ��״̬
//CPPDLL_API void  RecognierIsBegin(SpeechBegin begin) {
//
//
// }
////��������ǰ�Ľ���״̬
//CPPDLL_API void  RecognierIsEnd(SpeechEnd end) {
//
// }

//�������õ�ǰ�����ϳ�
CPPDLL_API void __stdcall StartSynthesizer(const char* content, AudioNeedStart audio) {
	 onTextToSpeech(content, audio);
 }



//����ע����ǰ�Ĳ���
CPPDLL_API void __stdcall onDestory() {
	onDestoryISE();
}