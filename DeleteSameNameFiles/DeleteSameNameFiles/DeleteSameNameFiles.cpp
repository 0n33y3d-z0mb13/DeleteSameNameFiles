// DeleteSameNameFiles.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <direct.h>
#include <conio.h>

int load_file(std::string filename);
int seek_same();
void banner();
int delete_file();

std::vector<std::string> v_xml;
std::vector<std::string> v_jpg;
std::vector<std::string> v_result;

int main()
{
	banner();

	// 파일 불러오기
	if (load_file("jpg.txt") == 1) {
		std::cout << "jpg.txt파일을 찾을 수 없어 프로그램을 종료합니다.\n";
		return 0;
	}

	if (load_file("xml.txt") == 1) {
		std::cout << "xml.txt파일을 찾을 수 없어 프로그램을 종료합니다.\n";
		return 0;
	}
	
	std::cout << "파일 목록을 성공적으로 불러왔습니다.\n";
	// 중복 파일 찾기
	seek_same();
	// 중복 파일 삭제
	delete_file();

	std::cout << "\n";
	std::cout << "\n";
	std::cout << "아무 키나 누르면 프로그램이 종료 됩니다.\n";

	_getch();
	return 0;
	//프로그램 종료
}

void banner()
{
	std::cout << "<<프로그램 사용 방법>>\n";
	std::cout << "----------------------------------------------------------------------------------------\n";
	std::cout << "1. xml과 jpg 파일들의 이름 목록을 추출하여 각각 xml.txt과 jpg.txt로 저장합니다.\n";
	std::cout << "2. 파일 이름 목록 추출은 cm에서 Dir /b *.* > xml.txt.와 같은 명령어를 사용합니다.\n";
	std::cout << "3. 추출 된 파일 이름 목록 텍스트 파일은 실행 파일과 같은 위치에 있어야 합니다.\n";
	std::cout << "4. 삭제하려는 파일들의 폴더를 실행 파일과 같은 위치에 두고 폴더 이름을 xml로 수정합니다.\n";
	std::cout << "----------------------------------------------------------------------------------------\n";
}

int load_file(std::string filename)
{
	//파일 읽어오는 함수

	std::ifstream file(filename);
	if (! file.is_open()) {
		std::cout << "파일 열기 실패 : 에러 발생" << std::endl;
		return 1;
	}

	std::string s;
	while (getline(file, s)) {
		if(filename == "xml.txt") 
			v_xml.push_back(s.substr(0, s.length() - 4));
		else
			v_jpg.push_back(s.substr(0, s.length() - 4));
	}
		
	return 0;
}

int seek_same()
{
	//같은 파일 찾기 - 기본 대상: XML  비교 대상: JPG 
	std::cout << "파일 비교가 진행중 입니다. 시간이 좀 걸릴 수 있습니다.\n";

	std::vector<std::string>::iterator xml_itr;
	std::vector<std::string>::iterator jpg_itr;
	for (xml_itr = v_xml.begin(); xml_itr != v_xml.end(); ++xml_itr) {
		for (jpg_itr = v_jpg.begin(); jpg_itr != v_jpg.end(); ++jpg_itr) {
			if (*xml_itr == *jpg_itr)
				v_result.push_back((*xml_itr).append(".xml"));
		}
	}
	std::cout << "같은 이름의 파일을 "<<v_result.size() <<"개 찾았습니다.\n";
	return 0;
}

int delete_file()
{

	std::vector<std::string>::iterator iter;
	for (iter = v_result.begin(); iter != v_result.end(); iter++)
	{
		std::string xmlfolder_path;
		xmlfolder_path = "del \"xml\\";
		xmlfolder_path.append(*iter);
		xmlfolder_path.append("\"");
		std::cout << xmlfolder_path << std::endl;
		system(xmlfolder_path.c_str());
	}
	
	std::cout << "파일 삭제가 완료되었습니다.\n";
	return 0;
}
