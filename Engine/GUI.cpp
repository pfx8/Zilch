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
	// ImGui��������
	ImGui::CreateContext();
	// I/O��������
	ImGuiIO& io{ImGui::GetIO()};
	(void)io;
	ImGui_ImplDX9_Init(hWnd, D3DDevice);
	// �X�^�C���J���[�����߂�
	ImGui::StyleColorsDark();
	// �f�t�H���g�t�H���g
	ImFont* font = io.Fonts->AddFontFromFileTTF("c:/Windows/Fonts/UDDigiKyokashoN-R.ttc", 16.0f, NULL, io.Fonts->GetGlyphRangesJapanese());

	// �����_�����O���[�h�ݒ�
	this->mIsWireframe = false;

	// 
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
			ImGui::Text(u8"�}�E�X�ʒu:"); ImGui::SameLine();
			ImGui::Text("%f,%f", ImGui::GetIO().MousePos.x, ImGui::GetIO().MousePos.y);
			ImGui::Separator();
		}

		// �����_�����O���[�h
		{
			// ���C���t���[����h��Ԃ�
			ImGui::Text(u8"���C���t���[�����[�h"); ImGui::SameLine();
			if (ImGui::Button("WIREFRAME"))
			{
				getD3DDevice()->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
				this->mIsWireframe = true;
			}
			// �ʂ�h��Ԃ�
			ImGui::Text(u8"�|���S�����[�h      "); ImGui::SameLine();
			if (ImGui::Button("SOLID"))
			{
				getD3DDevice()->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
				this->mIsWireframe = false;
			}
			ImGui::Separator();
		}

		// �X�N���[���V���b�g
		{
			ImGui::Text(u8"�X�N���[���V���b�g  "); ImGui::SameLine();
			if (ImGui::Button("SCREENSHOT"))
			{
				// �o�b�t�@��ʂ��擾
				LPDIRECT3DSURFACE9 backBuffer;
				getD3DDevice()->GetRenderTarget(0, &backBuffer);

				// �o�b�t�@�T�[�t�F�C�X��ۑ�
				D3DXSaveSurfaceToFile("screenShot.bmp", D3DXIFF_BMP, backBuffer, NULL, NULL);

				// �o�b�t�@�������[�X
				backBuffer->Release();
			}
			ImGui::Separator();
		}

		// �����_�����O���[�h��I��
		{
			// ���̂̃����_�����O���[�h(�f�t�H���g�̓e�N�X�`��)
			static int currentShadingMode {2};

			// �R���{�{�b�N�X�̕���ݒ�
			ImGui::PushItemWidth(160);
			ImGui::Text(u8"�����_�����O���[�h");
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
			static int currentColorRamp {0};

			// �R���{�{�b�N�X�̕���ݒ�
			ImGui::PushItemWidth(160);
			ImGui::Text(u8"�J���[�����v���[�h");
			ImGui::Combo("ColorRamp", &currentColorRamp, this->mColorRamp, IM_ARRAYSIZE(this->mColorRamp));
			switch (currentColorRamp)
			{
			case 0:
				getSceneManager()->mCurrentScene->mShader->mColorRamp = CR_LINEAR;
				break;
			case 1:
				ImGui::Text(u8"�J���[�Z�O�����g");
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
		unsigned int IDs {0};
		for (auto it : getSceneManager()->mCurrentScene->mGameObjectMap)
		{
			ImGui::PushID(IDs);
			if (ImGui::TreeNode(u8"%s", it.first.c_str(), ImGuiTreeNodeFlags_OpenOnArrow))
			{
				// GameObject�̊e�R���|�[�l���g���o��
				unsigned int ID2s {0};
				for (auto it2 : it.second->mComponentsMap)
				{
					ImGui::PushID(ID2s);
					string name{it2.first.name()};
					name = name.substr(name.find_last_of(" ") + 1, name.size());		// exp: class xxx -> xxx
					if (ImGui::TreeNode(u8"%s", name.c_str()))
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

		ImGui::Text(u8"GameObject���O");
		ImGui::InputText(" ", this->mNewGameObjectName, IM_ARRAYSIZE(this->mNewGameObjectName));

		if (ImGui::Button(u8"���"))
		{
			// �V����GameObject�����
			GameObject* gameObject {new GameObject()};
			getSceneManager()->mCurrentScene->addGameObject(this->mNewGameObjectName, gameObject);

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

	ImGui::End();


	//this->mIsAddingModel = false;
}