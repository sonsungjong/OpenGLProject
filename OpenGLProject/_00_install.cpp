/*
�ص��� ��ġ �� �׷��� �ֽŹ��� üũ &������Ʈ
����� ��Ʃ��� 2019 ��ġ
CMake ��ġ - CMake-3.19.0-win64-x64.msi ��ġ
glfw �ٿ�ε� - glfw.org/download.html ���� 3.3.2 Source package �ٿ�ε�
Glad �ٿ�ε� - glad.dav1.d.de���� gl���� Version 3.3, Profile���� : Core -> GL_AMD_framebuffer_multisample_advanced Ŭ�� -> glad.zip�� �ٿ�ε�

������Ʈ ���� �� �ҽ����� �ȿ� Libraries���� ����
�ȿ� lib������ include���� ����

glfw-3.3.2 �������� �� CMake�� ����
CMake - Browse Source - glfw-3.3.2���� ���� - Browse Build - glfw-3.3.2���� �ȿ� build���� ���� �� ����
Configure - Visual Studio 16 2019 - Finish - Congifure - Generate
glfw-3.3.2 - build - GLFW.sln�� �����Ʃ��� ���� - �ַ������ ��Ŭ�� �� Build solution (F7)
glfw-3.3.2/build/src/Debug/glfw3.lib ���� ���� - ����� �ξ��� Libraries/lib ���� �ȿ� �ٿ��ֱ�
glfw-3.3.2/include �ȿ� GLFW������ ���� - ����� �ξ��� Libraries/include �����ȿ� �ٿ��ֱ�

glad.zip�� ��������
glad/include �ȿ� glad������ KHR������ ���� - Libraries/include �ȿ� �ٿ��ֱ�
glad/src �ȿ� glad.c ������ ���� - �ڽ��� �ַ������ ���� �ٿ��ֱ�

�����Ʃ��� x64�� ����
Project - properties - Platform: AllPlatforms�� ����
VC++ Directories - Include Directories(���� ���丮) : Libraries/include ������ �߰�
VC++ Directories - Library Directories(���̺귯�� ���丮) : Libraries/lib ������ �߰�
Linker - Input - Additional Dependencies - glfw3.lib �� opengl32.lib �Է�
�ҽ����� �ȿ� �ξ��� glad.c�� ������Ʈ �ҽ����Ͽ� �ֱ�

cpp ������ �ϳ� �����
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

int main(){
	return 0;
}
�� �������� �� ���尡 �Ǹ� ����

learnopengl.com/Getting-started ���� �ڷ�����

*/