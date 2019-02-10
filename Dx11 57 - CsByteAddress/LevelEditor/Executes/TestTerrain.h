#pragma once

#include "Systems\IExecute.h"

class TestTerrain : public IExecute
{
public:
	// IExecute��(��) ���� ��ӵ�
	virtual void Initialize() override;
	virtual void Ready() override;
	virtual void Destroy() override;
	virtual void Update() override;
	virtual void PreRender() override;
	virtual void Render() override;
	virtual void PostRender() override;
	virtual void ResizeScreen() override;

private:
	class CubeSky* sky;

	Material* terrainMaterial;
	class Terrain* terrain;
	class PathFinding* pathFinding;
};