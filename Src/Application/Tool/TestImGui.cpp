#include"TestImGui.h"
#include"../Scene/SceneManager.h"
#include"ObjectController/ObjectController.h"

void TestImGui::Draw()
{
	ImGui::SetNextWindowPos(ImVec2(850, 20));
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
			if (ImGui::Button((const char*)u8"ドア"))
			{
				_objectcontroller->CreateObject(ObjectController::Object::Door);
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


	
		ImGui::InputFloat("m_pos.x", &m_pos.x, 1.0f);
		ImGui::InputFloat("m_pos.y", &m_pos.y, 1.0f);
		ImGui::InputFloat("m_pos.z", &m_pos.z, 1.0f);


		ImGui::InputFloat("RotateX", &m_angle.x, 1.0f);
		ImGui::InputFloat("RotateY", &m_angle.y, 1.0f);
		ImGui::InputFloat("RotateZ", &m_angle.z, 1.0f);

		ImGui::InputFloat("ScaleX", &m_scale.x, 0.1f);
		ImGui::InputFloat("ScaleY", &m_scale.y, 0.1f);
		ImGui::InputFloat("ScaleZ", &m_scale.z, 0.1f);

	}
	ImGui::End();

	ImGui::Render();
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

}
