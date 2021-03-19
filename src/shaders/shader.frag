#version 450
#extension GL_ARB_separate_shader_objects : enable

layout(binding = 1) uniform sampler2D texSampler;

layout(location = 0) in vec3 fragColor;
layout(location = 1) in vec2 fragTexCoord;

layout(location = 0) out vec4 outColor;

void main(){
    vec4 color = texture(texSampler, fragTexCoord);
    //outColor = vec4(fragTexCoord.x, fragTexCoord.y, (fragTexCoord.x + fragTexCoord.y) / 2.0f, 1.0f);
    if(color.w < 1){
        discard;
    }else{
        outColor = color;
    }
}