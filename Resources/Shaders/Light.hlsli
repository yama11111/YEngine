// 平行光源
static const float DireLightNum = 3;
struct DireLight
{
	float3 lightVec_;	 // 向き
	float3 lightColor_;	 // 色
	float active_;		 // 動作フラグ
};

// 点光源
static const float PointLightNum = 3;
struct PointLight
{
	float3 lightPos_;	 // 座標
	float3 lightColor_;	 // 色
	float3 lightAtten_;	 // 距離減衰係数
	float active_;		 // 動作フラグ
};

// スポットライト光源
static const float SpotLightNum = 3;
//struct SpotLight
//{
//	float3 lightPos_;	 // 座標
//	float3 lightVec_;	 // 向き
//	float3 lightColor_;	 // 色
//	float3 lightAtten_;	 // 距離減衰係数
//	float  lightStartFactorAngleCos_; // 減衰開始角度
//	float  lightEndFactorAngleCos_;	 // 減衰終了角度
//	float active_;		 // 動作フラグ
//};

struct LightGroup
{
	float3 ambientColor_; // 環境光色
	DireLight direLights_[DireLightNum]; // 平行光源
	PointLight pointLights_[PointLightNum]; // 点光源
	//SpotLight spotLights_[SpotLightNum]; // スポットライト光源
};