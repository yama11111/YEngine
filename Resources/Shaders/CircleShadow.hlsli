// 丸影
static const float CircleShadowNum = 30;
struct CircleShadow
{
    float3 shadowDir_; // 向き
    float3 casterPos_; // キャスター座標
    float distanceFromCasterToShadow_; // キャスターから影の距離
    float3 shadowAtten_; // 距離減衰係数
    float shadowStartFactorAngleCos_; // 減衰開始角度
    float shadowEndFactorAngleCos_; // 減衰終了角度
    float active_; // 動作フラグ
};