/*
앤디비아 설치 및 그래픽 최신버전 체크 &업데이트
비쥬얼 스튜디오 2019 설치
CMake 설치 - CMake-3.19.0-win64-x64.msi 설치
glfw 다운로드 - glfw.org/download.html 에서 3.3.2 Source package 다운로드
Glad 다운로드 - glad.dav1.d.de에서 gl버전 Version 3.3, Profile종류 : Core -> GL_AMD_framebuffer_multisample_advanced 클릭 -> glad.zip을 다운로드

프로젝트 생성 후 소스폴더 안에 Libraries폴더 생성
안에 lib폴더와 include폴더 생성

glfw-3.3.2 압축해제 후 CMake로 오픈
CMake - Browse Source - glfw-3.3.2폴더 적용 - Browse Build - glfw-3.3.2폴더 안에 build폴더 생성 후 적용
Configure - Visual Studio 16 2019 - Finish - Congifure - Generate
glfw-3.3.2 - build - GLFW.sln을 비쥬얼스튜디오 실행 - 솔루션파일 우클릭 후 Build solution (F7)
glfw-3.3.2/build/src/Debug/glfw3.lib 파일 복사 - 만들어 두었던 Libraries/lib 폴더 안에 붙여넣기
glfw-3.3.2/include 안에 GLFW폴더를 복사 - 만들어 두었던 Libraries/include 폴더안에 붙여넣기

glad.zip을 압축해제
glad/include 안에 glad폴더와 KHR폴더를 복사 - Libraries/include 안에 붙여넣기
glad/src 안에 glad.c 파일을 복사 - 자신의 솔루션파일 옆에 붙여넣기

비쥬얼스튜디오 x64로 설정
Project - properties - Platform: AllPlatforms로 셋팅
VC++ Directories - Include Directories(포함 디렉토리) : Libraries/include 폴더를 추가
VC++ Directories - Library Directories(라이브러리 디렉토리) : Libraries/lib 폴더를 추가
Linker - Input - Additional Dependencies - glfw3.lib 과 opengl32.lib 입력
소스폴더 안에 두었던 glad.c를 프로젝트 소스파일에 넣기

cpp 파일을 하나 만들고
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

int main(){
	return 0;
}
로 실행했을 때 빌드가 되면 성공

learnopengl.com/Getting-started 에서 자료제공

*/