#ifndef PATHS_H
#define PATHS_H

namespace Path
{
	namespace Settings
	{
		constexpr std::string_view CONFIG = "C:/Users/Cristi/Desktop/AgonyAndPain/config/settings.conf";
	}

	namespace Shader
	{
		constexpr std::string_view VERTEX = "C:/Users/Cristi/Desktop/AgonyAndPain/resources/shaders/shader.vert";
		constexpr std::string_view FRAGMENT = "C:/Users/Cristi/Desktop/AgonyAndPain/resources/shaders/shader.frag";
		constexpr std::string_view VERTEX_PLAYER = "C:/Users/Cristi/Desktop/AgonyAndPain/resources/shaders/player.vert";
		constexpr std::string_view FRAGMENT_PLAYER = "C:/Users/Cristi/Desktop/AgonyAndPain/resources/shaders/player.frag";
	}

	namespace Texture
	{
		constexpr std::string_view FACE = "C:/Users/Cristi/Desktop/AgonyAndPain/resources/assets/face.png";
		constexpr std::string_view CONTAINER = "C:/Users/Cristi/Desktop/AgonyAndPain/resources/assets/container.jpg";
	}
}

#endif