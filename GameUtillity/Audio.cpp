#include "Audio.h"
#include "YAssert.h"
#include <fstream>

#pragma region 名前空間

using std::unique_ptr;
using YGame::Audio;
using YDX::Result;

#pragma endregion

#pragma region Static

std::vector<unique_ptr<Audio>> Audio::audios_{};
Microsoft::WRL::ComPtr<IXAudio2> Audio::Base::xAudio2_{};
IXAudio2MasteringVoice* Audio::Base::masterVoice_ = nullptr;

#pragma endregion

void Audio::Base::StaticInitialize()
{
	// XAudio2のインスタンス生成
	Result(XAudio2Create(&xAudio2_, 0, XAUDIO2_DEFAULT_PROCESSOR));

	// マスターボイス生成
	Result(xAudio2_->CreateMasteringVoice(&masterVoice_));
}

Audio* Audio::Load(const std::string& fileName)
{
	// 読み込んだことがあるかチェック
	for (size_t i = 0; i < audios_.size(); i++)
	{
		// ファイルパス が同じなら
		if (fileName == audios_[i]->fileName_)
		{
			// そのテクスチャポインタを返す
			return audios_[i].get();
		}
	}

	// テクスチャ生成
	unique_ptr<Audio> newAudio = std::make_unique<Audio>();

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

	// 代入
	newAudio->sound_ = sound;


	// ポインタを取得
	Audio* newAudioPtr = newAudio.get();

	// サウンドデータを保存
	audios_.push_back(std::move(newAudio));

	// オーディオポインタを返す
	return newAudioPtr;
}

void Audio::Play()
{
	// 波形フォーマットを元にSourceVoice生成
	IXAudio2SourceVoice* pSourceVoice = nullptr;
	Result(Base::xAudio2_->CreateSourceVoice(&pSourceVoice, &sound_.wfex_));

	// 再生する波形データの設定
	XAUDIO2_BUFFER buff{};
	buff.pAudioData = sound_.pBuff_;
	buff.AudioBytes = sound_.buffSize_;
	buff.Flags = XAUDIO2_END_OF_STREAM;

	// 波形データの再生
	Result(pSourceVoice->SubmitSourceBuffer(&buff));
	Result(pSourceVoice->Start());
}

void Audio::AllClear()
{
	// オーディオ全消去
	for (size_t i = 0; i < audios_.size(); i++)
	{
		delete[] audios_[i]->sound_.pBuff_;
		audios_[i].reset(nullptr);
	}
	audios_.clear();
}

Audio::Base::~Base()
{
	xAudio2_.Reset();
}
