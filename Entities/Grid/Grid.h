#pragma once
#include "MyMath.h"

/// <summary>
/// グリッド線クラス
/// </summary>
class Grid {
private:
	/// <summary>
	/// メンバ変数
	/// </summary>
	
	/// <summary>
	/// 始点の構造体
	/// </summary>
	struct StartPoint{

		Matrix4x4 worldMatrix_;
		Matrix4x4 worldViewProjectionMatrix_;

		Vec3f localPos_;
		Vec3f screenPos_;
	};

	StartPoint startPoint_[11]{};

	/// <summary>
	/// 終点の構造体
	/// </summary>
	struct EndPoint{

		Matrix4x4 worldMatrix_;
		Matrix4x4 worldViewProjectionMatrix_;

		Vec3f localPos_;
		Vec3f screenPos_;
	};

	EndPoint endPoint_[11]{};

	Vec3f ndcPos_{};

	uint32_t gridColor_[2];
	bool isCenterLengthGrid_;
	bool isCenterWidthGrid_;
public:
	/// <summary>
	/// メンバ関数
	/// </summary>

	// コンストラクタ
	Grid() {};
	// デストラクタ
	~Grid() {}

	// グリッド線を表示する関数
	void DrawGid(
		const Matrix4x4& viewMatrix,const Matrix4x4& projectionMatrix, const Matrix4x4& viewportMatrix);
};