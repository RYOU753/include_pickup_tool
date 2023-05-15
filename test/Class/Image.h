#pragma once
#include <string_view>
#include <unordered_map>

class Image
{
public:
	Image(std::string_view filePath,bool isASync = false);
	~Image();
	/// @brief 非同期読み込み時のロード完了を調べる
	/// @return true:ロード完了
	[[nodiscard]] bool IsLoaded()const;

	/// @brief 画像ハンドルを返す
	/// @return 画像ハンドル
	[[nodiscard]] const int& GetHandle()const;

	int GetWidth()const;
	int GetHeight()const;
private:
	class ImageMng
	{
	public:
		~ImageMng();

		/// @brief 画像をロードし画像ハンドルを返す
		///	@details 以前ロードしたことある場合は保存したハンドルを返す
		/// @param filePath 画像のファイルパス
		/// @return 画像のハンドル
		int Load(std::string_view filePath);

		/// @brief ロードしているImageを消す
		/// @param filePath 画像のファイルパス
		/// @return デリートに成功したらtrueを返す
		bool DeleteImage(std::string_view filePath);

		bool AllDeleteImage();
	private:
		[[nodiscard]] bool HaveImageList(std::string_view filePath)const;
		std::unordered_map<std::string, int> loadImageList_;	//ロードされたハンドルをファイルパスをキーとして保存する場所
	};

	static ImageMng mng_;
	int handle_;
};
