#pragma once

auto base_vert = SHADER_MACRO(450 core,
							  precision highp float;
layout(location = 0) in vec3 i_pos;
layout(location = 2) in vec2 i_uv;
out vec2 vs_uv;
uniform mat4 u_mvpMat;

void main()
{
	vs_uv = i_uv;
	gl_Position = u_mvpMat * vec4(i_pos, 1.0);
}

);

auto base_frag = SHADER_MACRO(450 core,
							  precision highp float;
layout(binding = 0) uniform sampler2D u_tex;
layout(location = 0) out vec4 fs_color;

uniform vec2 u_tiling;

in vec2 vs_uv;

void main()
{
	fs_color = texture(u_tex, vs_uv * u_tiling);
}

);