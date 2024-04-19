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

public:
	/// <summary>
	/// メンバ関数
	/// </summary>

	// コンストラクタ
	Grid() {};
	// デストラクタ
	~Grid() {}

	// グリッド線を表示する関数
	/*void DrawGid(
		const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, const Vec3f& startPos, const Vec3f& endPos);*/

	void DrawGridLine(const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, const Vec3f& startPos, const Vec3f& endPos);
	void DrawGrid(const Matrix4x4& viewMatrix, const Matrix4x4& projectionMatrix, const Matrix4x4& viewportMatrix);
};