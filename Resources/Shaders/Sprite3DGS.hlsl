#include "Sprite3D.hlsli"

static const  uint vnum = 4;

static const float4 offset_array[vnum] =
{
	float4(-0.5f,-0.5f,0,0),
	float4(-0.5f,+0.5f,0,0),
	float4(+0.5f,-0.5f,0,0),
	float4(+0.5f,+0.5f,0,0),
};

static const float2 uv_array[vnum] =
{
	float2(0,1),
	float2(0,0),
	float2(1,1),
	float2(1,0),
};

[maxvertexcount(vnum)]
void main(
	point GSInput input[1] : SV_POSITION,
	inout TriangleStream<PSInput> output
)
{
	PSInput element;
	for (uint i = 0; i < vnum; i++)
	{
		float4 offset = mul(matBillboard_, offset_array[i]);

		element.svpos_ = input[0].pos_ + offset;
		element.svpos_ = mul(matWorld_, element.svpos_);
		element.uv_ = uv_array[i];
		output.Append(element);
	}
}