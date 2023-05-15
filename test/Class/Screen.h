#pragma once
#include <memory>
#include <optional>
#include "Math/Vector2.h"

class Screen
{
public:
	Screen(int width, int height,bool useAlpha = false);
	Screen(Kirara::Math::Vector2Int size, bool useAlpha = false);
	virtual ~Screen();
	void Draw(const int& x, const int& y, const bool& isTrans) const;
	void Draw(const int& x, const int& y, const float& extend,const bool& isTrans) const;

	virtual void Begin(void);
	void Begin(const int& screenHandle);
	void Begin(const Screen& screenHandle);
	void Begin(const std::unique_ptr<Screen>& screenHandle);
	void Begin(const std::shared_ptr<Screen>& screenHandle);
	void Begin(const std::weak_ptr<Screen>& screenHandle);

	void NoClearBegin();
	void NoClearBegin(const int& screenHandle);
	void NoClearBegin(const std::unique_ptr<Screen>& screenHandle);
	void NoClearBegin(const std::shared_ptr<Screen>& screenHandle);
	void NoClearBegin(const std::weak_ptr<Screen>& screenHandle);

	void End();
	void Clear();

	[[nodiscard]] const int& GetHandle()const;
	[[nodiscard]] const int& GetWidth()const;
	[[nodiscard]] const int& GetHeight()const;
private:
protected:
	Screen();
	int handle_;
	int width_;
	int height_;

	std::optional<int> justBeforeScr_;
	bool isClear_;
};
