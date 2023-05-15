#pragma once
#include "Shape.h"

namespace Kirara::Math
{
	class Cube :public Shape
	{
	public:
		Cube(const float& side);
		Cube(const Vector3& pos,const float& side);
		Cube(const float& width,const float& height,const float& depth);
		Cube(const Vector3& pos, const float& width, const float& height, const float& depth);
		~Cube()override = default;

		/// @brief 横幅を取得する
		/// @return 横幅
		[[nodiscard]]
		float GetWidth(void)const;

		/// @brief 横幅を設定する
		/// @param width 横幅
		/// @return 自身
		Cube& SetWidth(const float& width);

		/// @brief 高さを取得する
		/// @return 高さ
		[[nodiscard]]
		float GetHeight(void)const;

		/// @brief 高さを設定する
		/// @param height 高さ
		/// @return 自身
		Cube& SetHeight(const float& height);

		/// @brief 奥行を取得する
		/// @return 奥行
		[[nodiscard]]
		float GetDepth(void)const;

		/// @brief 奥行を設定する
		/// @param depth 奥行
		/// @return 自身
		Cube& SetDepth(const float& depth);

		/// @brief 横幅，高さ，奥行を設定する
		/// @param width 横幅
		/// @param height 高さ
		/// @param depth 奥行
		/// @return 自身
		Cube& SetWHD(const float& width, const float& height, const float& depth);

		/// @brief 上面から下面に頂点リストを格納している
		/// @return 頂点リスト
		[[nodiscard]]
		std::vector<Vector3> GetVertexes(void) override;
		[[nodiscard]] std::vector<int> GetVertexIndexes() override;
		[[nodiscard]] Mesh GetMesh() override;

	private:
	};
}
