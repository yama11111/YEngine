// 平行光源
static const float DireLightNum = 3;
struct DireLight
{
	float3 lightVec;	 // 向き
	float3 lightColor;	 // 色
	float active;		 // 動作フラグ
};

// 点光源
static const float PointLightNum = 3;
struct PointLight
{
	float3 lightPos;	 // 座標
	float3 lightColor;	 // 色
	float3 lightAtten;	 // 距離減衰係数
	float active;		 // 動作フラグ
};

// スポットライト光源
static const float SpotLightNum = 3;
struct SpotLight
{
    float3 lightPos; // 座標
    float3 lightVec; // 向き
    float3 lightColor; // 色
    float3 lightAtten; // 距離減衰係数
    float lightStartFactorAngleCos; // 減衰開始角度
    float lightEndFactorAngleCos; // 減衰終了角度
    float active; // 動作フラグ
};

struct LightGroup
{
	float3 ambientColor; // 環境光色
	DireLight direLights[DireLightNum]; // 平行光源
	PointLight pointLights[PointLightNum]; // 点光源
	SpotLight spotLights[SpotLightNum]; // スポットライト光源
};