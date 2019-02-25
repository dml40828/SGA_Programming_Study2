#include "Framework.h"
#include "ModelClip.h"

#include "../Utilities/BinaryFile.h"
#include "ModelBone.h"

ModelClip::ModelClip(wstring file)
	:texture(NULL), repeat(true)
{
	clipName = String::ToString(Path::GetFileNameWithoutExtension(file));

	BinaryReader* r = new BinaryReader();
	r->Open(file);

	name = String::ToWString(r->String());
	duration = r->Float();
	frameRate = r->Float();
	frameCount = r->UInt();

	UINT keyframesCount = r->UInt();
	for (UINT i = 0; i < keyframesCount; i++)
	{
		ModelKeyframe* keyframe = new ModelKeyframe();
		keyframe->BoneName = String::ToWString(r->String());

		UINT size = r->UInt();
		if (size > 0)
		{
			keyframe->Transforms.assign(size, ModelKeyframeData());

			void* ptr = (void *)&keyframe->Transforms[0];
			r->Byte(&ptr, sizeof(ModelKeyframeData) * size);
		}

		keyframeMap[keyframe->BoneName] = keyframe;
	}

	r->Close();
	SAFE_DELETE(r);
}

ModelClip::~ModelClip()
{
	unordered_map<wstring, ModelKeyframe *>::iterator iter;
	for (iter = keyframeMap.begin(); iter != keyframeMap.end(); iter++)
		SAFE_DELETE(iter->second);

	SAFE_RELEASE(texture);
}

ModelKeyframe * ModelClip::Keyframe(wstring name)
{
	if (keyframeMap.count(name) < 1) 
		return NULL;

	return keyframeMap[name];
}
