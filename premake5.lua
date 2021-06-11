project "TheEngine"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"

	targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

	files {
		"src/**.h",
		"src/**.c",
		"src/**.cpp",

		"vendor/entt/include/**.hpp",
		
		"vendor/glad/include/**.h",
		
		"vendor/glm/glm/**.hpp",
		"vendor/glm/glm/**.inl",
	
		"vendor/imgui/*.h",
		"vendor/imgui/backends/*.h",

		"vendor/ImGuizmo/ImGuizmo.h",
		"vendor/ImGuizmo/ImGuizmo.cpp",
	
		"vendor/spdlog/include/**.h",

		"vendor/stb/include/**.h",

		"vendor/yaml-cpp/include/**.h",
		"vendor/yaml-cpp/src/**.cpp",
	}

	includedirs {
		"src",

		"%{extIncludeDir.glfw}",
		"%{extIncludeDir.entt}",
		"%{extIncludeDir.glad}",
		"%{extIncludeDir.glm}",
		"%{extIncludeDir.imgui_imguizmo}",
		"%{extIncludeDir.imguiNative}",
		"%{extIncludeDir.imguizmoNative}",
		"%{extIncludeDir.spdlog}",
		"%{extIncludeDir.stb}",
		"%{extIncludeDir.yaml_cpp}",
		"%{extIncludeDir.shaderc}",
	}

	removefiles {
		"src/tests/**.h",
		"src/tests/**.cpp",
		
		"src/main/**.cpp",
		"src/main/**.h",

		"src/backend/opengl/camera.*"
	}

	defines {
		"_CRT_SECURE_NO_WARNINGS",
		"GLFW_INCLUDE_NONE",
		"ENGINE_BACKEND_OPENGL"
	}

	filter "configurations:Debug"
		staticruntime "off"
		runtime "Debug"
		symbols "on"
		defines {
			"ENGINE_DEBUG"
		}

	filter "configurations:Release"
		staticruntime "on"
		runtime "Release"
		optimize "on"
		defines {}