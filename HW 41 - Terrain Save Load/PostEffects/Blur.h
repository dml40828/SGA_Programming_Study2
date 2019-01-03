#pragma once

class Blur
{
public:
	Blur(wstring shaderFile, UINT width, UINT height, DXGI_FORMAT format, int blurCount);
	~Blur();

	void SetWeights(float sigma);
	void Dispatch(ID3D11ShaderResourceView* inputSRV, ID3D11UnorderedAccessView* inputUAV);

private:
	Shader* shader;
	UINT width, height;

	int blurCount;

	ID3D11ShaderResourceView* srv;
	ID3D11UnorderedAccessView* uav;
};