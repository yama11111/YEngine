// 丸影
static const float CircleShadowNum = 30;
struct CircleShadow
{
    float3 shadowDir; // 向き
    float3 casterPos; // キャスター座標
    float distanceFromCasterToShadow; // キャスターから影の距離
    float3 shadowAtten; // 距離減衰係数
    float shadowStartFactorAngleCos; // 減衰開始角度
    float shadowEndFactorAngleCos; // 減衰終了角度
    float active; // 動作フラグ
};

/// <summary>
/// 丸影の影色値を計算する
/// </summary>
/// <returns>影色値</returns>
float CalcCircleShadowColor(
	CircleShadow circleShadows_[CircleShadowNum], 
	const float3 worldPos)
{
    float result = 0.0f;
	
    for (float i = 0; i < CircleShadowNum; i++)
    {
        if (circleShadows_[i].active <= 0.0f) { continue; }
		
		// 向きを反転
        float3 shadowDir = -circleShadows_[i].shadowDir;
		
		// オブジェクト → キャスター のベクトル
        float3 objToCasterVec = circleShadows_[i].casterPos - worldPos;
			
		// 投影方向の距離
        float d = dot(objToCasterVec, shadowDir);
			
		// 距離減衰係数
        float atten = 
			saturate(1.0f /
				(circleShadows_[i].shadowAtten.x +
				circleShadows_[i].shadowAtten.y * d +
				circleShadows_[i].shadowAtten.z * d * d));
			
		// 距離 0以下 は 0 に
        atten *= step(0, d);

		// 影(仮想ライト)の座標
        float3 shadowPos =
			circleShadows_[i].casterPos +
			shadowDir * circleShadows_[i].distanceFromCasterToShadow;
			
		// オブジェクト → 影 のベクトル
        float3 objToShadowVec = normalize(shadowPos - worldPos);

		// 角度減衰
		// 減衰開始角 → 減衰終了角 にかけて減衰
		// 内側 は 1倍、外側 は 0倍 の輝度
        float cosAngle = dot(objToShadowVec, shadowDir);
        float angelAtten = 
			smoothstep(
				cos(circleShadows_[i].shadowEndFactorAngleCos),
				cos(circleShadows_[i].shadowStartFactorAngleCos),
				cosAngle);
			
		// 角度減衰を乗算
        atten *= angelAtten;
			
		// 全て減算する
        result -= atten;
    }
	
    return result;
}