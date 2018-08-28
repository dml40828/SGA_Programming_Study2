#include "../000_Header.hlsl"

cbuffer PS_Normal : register(b10)
{
    int VisibleNormal;
}

struct PixelInput
{
    float4 Position : SV_POSITION; // SV�� ������ ����� ������ ���Ѵ�� ���� ��
    float4 wPosition : POSITION0;
    float2 Uv : UV0;
    float3 Normal : NORMAL0;
    float3 Tangent : TANGENT0;
    float3 ViewDir : VIEWDIR0;
};

PixelInput VS(VertexTextureNormalTangent input)
{
     PixelInput output;

    matrix world = Bones[BoneIndex];

    // ��� ���� ��ȯ�� ���Ŀ� position�� ���� �ؾߵǱ� ��
    output.Position = mul(input.Position, world);
    output.wPosition = output.Position;

    output.ViewDir = WorldViewDirection(output.Position);

    output.Position = mul(output.Position, View);
    output.Position = mul(output.Position, Projection);

    output.Uv = input.Uv;

    //output.Normal = mul(input.Normal, (float3x3) world);
    output.Normal = WorldNormal(input.Normal, world);
    output.Tangent = WorldTangent(input.Tangent, world);

    return output;
}

float4 PS(PixelInput input) : SV_TARGET
{
    float4 color = 0;
    
	float4 diffuse = DiffuseMap.Sample(DiffuseSampler, input.Uv);
    if (length(diffuse) > 0)
        DiffuseLighting(color, diffuse, input.Normal);
	else
        DiffuseLighting(color, input.Normal);

    if (VisibleNormal == 1)
    {
        float4 normal = NormalMap.Sample(NormalSampler, input.Uv);
        if (length(normal) > 0)
            NormalMapping(color, normal, input.Normal, input.Tangent);
    }

	float4 specular = SpecularMap.Sample(SpecularSampler, input.Uv);
    if (length(specular) > 0)
        SpecularLighting(color, specular, input.Normal, input.ViewDir);
    else
        SpecularLighting(color, input.Normal, input.ViewDir);

    int i = 0;
    for (i = 0; i < PointLightCount; i++)
        PointLighting(color, PointLights[i], input.wPosition, input.Normal);

	color.a = 1.0f;
	return color;
    // ����� �ϱ� ���ؼ� normal�� ��ȯ���� ��������
    //return float4((input.Normal * 0.5f) + 0.5f, 1);
}