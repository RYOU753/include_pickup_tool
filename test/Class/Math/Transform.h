#pragma once
#include <optional>

#include "../Math/Quaternion.h"

namespace Kirara::Math
{
	/// @brief オブジェクトの制御情報
	class Transform
	{
	public:
		using TransformOptRef = std::optional<std::reference_wrapper<Transform>>;
		
		/// @brief コンストラクタ(デフォルト)
		Transform(void);
		
		/// @brief コンストラクタ(パラメーター設定付き)
		/// @param pos ローカル位置
		/// @param rot ローカル回転量
		/// @param scale ローカル拡大率
		Transform(Vector3 pos, Quaternion rot, Vector3 scale);
		
		/// @brief デストラクタ
		~Transform() = default;
		
		/// @brief 親を設定
		/// @param parent 親のTransform(std::nulloptで親なし)
		/// @return 親が循環した時にfalseを返す
		bool SetParent(TransformOptRef parent);
		
		/// @brief ローカル拡大率を設定
		/// @param scale 拡大率
		void SetLocalScale(Vector3 scale);
		
		/// @brief ローカル座標を設定
		/// @param pos 座標
		void SetLocalPosition(Vector3 pos);
		
		/// @brief ローカル回転を設定
		/// @param rot 回転量(クォータニオン)
		void SetLocalRot(Quaternion rot);
		
		/// @brief X軸を回転
		/// @param rotX X軸の回転量
		void SetLocalRotX(float rotX);
		
		/// @brief Y軸を回転
		/// @param rotY Y軸の回転量
		void SetLocalRotY(float rotY);
		
		/// @brief Z軸を回転
		/// @param rotZ Z軸の回転量
		void SetLocalRotZ(float rotZ);

		/// @brief 位置を加算
		/// @param vec 位置の加算量
		void AddLocalPosition(Vector3 vec);
		
		/// @brief ローカル拡大率を取得
		/// @return 拡大率の参照
		[[nodiscard]]
		const Vector3& GetLocalScale(void)const;

		/// @brief  ローカル座標を取得
		/// @return 座標の参照
		[[nodiscard]]
		const Vector3& GetLocalPosition(void)const;

		/// @brief ローカル回転を取得
		/// @return 回転のクォータニオンの参照
		[[nodiscard]]
		const Quaternion& GetLocalRot(void)const;
		
		/// @brief ワールドの拡大率を取得
		/// @return ワールド拡大率
		[[nodiscard]]
		Vector3 GetWorldScale(void)const;
		
		/// @brief ワールド座標を取得
		/// @return ワールド座標
		[[nodiscard]]
		Vector3 GetWorldPosition(void)const;

		/// @brief ワールド回転を取得
		/// @return 回転のクォータニオン
		[[nodiscard]]
		Quaternion GetWorldRot(void)const;
		
		/// @brief 前方を取得
		/// @return 前方方向のベクトル
		[[nodiscard]]
		Vector3 GetForward(void)const;
		
		/// @brief 後方を取得
		/// @return 後方のベクトル
		[[nodiscard]]
		Vector3 GetBack(void)const;

		/// @brief 右方を取得
		/// @return 右方のベクトル
		[[nodiscard]]
		Vector3 GetRight(void)const;
		
		/// @brief 左方を取得
		/// @return 左方のベクトル
		[[nodiscard]]
		Vector3 GetLeft(void)const;

		/// @brief 上方向を取得
		/// @return 上方向のベクトル
		[[nodiscard]]
		Vector3 GetUp(void)const;
		
		/// @brief 下方向のベクトルを取得
		/// @return 下方向のベクトル
		[[nodiscard]]
		Vector3 GetDown(void)const;
		
		/// @brief 任意方向のベクトルを取得
		/// @return 任意方向のベクトル
		[[nodiscard]]
		Vector3 GetDir(const Vector3& vec)const;

		bool IsCirculationParent(TransformOptRef parent)const;
	private:
		Transform& GetRootParent(void);

		Vector3 scale_;			//拡大率
		Vector3 pos_;				//位置
		Quaternion rot_;			//回転

		TransformOptRef parent_;		//親
	};
}
