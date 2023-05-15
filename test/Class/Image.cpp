#include "Image.h"
#include <DxLib.h>
#include <ranges>

#include "_debug/_DebugConOut.h"

Image::ImageMng Image::mng_;

Image::Image(std::string_view filePath, bool isASync)
{
	SetUseASyncLoadFlag(isASync);
	handle_ = mng_.Load(filePath);
	SetUseASyncLoadFlag(false);
}

Image::~Image()
{
}

bool Image::IsLoaded() const
{
	return FALSE == CheckHandleASyncLoad(handle_);
}

const int& Image::GetHandle() const
{
	return handle_;
}

int Image::GetWidth() const
{
	int width;
	GetGraphSize(handle_, &width, nullptr);
	return width;
}

int Image::GetHeight() const
{
	int height;
	GetGraphSize(handle_, nullptr, &height);
	return height;
}

Image::ImageMng::~ImageMng()
{
	AllDeleteImage();
}

int Image::ImageMng::Load(std::string_view filePath)
{
	if(HaveImageList(filePath))
	{
		return loadImageList_[filePath.data()];
	}
	int handle = LoadGraph(filePath.data());
	loadImageList_.emplace(filePath.data(), handle);

	return handle;
}

bool Image::ImageMng::DeleteImage(std::string_view filePath)
{
	if(!HaveImageList(filePath))
	{
		return false;
	}

	DeleteGraph(loadImageList_[filePath.data()]);
	loadImageList_.erase(filePath.data());
	return true;
}

bool Image::ImageMng::AllDeleteImage()
{
	for (auto itr = loadImageList_.begin(); itr != loadImageList_.end();)
	{
		if (!HaveImageList(itr->first))
		{
			itr = std::next(itr);
			continue;
		}
		DeleteGraph(itr->second);
		itr = loadImageList_.erase(itr);
	}
	return true;
}

bool Image::ImageMng::HaveImageList(std::string_view filePath) const
{
	return loadImageList_.contains(filePath.data());
}
