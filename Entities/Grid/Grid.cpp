#include "Grid.h"

/// <summary>
/// グリッド線を表示する関数、縦横11本ずつ
/// </summary>
void Grid::DrawGid(
	const Matrix4x4& viewMatrix, const Matrix4x4& projectionMatrix, const Matrix4x4& viewportMatrix) {

	// 半分の幅
	const float kGridHalfWidth_ = 2.0f;
	// 分割数
	const uint32_t kSubdivision_ = 10;
	// 1つ文の長さ
	const float kGirdEvery_ = (kGridHalfWidth_ * 2.0f) / static_cast<float>(kSubdivision_);

	// 奥から手前への線を順々に引いていく
	for (uint32_t xIndex = 0; xIndex <= kSubdivision_; xIndex++) {

		// 上の情報を使って始点と終点のワールド座標系を求める
		// 始点の設定
		startPoint_[xIndex].localPos_.x = static_cast<int>(xIndex - kSubdivision_ / 2) * kGirdEvery_;
		startPoint_[xIndex].localPos_.y = 0.0f;
		startPoint_[xIndex].localPos_.z = kGridHalfWidth_;
		// 終点の設定
		endPoint_[xIndex].localPos_.x = static_cast<int>(xIndex - kSubdivision_ / 2) * kGirdEvery_;
		endPoint_[xIndex].localPos_.y = 0.0f;
		endPoint_[xIndex].localPos_.z = -kGridHalfWidth_;

		// xIndexの値が6(真ん中の値)のとき黒で描画しその他は灰色で描画する
		isCenterLengthGrid_ = (xIndex == kSubdivision_ / 2);
		gridColor_[0] = isCenterLengthGrid_ ? 0x000000ff : 0xaaaaaaff;

		/****************************************************************************************************************************/
		// スクリーン座標系まで変換する
		// 始点の変換
		startPoint_[xIndex].worldMatrix_ =
			MakeAffineMatrix({ 1.0f,1.0f,1.0f }, { 0.0f,0.0f,0.0f }, startPoint_[xIndex].localPos_);

		startPoint_[xIndex].worldViewProjectionMatrix_ =
			Multiply(startPoint_[xIndex].worldMatrix_, Multiply(viewMatrix, projectionMatrix));

		ndcPos_ =
			Transform(startPoint_[xIndex].localPos_, startPoint_[xIndex].worldViewProjectionMatrix_);
		startPoint_[xIndex].screenPos_ =
			Transform(ndcPos_, viewportMatrix);

		/****************************************************************************************************************************/
		// 終点の変換
		endPoint_[xIndex].worldMatrix_ =
			MakeAffineMatrix({ 1.0f,1.0f,1.0f }, { 0.0f,0.0f,0.0f }, endPoint_[xIndex].localPos_);

		endPoint_[xIndex].worldViewProjectionMatrix_ =
			Multiply(endPoint_[xIndex].worldMatrix_, Multiply(viewMatrix, projectionMatrix));

		ndcPos_ =
			Transform(endPoint_[xIndex].localPos_, endPoint_[xIndex].worldViewProjectionMatrix_);
		endPoint_[xIndex].screenPos_ =
			Transform(ndcPos_, viewportMatrix);

		// 変換した座標を使って表示
		// 色は薄い灰色(0xaaaaaaff)、原点は黒くらいが良い
		Novice::DrawLine(
			static_cast<int>(startPoint_[xIndex].screenPos_.x), static_cast<int>(startPoint_[xIndex].screenPos_.y),
			static_cast<int>(endPoint_[xIndex].screenPos_.x), static_cast<int>(endPoint_[xIndex].screenPos_.y),
			gridColor_[0]
		);
	}

	// 左から右への線を順々に引いていく
	for (uint32_t zIndex = 0; zIndex <= kSubdivision_; zIndex++) {

		// 上の情報を使って始点と終点のワールド座標系を求める
		// 始点の設定
		startPoint_[zIndex].localPos_.x = kGridHalfWidth_;
		startPoint_[zIndex].localPos_.y = 0.0f;
		startPoint_[zIndex].localPos_.z = static_cast<int>(zIndex - kSubdivision_ / 2) * kGirdEvery_;
		// 終点の設定
		endPoint_[zIndex].localPos_.x = -kGridHalfWidth_;
		endPoint_[zIndex].localPos_.y = 0.0f;
		endPoint_[zIndex].localPos_.z = static_cast<int>(zIndex - kSubdivision_ / 2) * kGirdEvery_;

		// zIndexの値が6(真ん中の値)のとき黒で描画しその他は灰色で描画する
		isCenterWidthGrid_ = (zIndex == kSubdivision_ / 2);
		gridColor_[1] = isCenterWidthGrid_ ? 0x000000ff : 0xaaaaaaff;

		/****************************************************************************************************************************/
		// スクリーン座標系まで変換する
		// 始点の変換
		startPoint_[zIndex].worldMatrix_ =
			MakeAffineMatrix({ 1.0f,1.0f,1.0f }, { 0.0f,0.0f,0.0f }, startPoint_[zIndex].localPos_);

		startPoint_[zIndex].worldViewProjectionMatrix_ =
			Multiply(startPoint_[zIndex].worldMatrix_, Multiply(viewMatrix, projectionMatrix));

		ndcPos_ =
			Transform(startPoint_[zIndex].localPos_, startPoint_[zIndex].worldViewProjectionMatrix_);
		startPoint_[zIndex].screenPos_ =
			Transform(ndcPos_, viewportMatrix);

		/****************************************************************************************************************************/
		// 終点の変換
		endPoint_[zIndex].worldMatrix_ =
			MakeAffineMatrix({ 1.0f,1.0f,1.0f }, { 0.0f,0.0f,0.0f }, endPoint_[zIndex].localPos_);

		endPoint_[zIndex].worldViewProjectionMatrix_ =
			Multiply(endPoint_[zIndex].worldMatrix_, Multiply(viewMatrix, projectionMatrix));

		ndcPos_ =
			Transform(endPoint_[zIndex].localPos_, endPoint_[zIndex].worldViewProjectionMatrix_);
		endPoint_[zIndex].screenPos_ =
			Transform(ndcPos_, viewportMatrix);

		// 変換した座標を使って表示
		// 色は薄い灰色(0xaaaaaaff)、原点は黒くらいが良い
		Novice::DrawLine(
			static_cast<int>(startPoint_[zIndex].screenPos_.x), static_cast<int>(startPoint_[zIndex].screenPos_.y),
			static_cast<int>(endPoint_[zIndex].screenPos_.x), static_cast<int>(endPoint_[zIndex].screenPos_.y),
			gridColor_[1]
		);
	}
}