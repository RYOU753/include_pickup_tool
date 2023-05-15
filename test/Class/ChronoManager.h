#pragma once
#include <chrono>
#include "Singleton.h"

#define lpChronoMng ChronoManager::GetInstance()

class ChronoManager:public StaticSingleton<ChronoManager>
{
public:
	friend class StaticSingleton;
public:
	/// @brief 1フレーム時間を更新する
	void Update();

	/// @brief 1フレームの秒数を返す
	/// @return delta (s)
	const double& GetDelta() const;

	/// @brief 指定区間を計測する開始地点
	void StopWatchStart();

	/// @brief 指定区間を計測する終了地点
	void StopWatchEnd();
	
	int GetFPS();

	/// @brief FPSをデバッグ描画する
	/// @param x 出力する文字列の一番右の位置
	/// @param y 出力する文字列一番上の位置
	/// @param color 出力する文字列の色
	void DebugDrawFps(const int& x, const int& y, const int& color = 0xffffff);

	static constexpr double MILLI = 1000.0;
	static constexpr double MICRO = MILLI*MILLI;
	static constexpr double NANO = MICRO*MILLI;
	static constexpr double LIMIT = 0.1;
private:
	ChronoManager();
	~ChronoManager() override = default;
	double delta_;

	std::chrono::system_clock::time_point nowTime;
	std::chrono::system_clock::time_point oldTime;

	std::chrono::system_clock::time_point startTime;
	std::chrono::system_clock::time_point endTime;
	double sec_;
	int fpsCount_ = 0;
	int fpsView_ = 0;
};
