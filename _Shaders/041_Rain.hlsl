#include "000_Header2.hlsl"

cbuffer VS_Buffer : register(b10)
{
    float3 Velocity;
    float DrawDistance;

    float4 Color;
    float3 Origin;
    float Time;

    float3 Size;
}

struct VertexInput
{
    float4 Position : POSITION0;
    float2 Uv : UV0;
    float2 Scale : SCALE0;
};

struct VertexOutput
{
    float4 Position : SV_POSITION;
    float2 Uv : UV0;
    float Alpha : ALPHA0;
    float4 Color : COLOR0;
};

VertexOutput VS(VertexInput input)
{
    VertexOutput output;

    float3 velocity = Velocity;
	// y 스케일에 따라 xz의 크기를 조정해서 보여주려고 하는거
    velocity.xz /= input.Scale.y * 0.1f;

	// 위치 이동 시키는 거
    float3 displace = Time * velocity;

    //input.Position.y = Origin.y + (Size.y + (input.Position.y + displace.y) % Size.y) % Size.y;
    //if (velocity.x >= 0)
    //    input.Position.x = Origin.x + (input.Position.x + displace.x) % Size.x;
    //else
    //    input.Position.x = Origin.x + Size.x - (input.Position.x + displace.x) % Size.x;

    //if (velocity.z >= 0)
    //    input.Position.z = Origin.z + (input.Position.z + displace.z) % Size.z;
    //else
    //    input.Position.z = Origin.z + Size.z - (input.Position.z + displace.z) % Size.z;

	// 일진씨 방법
    //float3 size = Size * 2.0f;
    //int3 signValue = 0;
    //signValue = sign(velocity);
    //input.Position.xyz = Origin + (-1.0f * signValue * Size) + (input.Position.xyz + displace) % size;

	// 동헌씨 방법
    input.Position.xyz = Origin.xyz 
		+ (Size.xyz + (input.Position.xyz + displace.xyz) % Size.xyz) % Size.xyz 
		- (Size.xyz * 0.5f);

    float4 position = mul(input.Position, World);
    float3 axis = normalize(-velocity);
    float3 view = position.xyz - CameraPosition();
    float3 side = normalize(cross(axis, view));

    position.xyz += (input.Uv.x - 0.5f) * side * input.Scale.x;
    position.xyz += (1.5f - input.Uv.y * 1.5f) * axis * input.Scale.y;

    position.w = 1.0f;

    output.Position = mul(position, View);
    output.Position = mul(output.Position, Projection);

    output.Uv = input.Uv;
	output.Color = Color;

    float alpha = cos(Time + (input.Position.x + input.Position.z));
    alpha = saturate(1.5f + alpha / DrawDistance * 2);

    output.Alpha = 0.2f * saturate(1 - output.Position.z / DrawDistance) * alpha;

    return output;
}

Texture2D Map : register(t10);
SamplerState Sampler : register(s10);

float4 PS(VertexOutput input) : SV_TARGET
{
    float4 color = Map.Sample(Sampler, input.Uv);
    color.rgb *= input.Color.xyz * (1 + input.Alpha) * 2.0f;
    color.a *= input.Alpha;

    return color;
}