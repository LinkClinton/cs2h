#include "fix_resharper_error.hlsl"

struct vs_output {
	SYSTEM_VALUE(float4, position, SV_POSITION);
};

vs_output vs_main(SYSTEM_VALUE(float3, position, POSITION))
{
	vs_output output;

	output.position = float4(position, 1);

	return output;
}

SYSTEM_VALUE(float4, ps_main(vs_output input), SV_TARGET)
{
	return float4(1, 1, 1, 1);
}