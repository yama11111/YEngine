// トランスフォーム
cbuffer cbuff0 : register(b0)
{
	matrix matWorld_; // ワールド行列
	matrix matViewProj_; // ビュープロジェクション行列
	float3 cameraPos_; // カメラ座標
}

// 時間
cbuffer cbuff1 : register(b1)
{
	float time_; // 時間
}

// 色
cbuffer cbuff2 : register(b2)
{
	float4 baseColor_; // 色(RGBA)
	float4 texColorRate_; // 元の色の割合
}

// テクスチャ設定
cbuffer cbuff3 : register(b3)
{
	float2 texTiling_; // タイリング
	float2 texOffset_; // オフセット
}

// 頂点シェーダーの入力構造体 
struct VSInput
{
	// 頂点座標
	float4 pos_ : POSITION;
	// 法線ベクトル
	float3 normal_ : NORMAL;
	// uv値
	float2 uv_ : TEXCOORD;
	//// 接空間
	//float3 tangent_ : TANGENT;
	//// 頂点色
	//float4 color_ : COLOR;
};

// ピクセルシェーダーの入力構造体 
struct PSInput
{
	// システム様頂点座標
	float4 svPos_ : SV_POSITION;
	// ワールド座標
	float4 worldPos_ : POSITION;
	// 法線ベクトル
	float3 normal_ : NORMAL;
	// uv値
	float2 uv_ : TEXCOORD;

	// 視線ベクトル
	float3 eyeDir_ : EYE_DIRECTION;
};

// ピクセルシェーダーの出力構造体
struct PSOutput
{
	// 描画
	float4 target_ : SV_TARGET;
};

