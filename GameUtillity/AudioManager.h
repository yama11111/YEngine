#pragma once
#include <xaudio2.h>
#include <wrl.h>
#include <vector>

#pragma comment(lib, "xaudio2.lib")

namespace YGame
{
	// オーディオマネージャークラス
	class AudioManager
	{
	private:
		// チャンクヘッダ
		struct ChunkHeader 
		{
			char id_[4]; // チャンクごとのid
			int32_t size_; // チャンクサイズ
		};
		// RIFFヘッダチャンク
		struct RiffHeader
		{
			ChunkHeader chunk_; // "RIFF"
			char type_[4]; // "WAVE"
		};
		// FMIチャンク
		struct FormatChunk
		{
			ChunkHeader chunk_; // "fmt"
			WAVEFORMATEX fmt_; // 波形フォーマット
		};
		// 音声データ
		struct SoundData 
		{
			// 波形フォーマット
			WAVEFORMATEX wfex_;
			// バッファの先頭アドレス
			BYTE* pBuff_; 
			// バッファサイズ
			unsigned int buffSize_;
		};
	private:
		// XAudio2エンジン
		Microsoft::WRL::ComPtr<IXAudio2> xAudio2_;
		// マスターボイス
		IXAudio2MasteringVoice* masterVoice_ = nullptr;
		// オーディオ用vector配列
		std::vector<SoundData> audios_;
	public:
		// 初期化
		void Initialize();
		/// <summary>
		/// オーディオ読み込み(.wavのみ)
		/// </summary>
		/// <param name="fileName"> : ファイル名</param>
		/// <returns>オーディオ番号</returns>
		UINT Load(const char* fileName);
		////
		//UINT Load(const wchar_t* fileName);
		/// <summary>
		/// オーディオ再生
		/// </summary>
		/// <param name="audioIndex"> : オーディオ番号</param>
		void Play(const UINT audioIndex);
	public:
		// インスタンス取得
		static AudioManager* GetInstance();
	private:
		AudioManager() = default;
		~AudioManager();
		AudioManager(const AudioManager&) = delete;
		const AudioManager& operator=(const AudioManager&) = delete;
	};
}
