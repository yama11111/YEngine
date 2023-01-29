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
		float4 offset = mul(matBillboard, offset_array[i]);

		element.svpos = input[0].pos + offset;
		element.svpos = mul(matWorld, element.svpos);
		element.uv = uv_array[i];
		output.Append(element);
	}
}