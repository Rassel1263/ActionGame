Texture2D SpriteTexture;
float xGlowValue;
float2 xTextureSize : VPOS;
float4 xOutlineColor;
float4 xOutGlowColor;

sampler2D InputSampler = sampler_state
{
	Texture = <SpriteTexture>;
};

struct VertexShaderOutput
{
	float3 Position : SV_Position;
	float4 Color : COLOR0;
	float2 UV : TEXCOORD0;
};

float4 main(VertexShaderOutput input) : COLOR
{
	// 텍스쳐의 색깔을 가지고옴
	float4 currentPixel = tex2D(InputSampler, input.UV) * input.Color;
	float4 output = currentPixel;

	// 텍스쳐의 1픽셀의 UV값?
	if (currentPixel.a == 0.0f)
	{
		float2 uvPix = float2(1 / xTextureSize.x, 1 / xTextureSize.y);

		// 아웃라인을 그린 조건
		if (tex2D(InputSampler, float2(uvPix.x + input.UV.x, input.UV.y)).a > 0 ||
			tex2D(InputSampler, float2(input.UV.x, uvPix.y + input.UV.y)).a > 0 ||
			tex2D(InputSampler, float2(input.UV.x - uvPix.x, input.UV.y)).a > 0 ||
			tex2D(InputSampler, float2(input.UV.x, input.UV.y - uvPix.y)).a > 0
			)
		{
			output = xOutlineColor;
		}
	}
	else
	{
		// 인자값으로 넘어온 함수를 0 ~ 1
		output = currentPixel + xOutGlowColor * (1 - saturate(abs(input.UV.y - xGlowValue)));
	}

	return output;
}

technique Simple
{
	pass pass0
	{
		PixelShader = compile ps_2_0 main();
	}
};