#pragma once
#include "Sound.h"
#include "../Actor/ID.h"
#include <map>
class Audio{
public:
	Audio();
	~Audio();
	static Audio &GetInstance(){
		static Audio d;
		return d;
	}
	//�a�f�l�����[�h
	void LoadBGM(BGM_ID id, TCHAR* FileName);
	//�r�d�����[�h(bufferCount �����Đ���������)
	void LoadSE(SE_ID id, TCHAR* FileName, int bufferCount);

	//�a�f�l�Đ�
	void PlayBGM(BGM_ID id, bool loop = false);
	//�r�d�Đ�
	void PlaySE(SE_ID id, bool loop = false);

	//�a�f�l��~
	void StopBGM(BGM_ID id);
	//�r�d��~
	void StopSE(SE_ID id);

	void StopAllSE(bool reset = true);

	void SetPlaySpeedBGM(BGM_ID id, float speed);

	void SetPlaySpeedSE(SE_ID id, float speed);

	//�a�f�l�{�����[���Z�b�g
	void SetAllBGMVolume(int volume);
	//�r�d�{�����[���Z�b�g
	void SetAllSEVolume(int volume);

	//�a�f�l�{�����[���Z�b�g
	void SetBGMVolume(BGM_ID id,int volume);
	//�r�d�{�����[���Z�b�g
	void SetSEVolume(SE_ID id,int volume);

	float ReturnVolume(SE_ID id);

private:
	std::map<BGM_ID, Sound> bgm;
	std::map<SE_ID, Sound> se;
	std::vector<BGM_ID> bgmId;
	std::vector<SE_ID> seId;
};