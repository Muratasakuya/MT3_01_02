﻿#include "Grid.h"

/// <summary>
/// 縦横のグリッド線を描画する関数
/// </summary>
/// <param name="viewMatrix"></param>
/// <param name="projectionMatrix"></param>
/// <param name="viewportMatrix"></param>
void Grid::DrawGrid(const Matrix4x4& viewMatrix, const Matrix4x4& projectionMatrix, const Matrix4x4& viewportMatrix) {

	const float kGridHalfWidth = 2.0f;
	const uint32_t kSubdivision = 10;
	const float kGridEvery = (kGridHalfWidth * 2.0f) / float(kSubdivision);

	/****************************************************************************************************************************/
	// 縦線の描画

	for (uint32_t xIndex = 0; xIndex <= kSubdivision; xIndex++) {
		
		// グリッドの幅を均等に分割した位置を計算
		float xWorldPos = -kGridHalfWidth + xIndex * kGridEvery;

		// 始点と終点のワールド座標を設定
		Vec3f worldStartPos(xWorldPos, 0.0f, kGridHalfWidth);
		Vec3f worldEndPos(xWorldPos, 0.0f, -kGridHalfWidth);

		Vec3f ndcStartPos = Transform(worldStartPos, Multiply(viewMatrix, projectionMatrix));
		Vec3f ndcEndPos = Transform(worldEndPos, Multiply(viewMatrix, projectionMatrix));

		// 座標変換
		Vec3f screenStartPos = Transform(ndcStartPos, viewportMatrix);
		Vec3f screenEndPos = Transform(ndcEndPos, viewportMatrix);

		// xIndexの値が6(真ん中の値)のとき黒で描画しその他は灰色で描画する
		bool isCenterLengthGrid = (xIndex == kSubdivision / 2);
		uint32_t gridColor = isCenterLengthGrid ? 0x000000ff : 0xaaaaaaff;

		// 線を描画
		Novice::DrawLine(
			static_cast<int>(screenStartPos.x), static_cast<int>(screenStartPos.y),
			static_cast<int>(screenEndPos.x), static_cast<int>(screenEndPos.y),
			gridColor
		);
	}

	/****************************************************************************************************************************/
	// 横線の描画

	for (uint32_t zIndex = 0; zIndex <= kSubdivision; zIndex++) {
		// グリッドの幅を均等に分割した位置を計算
		float zWorldPos = -kGridHalfWidth + zIndex * kGridEvery;

		// 始点と終点のワールド座標を設定
		Vec3f worldStartPos(-kGridHalfWidth, 0.0f, zWorldPos);
		Vec3f worldEndPos(kGridHalfWidth, 0.0f, zWorldPos);

		Vec3f ndcStartPos = Transform(worldStartPos, Multiply(viewMatrix, projectionMatrix));
		Vec3f ndcEndPos = Transform(worldEndPos, Multiply(viewMatrix, projectionMatrix));

		// 座標変換
		Vec3f screenStartPos = Transform(ndcStartPos, viewportMatrix);
		Vec3f screenEndPos = Transform(ndcEndPos, viewportMatrix);

		// zIndexの値が6(真ん中の値)のとき黒で描画しその他は灰色で描画する
		bool isCenterLengthGrid = (zIndex == kSubdivision / 2);
		uint32_t gridColor = isCenterLengthGrid ? 0x000000ff : 0xaaaaaaff;

		// 線を描画
		Novice::DrawLine(
			static_cast<int>(screenStartPos.x), static_cast<int>(screenStartPos.y),
			static_cast<int>(screenEndPos.x), static_cast<int>(screenEndPos.y),
			gridColor
		);
	}
}