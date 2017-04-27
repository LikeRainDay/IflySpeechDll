using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Runtime.InteropServices;
using System.Threading;



namespace IflyDemoTest
{
    public partial class Form1 : Form
    {

        //停止当前的识别
        [DllImport(@"E:\GitHubSample\IflySpeechDll\x64\Debug\IflySpeechDll.dll", EntryPoint= "StopRecognier", SetLastError = true, CharSet = CharSet.Ansi, ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
        extern static void  StopRecognier();
        //委托事件
        public delegate void Resoult(string resoult);
        Resoult mResoult;
        void CSCallResoult(string resoult)
        {
            
            Console.WriteLine("委托结果的数据"+resoult);
        }
        public delegate void SpeechBegin();
         SpeechBegin mSpeechBegin;
         void CSCallSpeechBegin()
        {
            Console.WriteLine("SpeechBegin" );
        }
        public delegate void SpeechEnd();
         SpeechEnd mSpeechEnd;
         void CSCallSpeechEnd()
        {
            Console.WriteLine("SpeechEnd");
            //mResoult = new Resoult(Form1.CSCallResoult);
            //mSpeechEnd = new SpeechEnd(Form1.CSCallSpeechEnd);
            //mSpeechBegin = new SpeechBegin(Form1.CSCallSpeechBegin);
            //StartRecognier(mResoult, mSpeechBegin, mSpeechEnd);

        }
        //开启当前的识别
        [DllImport(@"E:\GitHubSample\IflySpeechDll\x64\Debug\IflySpeechDll.dll", EntryPoint = "StartRecognier", SetLastError = true, CharSet = CharSet.Ansi, ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
        extern static void StartRecognier(Resoult resolut, SpeechBegin speechBegin,SpeechEnd speechEnd,StringBuilder accent);

        [DllImport(@"E:\GitHubSample\IflySpeechDll\x64\Debug\IflySpeechDll.dll", EntryPoint = "InitIflyISE", SetLastError = true, CharSet = CharSet.Ansi, ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
        extern static int InitIflyISE();



        public delegate void NeedStartAudioPlay(string resoult);
        static NeedStartAudioPlay mNeedStartAudioPlay;
        static void CSCallNeedStartAudioPlay(string resoult)
        {
            Console.WriteLine("SpeechEnd:=="+resoult);
        }

        [DllImport(@"E:\GitHubSample\IflySpeechDll\x64\Debug\IflySpeechDll.dll", EntryPoint = "StartSynthesizer")]
        extern static void StartSynthesizer( StringBuilder content, NeedStartAudioPlay needStart);

        [DllImport(@"E:\GitHubSample\IflySpeechDll\x64\Debug\IflySpeechDll.dll", EntryPoint = "onDestory", SetLastError = true, CharSet = CharSet.Ansi, ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
        extern static void onDestory();



        Thread MyThread;
        public Form1()
        {
            InitializeComponent();
            //进行初始化语音识别
            InitIflyISE();
           
        }


        //用于语音识别
        private void button1_Click(object sender, EventArgs e)
        {
            //用来识别进行的相应委托
            mResoult = new Resoult(CSCallResoult);
            mSpeechEnd = new SpeechEnd(CSCallSpeechEnd);
            mSpeechBegin = new SpeechBegin(CSCallSpeechBegin);
            //开启当前的语音识别
            StringBuilder content = new StringBuilder();
            content.Append("mandarin");
            StartRecognier(mResoult, mSpeechBegin, mSpeechEnd, content);
        }
        //用于语音合成
        private void button2_Click(object sender, EventArgs e)
        {

            mNeedStartAudioPlay = new NeedStartAudioPlay(Form1.CSCallNeedStartAudioPlay);
            StringBuilder content = new StringBuilder();
            content.Append("你是个大傻瓜,我却很喜欢你,扥观察gas开该卡三横栓他阿斯根据ah感康搞僵防风杰卡斯待会杆坑啊港鄂网格暗感卡萨当过啊看似恒基卡横看郝金刚图网通阿恒阿峰喊到阿峰会是哈基坑汗啊空挡孤儿阿恒卡挡风镜框阿恒健康瑞恒金卡恒啊到金刚阿九开户干卡带恒看啊共打款较高ad方干啊当看啊等哈看横看阿訇干啊当风卡号");
            StartSynthesizer(content, mNeedStartAudioPlay);
        }


        private void listBox1_SelectedIndexChanged(object sender, EventArgs e)
        {

        }

        private void textBox1_TextChanged(object sender, EventArgs e)
        {

        }



        private void Form1_Load(object sender, EventArgs e)
        {
            MyThread = new Thread(new ThreadStart(onLoopSpeech));
        }

        private void onLoopSpeech()
        {
            //mResoult = new Resoult(Form1.CSCallResoult);
            //mSpeechEnd = new SpeechEnd(Form1.CSCallSpeechEnd);
            //mSpeechBegin = new SpeechBegin(Form1.CSCallSpeechBegin);
            //StartRecognier(mResoult, mSpeechBegin, mSpeechEnd);
        }

    }
}
