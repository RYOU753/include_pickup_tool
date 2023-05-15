#pragma once
#include "Math/Matrix.h"
#include "Math/MathDefinition.h"

namespace Kirara::Math
{
	template <ArithmeticType T, size_t RowCount, size_t ColumnCount>
	MatrixTemplate<T, RowCount, ColumnCount>::MatrixTemplate()
	{
		if constexpr (RowCount == ColumnCount)
		{
			*this = Identity();
			return;
		}

		*this = Zero();
	}

	template <ArithmeticType T, size_t RowCount, size_t ColumnCount>
	MatrixTemplate<T, RowCount, ColumnCount>::MatrixTemplate(const Elements& elements) :
		elements_(elements)
	{
	}

	template <ArithmeticType T, size_t RowCount, size_t ColumnCount>
	MatrixTemplate<T, RowCount, ColumnCount> MatrixTemplate<T, RowCount, ColumnCount>::Zero(void)
	{
		Elements elements;
		elements.fill(static_cast<T>(0));
		return MatrixTemplate(elements);
	}

	template <ArithmeticType T, size_t RowCount, size_t ColumnCount>
	template <typename Dummy>
		requires (RowCount == ColumnCount)
	MatrixTemplate<T, RowCount, ColumnCount> MatrixTemplate<T, RowCount, ColumnCount>::Identity(void)
	{
		Elements elements;

		for (size_t y = 0; y < RowCount; y++)
		{
			for (size_t x = 0; x < ColumnCount; x++)
			{
				elements[ColumnCount * y + x] = static_cast<T>(y == x ? 1 : 0);
			}
		}

		return MatrixTemplate(elements);
	}

	template <ArithmeticType T, size_t RowCount, size_t ColumnCount>
	template <typename Dummy>
		requires (RowCount == ColumnCount)
	MatrixTemplate<T, RowCount, ColumnCount>& MatrixTemplate<T, RowCount, ColumnCount>::Inverse(void)
	{
		return *this = Inversed();
	}

	template <ArithmeticType T, size_t RowCount, size_t ColumnCount>
	template <typename Dummy>
		requires (RowCount == ColumnCount)
	MatrixTemplate<T, RowCount, ColumnCount> MatrixTemplate<T, RowCount, ColumnCount>::Inversed(void) const
	{
		MatrixTemplate result;
		MatrixTemplate tempMat = *this;

		T temp = 0;

		for (size_t i = 0; i < ColumnCount; i++)
		{
			size_t maxIndex = i;
			T maxVal = abs(tempMat[maxIndex][maxIndex]);

			for (size_t j = i + 1; j < RowCount; j++)
			{
				if (abs(tempMat[j][i]) > maxVal)
				{
					maxVal = abs(tempMat[j][i]);
					maxIndex = j;
				}
			}

			if (maxVal <= static_cast<T>(K_EPSILON_NORMAL_SQRT))
			{
				assert(false, "Can not inverse this matrix.");
				return Identity();
			}

			if (i != maxIndex)
			{
				for (size_t j = 0; j < ColumnCount; j++)
				{
					std::swap(tempMat[i][j], tempMat[maxIndex][j]);
					std::swap(result[i][j], result[maxIndex][j]);
				}
			}

			temp = static_cast<T>(1) / tempMat[i][i];
			for (size_t j = 0; j < ColumnCount; j++)
			{
				tempMat[i][j] *= temp;
				result[i][j] *= temp;
			}

			for (size_t j = 0; j < RowCount; j++)
			{
				if (i == j)
				{
					continue;
				}

				temp = -tempMat[j][i];

				for (size_t k = 0; k < ColumnCount; k++)
				{
					tempMat[j][k] += tempMat[i][k] * temp;
					result[j][k] += result[i][k] * temp;
				}
			}
		}
		
		return result;
	}

	template <ArithmeticType T, size_t RowCount, size_t ColumnCount>
	template <typename Dummy>
		requires (RowCount == ColumnCount)
	MatrixTemplate<T, RowCount, ColumnCount>& MatrixTemplate<T, RowCount, ColumnCount>::Transpose(void)
	{
		return *this = Transposed();
	}

	template <ArithmeticType T, size_t RowCount, size_t ColumnCount>
	MatrixTemplate<T, ColumnCount, RowCount> MatrixTemplate<T, RowCount, ColumnCount>::Transposed(void) const
	{
		MatrixTemplate<T, ColumnCount, RowCount> result;
		for (size_t y = 0; y < ColumnCount; y++)
		{
			for (size_t x = 0; x < RowCount; x++)
			{
				result[y][x] = (*this)[x][y];
			}
		}

		return result;
	}

	template <ArithmeticType T, size_t RowCount, size_t ColumnCount>
	T& MatrixTemplate<T, RowCount, ColumnCount>::GetElement(const size_t& rowIndex, const size_t& columnIndex)
	{
		return elements_[rowIndex][columnIndex];
	}

	template <ArithmeticType T, size_t RowCount, size_t ColumnCount>
	const T& MatrixTemplate<T, RowCount, ColumnCount>::GetElement(const size_t& rowIndex, const size_t& columnIndex) const
	{
		return elements_[rowIndex][columnIndex];
	}

	template <ArithmeticType T, size_t RowCount, size_t ColumnCount>
	typename MatrixTemplate<T, RowCount, ColumnCount>::Elements& MatrixTemplate<T, RowCount, ColumnCount>::GetElements(void)
	{
		return elements_;
	}

	template <ArithmeticType T, size_t RowCount, size_t ColumnCount>
	const typename MatrixTemplate<T, RowCount, ColumnCount>::Elements& MatrixTemplate<T, RowCount, ColumnCount>::GetElements(void) const
	{
		return elements_;
	}

	template <ArithmeticType T, size_t RowCount, size_t ColumnCount>
	T* MatrixTemplate<T, RowCount, ColumnCount>::operator[](const size_t& rowIndex)
	{
		return &elements_[ColumnCount * rowIndex];
	}

	template <ArithmeticType T, size_t RowCount, size_t ColumnCount>
	const T* MatrixTemplate<T, RowCount, ColumnCount>::operator[](const size_t& rowIndex) const
	{
		return &elements_[ColumnCount * rowIndex];
	}

	template <ArithmeticType T, size_t RowCount, size_t ColumnCount>
	bool MatrixTemplate<T, RowCount, ColumnCount>::operator==(const MatrixTemplate& matrix) const
	{
		return std::ranges::equal(elements_, matrix.GetElements());
	}

	template <ArithmeticType T, size_t RowCount, size_t ColumnCount>
	MatrixTemplate<T, RowCount, ColumnCount> MatrixTemplate<T, RowCount, ColumnCount>::operator+(const MatrixTemplate& matrix) const
	{
		MatrixTemplate result = *this;

		auto& resultElement = result.GetElements();
		const auto& matElement = matrix.GetElements();

		const auto size = elements_.size();
		for (size_t i = 0; i < size; i++)
		{
			resultElement[i] += matElement[i];
		}
		return result;
	}

	template <ArithmeticType T, size_t RowCount, size_t ColumnCount>
	MatrixTemplate<T, RowCount, ColumnCount> MatrixTemplate<T, RowCount, ColumnCount>::operator-(const MatrixTemplate& matrix) const
	{
		MatrixTemplate result = *this;

		auto& resultElement = result.GetElements();
		const auto& matElement = matrix.GetElements();

		const auto size = elements_.size();
		for (size_t i = 0; i < size; i++)
		{
			resultElement[i] -= matElement[i];
		}
		return result;
	}

	template <ArithmeticType T, size_t RowCount, size_t ColumnCount>
	template <size_t ExtraColumnCount>
	MatrixTemplate<T, RowCount, ExtraColumnCount> MatrixTemplate<T, RowCount, ColumnCount>::operator*(const MatrixTemplate<T, ColumnCount, ExtraColumnCount>& matrix) const
	{
		MatrixTemplate<T, RowCount, ExtraColumnCount> result;
		result.GetElements().fill(0.0f);

		for (size_t y = 0; y < RowCount; y++)
		{
			for (size_t x = 0; x < ExtraColumnCount; x++)
			{
				for (size_t i = 0; i < ColumnCount; i++)
				{
					result[y][x] += (*this)[y][i] * matrix[i][x];
				}
			}
		}

		return result;
	}

	template <ArithmeticType T, size_t RowCount, size_t ColumnCount>
	MatrixTemplate<T, RowCount, ColumnCount> MatrixTemplate<T, RowCount, ColumnCount>::operator*(const T& val) const
	{
		MatrixTemplate result = *this;

		auto& resultElement = result.GetElements();

		const auto size = elements_.size();
		for (size_t i = 0; i < size; i++)
		{
			resultElement[i] *= val;
		}
		return result;
	}

	template <ArithmeticType T, size_t RowCount, size_t ColumnCount>
	MatrixTemplate<T, RowCount, ColumnCount>& MatrixTemplate<T, RowCount, ColumnCount>::operator+=(const MatrixTemplate& matrix)
	{
		*this = *this + matrix;
		return *this;
	}

	template <ArithmeticType T, size_t RowCount, size_t ColumnCount>
	MatrixTemplate<T, RowCount, ColumnCount>& MatrixTemplate<T, RowCount, ColumnCount>::operator-=(const MatrixTemplate& matrix)
	{
		*this = *this - matrix;
		return *this;
	}
}
