#ifndef PATHS_H
#define PATHS_H

namespace Path
{
	namespace Settings
	{
		constexpr std::string_view CONFIG = "config/settings.ini";
	}

	namespace Shader
	{
		constexpr std::string_view VERTEX = "resources/shaders/shader.vert";
		constexpr std::string_view FRAGMENT = "resources/shaders/shader.frag";
		constexpr std::string_view VERTEX_PLAYER = "resources/shaders/player.vert";
		constexpr std::string_view FRAGMENT_PLAYER = "resources/shaders/player.frag";
	}

	namespace Texture
	{
		constexpr std::string_view FACE = "resources/assets/face.png";
		constexpr std::string_view CONTAINER = "resources/assets/container.jpg";
	}
}

#endif