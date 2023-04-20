#pragma once
#include <xaudio2.h>
#include <wrl.h>
#include <vector>
#include <string>
#include <memory>

#pragma comment(lib, "xaudio2.lib")

namespace YGame
{
	// オーディオクラス
	class Audio
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

		// 音声データ
		SoundData sound_{};

		// テクスチャファイル名
		std::string fileName_;

	private:
		
		// 静的オーディオ格納用vector配列
		static std::vector<std::unique_ptr<Audio>> audios_;

	public:
		
		/// <summary>
		/// オーディオ読み込み(.wavのみ)
		/// </summary>
		/// <param name="fileName"> : ファイル名</param>
		/// <returns>オーディオポインタ</returns>
		static Audio* Load(const std::string& fileName);

		/// <summary>
		/// 全削除
		/// </summary>
		static void AllClear();

	public:
		
		/// <summary>
		/// オーディオ再生
		/// </summary>
		void Play();

	public:

		// 基礎クラス
		class Base
		{

		public:

			// XAudio2エンジン
			static Microsoft::WRL::ComPtr<IXAudio2> xAudio2_;

			// マスターボイス
			static IXAudio2MasteringVoice* masterVoice_;

		public:

			/// <summary>
			/// 静的初期化
			/// </summary>
			static void StaticInitialize();

		public:

			Base() = default;

			~Base();
		};

	public:
		
		Audio() = default;

		~Audio() = default;
	};
}
