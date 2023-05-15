#pragma once
#include "Shape.h"

namespace Kirara::Math
{
	class Sphere :
		public Shape
	{
	public:
		/// @brief 中心位置と半径を決める
		/// @param pos 中心
		/// @param radius 半径
		Sphere(const Vector3& pos ,const float& radius);

		/// @brief 中心位置は(0,0,0)で半径だけ決める
		/// @param radius 半径
		Sphere(const float& radius);

		/// @brief トランスフォームから球体の情報を受け取る
		/// @param transform 中心位置と回転と半径{scale(x,y,z)}
		Sphere(const Transform& transform);

		~Sphere() override = default;
		
		/// @brief 半径が取得できる(トランスフォームに親がいる時、それも反映される)
		/// @return 半径
		[[nodiscard]]
		float GetRadius(void)const;

		/// @brief 親がいない時、数値通りの半径が設定される
		/// @param radius 半径
		void SetRadius(const float& radius);

		/// @brief 球の頂点リストを取得する
		/// @return 頂点リスト
		///	@details リストの最初と最後が天点と底点\n
		///	上から下に円状に頂点が格納してある
		[[nodiscard]]
		std::vector<Vector3> GetVertexes(void) override;
		[[nodiscard]] std::vector<int> GetVertexIndexes() override;
		[[nodiscard]] Mesh GetMesh() override;

	private:
	};
}
