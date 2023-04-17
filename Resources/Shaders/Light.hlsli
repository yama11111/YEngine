// 平行光源
static const int DireLightNum = 3;
struct DireLight
{
	float3 lightVec;	 // 向き
	float3 lightColor;	 // 色
	uint active;		 // 動作フラグ
};
// 点光源
static const int PointLightNum = 3;
struct PointLight
{
	float3 lightPos;	 // 座標
	float3 lightColor;	 // 色
	float3 lightAtten;	 // 距離減衰係数
	uint active;		 // 動作フラグ
};
// スポットライト光源
static const int SpotLightNum = 3;
//struct SpotLight
//{
//	float3 lightPos;	 // 座標
//	float3 lightVec;	 // 向き
//	float3 lightColor;	 // 色
//	float3 lightAtten;	 // 距離減衰係数
//	float  lightStartFactorAngleCos; // 減衰開始角度
//	float  lightEndFactorAngleCos;	 // 減衰終了角度
//	uint active;		 // 動作フラグ
//};