#pragma once

namespace YBase
{
	class YFramework
	{
	protected:
		// �I���t���O
		bool isEnd_ = false;
	public:
		// ������
		virtual bool Initialize();
		// �I������
		virtual void Finalize();
		// �X�V
		virtual void Update();
		// �`��
		virtual void Draw() = 0;
		// �I���t���O�擾
		virtual bool IsEnd() { return isEnd_; }
	public:
		// ���s
		void Run();
	public:
		YFramework() = default;
		virtual ~YFramework() = default;
	};
}
