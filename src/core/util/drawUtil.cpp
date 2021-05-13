#include "core/util/drawUtil.h"
#include "core/app.h"
#include <imgui/imgui.h>
#include <imgui/imgui_internal.h>

namespace Engine7414 {

	bool DrawUtil::drawVec3Control(const char* label, glm::vec3& values, float resetVal, float columnWidth) {
		ImFont* boldFont = App::getImGuiLayer()->boldFont;
		ImFont* italicFont = App::getImGuiLayer()->italicFont;
		bool valChanged = false;
		
		ImGui::Columns(2);
		ImGui::SetColumnWidth(0, columnWidth);
		ImGui::Text(label);
		ImGui::NextColumn();

		ImGui::PushMultiItemsWidths(3, ImGui::CalcItemWidth());
		ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, { 0.0f, 0.0f });
		ImGui::PushID(label);

		float lineHeight = GImGui->Font->FontSize + GImGui->Style.FramePadding.y * 2.0f;
		ImVec2 btnSize = { lineHeight + 3.0f, lineHeight };

		ImGui::PushStyleColor(ImGuiCol_Button, { 0.5f, 0.1f, 0.05f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, { 0.7f, 0.2f, 0.1f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, { 0.9f, 0.05f, 0.05f, 1.0f });
		ImGui::PushFont(boldFont);
		if (ImGui::Button("X", btnSize)) {
			values.x = resetVal;
			valChanged = true;
		}
		ImGui::PopFont();
		ImGui::PopStyleColor(3);
		ImGui::SameLine();
		if (ImGui::DragFloat("##X", &values.x, 0.1f, 0.0f, 0.0f, "%.2f")) valChanged = true;
		ImGui::PopItemWidth();
		ImGui::SameLine();

		ImGui::PushStyleColor(ImGuiCol_Button, { 0.1f, 0.5f, 0.05f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, { 0.2f, 0.7f, 0.1f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, { 0.05f, 0.9f, 0.05f, 1.0f });
		ImGui::PushFont(boldFont);
		if (ImGui::Button("Y", btnSize)) {
			values.y = resetVal;
			valChanged = true;
		}
		ImGui::PopFont();
		ImGui::PopStyleColor(3);
		ImGui::SameLine();
		if (ImGui::DragFloat("##Y", &values.y, 0.1f, 0.0f, 0.0f, "%.2f")) valChanged = true;
		ImGui::PopItemWidth();
		ImGui::SameLine();

		ImGui::PushStyleColor(ImGuiCol_Button, { 0.0f, 0.0f, 0.6f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, { 0.0f, 0.1f, 0.7f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, { 0.0f, 0.0f, 1.0f, 1.0f });
		ImGui::PushFont(boldFont);
		if (ImGui::Button("Z", btnSize)) {
			values.z = resetVal;
			valChanged = true;
		}
		ImGui::PopFont();
		ImGui::PopStyleColor(3);
		ImGui::SameLine();
		if (ImGui::DragFloat("##Z", &values.z, 0.1f, 0.0f, 0.0f, "%.2f")) valChanged = true;
		ImGui::PopItemWidth();

		ImGui::PopID();
		ImGui::PopStyleVar();
		ImGui::Columns(1);

		return valChanged;
	}

}