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
GUI::GUI()
{

}

//*****************************************************************************
//
// �f�X�g���N�^
//
//*****************************************************************************
GUI::~GUI()
{
	// ImGui�I������
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
	ImGui::CreateContext();
	// I/O��������
	ImGuiIO& io = ImGui::GetIO();
	(void)io;
	// ImGui��������
	ImGui_ImplDX9_Init(hWnd, D3DDevice);
	// �X�^�C���J���[�����߂�
	ImGui::StyleColorsDark();
	// �f�t�H���g�t�H���g
	ImFont* font = io.Fonts->AddFontFromFileTTF("Resources\\Font\\NotoSansCJKjp-Regular.otf", 18.0f, NULL, io.Fonts->GetGlyphRangesJapanese());
	io.FontDefault = font;

	// �e�`�F�b�N��������
	this->mIsWireframe = false;
	this->mIsAddingModel = false;
	this->mIsModelFile = true;
	this->mCurrentShadingMode = 2;	// �f�t�H���g�̓e�N�X�`��
	this->mCurrentColorRamp = 0;	// �f�t�H���g�̓��j�A���[�h
	this->mCurrentLanguage = 0;		// �f�t�H���g�͓��{��
}

//*****************************************************************************
//
// ImGui�ƃA�v���P�[�V�����̑��앪��
//
//*****************************************************************************
bool GUI::isAnyImGuiFocused()
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
void GUI::draw()
{
	// ImGui�o�b�t�@�T�C�Y���m��
	ImGui::GetIO().DisplaySize.x = SCREEN_WIDTH;
	ImGui::GetIO().DisplaySize.y = SCREEN_HEIGHT;

	//�V�X�e������GUI
	systemGUI();

	// �V�[��GUI
	sceneGUI();

	// ���f���ǂݍ���
	if (this->mIsAddingModel == true)
	{
		addModelImGui();
	}

	// �h���b�v���ꂽ�t�@�C�����ΏۊO
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
void GUI::systemGUI()
{
	ImGui::Begin(u8"�f�o�b�O�E�C���h", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove);

	// ����I��
	{
		ImGui::Combo(u8"����", &this->mCurrentLanguage, this->mLanguage, IM_ARRAYSIZE(this->mLanguage));
		ImGui::Separator();
	}

	// FPS�ƃ^�C��
	{
		ImGui::Text("Fps:%.1f, Time:%.3fs", ImGui::GetIO().Framerate, getGameTimes()->mCurrentTime);
		ImGui::Separator();
	}

	// �}�E�X�ʒu
	{
		ImGui::Text("%f,%f", ImGui::GetIO().MousePos.x, ImGui::GetIO().MousePos.y);
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
			// �o�b�t�@��ʂ��擾
			LPDIRECT3DSURFACE9 backBuffer;
			getD3DDevice()->GetRenderTarget(0, &backBuffer);

			// �o�b�t�@�T�[�t�F�C�X��ۑ�
			D3DXSaveSurfaceToFile(L"screenShot.bmp", D3DXIFF_BMP, backBuffer, NULL, NULL);

			// Debug�E�C���h��
			cout << "<System> ..\screenShot.bmp ... successed!" << endl;

			// �o�b�t�@�������[�X
			backBuffer->Release();
		}
		ImGui::Separator();
	}

	// �V�X�e���J����
	{
		// �V�[���̃J�������擾
		Camera* camera = getSceneManager()->mCurrentScene->mCurrentCamera;

		if (ImGui::TreeNode(u8"�V�X�e���J����"))
		{
			float* v1[3] = { &camera->mCameraPos.x, &camera->mCameraPos.y, &camera->mCameraPos.z };
			ImGui::InputFloat3(u8"�ʒu", *v1);
			ImGui::Separator();

			float* v2[3] = { &camera->mTargetTrans->mPos.x, &camera->mTargetTrans->mPos.y, &camera->mTargetTrans->mPos.z };
			ImGui::InputFloat3(u8"�����_", *v2);
			ImGui::Separator();

			float* v3[3] = { &camera->mCameraFront.x, &camera->mCameraFront.y, &camera->mCameraFront.z };
			ImGui::DragFloat3(u8"��������", *v3);
			ImGui::Separator();

			float* v4[3] = { &camera->mCameraRight.x, &camera->mCameraRight.y, &camera->mCameraRight.z };
			ImGui::DragFloat3(u8"�E����", *v4);
			ImGui::Separator();

			float* v5[3] = { &camera->mCameraUp.x, &camera->mCameraUp.y, &camera->mCameraUp.z };
			ImGui::DragFloat3(u8"����", *v5);
			ImGui::Separator();

			ImGui::TreePop();
		}
		ImGui::Separator();
	}

	// �����_�����O���[�h��I��
	{
		// �R���{�{�b�N�X�̕���ݒ�
		ImGui::PushItemWidth(160);
		ImGui::Combo(u8"�����_�����O���[�h", &this->mCurrentShadingMode, this->mShadingMode, IM_ARRAYSIZE(this->mShadingMode));
		switch (this->mCurrentShadingMode)
		{
		case 0:
			getSceneManager()->mCurrentScene->mShader->mRenderMode = RT_DIFFUSE;
			break;
		case 1:
			getSceneManager()->mCurrentScene->mShader->mRenderMode = RT_NORMAL;
			break;
		case 2:
			getSceneManager()->mCurrentScene->mShader->mRenderMode = RT_TEXTURE;
			break;
		case 3:
			getSceneManager()->mCurrentScene->mShader->mRenderMode = RT_SHADING;
			break;
		}
		ImGui::Separator();
	}

	// �J���[���b�v�I��
	{
		// �R���{�{�b�N�X�̕���ݒ�
		ImGui::PushItemWidth(160);
		ImGui::Combo(u8"�J���[�����v���[�h", &this->mCurrentColorRamp, this->mColorRamp, IM_ARRAYSIZE(this->mColorRamp));
		switch (this->mCurrentColorRamp)
		{
		case 0:
			getSceneManager()->mCurrentScene->mShader->mColorRamp = CR_LINEAR;
			break;
		case 1:
			ImGui::TextUnformatted(u8"�J���[�Z�O�����g");
			ImGui::SliderFloat("Level1", &getSceneManager()->mCurrentScene->mShader->mColorRampSegment.x, 0.0f, 1.0f);
			ImGui::SliderFloat("Level2", &getSceneManager()->mCurrentScene->mShader->mColorRampSegment.y, 0.0f, 1.0f);
			ImGui::SliderFloat("Level3", &getSceneManager()->mCurrentScene->mShader->mColorRampSegment.z, 0.0f, 1.0f);
			getSceneManager()->mCurrentScene->mShader->mColorRamp = CR_CONSTANT;
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
void GUI::sceneGUI()
{
	// �V�[���̃}���`���x�����j���[
	ImGui::SetNextWindowSize(ImVec2(364,742));
	ImGui::Begin(u8"�V�[��", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove);
	{
		// GameObject�̍�胁�j���\
		//createNewGameObjectGUI();

		// �eGameObject
		unsigned int IDs = 0;
		for (auto it : getSceneManager()->mCurrentScene->mGameObjectMap)
		{
			ImGui::PushID(IDs);

			// Todo
			// ���C�g�Ə��Autf-8�ɕϊ����Ă��o���Ȃ�
			// UTF-8 to ANIS?

			// wstring -> string
			//string name1 = wStringToString(it.first);
			string name1 = wstringUnicodeToUTF8(it.first);
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
void GUI::createNewGameObjectGUI()
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
			// string -> wstring
			wstring newGameObjectName = stringToWString(this->mNewGameObjectName);
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
void GUI::addModelImGui()
{
	ImGui::Begin(u8"�C���|�[�g");
	ImGui::TextUnformatted(u8"GameObject���O");
	ImGui::InputText("name", this->mNewGameObjectName, IM_ARRAYSIZE(this->mNewGameObjectName));
	ImGui::TextUnformatted(u8"���f���t�@�C���p�X");
	//string path = wStringToString(this->mAddingFilePath);
	string path = wstringUnicodeToUTF8(this->mAddingFilePath);
	ImGui::Text(u8"%s", path.c_str());

	// string -> wstring
	wstring newGameObjectName = stringUTF8ToUnicode(this->mNewGameObjectName);

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
			meshRender->mModel = getResources()->getModel(name);								// ���\�[�X���烂�f�����擾
			getSceneManager()->mCurrentScene->mMeshRenders.push_back(meshRender);				// MeshRender���V�[���ɒǉ�
			gameObject->addComponent<MeshRender>(meshRender);
			getSceneManager()->mCurrentScene->addGameObject(newGameObjectName, gameObject);		// �V�[���ɒǉ�

			// mNewGameObjectName������
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
void GUI::dropFileErrorGUI()
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