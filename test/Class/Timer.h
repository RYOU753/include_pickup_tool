#pragma once
class Timer
{
public:
	explicit Timer(const float& limit = 0.0f, const float& currentTime = 0.0f);
	~Timer();

	/// @brief タイマーを進める
	void Update(const double& delta);

	/// @brief 時間がすぎたか
	[[nodiscard]] bool IsTimeOver() const;

	/// @brief ０～１に正規化した時間を取得
	[[nodiscard]] float NormalizedTime() const;

	/// @brief 現在の経過時間を取得
	[[nodiscard]] float GetDurationTime() const;

	/// @brief 1から０～１に正規化した時間を引いた時間を取得
	[[nodiscard]] float InverseNormalizedTime() const;

	/// @brief Limitから現在の経過時間を引いた時間を取得
	[[nodiscard]] float InverseTime() const;

	/// @brief 経過時間を0にする
	void ResetTime();

	/// @brief 経過時間を好きな時間に設定
	void SetTime(float time);

	/// @brief 制限を好きな時間に設定
	void SetLimitTime(float limit);

	/// @brief 制限時間を取得する
	/// @return 制限時間
	[[nodiscard]] const float& GetLimitTime() const;

	/// @brief リセットした回数を取得する
	/// @return リセットした回数
	[[nodiscard]] const int& GetResetCount() const;

	/// @brief リセットした回数を初期化する
	void InitResetCount();
private:
	float limitTime_;
	float currentTime_;
	int resetCounter_;
};
