#pragma once
#include "Execute.h"

class ExeGrid : public Execute
{
private:
	class ColorBuffer; // ���� Ŭ������ Ŭ���� �ȿ��� ���漱�� �������

	typedef VertexTexture VertexType;
	
public:
	ExeGrid(ExecuteValues* values);
	~ExeGrid();

	// Execute��(��) ���� ��ӵ�
	void Update();
	void PreRender();
	void Render();
	void PostRender();
	void ResizeScreen();
	
private:
	Shader* shader;
	WorldBuffer * worldBuffer;

	UINT width, height;

	ID3D11Buffer * vertexBuffer;
	ID3D11Buffer * indexBuffer;

	UINT vertexCount, indexCount;
	
	VertexType * vertices;
	UINT * indices;
	
	ColorBuffer * colorBuffer;

	// ������ Texture Ŭ���� �� ��
	Texture* texture[3];

private:
	class ColorBuffer : public ShaderBuffer
	{
	public:
		ColorBuffer()
			: ShaderBuffer(&Data, sizeof(Data))
		{
			Data.Color = D3DXCOLOR(1, 1, 1, 1);
		}

		~ColorBuffer() 
		{

		}

		struct Struct
		{
			D3DXCOLOR Color; 
		} Data;
	};
};