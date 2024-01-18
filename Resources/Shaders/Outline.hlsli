// トランスフォーム
cbuffer cbuff0 : register(b0)
{
	matrix matWorld_; // ワールド行列
	matrix matViewProj_; // ビュープロジェクション行列
	float3 cameraPos_; // カメラ座標
}

// アウトライン
cbuffer cbuff1 : register(b1)
{
	float4 color_; // 色(RGBA)
	float range_; // 範囲
}

// 頂点シェーダーの入力構造体 
struct VSInput
{
	// 頂点座標
	float4 pos : POSITION;
	// 法線ベクトル
	float3 normal : NORMAL;
	// uv値
	float2 uv : TEXCOORD;
};

// ピクセルシェーダーの入力構造体 
struct PSInput
{
	// システム様頂点座標
	float4 svPos : SV_POSITION;
	// ワールド座標
	float4 worldPos : POSITION;
	// 法線ベクトル
	float3 normal : NORMAL;
	// uv値
	float2 uv : TEXCOORD;
	// 視線ベクトル
	float3 eyeDir : EYE_DIRECTION;
};

// ピクセルシェーダーの出力構造体
struct PSOutput
{
	// 描画
	float4 target : SV_TARGET;
};
