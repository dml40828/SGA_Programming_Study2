#pragma once

class Material
{
private:
	class Buffer;

public:
	Material();
	Material(wstring shaderFile);
	~Material();

	Shader* GetShader() { return shader; }
	void SetShader(string file);
	void SetShader(wstring file);
	void SetShader(Shader* shader);

	D3DXCOLOR* GetDiffuse() { return &buffer->Data.Diffuse; }
	void SetDiffuse(D3DXCOLOR& color) { buffer->Data.Diffuse = color; }
	void SetDiffuse(float r, float g, float b, float a = 1.0f) {
		buffer->Data.Diffuse = D3DXCOLOR(r, g, b, a);
	}

	Texture* GetDiffuseMap() { return diffuseMap; }
	void SetDiffuseMap(string file, D3DX11_IMAGE_LOAD_INFO* info = NULL);
	void SetDiffuseMap(wstring file, D3DX11_IMAGE_LOAD_INFO* info = NULL);

	void PSSetBuffer();

private:
	Buffer* buffer;

	bool bShaderDelete; // Shader에서 입력된거면 내부에서 안지우려고 쓰는거
	Shader* shader;

	Texture* diffuseMap; // 재질 관리할 클래스

private:
	class Buffer : public ShaderBuffer
	{
	public:
		Buffer() : ShaderBuffer(&Data, sizeof(Struct))
		{
			Data.Diffuse = D3DXCOLOR(1, 1, 1, 1);
		};

		struct Struct
		{
			D3DXCOLOR Diffuse;
		} Data;
	};
};