#include "Audio.h"

Audio::Audio(){
}

Audio::~Audio(){

}

//�a�f�l�����[�h
void Audio::LoadBGM(BGM_ID id, TCHAR* FileName){
	bgm[id].Load(FileName, 1);
	bgmId.push_back(id);
}
//�r�d�����[�h(bufferCount �����Đ���������)
void Audio::LoadSE(SE_ID id, TCHAR* FileName, int bufferCount){
	se[id].Load(FileName, bufferCount);
	seId.push_back(id);
}

//�a�f�l�Đ�
void Audio::PlayBGM(BGM_ID id, bool loop){
	bgm[id].Play(loop);
}
//�r�d�Đ�
void Audio::PlaySE(SE_ID id, bool loop){
	se[id].Play(loop);
}

//�a�f�l��~
void Audio::StopBGM(BGM_ID id){
	bgm[id].Stop();
}
//�r�d��~
void Audio::StopSE(SE_ID id){
	se[id].Stop();
}

void Audio::StopAllSE(bool reset){
	for (auto& i : se){
		i.second.Stop(reset);
	}
}

void Audio::SetPlaySpeedBGM(BGM_ID id, float speed){
	bgm[id].SetPlaySpeed(speed);
}

void Audio::SetPlaySpeedSE(SE_ID id, float speed){
	se[id].SetPlaySpeed(speed);
}

//�a�f�l�{�����[���Z�b�g
void Audio::SetAllBGMVolume(int volume){
	for (auto& i : bgmId){
		bgm[i].SetVolume(volume);
	}
}
//�r�d�{�����[���Z�b�g
void Audio::SetAllSEVolume(int volume){
	for (auto& i : seId){
		se[i].SetVolume(volume);
	}
}

//�a�f�l�{�����[���Z�b�g
void Audio::SetBGMVolume(BGM_ID id, int volume){
	bgm[id].SetVolume(volume);
}
//�r�d�{�����[���Z�b�g
void Audio::SetSEVolume(SE_ID id, int volume){
	se[id].SetVolume(volume);
}

float Audio::ReturnVolume(SE_ID id){
	return (se[id].ReturnVolume() + 10000.0f) / 100.0f;
}