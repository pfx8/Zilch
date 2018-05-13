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
	ImFont* font = io.Fonts->AddFontFromFileTTF("c:/Windows/Fonts/UDDigiKyokashoN-R.ttc", 16.0f, NULL, io.Fonts->GetGlyphRangesJapanese());

	// �e�`�F�b�N��������
	this->mIsWireframe = false;
	this->mIsAddingModel = false;
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
	// �f�b�o�O�E�C���h(���C���E�C���h)
	{
		ImGui::Begin(u8"�f�o�b�O�E�C���h"/*, nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove*/);

		// FPS�ƃ^�C��
		{
			ImGui::Text("Fps:%.1f, Time:%.3fs", ImGui::GetIO().Framerate, getGameTimes()->mCurrentTime);
			ImGui::Separator();
		}

		// �}�E�X�ʒu
		{
			ImGui::TextUnformatted(u8"�}�E�X�ʒu:");
			ImGui::SameLine();
			ImGui::Text("%f,%f", ImGui::GetIO().MousePos.x, ImGui::GetIO().MousePos.y);
			ImGui::Separator();
		}

		// �����_�����O���[�h
		{
			// ���C���t���[����h��Ԃ�
			ImGui::TextUnformatted(u8"���C���t���[�����[�h");
			ImGui::SameLine();
			if (ImGui::Button("WIREFRAME"))
			{
				getD3DDevice()->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
				this->mIsWireframe = true;
			}
			// �ʂ�h��Ԃ�
			ImGui::TextUnformatted(u8"�|���S�����[�h      "); ImGui::SameLine();
			if (ImGui::Button("SOLID"))
			{
				getD3DDevice()->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
				this->mIsWireframe = false;
			}
			ImGui::Separator();
		}

		// �X�N���[���V���b�g
		{
			ImGui::TextUnformatted(u8"�X�N���[���V���b�g  "); ImGui::SameLine();
			if (ImGui::Button("SCREENSHOT"))
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

			if(ImGui::TreeNode(u8"�V�X�e���J����"))
			{
				ImGui::TextUnformatted(u8"�J�����ʒu");
				float* v1[3] = { &camera->mCameraPos.x, &camera->mCameraPos.y, &camera->mCameraPos.z };
				ImGui::InputFloat3("Pos", *v1);
				ImGui::Separator();

				ImGui::TextUnformatted(u8"�J���������_(���f���ʒu�ɐݒ肵�Ă�)");
				float* v2[3] = { &camera->mTargetTrans->mPos.x, &camera->mTargetTrans->mPos.y, &camera->mTargetTrans->mPos.z };
				ImGui::InputFloat3("Look", *v2);
				ImGui::Separator();

				ImGui::TextUnformatted(u8"���������x�N�g��");
				float* v3[3] = { &camera->mCameraFront.x, &camera->mCameraFront.y, &camera->mCameraFront.z };
				ImGui::DragFloat3("lookV", *v3);
				ImGui::Separator();

				ImGui::TextUnformatted(u8"�E�����x�N�g��");
				float* v4[3] = { &camera->mCameraRight.x, &camera->mCameraRight.y, &camera->mCameraRight.z };
				ImGui::DragFloat3("rightV", *v4);
				ImGui::Separator();

				ImGui::TextUnformatted(u8"������x�N�g��");
				float* v5[3] = { &camera->mCameraUp.x, &camera->mCameraUp.y, &camera->mCameraUp.z };
				ImGui::DragFloat3("upV", *v5);
				ImGui::Separator();

				ImGui::TreePop();
			}
			ImGui::Separator();
		}

		// �����_�����O���[�h��I��
		{
			// ���̂̃����_�����O���[�h(�f�t�H���g�̓e�N�X�`��)
			static int currentShadingMode = 2;

			// �R���{�{�b�N�X�̕���ݒ�
			ImGui::PushItemWidth(160);
			ImGui::TextUnformatted(u8"�����_�����O���[�h");
			ImGui::Combo("RenderMode", &currentShadingMode, this->mShadingMode, IM_ARRAYSIZE(this->mShadingMode));
			switch (currentShadingMode)
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
			// ���̂̃����_�����O���[�h(�f�t�H���g�̓e�N�X�`��)
			static int currentColorRamp = 0;

			// �R���{�{�b�N�X�̕���ݒ�
			ImGui::PushItemWidth(160);
			ImGui::TextUnformatted(u8"�J���[�����v���[�h");
			ImGui::Combo("ColorRamp", &currentColorRamp, this->mColorRamp, IM_ARRAYSIZE(this->mColorRamp));
			switch (currentColorRamp)
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
}

//*****************************************************************************
//
// �V�[��GUI
//
//*****************************************************************************
void GUI::sceneGUI()
{
	// �V�[���̃}���`���x�����j���[
	ImGui::Begin(u8"Scene"/*, nullptr, ImGuiWindowFlags_NoResize*/);
	{
		// GameObject�̍�胁�j���\
		createNewGameObjectGUI();

		// �eGameObject
		unsigned int IDs = 0;
		for (auto it : getSceneManager()->mCurrentScene->mGameObjectMap)
		{
			ImGui::PushID(IDs);

			// Todo
			// ���C�g�Ə��Autf-8�ɕϊ����Ă��o���Ȃ�

			// wstring -> string
			string name1 = wstringUnicodeToUTF8(it.first);
			if (ImGui::TreeNode(u8"%s", name1.c_str(), ImGuiTreeNodeFlags_OpenOnArrow))
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
	string path = wStringToString(this->mAddingFilePath);
	ImGui::Text(u8"%s", path.c_str());

	// string -> wstring
	wstring newGameObjectName = stringToWString(this->mNewGameObjectName);

	// �G���[�^�C�v 0 -- default�A1 -- Error1�A2 -- Error2
	static int errorType = 0;

	// �`�F�b�NGameObject���O
	if (ImGui::Button(u8"�C���|�[�g"))
	{
		if (strlen(this->mNewGameObjectName) == 0 )
		{
			errorType = 1;
		}

		// �`�F�b�NGameObject���O
		if (!isGameObjectNameRight(newGameObjectName))
		{
			errorType = 2;
		}

		if (errorType != 0)
		{
			// �G���[�E�C���h���J��
			ImGui::OpenPopup("Error");
		}
		else
		{
			// �V����GameObject�����
			GameObject* gameObject = new GameObject();
			getSceneManager()->mCurrentScene->addGameObject(newGameObjectName, gameObject);

			// ���f����ǂݍ���
			//getResources()->createModel(this->mAddingFilePath);

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
		this->mIsModelFile = false;
	}
	ImGui::End();
}