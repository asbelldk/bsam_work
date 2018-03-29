Texture2D txDiffuse : register( t0 );
SamplerState samLinear : register( s0 );

cbuffer cbNeverChanges : register( b0 )
{
    matrix View;
};

cbuffer cbChangeOnResize : register( b1 )
{
    matrix Projection;
};

cbuffer cbChangesEveryFrame : register( b2 )
{
    matrix World;
    float4 vLightColor;
};


//--------------------------------------------------------------------------------------
struct VS_INPUT
{
    float4 Pos : POSITION;    
    float3 Norm : NORMAL;
    float2 Tex : TEXCOORD0;
};

struct PS_INPUT
{
    float4 Pos : SV_POSITION;    
    float3 Norm : TEXCOORD0;
    float2 Tex : TEXCOORD1;
};

//struct PS_INPUT2
//{
//	float4 Pos : SV_POSITION;
//	float2 Tex : TEXCOORD0;
//	float2 Tex : TEXCOORD1;
//};

//--------------------------------------------------------------------------------------
// Vertex Shader
//--------------------------------------------------------------------------------------
PS_INPUT VS( VS_INPUT input )
{
    PS_INPUT output = (PS_INPUT)0;
    output.Pos = mul( input.Pos, World );
    output.Pos = mul( output.Pos, View );
    output.Pos = mul( output.Pos, Projection );

    output.Norm = mul( input.Norm, World );
    
    output.Tex = input.Tex;
    
    return output;
}


//--------------------------------------------------------------------------------------
// Pixel Shader
//--------------------------------------------------------------------------------------
float4 PS(PS_INPUT input) : SV_Target
{
	// �ؽ�ó�� �׸��� ���ǹ���� ť�������Ʈ�� �븻���� ����ؼ� ��Į���� ť�������Ʈ�� ����
	float4 finalColor = 1;
	//float N = saturate( dot( float3( -0.577f, 0.177f, -0.577f), input.Norm) );
	float N = saturate(dot(float3(1.0f, 1.0f, 1.0f), input.Norm));
	finalColor = txDiffuse.Sample(samLinear, input.Tex);
	//finalColor = finalColor + (vLightColor * N);

	return finalColor;
}
//float4 PS( PS_INPUT input) : SV_Target
//{
//	// �ؽ�ó�� �׸��� ���ǹ���� ť�������Ʈ�� �븻���� ����ؼ� ��Į���� ť�������Ʈ�� ����
//	float4 finalColor = 1;
//	//float N = saturate( dot( float3( -0.577f, 0.577f, -0.577f), input.Norm) );
//	float N = saturate(dot(float3(1.0f, 1.0f, 1.0f), input.Norm));
//    finalColor = txDiffuse.Sample( samLinear, input.Tex);
//    //finalColor = finalColor + (vLightColor * N);
//    
//    return finalColor;
//}

// �ΰ��� �ؽ�ó ������(���� ���� �ؽ�ó �ΰ��� ����
float4 Overlay(float4 a, float4 b) : SV_Target
{
	float4 r = a < .5 ? 2.0 * a * b : 1.0 - 2.0 * (1.0 - a) * (1.0 - b);
	r.a = b.a;
	return r;
}