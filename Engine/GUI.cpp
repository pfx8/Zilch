//*****************************************************************************
//
// GUI����[GUI.cpp]
//
// Author : LIAO HANCHEN
//
//****************************************************************************
#include "GUI.h"

//*****************************************************************************
//
// �R���X�g���N�^
//
//*****************************************************************************
GUI::GUI(void)
{

}

//*****************************************************************************
//
// �f�X�g���N�^
//
//*****************************************************************************
GUI::~GUI(void)
{
	ImGui_ImplDX9_Shutdown();
	ImGui::DestroyContext();
}

//*****************************************************************************
//
// ImGui������
//
//*****************************************************************************
void GUI::start(HWND hWnd, LPDIRECT3DDEVICE9 D3DDevice)
{
	// ImGui��������
	ImGui::CreateContext();
	ImGui_ImplDX9_Init(hWnd, D3DDevice);
	ImGui::StyleColorsDark();

	// I/O��������
	ImGuiIO& io = ImGui::GetIO();
	(void)io;
	ImFont* font = io.Fonts->AddFontFromFileTTF("Resources\\Font\\NotoSansCJKjp-Regular.otf", 18.0f, NULL, io.Fonts->GetGlyphRangesJapanese());
	io.FontDefault = font;

	// �e�`�F�b�N��������
	this->mIsWireframe = false;
	this->mIsAddingModel = false;
	this->mIsModelFile = true;
	this->mCurrentRenderingMode = RM_TEXTURE;	// �f�t�H���g�̓e�N�X�`�����[�h
	this->mCurrentColorRampType = CR_LINEAR;	// �f�t�H���g�̓��j�A���[�h
	this->mCurrentLanguage = 0;					// �f�t�H���g�͓��{��
}

//*****************************************************************************
//
// ImGui�ƃA�v���P�[�V�����̑��앪��
//
//*****************************************************************************
bool GUI::isAnyImGuiFocused(void)
{
	if (ImGui::IsAnyWindowFocused())
	{
		return true;
	}

	return false;
}

//*****************************************************************************
//
// ImGui�̕`�揈��
//
//*****************************************************************************
void GUI::draw(void)
{
	// ImGui�o�b�t�@�T�C�Y���m��
	ImGui::GetIO().DisplaySize.x = SCREEN_WIDTH;
	ImGui::GetIO().DisplaySize.y = SCREEN_HEIGHT;

	//�V�X�e������GUI
	systemGUI();

	// �V�[��GUI
	sceneGUI();

	// ���f���ǉ��E�C���h�E���`�F�b�N
	if (this->mIsAddingModel == true)
	{
		addModelImGui();
	}

	// �h���b�v�t�@�C���G���[�E�C���h�E���`�F�b�N
	if (this->mIsModelFile == false)
	{
		dropFileErrorGUI();
	}

	// ImGui��`��
	if (this->mIsWireframe)
	{
		getD3DDevice()->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
		ImGui::Render();
		ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
		getD3DDevice()->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
	}
	else
	{
		ImGui::Render();
		ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
	}
}

//*****************************************************************************
//
// �V�X�e������GUI
//
//*****************************************************************************
void GUI::systemGUI(void)
{
	ImGui::Begin(u8"�f�o�b�O�E�C���h", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove);

	// ����I�� -- �����ł��Ȃ�
	{
		ImGui::Combo(u8"����", &this->mCurrentLanguage, this->mLanguage, IM_ARRAYSIZE(this->mLanguage));
		ImGui::Separator();
	}

	// FPS�ƃ^�C��
	{
		ImGui::Text("Fps:%.3f fps, Time:%.3f s/fps", ImGui::GetIO().Framerate, getGameTimes()->mDeltaTime);
		ImGui::Separator();
	}

	// �}�E�X�ʒu
	{
		ImGui::Text("%f, %f", ImGui::GetIO().MousePos.x, ImGui::GetIO().MousePos.y);
		ImGui::SameLine();
		ImGui::Text(u8"�}�E�X�ʒu");
		ImGui::Separator();
	}

	// �����_�����O���[�h
	{
		// ���C���t���[����h��Ԃ�
		ImGui::TextUnformatted(u8"�h��Ԃ�");
		if (ImGui::Button(u8"���C���[�t���[��"))
		{
			getD3DDevice()->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
			this->mIsWireframe = true;
		}
		// �ʂ�h��Ԃ�
		ImGui::SameLine();
		if (ImGui::Button(u8"�|���S�����[�h"))
		{
			getD3DDevice()->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
			this->mIsWireframe = false;
		}
		ImGui::Separator();
	}

	// �X�N���[���V���b�g
	{
		ImGui::TextUnformatted(u8"�@�\");
		if (ImGui::Button(u8"�X�N���[���V���b�g"))
		{
			ImGui::OpenPopup(u8"�X�N���[���V���b�g");
		}
		ImGui::Separator();

		if (ImGui::BeginPopupModal(u8"�X�N���[���V���b�g"))
		{
			// �o�b�t�@��ʂ��擾
			static LPDIRECT3DSURFACE9 backBuffer = nullptr;
			getD3DDevice()->GetRenderTarget(0, &backBuffer);

			ImGui::TextUnformatted(u8"�X�N���[���V���b�g.bmp���ۑ�����܂����I");
			if (ImGui::Button(u8"�͂�"))
			{
				// �o�b�t�@�T�[�t�F�C�X��ۑ�
				D3DXSaveSurfaceToFile(L"�X�N���[���V���b�g.bmp", D3DXIFF_BMP, backBuffer, NULL, NULL);
				wcout << L"<System> ..\\�X�N���[���V���b�g.bmp ... successed!" << endl;

				// �o�b�t�@��nullptr����
				backBuffer = nullptr;

				// �T�u�E�C���h��߂�
				ImGui::CloseCurrentPopup();
			}

			ImGui::EndPopup();
		}
	}

	// �V�X�e���J����
	{
		// �V�[���̃J�������擾
		Camera* camera = getSceneManager()->mCurrentScene->mCurrentCamera;

		if (ImGui::TreeNode(u8"�V�X�e���J����"))
		{
			float* v1[3] = { &camera->mCameraPos.x, &camera->mCameraPos.y, &camera->mCameraPos.z };
			ImGui::TextUnformatted(u8"�ʒu");
			ImGui::InputFloat3(u8"Pos", *v1);
			ImGui::Separator();

			float* v2[3] = { &camera->mTargetPos.x, &camera->mTargetPos.y, &camera->mTargetPos.z };
			ImGui::TextUnformatted(u8"�����_");
			ImGui::InputFloat3(u8"At", *v2);
			ImGui::Separator();

			float* v3[3] = { &camera->mCameraFront.x, &camera->mCameraFront.y, &camera->mCameraFront.z };
			ImGui::TextUnformatted(u8"��������");
			ImGui::DragFloat3(u8"Look", *v3);
			ImGui::Separator();

			float* v4[3] = { &camera->mCameraRight.x, &camera->mCameraRight.y, &camera->mCameraRight.z };
			ImGui::TextUnformatted(u8"�E����");
			ImGui::DragFloat3(u8"Right", *v4);
			ImGui::Separator();

			float* v5[3] = { &camera->mCameraUp.x, &camera->mCameraUp.y, &camera->mCameraUp.z };
			ImGui::TextUnformatted(u8"�����");
			ImGui::DragFloat3(u8"Up", *v5);
			ImGui::Separator();

			ImGui::TreePop();
		}
		ImGui::Separator();
	}

	// �����_�����O���[�h��I��
	{
		// �R���{�{�b�N�X�̕���ݒ�
		ImGui::PushItemWidth(160);
		ImGui::TextUnformatted(u8"�����_�����O���[�h");
		ImGui::Combo(u8"RenderingMode", (int*)&this->mCurrentRenderingMode, this->mRenderingMode, IM_ARRAYSIZE(this->mRenderingMode));
		switch (this->mCurrentRenderingMode)
		{
		case 0:
			getSceneManager()->mCurrentScene->mShader->mRenderingMode = RM_TEXTURE;
			break;
		case 1:
			getSceneManager()->mCurrentScene->mShader->mRenderingMode = RM_DIFFUSE;
			break;
		case 2:
			getSceneManager()->mCurrentScene->mShader->mRenderingMode = RM_SPECULAR;
			break;
		case 3:
			getSceneManager()->mCurrentScene->mShader->mRenderingMode = RM_NORMAL;
			break;
		case 4:
			getSceneManager()->mCurrentScene->mShader->mRenderingMode = RM_SHADING;
			break;
		}
		ImGui::Separator();
	}

	// �J���[���b�v�I��
	{
		// �R���{�{�b�N�X�̕���ݒ�
		ImGui::PushItemWidth(160);
		ImGui::TextUnformatted(u8"�J���[�����v���[�h");
		ImGui::Combo(u8"ColorRamp", (int*)&this->mCurrentColorRampType, this->mColorRamp, IM_ARRAYSIZE(this->mColorRamp));
		switch (this->mCurrentColorRampType)
		{
		case 0:
			getSceneManager()->mCurrentScene->mShader->mColorRampType = CR_LINEAR;
			break;
		case 1:
			D3DXVECTOR3* colorRampSegment = &getSceneManager()->mCurrentScene->mShader->mColorRampSegment;

			ImGui::TextUnformatted(u8"�J���[�Z�O�����g");
			ImGui::SliderFloat("Level1", &colorRampSegment->x, 0.0f, 1.0f);
			if (colorRampSegment->x > colorRampSegment->y)
			{
				colorRampSegment->y = colorRampSegment->x;
			}

			ImGui::SliderFloat("Level2", &colorRampSegment->y, 0.0f, 1.0f);
			if (colorRampSegment->y > colorRampSegment->z)
			{
				colorRampSegment->z = colorRampSegment->y;
			}

			ImGui::SliderFloat("Level3", &colorRampSegment->z, 0.0f, 1.0f);
			if (colorRampSegment->z < colorRampSegment->y)
			{
				colorRampSegment->y = colorRampSegment->z;
			}
			if (colorRampSegment->y < colorRampSegment->x)
			{
				colorRampSegment->x = colorRampSegment->y;
			}

			getSceneManager()->mCurrentScene->mShader->mColorRampType = CR_CONSTANT;
			break;
		}
	}

	ImGui::End();
}

//*****************************************************************************
//
// �V�[��GUI
//
//*****************************************************************************
void GUI::sceneGUI(void)
{
	// �V�[���̃}���`���x�����j���[
	ImGui::SetNextWindowSize(ImVec2(364,742));
	ImGui::Begin(u8"�V�[��", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove);
	{
		// GameObject�̍�胁�j���\
		//createNewGameObjectGUI();

		// BG�J���[
		ImGui::ColorEdit4(u8"���C�g�J���[", getSceneManager()->mCurrentScene->mBGColor, ImGuiColorEditFlags_RGB);
		ImGui::Separator();

		// �eGameObject
		unsigned int IDs = 0;
		for (auto it : getSceneManager()->mCurrentScene->mGameObjectMap)
		{
			ImGui::PushID(IDs);
			string name1 = wstringToString(it.first);
			if (ImGui::TreeNode("gameObject", u8"%s", name1.c_str(), ImGuiTreeNodeFlags_OpenOnArrow))
			{
				// GameObject�̊e�R���|�[�l���g���o��
				unsigned int ID2s = 0;
				for (auto it2 : it.second->mComponentsMap)
				{
					ImGui::PushID(ID2s);
					string name2 = it2.first.name();
					name2 = name2.substr(name2.find_last_of(" ") + 1, name2.size());		// exp: class xxx -> xxx
					if (ImGui::TreeNode(u8"%s", name2.c_str()))
					{
						it2.second->drawImGui();
						ImGui::TreePop();
					}

					ID2s++;
					ImGui::PopID();
				}
				ImGui::TreePop();
			}

			IDs++;
			ImGui::PopID();
		}
		
	}
	ImGui::End();
}

//*****************************************************************************
//
//  �V����GameObject����胁�j���[
//
//*****************************************************************************
void GUI::createNewGameObjectGUI(void)
{
	if (ImGui::Button("Create GameObject"))
	{
		// �T�u�E�C���h���J��
		ImGui::OpenPopup("Create GameObject");
	}

	// �T�u�E�C���h�ݒ�
	if (ImGui::BeginPopupModal("Create GameObject"))
	{
		ImGui::TextUnformatted(u8"GameObject���O");
		ImGui::InputText("name", this->mNewGameObjectName, IM_ARRAYSIZE(this->mNewGameObjectName));

		if (ImGui::Button(u8"���"))
		{
			// �V����GameObject�����
			GameObject* gameObject = new GameObject();
			wstring newGameObjectName = stringToWstring(this->mNewGameObjectName);
			getSceneManager()->mCurrentScene->addGameObject(newGameObjectName, gameObject);

			// mNewGameObjectName������
			*this->mNewGameObjectName = { NULL };

			// �T�u�E�C���h��߂�
			ImGui::CloseCurrentPopup();
		}
		ImGui::SameLine();
		if (ImGui::Button(u8"�L�����Z��"))
		{
			// �T�u�E�C���h��߂�
			ImGui::CloseCurrentPopup();

		}

		ImGui::EndPopup();
	}
}

//*****************************************************************************
//
// ���f���ǉ�GUI
//
//*****************************************************************************
void GUI::addModelImGui(void)
{
	ImGui::Begin(u8"�C���|�[�g");
	ImGui::TextUnformatted(u8"GameObject���O");
	ImGui::InputText("name", this->mNewGameObjectName, IM_ARRAYSIZE(this->mNewGameObjectName));
	ImGui::TextUnformatted(u8"���f���t�@�C���p�X");
	string path = wstringToString(this->mAddingFilePath);
	ImGui::Text(u8"%s", path.c_str());

	wstring newGameObjectName = stringToWstring(this->mNewGameObjectName);

	// �G���[�^�C�v 0 -- default�A1 -- Error1�A2 -- Error2
	static int errorType = 0;

	// �`�F�b�NGameObject���O
	if (ImGui::Button(u8"�C���|�[�g"))
	{
		if (strlen(this->mNewGameObjectName) == 0 )
		{
			// GameObject���O���Ȃ�
			errorType = 1;
		}

		if (!isGameObjectNameRight(newGameObjectName))
		{
			// GameObject���O����@
			errorType = 2;
		}

		if (errorType != 0)
		{
			// �G���[�E�C���h���J��
			ImGui::OpenPopup("Error");
		}
		else
		{
			// ���f����ǂݍ���
			getResources()->createModel(this->mAddingFilePath);

			// �V����GameObject�����
			GameObject* gameObject = new GameObject();
			Transform* transform = new Transform();												// �f�t�H���g��pos(0,0,0)�Ascl(1,1,1)�Arot(0,0,0)
			gameObject->addComponent<Transform>(transform);
			MeshRender* meshRender = new MeshRender();
			wstring name = pathToFileName(this->mAddingFilePath);
			meshRender->mModel = getResources()->getModel(name);
			getSceneManager()->mCurrentScene->mMeshRenders.push_back(meshRender);
			gameObject->addComponent<MeshRender>(meshRender);
			getSceneManager()->mCurrentScene->addGameObject(newGameObjectName, gameObject);

			// this->mNewGameObjectName������
			*this->mNewGameObjectName = { NULL };
			this->mIsAddingModel = false;
		}
	}

	// �G���[�E�C���h
	if (ImGui::BeginPopupModal("Error"))
	{
		if (errorType == 1)
		{
			ImGui::TextUnformatted(u8"GameObject���O����͂��Ă�������");
		}
		if (errorType == 2)
		{
			ImGui::TextUnformatted(u8"����GameObject���O�����݂��Ă�");
		}

		if (ImGui::Button(u8"�͂�"))
		{
			// �T�u�E�C���h��߂�
			ImGui::CloseCurrentPopup();

			// �G���[�^�C�v������
			errorType = 0;
		}

		ImGui::EndPopup();
	}

	// �L�����Z��
	ImGui::SameLine();
	if (ImGui::Button(u8"�L�����Z��"))
	{
		// mNewGameObjectName������
		*this->mNewGameObjectName = { NULL };

		this->mIsAddingModel = false;
	}

	if (this->mIsAddingModel == false)
	{
		// ���f���ǉ�GUI��߂�
		ImGui::CloseCurrentPopup();
	}

	ImGui::End();
}

//*****************************************************************************
//
// �`�F�b�N�ǉ�GameObject���O
//
//*****************************************************************************
bool GUI::isGameObjectNameRight(wstring name)
{
	for (auto it : getSceneManager()->mCurrentScene->mGameObjectMap)
	{
		// �V�[���Ɋ��ɂ��̖��O��GameObject�����݂����
		if (it.first == name)
		{
			return false;
		}
	}

	return true;
}

//*****************************************************************************
//
// �h���b�v�t�@�C���͑Ή��ł��Ȃ�GUI
//
//*****************************************************************************
void GUI::dropFileErrorGUI(void)
{
	ImGui::Begin(u8"Error");
	ImGui::TextUnformatted(u8"�h���b�v���ꂽ�t�@�C���̓��f���t�@�C���ł͂���܂���I");
	if (ImGui::Button(u8"�͂�"))
	{
		// �E�C���h�E�����
		this->mIsModelFile = true;
	}
	ImGui::End();
}