#pragma once
#include <DxLib.h>
#include <cassert>

class ConstantBufferBase
{
public:
	ConstantBufferBase() = default;
	virtual ~ConstantBufferBase() = default;
	[[nodiscard]] virtual const int& GetHandle()const = 0;
};

template<typename T>
requires (sizeof(T)%16 == 0)
class ConstantBuffer :public ConstantBufferBase
{
public:
	ConstantBuffer();

	~ConstantBuffer() override;

	T& Value();

	void Update();

	[[nodiscard]] const int& GetHandle()const override;

private:
	int handle_;
};

template <typename T> requires (sizeof(T) % 16 == 0)
ConstantBuffer<T>::ConstantBuffer()
{
	handle_ = CreateShaderConstantBuffer(sizeof(T));
	assert(handle_ != -1);
}

template <typename T> requires (sizeof(T) % 16 == 0)
ConstantBuffer<T>::~ConstantBuffer()
{
	DeleteShaderConstantBuffer(handle_);
}

template <typename T> requires (sizeof(T) % 16 == 0)
T& ConstantBuffer<T>::Value()
{
	return *static_cast<T*>(GetBufferShaderConstantBuffer(handle_));
}

template <typename T> requires (sizeof(T) % 16 == 0)
void ConstantBuffer<T>::Update()
{
	UpdateShaderConstantBuffer(handle_);
}

template <typename T> requires (sizeof(T) % 16 == 0)
const int& ConstantBuffer<T>::GetHandle() const
{
	return handle_;
}
