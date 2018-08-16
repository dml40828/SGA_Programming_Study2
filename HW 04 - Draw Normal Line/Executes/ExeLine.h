#pragma once
#include "Execute.h"

class ExeLine : public Execute
{
private:
	class ColorBuffer; // ���� Ŭ������ Ŭ���� �ȿ��� ���漱�� �������

	typedef VertexColor VertexType;
public:
	ExeLine(ExecuteValues* values, 
		D3DXVECTOR3 * startPos, D3DXVECTOR3 * endPos,
		UINT lineCount);
	~ExeLine();

	// Execute��(��) ���� ��ӵ�
	void Update();
	void PreRender();
	void Render();
	void PostRender();
	void ResizeScreen();
	
	void ResizeLength(D3DXVECTOR3 * endPos);
private:
	Shader* shader;
	WorldBuffer * worldBuffer;

	ID3D11Buffer * vertexBuffer;
	//ID3D11Buffer * indexBuffer;

	UINT vertexCount, indexCount;
	
	VertexType * vertices;
	//UINT * indices;
	
	ColorBuffer * colorBuffer;

	D3DXVECTOR3 * startPos;
	D3DXVECTOR3 * endPos;
	UINT lineCount;
private:
	// �÷����� ����Ʈ�� ����
	class ColorBuffer : public ShaderBuffer
	{
	public:
		ColorBuffer()
			: ShaderBuffer(&Data, sizeof(Data))
		{
			Data.Color = D3DXVECTOR4(1, 1, 1, 1);
		}

		~ColorBuffer() 
		{

		}

		struct Struct
		{
			D3DXVECTOR4 Color;
		} Data;
	};
};