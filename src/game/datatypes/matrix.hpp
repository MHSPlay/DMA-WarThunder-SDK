#pragma once

struct ViewMatrix_t
{
	constexpr float* operator[](int index) noexcept
	{
		return m_flMatrix[index];
	}

	constexpr const float* operator[](int index) const noexcept
	{
		return m_flMatrix[index];
	}

	float m_flMatrix[4][4] = { };
};