#pragma once
#include "Shape.h"

namespace Kirara::Math
{
	class Capsule
		:public Shape
	{
	public:
		Capsule(float radius,float height);
		~Capsule()override = default;

		/// @brief 半径が取得できる(トランスフォームに親がいる時、それも反映される)
		/// @return 半径
		[[nodiscard]]
		float GetRadius(void)const;

		/// @brief 親がいない時、数値通りの半径が設定される
		/// @param radius 半径
		Capsule& SetRadius(const float& radius);

		/// @brief 天点から底点の長さを取得する
		/// @return 天点から底点の長さ
		[[nodiscard]]
		float GetHeight(void)const;

		/// @brief 天点から底点の長さを設定する
		/// @param height 天点から底点の長さ
		/// @return 自身
		Capsule& SetHeight(const float& height);

		/// @brief 天点を取得する
		/// @return 天点
		[[nodiscard]]
		Vector3 GetTop(void)const;

		/// @brief 底点を取得する
		/// @return 底点
		[[nodiscard]]
		Vector3 GetBottom(void)const;

		/// @brief 上の球の中心座標を取得する
		/// @return 上の球の中心座標
		[[nodiscard]]
		Vector3 GetTopSpherePos(void)const;

		/// @brief 下の球の中心座標を取得する
		/// @return 下の球の中心座標
		[[nodiscard]]
		Vector3 GetBottomSpherePos(void)const;

		/// @brief 天点から底点に向かって並んでいる
		/// @return カプセルの頂点リスト
		[[nodiscard]]
		std::vector<Vector3> GetVertexes() override;
		[[nodiscard]] std::vector<int> GetVertexIndexes() override;
		[[nodiscard]] Mesh GetMesh() override;
	};
}

