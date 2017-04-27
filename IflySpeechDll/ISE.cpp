#pragma once

#ifdef __cplusplus
#include <iostream>

extern "C" {
#endif // __cplusplus

#pragma warning(disable:4996)
	/*
	* ������д(iFly Auto Transform)�����ܹ�ʵʱ�ؽ�����ת���ɶ�Ӧ�����֡�
	*/

#include <stdlib.h>
#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include <errno.h>
#include <process.h>

#include "msp_cmn.h"
#include "msp_errors.h"
#include "speech_sample.h"
#include "ISE.h"

#define FRAME_LEN	640 
#define	BUFFER_SIZE	4096
////��ͨ��
//#define MARDRAIN \
//    "sub = iat, domain = iat, language = zh_cn, accent = mandarin, sample_rate = 16000, result_type = plain, result_encoding = gb2312"
////����
//#define CANTONESE \
//    "sub = iat, domain = iat, language = zh_cn, accent = cantonese, sample_rate = 16000, result_type = plain, result_encoding = gb2312"
////�Ĵ���
//#define LMZ \
//    "sub = iat, domain = iat, language = zh_cn, accent = lmz, sample_rate = 16000, result_type = plain, result_encoding = gb2312"
////���ϻ�
//#define HENANESE \
//    "sub = iat, domain = iat, language = zh_cn, accent = henanese, sample_rate = 16000, result_type = plain, result_encoding = gb2312"
//



		
	//����ȫ������
	struct speech_rec iat;
	//��ǰ�Ĵ������  ����Ϊ0
	int errcode;
	//�Ƿ��ʼ���ɹ�
	boolean isInitalSuccess = false;
	enum {
		EVT_START = 0,
		EVT_STOP,
		EVT_QUIT,
		EVT_TOTAL
	};


	inline void isInitSuccess() {
		if (!isInitalSuccess)return;
	}

	Resoult mResult = NULL;
	SpeechBegin mSpeechBegin = NULL;
	SpeechEnd mSpeechEnd = NULL;

	static HANDLE events[EVT_TOTAL] = { NULL,NULL,NULL };

	static COORD begin_pos = { 0, 0 };
	static COORD last_pos = { 0, 0 };
	//������ʾ�����Ľ��
	static char * lastWord = NULL;

	static void show_result(char *string, char is_over)
	{
		//lastWord = string;
	/*	printf("��ǰʶ����  : [%s]" , string);
		if (mResult) {
			mResult(string);
		}*/
	}



	static char *g_result = NULL;
	static unsigned int g_buffersize = BUFFER_SIZE;

	void on_result(const char *result, char is_last)
	{
		std::cout << "--on_result--result--"<< result << std::endl;
		std::cout << "--on_result----is_last--" << is_last << std::endl;
		if (result&&mResult) {
			mResult((char* )result);
		}
		//ת��֤
		/*if (result) {
			size_t left = g_buffersize - 1 - strlen(g_result);
			size_t size = strlen(result);
			if (left < size) {
				g_result = (char*)realloc(g_result, g_buffersize + BUFFER_SIZE);
				if (g_result)
					g_buffersize += BUFFER_SIZE;
				else {
					printf("mem alloc failed\n");
					return;
				}
			}
			strncat(g_result, result, size);
			show_result(g_result, is_last);
		}*/
	}
	void on_speech_begin()
	{
		std::cout << "--on_speech_begin--" << std::endl;
		if (g_result)
		{
			free(g_result);
		}
		g_result = (char*)malloc(BUFFER_SIZE);
		g_buffersize = BUFFER_SIZE;
		memset(g_result, 0, g_buffersize);

		if (mSpeechBegin)
		{
			
			mSpeechBegin();
		}
		std::cout << "Start Listening...\n" << std::endl;
	}
	void on_speech_end(int reason)
	{
		std::cout << "--on_speech_end--" << std::endl;
		if (reason == END_REASON_VAD_DETECT) {
			std::cout << "\nSpeaking done \n" << std::endl;
		}
		if (mSpeechEnd)
		{
			//��ʾ���

			mSpeechEnd();
		}
		else
		 std::cout << "\nRecognizer error %d\n" << std::endl;


	}


	//��������ֹͣ��ǰ������ʶ��
	 void onStopRecoginer(){
		 isInitSuccess();
		 if (errcode = sr_stop_listening(&iat)) {
			 std::cout << "top listening failed -------%d\n"<< errcode << std::endl;
		 }
	 
	 }

	 //�������ٵ�ǰ������ʶ��
	 void onDestoryISE(){
		 isInitSuccess();
		 sr_uninit(&iat);
	 }
	


	 struct speech_rec_notifier recnotifier = {
		 on_result,
		 on_speech_begin,
		 on_speech_end
	 };
	 void onStartRecognier(Resoult result, SpeechBegin begin, SpeechEnd end,const char * accent) {

		 if (!&iat) {
			 sr_uninit(&iat);
		 }
		 char  c[200];
		 sprintf(c,"sub = iat, domain = iat, language = zh_cn, accent = %s, sample_rate = 16000, result_type = plain, result_encoding = gb2312", accent);
		 std::cout << "--��ǰ--" << c << "---\n" << std::endl;
		 std::cout << "--������--" << errcode << "\n" << std::endl;
		 errcode = sr_init(&iat, c, SR_MIC, DEFAULT_INPUT_DEVID, &recnotifier);
		 if (errcode) {
			 printf("speech recognizer init failed\n");
			 isInitalSuccess = false;
			 return;
		 }
		 isInitalSuccess = true;
		 //isInitSuccess();
		 mResult = result;
		 mSpeechBegin = begin;
		 mSpeechEnd = end;
		 if (errcode = sr_start_listening(&iat)) {
			 printf("stop listening failed %d\n", errcode);
		 }
	 }


	 ////��������ǰ��ʼ��״̬
	 //void Recognier_IsBegin(SpeechBegin begin);
	 // void  Recognier_IsEnd(SpeechEnd end);
	 //������ʼ��ISE�������ϳ�



	 void onInitalISE() {
		const char* login_params = "appid = 58d4949a, work_dir = ."; // ��¼������appid��msc���,��������Ķ�
		int	ret = MSPLogin(NULL, NULL, login_params); //��һ���������û������ڶ������������룬����NULL���ɣ������������ǵ�¼����	
		if (MSP_SUCCESS != ret) {
			std::cout << "MSPLogin failed , Error code %d.\n" << ret << std::endl;
			return; //��¼ʧ�ܣ��˳���¼
		}
	 }


	///* main thread: start/stop record ; query the result of recgonization.
	//* record thread: record callback(data write)
	//* helper thread: ui(keystroke detection)
	//*/
	//int main(int argc, char* argv[])
	//{
	//	int			ret = MSP_SUCCESS;
	//	int			upload_on = 1; //�Ƿ��ϴ��û��ʱ�
	//	const char* login_params = "appid = 58d8b9b7, work_dir = ."; // ��¼������appid��msc���,��������Ķ�
	//	int aud_src = 0;

	//	/*
	//	* sub:				����ҵ������
	//	* domain:			����
	//	* language:			����
	//	* accent:			����
	//	* sample_rate:		��Ƶ������
	//	* result_type:		ʶ������ʽ
	//	* result_encoding:	��������ʽ
	//	*
	//	* ��ϸ����˵������ġ�iFlytek MSC Reference Manual��
	//	*/
	//	const char* session_begin_params = "sub = iat, domain = iat, language = zh_cn, accent = mandarin, sample_rate = 16000, result_type = plain, result_encoding = gb2312";

	//	/* �û���¼ */
	//	ret = MSPLogin(NULL, NULL, login_params); //��һ���������û������ڶ������������룬����NULL���ɣ������������ǵ�¼����	
	//	if (MSP_SUCCESS != ret) {
	//		printf("MSPLogin failed , Error code %d.\n", ret);
	//		goto exit; //��¼ʧ�ܣ��˳���¼
	//	}

	//	printf("\n########################################################################\n");
	//	printf("## ������д(iFly Auto Transform)�����ܹ�ʵʱ�ؽ�����ת���ɶ�Ӧ�����֡�##\n");
	//	printf("########################################################################\n\n");
	//	printf("��ʾʾ��ѡ��:�Ƿ��ϴ��û��ʱ�\n0:��ʹ��\n1:ʹ��\n");

	//	scanf("%d", &upload_on);
	//	if (upload_on)
	//	{
	//		printf("�ϴ��û��ʱ� ...\n");
	//		ret = upload_userwords();
	//		if (MSP_SUCCESS != ret)
	//			goto exit;
	//		printf("�ϴ��û��ʱ�ɹ�\n");
	//	}

	//	printf("��Ƶ��������? \n0: ���ļ�����\n1:��MIC˵��\n");
	//	scanf("%d", &aud_src);
	//	if (aud_src != 0) {
	//		demo_mic(session_begin_params);
	//	}
	//	else {
	//		//iflytek02��Ƶ����Ϊ���������ء�������ϴ����û��ʱ�ʶ����Ϊ���������ٿء���;
	//		demo_file("wav/iflytek02.wav", session_begin_params);
	//	}
	//exit:
	//	printf("��������˳� ...\n");
	//	_getch();
	//	MSPLogout(); //�˳���¼

	//	return 0;
	//}



#ifdef __cplusplus
}
#endif // __cplusplus

