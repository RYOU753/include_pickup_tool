#pragma once
#include "MathDefinition.h"

namespace Kirara::Math
{
	/// @brief 行列
	/// @tparam T 要素型
	/// @tparam RowCount 行数
	/// @tparam ColumnCount 列数
	template<ArithmeticType T, size_t RowCount, size_t ColumnCount>
	class MatrixTemplate
	{
	public:
		/// @brief 要素型
		using Type = T;

		/// @brief 要素の配列型
		using Elements = std::array<Type, RowCount* ColumnCount>;

		/// @brief コンストラクタ(正方行列時は単位行列として初期化)
		MatrixTemplate();

		/// @brief コンストラクタ(要素を直接配置する場合)
		/// @param elements 要素の配列
		MatrixTemplate(const Elements& elements);
		~MatrixTemplate() = default;

		/// @brief ゼロ行列を取得
		/// @return ゼロ行列
		static MatrixTemplate Zero(void);

		/// @brief 単位行列を取得
		/// @return 単位行列
		template<typename Dummy = void>
			requires (RowCount == ColumnCount)
		static MatrixTemplate Identity(void);

		/// @brief 逆行列に変換
		/// @return 自身の参照
		template<typename Dummy = void>
			requires (RowCount == ColumnCount)
		MatrixTemplate& Inverse(void);

		/// @brief 逆行列を取得
		/// @return 逆行列
		template<typename Dummy = void>
			requires (RowCount == ColumnCount)
		[[nodiscard]]
		MatrixTemplate Inversed(void)const;

		/// @brief 転置行列に変換
		/// @return 自身の参照
		template<typename Dummy = void>
			requires (RowCount == ColumnCount)
		MatrixTemplate& Transpose(void);

		/// @brief 転置行列を取得
		/// @return 転置行列
		[[nodiscard]]
		MatrixTemplate<T, ColumnCount, RowCount> Transposed(void) const;

		/// @brief 要素の取得
		/// @param rowIndex 行のインデックス
		/// @param columnIndex 列のインデックス
		/// @return 要素の参照
		[[nodiscard]]
		T& GetElement(const size_t& rowIndex, const size_t& columnIndex);

		/// @brief 要素の取得(const付)
		/// @param rowIndex 行のインデックス
		/// @param columnIndex 列のインデックス
		/// @return 要素の参照
		[[nodiscard]]
		const T& GetElement(const size_t& rowIndex, const size_t& columnIndex) const;

		/// @brief 要素の配列を取得
		/// @return 要素の配列
		[[nodiscard]]
		Elements& GetElements(void);

		/// @brief 要素の配列を取得(const付)
		/// @return 要素の配列
		[[nodiscard]]
		const Elements& GetElements(void) const;

		/// @brief 要素にアクセス(二次元配列として)
		/// @param rowIndex 行のインデックス
		/// @return その行の先頭ポインタ
		T* operator[](const size_t& rowIndex);

		/// @brief 要素にアクセス(二次元配列として)(const付)
		/// @param rowIndex 行のインデックス
		/// @return その行の先頭ポインタ
		const T* operator[](const size_t& rowIndex) const;

		/// @brief 要素の比較
		/// @param matrix 行列
		/// @return true:等しい false:等しくない
		bool operator==(const MatrixTemplate& matrix) const;

		MatrixTemplate operator+(const MatrixTemplate& matrix) const;
		MatrixTemplate operator-(const MatrixTemplate& matrix) const;

		template<size_t ExtraColumnCount>
		MatrixTemplate<T, RowCount, ExtraColumnCount> operator*(const MatrixTemplate<T, ColumnCount, ExtraColumnCount>& matrix) const;

		MatrixTemplate operator*(const T& val) const;

		MatrixTemplate& operator+=(const MatrixTemplate& matrix);
		MatrixTemplate& operator-=(const MatrixTemplate& matrix);

		MatrixTemplate(const MatrixTemplate&) = default;
		MatrixTemplate& operator=(const MatrixTemplate&) = default;

		MatrixTemplate(MatrixTemplate&&) = default;
		MatrixTemplate& operator=(MatrixTemplate&&) = default;

	protected:
		Elements elements_;		//要素の配列
	};

	using Matrix1x1 = MatrixTemplate<DefinitionArithmeticType, 1, 1>;
	using Matrix1x2 = MatrixTemplate<DefinitionArithmeticType, 1, 2>;
	using Matrix1x3 = MatrixTemplate<DefinitionArithmeticType, 1, 3>;
	using Matrix1x4 = MatrixTemplate<DefinitionArithmeticType, 1, 4>;

	using Matrix2x1 = MatrixTemplate<DefinitionArithmeticType, 2, 1>;
	using Matrix2x2 = MatrixTemplate<DefinitionArithmeticType, 2, 2>;
	using Matrix2x3 = MatrixTemplate<DefinitionArithmeticType, 2, 3>;
	using Matrix2x4 = MatrixTemplate<DefinitionArithmeticType, 2, 4>;

	using Matrix3x1 = MatrixTemplate<DefinitionArithmeticType, 3, 1>;
	using Matrix3x2 = MatrixTemplate<DefinitionArithmeticType, 3, 2>;
	using Matrix3x3 = MatrixTemplate<DefinitionArithmeticType, 3, 3>;
	using Matrix3x4 = MatrixTemplate<DefinitionArithmeticType, 3, 4>;

	using Matrix4x1 = MatrixTemplate<DefinitionArithmeticType, 4, 1>;
	using Matrix4x2 = MatrixTemplate<DefinitionArithmeticType, 4, 2>;
	using Matrix4x3 = MatrixTemplate<DefinitionArithmeticType, 4, 3>;
	using Matrix4x4 = MatrixTemplate<DefinitionArithmeticType, 4, 4>;

	using Matrix = Matrix4x4;
}

#include "Details/Matrix.h"
