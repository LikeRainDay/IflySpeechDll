#pragma once
#define CPPDLL_API __declspec(dllexport)

//����ֹͣ��ǰ������
extern "C" CPPDLL_API void __stdcall StopRecognier();


//ί���¼�
//���ݽ��
typedef void (__stdcall *Resoult)(char*  content );
//���ݿ�ʼ״̬
typedef void (__stdcall *SpeechBegin)();
//���ݽ���״̬
typedef void (__stdcall *SpeechEnd)();

//����������ǰ������

extern "C" CPPDLL_API void  StartRecognier(Resoult result, SpeechBegin begin,SpeechEnd end, const char* accents);
////��������ǰ��ʼ��״̬
//extern "C" CPPDLL_API void  RecognierIsBegin(SpeechBegin begin);
////��������ǰ�Ľ���״̬
//extern "C" CPPDLL_API void  RecognierIsEnd(SpeechEnd end);


//�������������ϳɵĿ�ʼ״̬

//�������������ϳɵĲ���״̬


//ί���¼�
//�ص� ��Ƶ�ĵ�ַ 
typedef void(__stdcall *AudioNeedStart)(char*  content);

//�������õ�ǰ�����ϳ�
extern "C" CPPDLL_API void __stdcall StartSynthesizer(const char* content, AudioNeedStart audio);

////����ֹͣ��������
//extern "C" CPPDLL_API void __stdcall StopSynthesizer();

//���г�ʼ���ƴ������ʶ��
extern "C" CPPDLL_API int __stdcall InitIflyISE();

//�����ͷŵ�ǰ����Դ �������˳���ǰ  �ƴ�ĵ�½
extern "C" CPPDLL_API void __stdcall onDestory();

