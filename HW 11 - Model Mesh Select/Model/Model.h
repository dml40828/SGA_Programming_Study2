#pragma once

class ModelBone;
class ModelMesh;

class Model
{
public:
	Model();
	~Model();

	UINT MaterialCount() { return materials.size(); }
	vector<Material *>& Materials() { return materials; }
	Material* MaterialByIndex(UINT index) { return materials[index]; }
	Material* MaterialByName(wstring name);

	UINT BoneCount() { return bones.size(); }
	vector<ModelBone *>& Bones() { return bones; }
	ModelBone* BoneByIndex(UINT index) { return bones[index]; }
	ModelBone* BoneByName(wstring name);

	UINT MeshCount() { return meshes.size(); }
	vector<ModelMesh *>& Meshes() { return meshes; }
	ModelMesh* MeshByIndex(UINT index) { return meshes[index]; }
	ModelMesh* MeshByName(wstring name);

	void ReadMaterial(wstring folder, wstring file);
	void ReadMesh(wstring folder, wstring file);

	// �⺻���� ��ﶩ �̳༮ �ᵵ ��
	void CopyGlobalBoneTo(vector<D3DXMATRIX>& transforms);
	// �̵���ų�� �̳༮ ȣ��
	void CopyGlobalBoneTo(vector<D3DXMATRIX>& transforms, D3DXMATRIX& w);

public:
	void MinMaxVertex(D3DXVECTOR3* min, D3DXVECTOR3* max);

	bool IsPick(D3DXVECTOR3& start, D3DXVECTOR3& direction, 
		OUT float& u, OUT float& v, OUT float& distance);

	bool IsPickMesh(D3DXVECTOR3& start, D3DXVECTOR3& direction,
		OUT float& u, OUT float& v, OUT float& distance,
		OUT wstring& meshName);

	vector<wstring> GetMesheNames();
private:
	// �θ� �ڽ� ���� ���� ���� �Լ�
	void BindingBone();
	void BindingMesh();

private:
	class ModelBone* root;

	vector<Material *> materials;
	vector<class ModelMesh *> meshes;
	vector<class ModelBone *> bones;

private:
	class BoneBuffer : public ShaderBuffer
	{
	public:
		BoneBuffer() : ShaderBuffer(&Data, sizeof(Data))
		{
			for (int i = 0; i < 128; i++)
				D3DXMatrixIdentity(&Data.Bones[i]);
		}


		void Bones(D3DXMATRIX* m, UINT count)
		{
			memcpy(Data.Bones, m, sizeof(D3DXMATRIX)*  count);

			for (UINT i = 0; i < count; i++)
				D3DXMatrixTranspose(&Data.Bones[i], &Data.Bones[i]);
		}

	private:
		struct Struct
		{
			// �ٸ� ����� ��Ʈ������ ����
			// �׳� ���� ���� �ȵǰ� Transpose ���ذ� �־������
			D3DXMATRIX Bones[128];
		} Data;
	};

	BoneBuffer* buffer;

public:
	BoneBuffer* Buffer() { return buffer; }
};

// �� �ѹ� �ҷ����� �ٽ� �Ⱥҷ����� �ϱ� ���� Ŭ����
class Models
{
public:
	friend class Model;

public:
	static void Create();
	static void Delete();

private:
	static void LoadMaterial(wstring file, vector<Material *>* materials);
	static void ReadMaterialData(wstring file);

	static void LoadMesh(wstring file, vector<class ModelBone *>* bones, vector<class ModelMesh *>* meshes);
	static void ReadMeshData(wstring file);

private:
	static map<wstring, vector<Material *>> materialMap;

	struct MeshData
	{
		vector<class ModelBone *> Bones;
		vector<class ModelMesh *> Meshes;
	};
	static map<wstring, MeshData> meshDataMap;
};