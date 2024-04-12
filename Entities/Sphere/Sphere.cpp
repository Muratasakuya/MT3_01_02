#include "Sphere.h"

/// <summary>
/// 球を描画する関数
/// </summary>
void Sphere::DrawSphere(
	const Matrix4x4& viewMatrix, const Matrix4x4& projectionMatrix, const Matrix4x4& viewportMatrix) {

	ImGui::Begin("Sphere");

	ImGui::SliderFloat3("translate", &center.localPos_.x, -10.0f, 10.0f);
	ImGui::SliderFloat("radius", &radius_, 0.0f, 10.0f);

	ImGui::End();

	// 分割数
	const uint32_t kSubdivision = 32;
	// 緯度分割1つ文の角度
	const float kLatEvery = Pi() / kSubdivision;
	// 経度分割1つ分の角度
	const float kLonEvery = 2.0f * Pi() / kSubdivision;

	// 緯度方向に分割 -π/2 ~ π/2
	for (uint32_t latIndex = 0; latIndex < kSubdivision; ++latIndex) {

		// 現在の緯度
		float lat = -Pi() / 2.0f + kLatEvery * latIndex;

		// 経度の方向に分割 0 ~ 2π
		for (uint32_t lonIndex = 0; lonIndex < kSubdivision; ++lonIndex) {

			// 現在の経度
			float lon = lonIndex * kLonEvery;

			// world座標系でのa、b、cを求める
			a.localPos_ =
			{ radius_ * std::cos(lat) * std::cos(lon),radius_ * std::sin(lat),radius_ * std::cos(lat) * std::sin(lon) };

			a.localPos_ += center.localPos_;

			b.localPos_ =
			{ radius_ * std::cos(lat + kLatEvery) * std::cos(lon),radius_ * std::sin(lat + kLatEvery),radius_ * std::cos(lat + kLatEvery) * std::sin(lon) };

			b.localPos_ += center.localPos_;

			c.localPos_ =
			{ radius_ * std::cos(lat) * std::cos(lon + kLonEvery),radius_ * std::sin(lat),radius_ * std::cos(lat) * std::sin(lon + kLonEvery) };

			c.localPos_ += center.localPos_;

			/****************************************************************************************************************************/
			// a、b、c、中心座標をスクリーン座標に変換
			// 中心座標の変換
			center.worldMatrix_ =
				MakeAffineMatrix({ 1.0f,1.0f,1.0f }, { 0.0f,0.0f,0.0f }, center.localPos_);
			center.worldViewProjectionMatrix_ =
				Multiply(center.worldMatrix_, Multiply(viewMatrix, projectionMatrix));
			ndcPos_ =
				Transform(center.localPos_, center.worldViewProjectionMatrix_);
			center.screenPos_ =
				Transform(ndcPos_, viewportMatrix);

			/****************************************************************************************************************************/
			// a地点の変換
			a.worldMatrix_ =
				MakeAffineMatrix({ 1.0f,1.0f,1.0f }, { 0.0f,0.0f,0.0f }, a.localPos_);
			a.worldViewProjectionMatrix_ =
				Multiply(a.worldMatrix_, Multiply(viewMatrix, projectionMatrix));
			ndcPos_ =
				Transform(a.localPos_, a.worldViewProjectionMatrix_);
			a.screenPos_ =
				Transform(ndcPos_, viewportMatrix);

			/****************************************************************************************************************************/
			// b地点の変換
			b.worldMatrix_ =
				MakeAffineMatrix({ 1.0f,1.0f,1.0f }, { 0.0f,0.0f,0.0f }, b.localPos_);
			b.worldViewProjectionMatrix_ =
				Multiply(b.worldMatrix_, Multiply(viewMatrix, projectionMatrix));
			ndcPos_ =
				Transform(b.localPos_, b.worldViewProjectionMatrix_);
			b.screenPos_ =
				Transform(ndcPos_, viewportMatrix);

			/****************************************************************************************************************************/
			// c地点の変換
			c.worldMatrix_ =
				MakeAffineMatrix({ 1.0f,1.0f,1.0f }, { 0.0f,0.0f,0.0f }, c.localPos_);
			c.worldViewProjectionMatrix_ =
				Multiply(c.worldMatrix_, Multiply(viewMatrix, projectionMatrix));
			ndcPos_ =
				Transform(c.localPos_, c.worldViewProjectionMatrix_);
			c.screenPos_ =
				Transform(ndcPos_, viewportMatrix);

			/****************************************************************************************************************************/
			// ab、bcで描画
			// ab
			Novice::DrawLine(
				static_cast<int>(a.screenPos_.x), static_cast<int>(a.screenPos_.y),
				static_cast<int>(b.screenPos_.x), static_cast<int>(b.screenPos_.y),
				0x000000ff
			);

			// bc
			Novice::DrawLine(
				static_cast<int>(a.screenPos_.x), static_cast<int>(a.screenPos_.y),
				static_cast<int>(c.screenPos_.x), static_cast<int>(c.screenPos_.y),
				0x000000ff
			);
		}
	}
}