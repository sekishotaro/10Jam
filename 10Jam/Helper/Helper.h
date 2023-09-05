#pragma once
#include "Camera.h"
#include "WinApp.h"
/*--�~���Ƃ����߂�p--*/
#define PI 3.14f
#define PI_90 90.00f
#define PI_180 180.00f
#define PI_360 360.00f
/*-----------------*/

//�⏕�N���X
class Helper
{
private:
	// DirectX::���ȗ�
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMVECTOR = DirectX::XMVECTOR;
	using XMMATRIX = DirectX::XMMATRIX;

public:
	static Helper* GetInstance();
	void SetCamera(Camera* camera) {
		m_Camera = camera;
	}
	//Clamp��Ԃ��֐�
	template<typename T>
	//�v�Z�n
	bool CheckMax(T& Num, const T Max, const T Add);
	//Clamp��Ԃ��֐�
	template<typename T>
	bool CheckMin(T& Num, const T Min, const T Add);
	bool FrameCheck(float& frame, const float addframe);
	//Clamp��Ԃ��֐�
	template<typename T>
	void Clamp(T& Num, const T Min, const T Max);
	//XMFLOAT3��float�����Z����֐�
	XMFLOAT3 Float3AddFloat(const XMFLOAT3& Num, const float Add);
	//XMFLOAT3��XMFLOAT3�����Z����֐�
	XMFLOAT3 Float3AddFloat3(const XMFLOAT3& Num, const XMFLOAT3& Add);
	//XMFLOAT3��float�����Z����֐�
	XMFLOAT3 Float3SubFloat(const XMFLOAT3& Num, const float Sub);
	//XMFLOAT3��XMFLOAT3�����Z����֐�
	XMFLOAT3 Float3SubFloat3(const XMFLOAT3& Num, const XMFLOAT3& Sub);

	//�Ǐ]�֐�
	void FollowMove(XMFLOAT3& pos, const XMFLOAT3& pos2, const float vel);
	//�����𑪂�
	float ChechLength(const XMFLOAT3& pos, const XMFLOAT3& pos2);
	//�~�^��
	XMFLOAT3 CircleMove(const XMFLOAT3& basepos, const float scale, const float speed);
	//if���̔���̊֐�(�l���͈͊O�ɂ��邩)
	bool CheckNotValueRange(float& Num, const float Min, const float Max);
	//�t�ɔ͈͓��ɂ��邩
	bool CheckValueRange(float& Num, const float Min, const float Max);
public:
	//������Ԃ�
	float GetPercent(const float amount, const float num);

	//2D->3D�ϊ��Ɏg��(�X�v���C�g�̍��W���v���C���[�̃��[���h���W�ɕ\�������肷��̂Ɏg��)
	//���W�n�����m�łȂ��ꍇ->�s�񂩂�v�Z->W���Z
	XMVECTOR WDivision(const XMVECTOR& pos, const XMMATRIX& mat, const bool sub);
	//���W�n�����m�ȏꍇ->���̂܂܌v�Z->W���Z
	XMVECTOR WDivision(const XMVECTOR& pos, const bool sub);
	//���[���h���W�ɕϊ�
	XMVECTOR PosDivi(const XMVECTOR& pos, const XMMATRIX& mat, const bool sub);
	//���W�ϊ�
	XMVECTOR WorldDivision(const XMVECTOR& pos, const bool sub);
	//3D���W��2D�ɕς���(���e�B�N���Ȃǂ̓����蔻��ȂǂɎg��
	XMFLOAT2 WorldtoScreen(const XMVECTOR& pos, const XMMATRIX& mat);
	//XMFLOAT��XMVECTOR�ɕϊ�����
	XMVECTOR ChangeFLOAT(const XMFLOAT3& pos);
	//XMFLOAT��XMVECTOR�ɕϊ�����
	XMFLOAT3 ChangeVECTOR(const XMVECTOR& pos);
	void ChangeViewPort(XMMATRIX& matviewport, const XMVECTOR& offset);

	float DirRotation(const XMFLOAT3& target, const XMFLOAT3& base,float margin);
	//�z��̒��g���S��true��
	bool All_Of(bool* flag, int size);
	bool All_OfF(bool* flag, int size);
	bool All_Of_float(float *list,int size,float standVal);
private:

	//�J����
	Camera* m_Camera;

};


namespace Easing
{
	inline int EaseIn(int t)
	{
		return t * t;
	}

	inline float EaseOut(float t, float start, float end)
	{
		return (end - start) * (1.0f - cosf(t * PI / 2.0f)) + start;
	}

	inline float EaseInOut(int& t);
	inline float EaseOutIn(int& t);
}

template<typename T>
inline void Helper::Clamp(T& Num, const T Min, const T Max) {
	Num = min(max(Num, Min), Max);
}

//float�^
//max min��bool���ŕԂ�
template<typename T>
inline bool Helper::CheckMax(T& Num, const T Max, const T Add) {
	Num += Add;

	Num = max(Num, Max);


	if (Num <= Max) {
		return true;
	}
	else {
		return false;
	}

	return false;
}
//Min������
template<typename T>
inline bool Helper::CheckMin(T& Num, const T Min, const T Add) {
	Num += Add;
	Num = min(Num, Min);

	if (Num >= Min) {
		return true;
	}
	else {
		return false;
	}

	return false;
}
