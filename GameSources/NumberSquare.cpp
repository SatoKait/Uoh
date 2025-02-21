
#include "stdafx.h"
#include "Project.h"

namespace basecross {
	//--------------------------------------------------------------------------------------
	//	数字のスクエア
	//--------------------------------------------------------------------------------------
	//構築と破棄
	NumberSquare::NumberSquare(const shared_ptr<Stage>& StagePtr,
		const shared_ptr<Poll>& PollObjectPtr, const wstring& ResKey) :
		GameObject(StagePtr),
		m_PollObject(PollObjectPtr),
		m_ResKey(ResKey)
	{ }

	NumberSquare::~NumberSquare() {}

	//初期化
	void NumberSquare::OnCreate() {

		auto PtrTransform = GetComponent<Transform>();
		if (!m_PollObject.expired()) {
			auto SeekPtr = m_PollObject.lock();
			auto SeekTransPtr = SeekPtr->GetComponent<Transform>();
			auto Pos = SeekTransPtr->GetPosition();
			Pos.y += 0.75f;
			PtrTransform->SetPosition(Pos);
			PtrTransform->SetScale(1.0f, 1.0f, 1.0f);
			PtrTransform->SetQuaternion(SeekTransPtr->GetQuaternion());
			//変更できるスクエアリソースを作成

			//頂点配列
			vector<VertexPositionNormalTexture> vertices;
			//インデックスを作成するための配列
			vector<uint16_t> indices;
			//Squareの作成(ヘルパー関数を利用)
			MeshUtill::CreateSquare(1.0f, vertices, indices);
			////UV値の変更
			//float from = ((float)m_Number) / 10.0f;
			//float to = from + (1.0f / 10.0f);
			////左上頂点
			vertices[0].textureCoordinate = Vec2(0.0f, 0);
			//右上頂点
			vertices[1].textureCoordinate = Vec2(1.0f, 0);
			//左下頂点
			vertices[2].textureCoordinate = Vec2(0.0f, 1.0f);
			//右下頂点
			vertices[3].textureCoordinate = Vec2(1.0f, 1.0f);
			//頂点の型を変えた新しい頂点を作成
			vector<VertexPositionColorTexture> new_vertices;
			for (auto& v : vertices) {
				VertexPositionColorTexture nv;
				nv.position = v.position;
				nv.color = Col4(1.0f, 1.0f, 1.0f, 1.0f);
				nv.textureCoordinate = v.textureCoordinate;
				new_vertices.push_back(nv);
			}
			//新しい頂点を使ってメッシュリソースの作成
			m_SquareMeshResource = MeshResource::CreateMeshResource<VertexPositionColorTexture>(new_vertices, indices, true);

			auto DrawComp = AddComponent<PCTStaticDraw>();
			DrawComp->SetMeshResource(m_SquareMeshResource);
			DrawComp->SetTextureResource(m_ResKey);
			SetAlphaActive(true);
			SetDrawLayer(1);
		}

	}


	//変化
	void NumberSquare::OnUpdate() {

		if (!m_PollObject.expired()) {
			auto SeekPtr = m_PollObject.lock();
			auto SeekTransPtr = SeekPtr->GetComponent<Transform>();

			auto PtrTransform = GetComponent<Transform>();
			auto Pos = SeekTransPtr->GetPosition();
			Pos.y += 2.75f;
			PtrTransform->SetPosition(Pos);
			PtrTransform->SetScale(5.0f, 3.0f, 1.0f);

			auto PtrCamera = GetStage()->GetView()->GetTargetCamera();

			Quat Qt;
			//向きをビルボードにする
			Qt = Billboard(PtrCamera->GetAt() - PtrCamera->GetEye());

			PtrTransform->SetQuaternion(Qt);

		}

		auto Playerptr = GetStage()->GetSharedGameObject<Player>(L"Player");
		auto PlayerCicle = Playerptr->m_CircleCount;
		auto DrawComp = GetComponent<PCTStaticDraw>();
		switch (PlayerCicle)
		{
		case 0:
			DrawComp->SetMeshResource(m_SquareMeshResource);
			DrawComp->SetTextureResource(L"Number300_TX");
			break;

		case 1:
			DrawComp->SetMeshResource(m_SquareMeshResource);
			DrawComp->SetTextureResource(L"Number300_TX");
			break;
		case 2:
			DrawComp->SetMeshResource(m_SquareMeshResource);
			DrawComp->SetTextureResource(L"Number600_TX");
			break;
		case 3:
			DrawComp->SetMeshResource(m_SquareMeshResource);
			DrawComp->SetTextureResource(L"Number900_TX");
			break;
		case 4:
			DrawComp->SetMeshResource(m_SquareMeshResource);
			DrawComp->SetTextureResource(L"Number1200_TX");
			break;
		case 5:
			DrawComp->SetMeshResource(m_SquareMeshResource);
			DrawComp->SetTextureResource(L"Number1500_TX");
			break;

		}
	}

	//--------------------------------------------------------------------------------------
	//	数字のスクエア
	//--------------------------------------------------------------------------------------
	//構築と破棄
	NumberSquare2::NumberSquare2(const shared_ptr<Stage>& StagePtr,
		const shared_ptr<PollBlue>& PollObjectPtr, const wstring& ResKey) :
		GameObject(StagePtr),
		m_PollObject(PollObjectPtr),
		m_ResKey(ResKey)
	{
	}

	NumberSquare2::~NumberSquare2() {}

	//初期化
	void NumberSquare2::OnCreate() {

		auto PtrTransform = GetComponent<Transform>();
		if (!m_PollObject.expired()) {
			auto SeekPtr = m_PollObject.lock();
			auto SeekTransPtr = SeekPtr->GetComponent<Transform>();
			auto Pos = SeekTransPtr->GetPosition();
			Pos.y += 0.75f;
			PtrTransform->SetPosition(Pos);
			PtrTransform->SetScale(1.0f, 1.0f, 1.0f);
			PtrTransform->SetQuaternion(SeekTransPtr->GetQuaternion());
			//変更できるスクエアリソースを作成

			//頂点配列
			vector<VertexPositionNormalTexture> vertices;
			//インデックスを作成するための配列
			vector<uint16_t> indices;
			//Squareの作成(ヘルパー関数を利用)
			MeshUtill::CreateSquare(1.0f, vertices, indices);
			////UV値の変更
			//float from = ((float)m_Number) / 10.0f;
			//float to = from + (1.0f / 10.0f);
			////左上頂点
			vertices[0].textureCoordinate = Vec2(0.0f, 0);
			//右上頂点
			vertices[1].textureCoordinate = Vec2(1.0f, 0);
			//左下頂点
			vertices[2].textureCoordinate = Vec2(0.0f, 1.0f);
			//右下頂点
			vertices[3].textureCoordinate = Vec2(1.0f, 1.0f);
			//頂点の型を変えた新しい頂点を作成
			vector<VertexPositionColorTexture> new_vertices;
			for (auto& v : vertices) {
				VertexPositionColorTexture nv;
				nv.position = v.position;
				nv.color = Col4(1.0f, 1.0f, 1.0f, 1.0f);
				nv.textureCoordinate = v.textureCoordinate;
				new_vertices.push_back(nv);
			}
			//新しい頂点を使ってメッシュリソースの作成
			m_SquareMeshResource = MeshResource::CreateMeshResource<VertexPositionColorTexture>(new_vertices, indices, true);

			auto DrawComp = AddComponent<PCTStaticDraw>();
			DrawComp->SetMeshResource(m_SquareMeshResource);
			DrawComp->SetTextureResource(m_ResKey);
			SetAlphaActive(true);
			SetDrawLayer(1);
		}

	}


	//変化
	void NumberSquare2::OnUpdate() {

		if (!m_PollObject.expired()) {
			auto SeekPtr = m_PollObject.lock();
			auto SeekTransPtr = SeekPtr->GetComponent<Transform>();

			auto PtrTransform = GetComponent<Transform>();
			auto Pos = SeekTransPtr->GetPosition();
			Pos.y += 2.75f;
			PtrTransform->SetPosition(Pos);
			PtrTransform->SetScale(5.0f, 3.0f, 1.0f);

			auto PtrCamera = GetStage()->GetView()->GetTargetCamera();

			Quat Qt;
			//向きをビルボードにする
			Qt = Billboard(PtrCamera->GetAt() - PtrCamera->GetEye());

			PtrTransform->SetQuaternion(Qt);

		}

		auto Playerptr = GetStage()->GetSharedGameObject<Player>(L"Player");
		auto PlayerCicle = Playerptr->m_CircleCount;
		auto DrawComp = GetComponent<PCTStaticDraw>();
		switch (PlayerCicle)
		{
		case 0:
			DrawComp->SetMeshResource(m_SquareMeshResource);
			DrawComp->SetTextureResource(L"Number100_TX");
			break;
		case 1:
			DrawComp->SetMeshResource(m_SquareMeshResource);
			DrawComp->SetTextureResource(L"Number100_TX");
			break;
		case 2:
			DrawComp->SetMeshResource(m_SquareMeshResource);
			DrawComp->SetTextureResource(L"Number200_TX");
			break;
		case 3:
			DrawComp->SetMeshResource(m_SquareMeshResource);
			DrawComp->SetTextureResource(L"Number300_TX");
			break;
		case 4:
			DrawComp->SetMeshResource(m_SquareMeshResource);
			DrawComp->SetTextureResource(L"Number400_TX");
			break;
		case 5:
			DrawComp->SetMeshResource(m_SquareMeshResource);
			DrawComp->SetTextureResource(L"Number500_TX");
			break;

		}
	}

	//--------------------------------------------------------------------------------------
	//	数字のスクエア
	//--------------------------------------------------------------------------------------
	//構築と破棄
	NumberSquare3::NumberSquare3(const shared_ptr<Stage>& StagePtr,
		const shared_ptr<PollRed>& PollObjectPtr, const wstring& ResKey) :
		GameObject(StagePtr),
		m_PollObject(PollObjectPtr),
		m_ResKey(ResKey)
	{
	}

	NumberSquare3::~NumberSquare3() {}

	//初期化
	void NumberSquare3::OnCreate() {

		auto PtrTransform = GetComponent<Transform>();
		if (!m_PollObject.expired()) {
			auto SeekPtr = m_PollObject.lock();
			auto SeekTransPtr = SeekPtr->GetComponent<Transform>();
			auto Pos = SeekTransPtr->GetPosition();
			Pos.y += 0.75f;
			PtrTransform->SetPosition(Pos);
			PtrTransform->SetScale(1.0f, 1.0f, 1.0f);
			PtrTransform->SetQuaternion(SeekTransPtr->GetQuaternion());
			//変更できるスクエアリソースを作成

			//頂点配列
			vector<VertexPositionNormalTexture> vertices;
			//インデックスを作成するための配列
			vector<uint16_t> indices;
			//Squareの作成(ヘルパー関数を利用)
			MeshUtill::CreateSquare(1.0f, vertices, indices);
			////UV値の変更
			//float from = ((float)m_Number) / 10.0f;
			//float to = from + (1.0f / 10.0f);
			////左上頂点
			vertices[0].textureCoordinate = Vec2(0.0f, 0);
			//右上頂点
			vertices[1].textureCoordinate = Vec2(1.0f, 0);
			//左下頂点
			vertices[2].textureCoordinate = Vec2(0.0f, 1.0f);
			//右下頂点
			vertices[3].textureCoordinate = Vec2(1.0f, 1.0f);
			//頂点の型を変えた新しい頂点を作成
			vector<VertexPositionColorTexture> new_vertices;
			for (auto& v : vertices) {
				VertexPositionColorTexture nv;
				nv.position = v.position;
				nv.color = Col4(1.0f, 1.0f, 1.0f, 1.0f);
				nv.textureCoordinate = v.textureCoordinate;
				new_vertices.push_back(nv);
			}
			//新しい頂点を使ってメッシュリソースの作成
			m_SquareMeshResource = MeshResource::CreateMeshResource<VertexPositionColorTexture>(new_vertices, indices, true);

			auto DrawComp = AddComponent<PCTStaticDraw>();
			DrawComp->SetMeshResource(m_SquareMeshResource);
			DrawComp->SetTextureResource(m_ResKey);
			SetAlphaActive(true);
			SetDrawLayer(1);
		}

	}


	//変化
	void NumberSquare3::OnUpdate() {

		if (!m_PollObject.expired()) {
			auto SeekPtr = m_PollObject.lock();
			auto SeekTransPtr = SeekPtr->GetComponent<Transform>();

			auto PtrTransform = GetComponent<Transform>();
			auto Pos = SeekTransPtr->GetPosition();
			Pos.y += 2.75f;
			PtrTransform->SetPosition(Pos);
			PtrTransform->SetScale(5.0f, 3.0f, 1.0f);

			auto PtrCamera = GetStage()->GetView()->GetTargetCamera();

			Quat Qt;
			//向きをビルボードにする
			Qt = Billboard(PtrCamera->GetAt() - PtrCamera->GetEye());

			PtrTransform->SetQuaternion(Qt);

		}

		auto Playerptr = GetStage()->GetSharedGameObject<Player>(L"Player");
		auto PlayerCicle = Playerptr->m_CircleCount;
		auto DrawComp = GetComponent<PCTStaticDraw>();
		switch (PlayerCicle)
		{
		case 0:
			DrawComp->SetMeshResource(m_SquareMeshResource);
			DrawComp->SetTextureResource(L"Number100_TX");
			break;
		case 1:
			DrawComp->SetMeshResource(m_SquareMeshResource);
			DrawComp->SetTextureResource(L"Number100_TX");
			break;
		case 2:
			DrawComp->SetMeshResource(m_SquareMeshResource);
			DrawComp->SetTextureResource(L"Number200_TX");
			break;
		case 3:
			DrawComp->SetMeshResource(m_SquareMeshResource);
			DrawComp->SetTextureResource(L"Number300_TX");
			break;
		case 4:
			DrawComp->SetMeshResource(m_SquareMeshResource);
			DrawComp->SetTextureResource(L"Number400_TX");
			break;
		case 5:
			DrawComp->SetMeshResource(m_SquareMeshResource);
			DrawComp->SetTextureResource(L"Number500_TX");
			break;
		}
	}

	//--------------------------------------------------------------------------------------
	//	数字のスクエア
	//--------------------------------------------------------------------------------------
	//構築と破棄
	NumberSquare4::NumberSquare4(const shared_ptr<Stage>& StagePtr,
		const shared_ptr<CirclePoll>& PollObjectPtr, const wstring& ResKey) :
		GameObject(StagePtr),
		m_PollObject(PollObjectPtr),
		m_ResKey(ResKey)
	{
	}

	NumberSquare4::~NumberSquare4() {}

	//初期化
	void NumberSquare4::OnCreate() {

		auto PtrTransform = GetComponent<Transform>();
		if (!m_PollObject.expired()) {
			auto SeekPtr = m_PollObject.lock();
			auto SeekTransPtr = SeekPtr->GetComponent<Transform>();
			auto Pos = SeekTransPtr->GetPosition();
			Pos.y += 0.75f;
			PtrTransform->SetPosition(Pos);
			PtrTransform->SetScale(1.0f, 1.0f, 1.0f);
			PtrTransform->SetQuaternion(SeekTransPtr->GetQuaternion());
			//変更できるスクエアリソースを作成

			//頂点配列
			vector<VertexPositionNormalTexture> vertices;
			//インデックスを作成するための配列
			vector<uint16_t> indices;
			//Squareの作成(ヘルパー関数を利用)
			MeshUtill::CreateSquare(1.0f, vertices, indices);
			////UV値の変更
			//float from = ((float)m_Number) / 10.0f;
			//float to = from + (1.0f / 10.0f);
			////左上頂点
			vertices[0].textureCoordinate = Vec2(0.0f, 0);
			//右上頂点
			vertices[1].textureCoordinate = Vec2(1.0f, 0);
			//左下頂点
			vertices[2].textureCoordinate = Vec2(0.0f, 1.0f);
			//右下頂点
			vertices[3].textureCoordinate = Vec2(1.0f, 1.0f);
			//頂点の型を変えた新しい頂点を作成
			vector<VertexPositionColorTexture> new_vertices;
			for (auto& v : vertices) {
				VertexPositionColorTexture nv;
				nv.position = v.position;
				nv.color = Col4(1.0f, 1.0f, 1.0f, 1.0f);
				nv.textureCoordinate = v.textureCoordinate;
				new_vertices.push_back(nv);
			}
			//新しい頂点を使ってメッシュリソースの作成
			m_SquareMeshResource = MeshResource::CreateMeshResource<VertexPositionColorTexture>(new_vertices, indices, true);

			auto DrawComp = AddComponent<PCTStaticDraw>();
			DrawComp->SetMeshResource(m_SquareMeshResource);
			DrawComp->SetTextureResource(m_ResKey);
			SetAlphaActive(true);
			SetDrawLayer(1);
		}

	}


	//変化
	void NumberSquare4::OnUpdate() {

		if (!m_PollObject.expired()) {
			auto SeekPtr = m_PollObject.lock();
			auto SeekTransPtr = SeekPtr->GetComponent<Transform>();

			auto PtrTransform = GetComponent<Transform>();
			auto Pos = SeekTransPtr->GetPosition();
			Pos.y += 4.5f;
			PtrTransform->SetPosition(Pos);
			PtrTransform->SetScale(5.0f, 3.0f, 1.0f);

			auto PtrCamera = GetStage()->GetView()->GetTargetCamera();

			Quat Qt;
			//向きをビルボードにする
			Qt = Billboard(PtrCamera->GetAt() - PtrCamera->GetEye());

			PtrTransform->SetQuaternion(Qt);

		}

		auto Playerptr = GetStage()->GetSharedGameObject<Player>(L"Player");
		auto PlayerCicle = Playerptr->m_CircleCount;
		auto DrawComp = GetComponent<PCTStaticDraw>();
		switch (PlayerCicle)
		{
		case 0:
			DrawComp->SetMeshResource(m_SquareMeshResource);
			DrawComp->SetTextureResource(L"Number200_TX");
			break;
		case 1:
			DrawComp->SetMeshResource(m_SquareMeshResource);
			DrawComp->SetTextureResource(L"Number200_TX");
			break;
		case 2:
			DrawComp->SetMeshResource(m_SquareMeshResource);
			DrawComp->SetTextureResource(L"Number400_TX");
			break;
		case 3:
			DrawComp->SetMeshResource(m_SquareMeshResource);
			DrawComp->SetTextureResource(L"Number600_TX");
			break;
		case 4:
			DrawComp->SetMeshResource(m_SquareMeshResource);
			DrawComp->SetTextureResource(L"Number800_TX");
			break;
		case 5:
			DrawComp->SetMeshResource(m_SquareMeshResource);
			DrawComp->SetTextureResource(L"Number1000_TX");
			break;
		}
	}

	//--------------------------------------------------------------------------------------
	//	数字のスクエア
	//--------------------------------------------------------------------------------------
	//構築と破棄
	NumberSquare5::NumberSquare5(const shared_ptr<Stage>& StagePtr,
		const shared_ptr<RedCirclePoll>& PollObjectPtr, const wstring& ResKey) :
		GameObject(StagePtr),
		m_PollObject(PollObjectPtr),
		m_ResKey(ResKey)
	{
	}

	NumberSquare5::~NumberSquare5() {}

	//初期化
	void NumberSquare5::OnCreate() {

		auto PtrTransform = GetComponent<Transform>();
		if (!m_PollObject.expired()) {
			auto SeekPtr = m_PollObject.lock();
			auto SeekTransPtr = SeekPtr->GetComponent<Transform>();
			auto Pos = SeekTransPtr->GetPosition();
			Pos.y += 0.75f;
			PtrTransform->SetPosition(Pos);
			PtrTransform->SetScale(1.0f, 1.0f, 1.0f);
			PtrTransform->SetQuaternion(SeekTransPtr->GetQuaternion());
			//変更できるスクエアリソースを作成

			//頂点配列
			vector<VertexPositionNormalTexture> vertices;
			//インデックスを作成するための配列
			vector<uint16_t> indices;
			//Squareの作成(ヘルパー関数を利用)
			MeshUtill::CreateSquare(1.0f, vertices, indices);
			////UV値の変更
			//float from = ((float)m_Number) / 10.0f;
			//float to = from + (1.0f / 10.0f);
			////左上頂点
			vertices[0].textureCoordinate = Vec2(0.0f, 0);
			//右上頂点
			vertices[1].textureCoordinate = Vec2(1.0f, 0);
			//左下頂点
			vertices[2].textureCoordinate = Vec2(0.0f, 1.0f);
			//右下頂点
			vertices[3].textureCoordinate = Vec2(1.0f, 1.0f);
			//頂点の型を変えた新しい頂点を作成
			vector<VertexPositionColorTexture> new_vertices;
			for (auto& v : vertices) {
				VertexPositionColorTexture nv;
				nv.position = v.position;
				nv.color = Col4(1.0f, 1.0f, 1.0f, 1.0f);
				nv.textureCoordinate = v.textureCoordinate;
				new_vertices.push_back(nv);
			}
			//新しい頂点を使ってメッシュリソースの作成
			m_SquareMeshResource = MeshResource::CreateMeshResource<VertexPositionColorTexture>(new_vertices, indices, true);

			auto DrawComp = AddComponent<PCTStaticDraw>();
			DrawComp->SetMeshResource(m_SquareMeshResource);
			DrawComp->SetTextureResource(m_ResKey);
			SetAlphaActive(true);
			SetDrawLayer(1);
		}

	}


	//変化
	void NumberSquare5::OnUpdate() {

		if (!m_PollObject.expired()) {
			auto SeekPtr = m_PollObject.lock();
			auto SeekTransPtr = SeekPtr->GetComponent<Transform>();

			auto PtrTransform = GetComponent<Transform>();
			auto Pos = SeekTransPtr->GetPosition();
			Pos.y += 4.5f;
			PtrTransform->SetPosition(Pos);
			PtrTransform->SetScale(5.0f, 3.0f, 1.0f);

			auto PtrCamera = GetStage()->GetView()->GetTargetCamera();

			Quat Qt;
			//向きをビルボードにする
			Qt = Billboard(PtrCamera->GetAt() - PtrCamera->GetEye());

			PtrTransform->SetQuaternion(Qt);

		}

		auto Playerptr = GetStage()->GetSharedGameObject<Player>(L"Player");
		auto PlayerCicle = Playerptr->m_CircleCount;
		auto DrawComp = GetComponent<PCTStaticDraw>();
		switch (PlayerCicle)
		{
		case 0:
			DrawComp->SetMeshResource(m_SquareMeshResource);
			DrawComp->SetTextureResource(L"Number200_TX");
			break;
		case 1:
			DrawComp->SetMeshResource(m_SquareMeshResource);
			DrawComp->SetTextureResource(L"Number200_TX");
			break;
		case 2:
			DrawComp->SetMeshResource(m_SquareMeshResource);
			DrawComp->SetTextureResource(L"Number400_TX");
			break;
		case 3:
			DrawComp->SetMeshResource(m_SquareMeshResource);
			DrawComp->SetTextureResource(L"Number600_TX");
			break;
		case 4:
			DrawComp->SetMeshResource(m_SquareMeshResource);
			DrawComp->SetTextureResource(L"Number800_TX");
			break;
		case 5:
			DrawComp->SetMeshResource(m_SquareMeshResource);
			DrawComp->SetTextureResource(L"Number1000_TX");
			break;
		}
	}

}