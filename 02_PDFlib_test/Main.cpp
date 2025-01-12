#include <iostream>
#include <string>
#include <Windows.h>
#include "pdflib.h"
using namespace std;

std::string UnicodeToUtf8(const std::wstring& strUnicode)
{
	int len = WideCharToMultiByte(CP_UTF8, 0, strUnicode.c_str(), -1, NULL, 0, NULL, NULL);
	if (len == 0)
	{
		return "";
	}

	char* pRes = new char[len];
	if (pRes == NULL)
	{
		return "";
	}

	WideCharToMultiByte(CP_UTF8, 0, strUnicode.c_str(), -1, pRes, len, NULL, NULL);
	pRes[len - 1] = '\0';
	std::string result = pRes;
	delete[] pRes;

	return result;
}
std::wstring StringToWString(const std::string& str)
{
	int len = MultiByteToWideChar(CP_ACP, 0, str.c_str(), -1, NULL, 0);
	if (len == 0)
	{
		return L"";
	}

	wchar_t* pRes = new wchar_t[len];
	if (pRes == NULL)
	{
		return L"";
	}

	MultiByteToWideChar(CP_ACP, 0, str.c_str(), -1, pRes, len);
	pRes[len - 1] = L'\0';
	std::wstring result = pRes;
	delete[] pRes;

	return result;
}
string toUtf8(const char* str) {
	string s = UnicodeToUtf8(StringToWString(str));
	return s;
}
int main() {
	
	PDF* pdf = PDF_new();
		if (PDF_begin_document(pdf, "this.pdf", 0, "") == -1) {
		cout << "创建pdf文件失败，程序即将退出" << endl;
		return 1;
	}
		else {
		std::cout << "csdn pdf begin success" << std::endl;
	}
			PDF_set_option(pdf, "charref=true");              //启用字符引用模式。字符引用模式允许在文本中使用字符的 Unicode 码点作为引用，这对于处理非 ASCII 字符（如中文、日文、韩文等）非常有用。
	PDF_set_option(pdf, "textformat=utf8");        //指定输入文本的编码格式为 UTF-8。UTF-8 是一种广泛使用的字符编码，能够表示几乎所有书写系统的字符，因此在处理多语言文本时非常有用。

	PDF_set_info(pdf, "Creator", "PDF Creator");   //创建者
	PDF_set_info(pdf, "Title", "Convert to PDF");   //标题

	PDF_begin_page_ext(pdf, a4_width, a4_height, "");// 开始A4页面
	int nHeight = a4_height;

	int font_song = PDF_load_font(pdf, "C:\\Windows\\Fonts\\simsun:1", 0, "unicode", "");
	if (font_song == -1) {

		std::cout << "load font error" << endl;

	}
	else {
		std::cout << "load font success" << endl;
	}
	PDF_setfont(pdf, font_song, 34);// 设置字体为34号宋体
	nHeight -= 50;
	PDF_set_text_pos(pdf, 50, nHeight);
	PDF_setcolor(pdf, "fill", "rgb", 0, 0, 1, 0);

	static const char* DFTitle[] = { "你好世界。", "hello world." };
	for (int i = 0; i < 2; i++)
	{
		PDF_set_text_pos(pdf, 100 * i, nHeight - 40 * i);//字体坐标
				char a[100];

				strcpy_s(a, toUtf8(DFTitle[i]).c_str());
				 			strcpy_s(a, DFTitle[i]);
				 
				 			PDF_show(pdf, toUtf8(DFTitle[i]).c_str());
	}

    	   PDF_end_page_ext(pdf, "");
		   PDF_end_document(pdf, "");
		   PDF_delete(pdf);
		   std::cout << "pdf create success" << endl;

	cout << "hello world" << endl;
	return 0;
	
}
