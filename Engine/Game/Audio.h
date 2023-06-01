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

		// SourceVoice
		IXAudio2SourceVoice* pSourceVoice_ = nullptr;

	private:
		
		// 静的オーディオ格納用vector配列
		static std::vector<std::unique_ptr<Audio>> audios_;

	public:
		
		/// <summary>
		/// オーディオ読み込み(.wavのみ)
		/// </summary>
		/// <param name="audioFileName"> : 音声ファイル名</param>
		/// <returns>オーディオポインタ</returns>
		static Audio* Load(const std::string& audioFileName);

		/// <summary>
		/// オーディオ読み込み(.wavのみ)
		/// </summary>		
		/// <param name="directoryPath"> : ディレクトリパス名</param>
		/// <param name="audioFileName"> : 音声ファイル名</param>
		/// <returns></returns>
		static Audio* Load(const std::string& directoryPath, const std::string& audioFileName);

		/// <summary>
		/// 全削除
		/// </summary>
		static void AllClear();

	private:

		/// <summary>
		/// ヘッダー捜索
		/// </summary>
		static void SearchHeader(std::ifstream& file, const char* chunkId);

	public:

		/// <summary>
		/// オーディオ再生
		/// </summary>
		/// <param name="isLoop"> : ループするか</param>
		void Play(const bool isLoop);

		/// <summary>
		/// ボリューム設定
		/// </summary>
		/// <param name="volume"> : 音量</param>
		void SetVolume(const float volume);

		/// <summary>
		/// オーディオ停止
		/// </summary>
		void Stop();

	public:

		// ベースクラス
		class Base
		{
		public:

			// XAudio2エンジン
			static Microsoft::WRL::ComPtr<IXAudio2> sXAudio2_;

			// マスターボイス
			static IXAudio2MasteringVoice* sMasterVoice_;

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
