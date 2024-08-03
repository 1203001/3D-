#include"TestImGui.h"
#include"../Scene/SceneManager.h"
#include"ObjectController/ObjectController.h"

void TestImGui::Draw()
{
	// デバッグウィンドウ
	if (ImGui::Begin("Test Window"))
	{
		//お化け
		std::shared_ptr<ObjectController> _objectcontroller = m_wpObjectController.lock();
		if (!_objectcontroller)return;

		if (ImGui::BeginPopup("Object"))
		{
			if (ImGui::Button((const char*)u8"おばけ"))
			{
				_objectcontroller->CreateObject(ObjectController::Object::Ghost);
			}

			if (ImGui::Button((const char*)u8"掃除機"))
			{
				_objectcontroller->CreateObject(ObjectController::Object::Cleaner);
			}

			ImGui::EndPopup();
		}

		if (ImGui::Button("Object"))
			ImGui::OpenPopup("Object");

		ImGui::SameLine();

		if (ImGui::Button((const char*)u8"座標確定"))
		{
			_objectcontroller->Confirm();
		}

		ImGui::SameLine();
		if (ImGui::Button((const char*)u8"削除"))
		{
		
			_objectcontroller->DeleteObject();
			
		}


	
		ImGui::InputFloat("m_pos.x", &m_pos.x, 0.1f);
		ImGui::InputFloat("m_pos.y", &m_pos.y, 0.1f);
		ImGui::InputFloat("m_pos.z", &m_pos.z, 0.1f);


	}
	ImGui::End();

	ImGui::Render();
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

}
