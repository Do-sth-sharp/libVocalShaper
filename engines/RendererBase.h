#pragma once
#include "../Macros.h"
#include <JuceHeader.h>
#include "../projects/datas/Track.h"
#include "../projects/tempo/TempoTemp.h"

namespace vocalshaper {
	//渲染器：根据轨道数据生成音频片段
	//所有引擎渲染器的共同基类，继承此类并重写接口实现引擎渲染器
	class VSAPI RendererBase
	{
	public:
		RendererBase() = default;
		virtual ~RendererBase() = default;

		//以音高曲线为代表的曲线序列
		using PitchArray = juce::Array<float>;
		//以语谱图为代表的二维图谱，以列的序列的形式储存
		using SpectrogrumArray = juce::Array<juce::Array<float>>;

		//重写此方法渲染某一乐句
		//根据track和sentence中的数据，将音频写入到buffer中
		//返回音频起始点相较于乐句首个音符起始点的偏移量，单位秒
		//sentence区间为闭区间
		//buffer中的空间应自行分配，以占用空间最小为基本原则
		//时间的转换可以从tempoTemp中获得
		//sampleRate为采样率，单位采样数每秒
		//frameLength为信号处理帧长，单位为点数，数值通常为2的整数次幂，但不保证必然性
		//注意该方法可能同时在多个线程上执行多次
		//循环时要注意使用juce::Thread::currentThreadShouldExit()判断中止符号
		virtual double renderSentence(
			juce::AudioBuffer<float>& buffer, const Track* track,
			const std::tuple<int, int> sentence,
			const TempoTemp* tempoTemp, uint32_t sampleRate, uint32_t frameLength) const = 0;

		//重写此方法渲染某一乐句的基础音高曲线
		//合成时实际的音高曲线应在基础音高曲线基础上叠加颤音参数与pit参数
		//根据track和sentence中的数据，将音高曲线写入到pitchArray中
		//返回曲线起始点相较于乐句首个音符起始点的偏移量，单位四分音符时长
		//sentence区间为闭区间
		//pitchArray中的空间应自行分配，以占用空间最小为基本原则
		//时间的转换可以从tempoTemp中获得
		//sampleRate为渲染音频时的采样率，单位采样数每秒
		//curveQuantification为音高曲线采样率，单位采样点数每四分音符时长
		//frameLength为信号处理帧长，单位为点数，数值通常为2的整数次幂，但不保证必然性
		//注意该方法可能同时在多个线程上执行多次
		//循环时要注意使用juce::Thread::currentThreadShouldExit()判断中止符号
		virtual double renderBasePitch(
			PitchArray& pitchArray, const Track* track,
			const std::tuple<int, int> sentence,
			const TempoTemp* tempoTemp, uint32_t sampleRate,
			uint32_t curveQuantification, uint32_t frameLength) const = 0;

		//重写此方法获取某一乐句的音高曲线
		//该音高曲线为渲染的音频的实际音高曲线
		//根据track和sentence中的数据或audio中的音频（二选一），将音高曲线写入到pitchArray中
		//返回曲线起始点相较于乐句首个音符起始点的偏移量，单位四分音符时长
		//sentence区间为闭区间
		//pitchArray中的空间应自行分配，以占用空间最小为基本原则
		//时间的转换可以从tempoTemp中获得
		//sampleRate为音频的采样率，单位采样数每秒
		//curveQuantification为音高曲线采样率，单位采样点数每四分音符时长
		//frameLength为信号处理帧长，单位为点数，数值通常为2的整数次幂，但不保证必然性
		//注意该方法可能同时在多个线程上执行多次
		//循环时要注意使用juce::Thread::currentThreadShouldExit()判断中止符号
		virtual double getPitch(
			PitchArray& pitchArray, const juce::AudioBuffer<float>& audio,
			const Track* track, const std::tuple<int, int> sentence,
			const TempoTemp* tempoTemp, uint32_t sampleRate,
			uint32_t curveQuantification, uint32_t frameLength) const = 0;

		//重写此方法获取某一乐句的动态曲线
		//该动态曲线为渲染的音频的实际动态曲线
		//根据track和sentence中的数据或audio中的音频（二选一），将动态曲线写入到dynamicArray中
		//返回曲线起始点相较于乐句首个音符起始点的偏移量，单位四分音符时长
		//sentence区间为闭区间
		//dynamicArray中的空间应自行分配，以占用空间最小为基本原则
		//时间的转换可以从tempoTemp中获得
		//sampleRate为音频的采样率，单位采样数每秒
		//curveQuantification为动态曲线采样率，单位采样点数每四分音符时长
		//frameLength为信号处理帧长，单位为点数，数值通常为2的整数次幂，但不保证必然性
		//注意该方法可能同时在多个线程上执行多次
		//循环时要注意使用juce::Thread::currentThreadShouldExit()判断中止符号
		virtual double getDynamic(
			PitchArray& dynamicArray, const juce::AudioBuffer<float>& audio,
			const Track* track, const std::tuple<int, int> sentence,
			const TempoTemp* tempoTemp, uint32_t sampleRate,
			uint32_t curveQuantification, uint32_t frameLength) const = 0;

		//重写此方法获取某一乐句的语谱图
		//该语谱图为渲染的音频的实际语谱图
		//根据track和sentence中的数据或audio中的音频（二选一），将语谱图写入到spectArray中
		//返回图起始点相较于乐句首个音符起始点的偏移量，单位秒
		//sentence区间为闭区间
		//spectArray中的空间应自行分配，以占用空间最小为基本原则
		//时间的转换可以从tempoTemp中获得
		//sampleRate为音频的采样率，单位采样数每秒
		//frameLength为信号处理帧长，单位为点数，数值通常为2的整数次幂，但不保证必然性
		//图的水平分辨率应为采样率除以scaleRatio，纵向分辨率应为帧长的一半
		//注意该方法可能同时在多个线程上执行多次
		//循环时要注意使用juce::Thread::currentThreadShouldExit()判断中止符号
		virtual double getSpectrogrum(
			SpectrogrumArray& spectArray, const juce::AudioBuffer<float>& audio,
			const Track* track, const std::tuple<int, int> sentence,
			const TempoTemp* tempoTemp, uint32_t sampleRate,
			uint32_t frameLength, uint32_t scaleRatio) const = 0;

		//重写此方法获取某一乐句的共振峰谱图
		//该共振峰谱图为渲染的音频的实际共振峰谱图
		//根据track和sentence中的数据或audio中的音频（二选一），将共振峰谱图写入到formantArray中
		//返回图起始点相较于乐句首个音符起始点的偏移量，单位秒
		//sentence区间为闭区间
		//formantArray中的空间应自行分配，以占用空间最小为基本原则
		//时间的转换可以从tempoTemp中获得
		//sampleRate为音频的采样率，单位采样数每秒
		//frameLength为信号处理帧长，单位为点数，数值通常为2的整数次幂，但不保证必然性
		//图的水平分辨率应为采样率除以scaleRatio，纵向分辨率应为帧长的一半
		//注意该方法可能同时在多个线程上执行多次
		//循环时要注意使用juce::Thread::currentThreadShouldExit()判断中止符号
		virtual double getFormantrogrum(
			SpectrogrumArray& formantArray, const juce::AudioBuffer<float>& audio,
			const Track* track, const std::tuple<int, int> sentence,
			const TempoTemp* tempoTemp, uint32_t sampleRate,
			uint32_t frameLength, uint32_t scaleRatio) const = 0;

	private:
		JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(RendererBase)
	};
}