/*!
 * @brief	モデルシェーダー。
 */

#include "modelCB.h"
#include "modelStruct.h"
#include "modelSRV.h"
#include "sampleBRDF.h"

#include "LightingFunction.h"


/*!
 *@brief	影が落ちる確率を計算する。
 */
float CalcShadowPercentPCF4x4(Texture2D<float4> tex, float2 uv, float2 offset, float depth, float dOffset)
{
	float2 offsetTbl[] = {
		float2(	 -1.5f * offset.x, -1.5f * offset.y),
		float2(	 -0.5f * offset.x, -1.5f * offset.y),
		float2(   0.5f * offset.x, -1.5f * offset.y),
		float2(	  1.5f * offset.x, -1.5f * offset.y),

		float2(	 -1.5f * offset.x, -0.5f * offset.y),
		float2(	 -0.5f * offset.x, -0.5f * offset.y),
		float2(	  0.5f * offset.x, -0.5f * offset.y),
		float2(	  1.5f * offset.x, -0.5f * offset.y),

		float2(	-1.5f * offset.x, 0.5f * offset.y),
		float2(	-0.5f * offset.x, 0.5f * offset.y),
		float2(	 0.5f * offset.x, 0.5f * offset.y),
		float2(	 1.5f * offset.x, 0.5f * offset.y),

		float2(	-1.5f * offset.x, 1.5f * offset.y),
		float2(	-0.5f * offset.x, 1.5f * offset.y),
		float2(	 0.5f * offset.x, 1.5f * offset.y),
		float2(	 1.5f * offset.x, 1.5f * offset.y),
		
	};
	float weightTbl[] = {
		1,2,2,1,
		2,3,3,2,
		2,3,3,2,
		1,2,2,1,
	};
	float percent = 0.0f;
	float shadow_val=0.0f;
	float totalWeight = 0.0f;
	for (int i = 0; i < 16; i++) {
		shadow_val = tex.Sample(Sampler, uv + offsetTbl[i]).r;
		totalWeight += weightTbl[i];
		if (depth > shadow_val.r + dOffset) {
			//影が落ちている。
			percent += 1.0f * weightTbl[i];
		}
	}
	percent /= totalWeight;
	return percent;
}
/*!
*@brief	影が落ちる確率を計算する。
*/
float CalcShadowPercentPCF2x2(Texture2D<float4> tex, float2 uv, float2 offset, float depth, float dOffset)
{
	float2 offsetTbl[] = {
		float2(-0.5f * offset.x, -0.5f * offset.y),
		float2(0.5f * offset.x, -0.5f * offset.y),
		float2(-0.5f * offset.x, 0.5f * offset.y),
		float2(0.5f * offset.x, 0.5f * offset.y),

	};

	float percent = 0.0f;
	float shadow_val = 0.0f;
	for (int i = 0; i < 4; i++) {
		shadow_val = tex.Sample(Sampler, uv + offsetTbl[i]).r;
		if (depth > shadow_val.r + dOffset) {
			//影が落ちている。
			percent += 1.0f;
		}
	}
	percent /= 4.0f;
	return percent;
}
float CalcShadowPercent(Texture2D<float4> tex, float2 uv, float2 offset, float depth, float dOffset)
{
	float shadow_val = tex.Sample(Sampler, uv).r;
	if (depth > shadow_val.r + dOffset) {
		return 1.0f;
	}
	return 0.0f;
}
/*!
 *@brief	ソフト影を計算。
 *@return 影が落ちる確率が返ります。0.0なら影が落ちない。1.0なら影が落ちる。
 */
float CalcSoftShadow( float3 worldPos )
{
	float shadow = 0.0f;
	//ちょっと適当。
	if(isShadowReceiver){
		//影を落とす。
		[unroll]
		for(int i = 0; i < NUM_SHADOW_MAP; i++ ){
			float4 posInLVP = mul(mLVP[i], float4(worldPos, 1.0f) );
			posInLVP.xyz /= posInLVP.w;
			
			float depth = min(posInLVP.z / posInLVP.w, 1.0f);
			
			//uv座標に変換。
			float2 shadowMapUV = float2(0.5f, -0.5f) * posInLVP.xy  + float2(0.5f, 0.5f);
			float shadow_val = 1.0f;
			if(shadowMapUV.x < 0.95f && shadowMapUV.y < 0.95f && shadowMapUV.x > 0.05f && shadowMapUV.y > 0.05f){
				if(i == 0){					
					shadow = CalcShadowPercentPCF4x4(shadowMap_0, shadowMapUV, texOffset[i], depth, depthOffset.x);
				}else if(i == 1){
					shadow = CalcShadowPercentPCF2x2(shadowMap_1, shadowMapUV, texOffset[i], depth, depthOffset.y);
				}else if(i == 2){
					shadow = CalcShadowPercent(shadowMap_2, shadowMapUV, texOffset[i], depth, depthOffset.z);
				}
				break;
			}
		}
	}
	return shadow;
}
/*!
 *@brief	ソフト影を計算。
 *@return 影が落ちる確率が返ります。0.0なら影が落ちない。1.0なら影が落ちる。
 */
float CalcShadow( float3 worldPos )
{
	float shadow = 0.0f;
	//ちょっと適当。
	if(isShadowReceiver){
		//影を落とす。
		[unroll]
		for(int i = 0; i < NUM_SHADOW_MAP; i++ ){
			float4 posInLVP = mul(mLVP[i], float4(worldPos, 1.0f) );
			posInLVP.xyz /= posInLVP.w;
			
			float depth = min(posInLVP.z / posInLVP.w, 1.0f);
			
			//uv座標に変換。
			float2 shadowMapUV = float2(0.5f, -0.5f) * posInLVP.xy  + float2(0.5f, 0.5f);
			float shadow_val = 1.0f;
			if(shadowMapUV.x < 0.95f && shadowMapUV.y < 0.95f && shadowMapUV.x > 0.05f && shadowMapUV.y > 0.05f){
				if(i == 0){
					shadow = CalcShadowPercent(shadowMap_0, shadowMapUV, texOffset[i], depth, depthOffset.x);
				}else if(i == 1){
					shadow = CalcShadowPercent(shadowMap_1, shadowMapUV, texOffset[i], depth, depthOffset.y);
				}else if(i == 2){
					shadow = CalcShadowPercent(shadowMap_2, shadowMapUV, texOffset[i], depth, depthOffset.z);
				}
				break;
			}
		}
	}
	return shadow;
}
/*!
 *@brief	法線を計算。
 */
float3 CalcNormal( float3 normal, float3 biNormal, float3 tangent, float2 uv )
{
	if(hasNormalMap){
		//法線マップがある。
		float3 binSpaceNormal = normalMap.Sample(Sampler, uv).xyz;
		binSpaceNormal = (binSpaceNormal * 2.0f)- 1.0f;
		normal = tangent * binSpaceNormal.x + biNormal * binSpaceNormal.y + normal * binSpaceNormal.z; 
	}
	return normal;
}
/*!
 *@brief	スキン行列を計算。
 */
float4x4 CalcSkinMatrix(VSInputNmTxWeights In)
{
	float4x4 skinning = 0;	
	float w = 0.0f;
	[unroll]
    for (int i = 0; i < 3; i++)
    {
        skinning += boneMatrix[In.Indices[i]] * In.Weights[i];
        w += In.Weights[i];
    }
    
    skinning += boneMatrix[In.Indices[3]] * (1.0f - w);
    return skinning;
}
/*!--------------------------------------------------------------------------------------
 * @brief	スキンなしモデル用の頂点シェーダーのコアプログラム。
-------------------------------------------------------------------------------------- */
PSInput VSMainCore( VSInputNmTxVcTangent In, float4x4 worldMat )
{
	PSInput psInput = (PSInput)0;
	float4 pos = mul(worldMat, In.Position);
	psInput.Pos = pos;
	pos = mul(mView, pos);
	psInput.posInView = pos;
	pos = mul(mProj, pos);
	psInput.posInProj = pos;
	psInput.Position = pos;
	psInput.TexCoord = In.TexCoord;
	psInput.Normal = normalize(mul(worldMat, In.Normal));
	psInput.Tangent = normalize(mul(worldMat, In.Tangent));
    return psInput;
}
/*!--------------------------------------------------------------------------------------
 * @brief	スキンなしモデル用の頂点シェーダー。
-------------------------------------------------------------------------------------- */
PSInput VSMain( VSInputNmTxVcTangent In ) 
{
	return VSMainCore(In, mWorld);
}
/*!--------------------------------------------------------------------------------------
 * @brief	スキンなしモデル用の頂点シェーダー(インスタンシング描画用)。
-------------------------------------------------------------------------------------- */
PSInput VSMainInstancing( VSInputNmTxVcTangent In, uint instanceID : SV_InstanceID )
{
	return VSMainCore(In, instanceMatrix[instanceID]);
}
/*!--------------------------------------------------------------------------------------
 * @brief	スキンありモデル用の頂点シェーダー。
-------------------------------------------------------------------------------------- */
PSInput VSMainSkin( VSInputNmTxWeights In ) 
{
	PSInput psInput = (PSInput)0;
	//スキン行列を計算。
	float4x4 skinning = CalcSkinMatrix(In);
	//ワールド座標、法線、接ベクトルを計算。
	float4 pos = mul(skinning, In.Position);
	psInput.Normal = normalize( mul(skinning, In.Normal) );
	psInput.Tangent = normalize( mul(skinning, In.Tangent) );
	
	psInput.Pos = pos;
	pos = mul(mView, pos);
	psInput.posInView = pos;
	pos = mul(mProj, pos);
	psInput.posInProj = pos;

	psInput.Position = pos;
	psInput.TexCoord = In.TexCoord;
	
    return psInput;
}


/*!
 *@brief	Z値を書き込むためだけの描画パスで使用される頂点シェーダー。
 *			スキンなしモデル用
 *@details
 * 現在はシャドウマップ作成とZPrepassで使用されています。
 */
PSInput_RenderToDepth VSMain_RenderDepth(VSInputNmTxVcTangent In)
{
	PSInput_RenderToDepth psInput = (PSInput_RenderToDepth)0;
	float4 pos;
	pos = mul(mWorld, In.Position);
	psInput.Pos = pos;
	pos = mul(mView, pos);
	pos = mul(mProj, pos);
	psInput.Position = pos;
	psInput.posInProj = pos;
	return psInput;
}
/*!
 *@brief	Z値を書き込むためだけの描画パスで使用される頂点シェーダー。
 *			スキンなしインスタンシングモデル用
 *@details
 * 現在はシャドウマップ作成とZPrepassで使用されています。
 */

PSInput_RenderToDepth VSMainInstancing_RenderDepth(
	VSInputNmTxVcTangent In, 
	uint instanceID : SV_InstanceID
)
{
	PSInput_RenderToDepth psInput = (PSInput_RenderToDepth)0;
	float4 pos;
	pos = mul(instanceMatrix[instanceID], In.Position);
	psInput.Pos = pos;
	pos = mul(mView, pos);
	pos = mul(mProj, pos);
	psInput.Position = pos;
	psInput.posInProj = pos;
	return psInput;
}
/*!
 *@brief	Z値を書き込むためだけの描画パスで使用される頂点シェーダー。
 *			スキンありモデル用。
 *@details
 * 現在はシャドウマップ作成とZPrepassで使用されています。
 */
PSInput_RenderToDepth VSMainSkin_RenderDepth(VSInputNmTxWeights In)
{
	PSInput_RenderToDepth psInput = (PSInput_RenderToDepth)0;
	//スキン行列を計算。
	float4x4 skinning = CalcSkinMatrix(In);
	//ワールド座標、法線、接ベクトルを計算。
	float4 pos = mul(skinning, In.Position);
	psInput.Pos = pos;
	pos = mul(mView, pos);
	pos = mul(mProj, pos);
	
	psInput.Position = pos;
	psInput.posInProj = pos;
	return psInput;
	
}
//--------------------------------------------------------------------------------------
// ピクセルシェーダーのエントリ関数。
//--------------------------------------------------------------------------------------
float4 PSMain( PSInput In ) : SV_Target0
{
	//for 今井 In.Posに鏡のビュー行列とプロジェクション行列を乗算する。
	//その座標が-1.0から1.0の間にいたらピクセルキル。
	float4 pos = float4(In.Pos, 1.0f);
	//鏡カメラの座標系に変換する。
	pos = mul(mMirrorView, pos);
	//鏡スクリーンの座標系に変換する。
	pos = mul(mMirrorProj, pos);
	pos.xyz /= pos.w;
	if (alphaflag == 0
		&&pos.x <= 1.0f && pos.x >= -1.0f
		&& pos.y <= 1.0f && pos.y >= -1.0f
		&& pos.z >= 0.0f && pos.z < 1.0f
		) {
		//鏡に映っているのでピクセルキル。
		discard;
	}
	if (enableDithering == 1) {
		//ディザディザ
		pos = float4(In.Pos, 1.0f);
		//ディザの基点となる座標をカメラ空間に変換する。
		float4 ditherPosInView = mul(mView, dithreingOrigin);
		float4 posInView = mul(mView, pos);
		//テスト。
		if (posInView.z < ditherPosInView.z) {
			float2 screenPos = In.posInProj.xy / In.posInProj.w;
			//-1.0〜1.0の座標系を保存。
			float2 screenPosBackup = screenPos;
			//0.0〜1.0の座標系に変換。
			screenPos = screenPos * float2(0.5f, -0.5f) + 0.5f;
			//ディザで半透明。
			//ディザパターン
			static const int pattern[] = {
				0, 32,  8, 40,  2, 34, 10, 42,   /* 8x8 Bayer ordered dithering  */
				48, 16, 56, 24, 50, 18, 58, 26,  /* pattern.  Each input pixel   */
				12, 44,  4, 36, 14, 46,  6, 38,  /* is scaled to the 0..63 range */
				60, 28, 52, 20, 62, 30, 54, 22,  /* before looking in this table */
				3, 35, 11, 43,  1, 33,  9, 41,   /* to determine the action.     */
				51, 19, 59, 27, 49, 17, 57, 25,
				15, 47,  7, 39, 13, 45,  5, 37,
				63, 31, 55, 23, 61, 29, 53, 21
			};
			screenPos.x *= 1.7777f;
			float2 uv = fmod(screenPos * 200.0f, 8.0f);
			float t = 0.0f;
			int x = (int)uv.x;
			int y = (int)uv.y;
			int index = y * 8 + x;
			t = (float)pattern[index] / 64.0f;
			//ディザ
			//float ditherRate = 1.0; //ディザ係数を定数バッファに用意して、CPU側から指定できるようにする。
			float ditherR = ditherRate;
			if (DeadFlag == 0) {
				ditherR *= pow(min(1.0f, 1.0f - abs(screenPosBackup.x) + 0.1f), 1.3);
				ditherR *= min(1.0f, 1.0f - abs(max(-1.0f, screenPosBackup.y + 0.7f)) + 0.1f);
				clip(t - ditherR); //ディザ係数を定数バッファに用意して、CPU側から指定できるようにする。
			}
			if (DeadFlag == 1) {
				ditherR *= pow(min(1.0f, 1.0f - abs(screenPosBackup.x) + 0.1f), 1.3);
				ditherR *= min(1.1f, 1.0f - abs(max(-1.0f, screenPosBackup.y + 0.2f)) + 1.0f);
				clip(t - ditherR); //ディザ係数を定数バッファに用意して、CPU側から指定できるようにする。
			}
		}
		
	}
#if 0
	//アルベド。
	float4 albedo = float4(albedoTexture.Sample(Sampler, In.TexCoord).xyz, 1.0f);
	float4 color = albedo * float4(ambientLight, 1.0f);
	float2 uv = In.posInProj.xy / In.posInProj.w;
	uv = (uv * float2(0.5f, -0.5f)) + 0.5f;
	float shadow = softShadowMap.Sample(Sampler, uv).r ;
	color.xyz *= lerp( 1.0f, 0.5f, shadow);
	
	//視点までのベクトルを求める。
	float3 toEye = normalize(eyePos - In.Pos);
	//従ベクトルを計算する。
	float3 biNormal = normalize(cross(In.Tangent, In.Normal));
	//法線を計算。
	float3 normal = normalize(In.Normal);
	float toEyeLen = length(toEye);
	float3 toEyeDir = float3(1.0f, 0.0f, 0.0f);
	if(toEyeLen > 0.001f){
		toEyeDir = toEye / toEyeLen;
	}
	
	float3 toEyeReflection = -toEyeDir + 2.0f * dot(normal, toEyeDir) * normal;
	
	//ポイントライトを計算。
	color.xyz += CalcPointLight(
		albedo,
		In.Pos, 
		In.posInProj, 
		normal,
		In.Tangent,
		biNormal,
		toEyeDir,
		toEyeReflection, 
		1.0f,
		0.0f
	);
	
	return color;
#else
	float3 lig = 0.0f;
	//視点までのベクトルを求める。
	float3 toEye = normalize(eyePos - In.Pos);
	//従ベクトルを計算する。
	float3 biNormal = normalize(cross(In.Tangent, In.Normal));
	//アルベド。
	float4 albedo = float4(albedoTexture.Sample(Sampler, In.TexCoord).xyz, 1.0f);
	//法線を計算。
	float3 normal = CalcNormal( In.Normal, biNormal, In.Tangent, In.TexCoord);
		
	float specPow = 0.0f;
	float roughness = 1.0f;
	if(hasSpecularMap){
		float4 t = specularMap.Sample(Sampler, In.TexCoord);
		specPow = t.x;
		roughness = 1.0f - t.w;
		roughness *= 0.8f;	//@todo マテリアルパラメータにすべきだな。
	}
	float toEyeLen = length(toEye);
	float3 toEyeDir = float3(1.0f, 0.0f, 0.0f);
	if(toEyeLen > 0.001f){
		toEyeDir = toEye / toEyeLen;
	}

	float3 toEyeReflection = -toEyeDir + 2.0f * dot(normal, toEyeDir) * normal;
	
	//影を計算。
	float2 uv = In.posInProj.xy / In.posInProj.w;
	uv = (uv * float2(0.5f, -0.5f)) + 0.5f;
	float shadow = softShadowMap.Sample(Sampler, uv).r ;	
	//ディレクションライト
	float3 finalColor = 0.0f;
	if(shadow < 0.99f){ 
		//影が落ちる可能性が低い場合のみ計算する。
		finalColor = CalcDirectionLight(
			albedo,
			In.Pos, 
			normal, 
			In.Tangent,
			biNormal,
			toEyeDir,
			toEyeReflection, 
			roughness,
			specPow
		) * (1.0f - shadow);
	}
	
	//ポイントライトを計算。
	finalColor += CalcPointLight(
		albedo,
		In.Pos, 
		In.posInProj, 
		normal,
		In.Tangent,
		biNormal,
		toEyeDir,
		toEyeReflection, 
		roughness,
		specPow
	);
    
	//アンビエントライト。
	finalColor += CalcAmbientLight(
		albedo,
		normal,
		In.Tangent,
		biNormal,
		toEyeDir,
		roughness,
		specPow
	);
	
	// brightness
	float brightness = 1.0f;
    finalColor *= brightness;
/*
    // exposure
    float exposure = 1.0f;
    finalColor *= pow( 2.0, exposure );
  */  
    float gamma = 2.2f;
    finalColor = max( 0.0f, pow( finalColor, 1.0 / gamma ) );
    if(isnan(finalColor.x) || isnan(finalColor.y) || isnan(finalColor.z)){
		return float4(1.0f, 0.0f, 0.0f, 1.0f);
	}
    return float4(finalColor, 1.0f); 
#endif
}


/*!
 *@brief	Z値を書き込むためだけの描画パスで使用されるピクセルシェーダー。
 *@details
 * 現在はシャドウマップ作成とZPrepassで使用されています。
 */
float4 PSMain_RenderDepth( PSInput_RenderToDepth In ) : SV_Target0
{
	//for 今井 In.Posに鏡のビュー行列とプロジェクション行列を乗算する。
	//その座標が-1.0から1.0の間にいたらピクセルキル。
	float4 pos = float4(In.Pos, 1.0f);
	//鏡カメラの座標系に変換する。
	pos = mul(mMirrorView, pos);
	//鏡スクリーンの座標系に変換する。
	pos = mul(mMirrorProj, pos);
	pos.xyz /= pos.w;
	if (alphaflag==0 
		&&pos.x <= 1.0f && pos.x >= -1.0f
		&& pos.y <= 1.0f && pos.y >= -1.0f
		&& pos.z >= 0.0f && pos.z < 1.0f
		) {
		//鏡に映っているのでピクセルキル。
		discard;
	}
	float z = In.posInProj.z / In.posInProj.w;
	return z;
}
/*!
 * @brief	G-Buffer書き込み用の描画パスで使用されるピクセルシェーダー。
 */
PSOutput_RenderGBuffer PSMain_RenderGBuffer( PSInput In )
{
	PSOutput_RenderGBuffer Out = (PSOutput_RenderGBuffer)0;
	float4 pos = float4(In.Pos, 1.0f);
	//鏡カメラの座標系に変換する。
	pos = mul(mMirrorView, pos);
	//鏡スクリーンの座標系に変換する。
	pos = mul(mMirrorProj, pos);
	pos.xyz /= pos.w;
	if (alphaflag == 0
		&& pos.x <= 1.0f && pos.x >= -1.0f
		&& pos.y <= 1.0f && pos.y >= -1.0f
		&& pos.z >= 0.0f && pos.z < 1.0f
		) {
		//鏡に映っているのでピクセルキル。
		discard;
	}
	//法線はまだ出さない。
	//シャドウマスク出力する。
	if(isPCFShadowMap){
		//PCFをかける。
		Out.shadow = CalcSoftShadow(In.Pos);
	}else{
		//何もしない。
		Out.shadow = CalcShadow(In.Pos);
	}
	return Out;
}
/*!
 *@brief	シルエット描画。
 * GameDemoのためのスペシャルシェーダー。
 */
float4 PSMain_Silhouette( PSInput In ) : SV_Target0
{
	float2 screenPos = In.posInProj.xy / In.posInProj.w;
	screenPos = screenPos * float2( 0.5f, -0.5f ) + 0.5f;
	
#if 1 ////ディザリングを試す。
	//ディザパターン
	static const int pattern[] = {
	    0, 32,  8, 40,  2, 34, 10, 42,   /* 8x8 Bayer ordered dithering  */
	    48, 16, 56, 24, 50, 18, 58, 26,  /* pattern.  Each input pixel   */
	    12, 44,  4, 36, 14, 46,  6, 38,  /* is scaled to the 0..63 range */
	    60, 28, 52, 20, 62, 30, 54, 22,  /* before looking in this table */
	    3, 35, 11, 43,  1, 33,  9, 41,   /* to determine the action.     */
	    51, 19, 59, 27, 49, 17, 57, 25,
	    15, 47,  7, 39, 13, 45,  5, 37,
	    63, 31, 55, 23, 61, 29, 53, 21 
	};
	screenPos.x *= 1.7777f;
	float2 uv = fmod(screenPos * 200.0f, 8.0f);
	float t = 0.0f;
	int x = (int)uv.x;
	int y = (int)uv.y;
	int index = y * 8 + x;
	t = (float)pattern[index] / 64.0f;
	//ディザ
	clip(t - 0.5f);
	return float4(t, t, t, 1.0f);

#else
	screenPos.x *= 1.7777f;		//アスペクト比をかける。
	return silhouetteTexture.Sample(Sampler, screenPos * 12.0f) * 4.0f;
#endif
}