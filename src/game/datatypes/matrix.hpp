#pragma once

struct matrix4x4_t
{
	constexpr float* operator[ ]( int index ) noexcept
	{
		return m_matrix[ index ];
	}

	constexpr const float* operator[ ]( int index ) const noexcept
	{
		return m_matrix[ index ];
	}

	float m_matrix[ 4 ][ 4 ] = { };
};

// temporarily
struct matrix3x4_t 
{
    vec3_t right;    // local X
    vec3_t forward;  // local Y
    vec3_t up;       // local Z

    inline vec3_t transform(const vec3_t& v) const
    {
        // local: x = right, y = forward, z = up
        // world = right * x + forward * y + up * z
        return vec3_t{
            right.x * v.x + forward.x * v.y + up.x * v.z,
            right.y * v.x + forward.y * v.y + up.y * v.z,
            right.z * v.x + forward.z * v.y + up.z * v.z
        };
    }
};