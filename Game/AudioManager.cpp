#include "AudioManager.h"
#include "YAssert.h"
#include <fstream>

using Game::AudioManager;
using DX::Result;

AudioManager::~AudioManager()
{
	xAudio2_.Reset();
	if (!audios_.empty())
	{
		for (size_t i = 0; i < audios_.size(); i++)
		{
			delete[] audios_[i].pBuff_;
		}
	}
}

void AudioManager::Initialize()
{
	// XAudio2のインスタンス生成
	Result(XAudio2Create(&xAudio2_, 0, XAUDIO2_DEFAULT_PROCESSOR));

	// マスターボイス生成
	Result(xAudio2_->CreateMasteringVoice(&masterVoice_));
}

UINT AudioManager::Load(const char* fileName)
{
	// ファイル入力ストリームのインスタンス
	std::ifstream file;
	// .wavファイルをバイナリモードで開く
	file.open(fileName, std::ios_base::binary);
	// ファイルオープン失敗を検出
	assert(file.is_open());

	// RIFFヘッダ－の読み込み
	RiffHeader riff;
	file.read((char*)&riff, sizeof(riff));
	// ファイルがRIFFかチェック
	assert(strncmp(riff.chunk_.id_, "RIFF", 4) == 0);
	// ファイルがWAVEかチェック
	assert(strncmp(riff.type_, "WAVE", 4) == 0);

	// Formatチャンクの読み込み
	FormatChunk format = {};
	// チャンクヘッダーの確認
	file.read((char*)&format, sizeof(ChunkHeader));
	assert(strncmp(format.chunk_.id_, "fmt ", 4) == 0);
	// チャンク本体の読み込み
	assert(format.chunk_.size_ <= sizeof(format.fmt_));
	file.read((char*)&format.fmt_, format.chunk_.size_);

	// Dataチャンクの読み込み
	ChunkHeader data;
	file.read((char*)&data, sizeof(data));
	// JUNKチャンクを検出した場合
	if (strncmp(data.id_, "JUNK", 4) == 0)
	{
		// 読み取り位置をJUMKチャンクの終わりまで進める
		file.seekg(data.size_, std::ios_base::cur);
		// ファイル再読み込み
		file.read((char*)&data, sizeof(data));
	}
	assert(strncmp(data.id_, "data", 4) == 0);
	// Dataチャンクのデータ部(波形データ)の読み込み
	char* pBuff = new char[data.size_];
	file.read(pBuff, data.size_);

	// ファイルを閉じる
	file.close();

	// サウンドデータ
	SoundData sound = {};
	sound.wfex_ = format.fmt_;
	sound.pBuff_ = reinterpret_cast<BYTE*>(pBuff);
	sound.buffSize_ = data.size_;

	// サウンドデータを保存
	audios_.push_back(sound);

	return static_cast<UINT>(audios_.size() - 1);
}


//UINT AudioManager::Load(wchar_t* fileName)
//{
//	// ファイル操作
//	HMMIO mmio;
//	MMIOINFO info;
//	mmio = mmioOpen(fileName, &info, MMIO_READ);
//	assert(mmio);
//
//	// RIFF 読み込み
//	MMCKINFO riffChunk;
//	riffChunk.fccType = mmioFOURCC('W', 'A', 'V', 'E');
//	assert(mmioDescend(mmio, &riffChunk, nullptr, MMIO_FINDRIFF) == MMSYSERR_NOERROR);
//
//	// fmt 読み込み
//	MMCKINFO chunk;
//	chunk.ckid = mmioFOURCC('f', 'm', 't', ' ');
//	assert(mmioDescend(mmio, &chunk, &riffChunk, MMIO_FINDCHUNK) == MMSYSERR_NOERROR);
//
//	WAVEFORMATEX format;
//	assert(mmioRead(mmio, (HPSTR)&format, chunk.cksize) == chunk.cksize);
//
//	// data 読み込み
//	chunk.ckid = mmioFOURCC('d', 'a', 't', 'a');
//	assert(mmioDescend(mmio, &chunk, &riffChunk, MMIO_FINDCHUNK) == MMSYSERR_NOERROR);
//
//	return 0;
//}


void AudioManager::Play(const UINT audioIndex)
{
	// 波形フォーマットを元にSourceVoice生成
	IXAudio2SourceVoice* pSourceVoice = nullptr;
	Result(xAudio2_->CreateSourceVoice(&pSourceVoice, &audios_[audioIndex].wfex_));

	// 再生する波形データの設定
	XAUDIO2_BUFFER buff{};
	buff.pAudioData = audios_[audioIndex].pBuff_;
	buff.AudioBytes = audios_[audioIndex].buffSize_;
	buff.Flags = XAUDIO2_END_OF_STREAM;

	// 波形データの再生
	Result(pSourceVoice->SubmitSourceBuffer(&buff));
	Result(pSourceVoice->Start());
}
