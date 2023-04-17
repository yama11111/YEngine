#include "Audio.h"
#include "YAssert.h"
#include <fstream>

#pragma region ���O���

using std::unique_ptr;
using YGame::Audio;
using YDX::Result;

#pragma endregion

#pragma region Static

std::vector<unique_ptr<Audio>> Audio::audios_{};
Audio::Common Audio::common_{};
Microsoft::WRL::ComPtr<IXAudio2> Audio::Common::xAudio2_{};
IXAudio2MasteringVoice* Audio::Common::masterVoice_ = nullptr;

#pragma endregion

void Audio::Common::StaticInitialize()
{
	// XAudio2�̃C���X�^���X����
	Result(XAudio2Create(&xAudio2_, 0, XAUDIO2_DEFAULT_PROCESSOR));

	// �}�X�^�[�{�C�X����
	Result(xAudio2_->CreateMasteringVoice(&masterVoice_));
}

Audio* Audio::Load(const std::string& fileName)
{
	// �ǂݍ��񂾂��Ƃ����邩�`�F�b�N
	for (size_t i = 0; i < audios_.size(); i++)
	{
		// �t�@�C���p�X �������Ȃ�
		if (fileName == audios_[i]->fileName_)
		{
			// ���̃e�N�X�`���|�C���^��Ԃ�
			return audios_[i].get();
		}
	}

	// �e�N�X�`������
	unique_ptr<Audio> newAudio = std::make_unique<Audio>();

	// �t�@�C�����̓X�g���[���̃C���X�^���X
	std::ifstream file;
	// .wav�t�@�C�����o�C�i�����[�h�ŊJ��
	file.open(fileName, std::ios_base::binary);
	// �t�@�C���I�[�v�����s�����o
	assert(file.is_open());

	// RIFF�w�b�_�|�̓ǂݍ���
	RiffHeader riff;
	file.read((char*)&riff, sizeof(riff));
	// �t�@�C����RIFF���`�F�b�N
	assert(strncmp(riff.chunk_.id_, "RIFF", 4) == 0);
	// �t�@�C����WAVE���`�F�b�N
	assert(strncmp(riff.type_, "WAVE", 4) == 0);

	// Format�`�����N�̓ǂݍ���
	FormatChunk format = {};
	// �`�����N�w�b�_�[�̊m�F
	file.read((char*)&format, sizeof(ChunkHeader));
	assert(strncmp(format.chunk_.id_, "fmt ", 4) == 0);
	// �`�����N�{�̂̓ǂݍ���
	assert(format.chunk_.size_ <= sizeof(format.fmt_));
	file.read((char*)&format.fmt_, format.chunk_.size_);

	// Data�`�����N�̓ǂݍ���
	ChunkHeader data;
	file.read((char*)&data, sizeof(data));
	// JUNK�`�����N�����o�����ꍇ
	if (strncmp(data.id_, "JUNK", 4) == 0)
	{
		// �ǂݎ��ʒu��JUMK�`�����N�̏I���܂Ői�߂�
		file.seekg(data.size_, std::ios_base::cur);
		// �t�@�C���ēǂݍ���
		file.read((char*)&data, sizeof(data));
	}
	assert(strncmp(data.id_, "data", 4) == 0);
	// Data�`�����N�̃f�[�^��(�g�`�f�[�^)�̓ǂݍ���
	char* pBuff = new char[data.size_];
	file.read(pBuff, data.size_);

	// �t�@�C�������
	file.close();

	// �T�E���h�f�[�^
	SoundData sound = {};
	sound.wfex_ = format.fmt_;
	sound.pBuff_ = reinterpret_cast<BYTE*>(pBuff);
	sound.buffSize_ = data.size_;

	// ���
	newAudio->sound_ = sound;


	// �|�C���^���擾
	Audio* newAudioPtr = newAudio.get();

	// �T�E���h�f�[�^��ۑ�
	audios_.push_back(std::move(newAudio));

	// �I�[�f�B�I�|�C���^��Ԃ�
	return newAudioPtr;
}

void Audio::Play()
{
	// �g�`�t�H�[�}�b�g������SourceVoice����
	IXAudio2SourceVoice* pSourceVoice = nullptr;
	Result(common_.xAudio2_->CreateSourceVoice(&pSourceVoice, &sound_.wfex_));

	// �Đ�����g�`�f�[�^�̐ݒ�
	XAUDIO2_BUFFER buff{};
	buff.pAudioData = sound_.pBuff_;
	buff.AudioBytes = sound_.buffSize_;
	buff.Flags = XAUDIO2_END_OF_STREAM;

	// �g�`�f�[�^�̍Đ�
	Result(pSourceVoice->SubmitSourceBuffer(&buff));
	Result(pSourceVoice->Start());
}

void Audio::AllClear()
{
	// �I�[�f�B�I�S����
	for (size_t i = 0; i < audios_.size(); i++)
	{
		delete[] audios_[i]->sound_.pBuff_;
		audios_[i].reset(nullptr);
	}
	audios_.clear();
}

Audio::Common::~Common()
{
	xAudio2_.Reset();
}
